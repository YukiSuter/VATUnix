#include "fts_page.h"
#include <iostream>
#include <glibmm/miscutils.h>

#include "AppGlobals.h"
#include "cli_utils.h"
#include "file_utils.h"
#include "wine_utils.h"

FTSPage::FTSPage() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_margin_start(50);
    set_margin_end(50);
    set_margin_top(20);
    set_margin_bottom(20);

    env_created_dispatcher.connect(sigc::mem_fun(*this, &FTSPage::on_env_created));

    wizard_stack.set_transition_type(Gtk::StackTransitionType::SLIDE_LEFT_RIGHT);
    append(wizard_stack);

    wizard_stack.add(start_page, "Start", "Start");
    wizard_stack.add(dep_page, "Dependencies", "Dependencies");
    wizard_stack.add(wine_page, "Wine", "Wine");
    wizard_stack.add(soft_page, "Soft", "Soft");
    wizard_stack.add(soft_choice_page, "SoftChoice", "SoftChoice");

    wizard_stack.set_visible_child("Start");

    AppGlobals::prefix_dir = Glib::build_filename(FileUtils::get_vatunix_data_path(), "VATUnixWine");

    start_page.get_nav_buttons().change_signal().connect([this](const std::string& name) {
        on_page_change(name);
    });

    dep_page.get_nav_buttons().change_signal().connect([this](const std::string& name) {
        on_page_change(name);
    });

    soft_page.get_nav_buttons().change_signal().connect([this](const std::string& name) {
        on_page_change(name);
    });

    dep_page.get_refresh_button().signal_clicked().connect([this] {
        dep_page.get_refresh_button().set_label("Refreshing... ⟳");
        check_packages();
        create_refresh_buttons();
        dep_page.get_refresh_button().set_label("Refresh");
    });

    dep_page.get_back_button().signal_clicked().connect([this] {
        on_page_change("Start", {});
    });

    wine_page.get_back_button().signal_clicked().connect([this] {
        on_page_change("Dependencies", {});
    });

    wine_page.get_install_button().signal_clicked().connect([this] {
        if (!buttons_blocked) {
            try {
                buttons_blocked = true;
                create_env_async();
            } catch (const std::exception& e) {
                std::cout << "Error occurred creating wine environment: " << e.what() << std::endl;
                wine_page.get_install_button().set_label("An error occurred. Please make a GitHub issue.");
                buttons_blocked = false;
            }
        }
    });

    soft_choice_page.get_install_button().signal_clicked().connect([this] {
        soft_choice_page.get_install_button().set_label("Installing... ⟳");
        soft_choice_page.get_install_button().set_label("Installed. Next >");
    });

    soft_choice_page.get_back_button().signal_clicked().connect([this] {
        on_page_change("Soft", {});
    });

    check_packages();
    create_refresh_buttons();
}

void FTSPage::on_page_change(const std::string& page_name, bool force) {
    if (!buttons_blocked || force) {
        wizard_stack.set_visible_child(page_name);
    }
}

void FTSPage::check_packages() {
    Gtk::Box& box = dep_page.get_missing_dep_box();
    for (auto* child : box.get_children()) {
        box.remove(*child);
    }

    missing_packages.clear();

    for (const auto& pkg : required_packages) {
        if (CLIUtils::execute_command(pkg)) {
            Gtk::Box row;
            Gtk::Label status;
            row.set_orientation(Gtk::Orientation::HORIZONTAL);
            status.set_markup("<span foreground='red'>" + pkg + "</span>");
            row.append(status);
            missing_packages.push_back(pkg);
            box.append(row);
        }
    }

    Gtk::Label info;
    info.set_wrap();
    info.set_xalign(0);
    info.set_margin_top(10);
    info.set_margin_bottom(10);
    box.prepend(info);

    if (!missing_packages.empty()) {
        info.set_markup("<span foreground='red'>The following packages are missing. Please install them:</span>");
    } else {
        info.set_markup("<span foreground='green'>All packages are installed, click next to continue.</span>");
    }
}

void FTSPage::create_refresh_buttons() {
    Gtk::Box& parent = dep_page;
    Gtk::Widget* last = parent.get_last_child();
    if (last)
        parent.remove(*last);

    if (missing_packages.empty()) {
        parent.append(dep_page.get_nav_buttons());
    } else {
        parent.append(dep_page.get_custom_button_box());
    }
}

void FTSPage::create_env_async() {
    dot_count = 0;
    label_anim_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &FTSPage::update_install_label), 400);
    background_thread = std::thread([this]() {
        wine_utils::create_env();
        env_created_dispatcher.emit();
    });
}

bool FTSPage::update_install_label() {
    const std::vector<std::string> states = { "Installing .", "Installing ..", "Installing ..." };
    wine_page.get_install_button().set_label(states[dot_count % states.size()]);
    dot_count++;
    return true;
}

void FTSPage::on_env_created() {
    if (label_anim_conn.connected()) label_anim_conn.disconnect();
    wine_page.get_install_button().set_label("Installed");
    if (background_thread.joinable()) background_thread.join();
    buttons_blocked = false;
    on_page_change("Soft", {});
}