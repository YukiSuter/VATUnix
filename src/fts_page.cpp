#include "fts_page.h"

#include <future>
#include <chrono>
#include <thread>
#include <iostream>

#include "cli_utils.h"
#include "file_utils.h"
#include "wine_utils.h"
#include "softwares/euroscope.h"

FTSPage::FTSPage(): start_wiz_buttons(0, "Dependencies"), dep_wiz_buttons(1, "Wine", "Next >", "Start"), wine_wiz_buttons(1, "Soft", "Next >", "Dependencies"), soft_wiz_buttons(1, "SoftChoice", "Next >", "Wine") {
    required_packages.insert(required_packages.end(), {"unzip", "wine", "winetricks", "wineserver", "grep", "wget"});  // Appends 3, 4, 5
    check_packages();

    env_created_dispatcher.connect(sigc::mem_fun(*this, &FTSPage::on_env_created));
    buttons_blocked = false;

    set_margin_start(50);
    set_margin_end(50);
    set_margin_top(20);
    set_margin_bottom(20);
    set_orientation(Gtk::Orientation::VERTICAL);

    wizard_stack.set_transition_type(Gtk::StackTransitionType::SLIDE_LEFT_RIGHT);

    append(wizard_stack);


    // Start Page
    Gtk::Box start_box;
    Gtk::Label start_title;
    Gtk::Label start_text;
    Gtk::Separator start_separator;  // 👈 Create the separator

    start_box.set_orientation(Gtk::Orientation::VERTICAL);
    start_box.set_vexpand();   // Make box expand vertically
    start_box.set_valign(Gtk::Align::FILL);

    start_title.set_text("Welcome");
    start_title.add_css_class("wizard-title");
    start_title.set_xalign(0);
    start_box.append(start_title);

    start_text.set_text("VATUnix is software used to manage the Euroscope and associated software on systems without official support.");
    start_text.set_wrap();
    start_text.set_xalign(0);
    start_text.set_vexpand();
    start_text.set_valign(Gtk::Align::FILL);
    start_box.append(start_text);

    start_separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    start_separator.set_margin_top(10);
    start_separator.set_margin_bottom(10);
    start_box.append(start_separator);  // 👈 Add it to the box


    start_box.append(start_wiz_buttons);

    // Dependencies Page
    dep_box.set_orientation(Gtk::Orientation::VERTICAL);
    dep_box.set_vexpand();   // Make box expand vertically
    dep_box.set_valign(Gtk::Align::FILL);

    dep_title.set_text("Dependencies");
    dep_title.add_css_class("wizard-title");
    dep_title.set_xalign(0);
    dep_box.append(dep_title);

    dep_cwb.set_orientation(Gtk::Orientation::HORIZONTAL);
    dep_cwb.set_halign(Gtk::Align::END);
    dep_cwb.append(dep_btn_back);
    dep_cwb.append(dep_btn_fwd);

    dep_text.set_text("VATUnix requires some dependencies to run correctly. Depending on the installation method not all may be installed. ");
    dep_text.set_wrap();
    dep_text.set_xalign(0);
    dep_text.set_vexpand();
    dep_text.set_valign(Gtk::Align::FILL);
    dep_box.append(dep_text);

    // Dep Table
    missing_dep_box.set_orientation(Gtk::Orientation::VERTICAL);
    dep_box.append(missing_dep_box);

    dep_separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    dep_separator.set_margin_top(10);
    dep_separator.set_margin_bottom(10);
    dep_box.append(dep_separator);  // 👈 Add it to the box

    dep_btn_fwd.set_label("Refresh");
    dep_btn_back.set_label("< Back");
    dep_btn_fwd.signal_clicked().connect([this] {
        dep_btn_fwd.set_label("Refreshing... ⟳");
        check_packages();
        create_refresh_buttons();
        dep_btn_fwd.set_label("Refresh");
    });
    dep_btn_back.signal_clicked().connect([this] {
        on_page_change("Start", {});
    });

    create_refresh_buttons();

    // Wine Page
    Gtk::Box wine_box;
    Gtk::Label wine_title;
    Gtk::Label wine_text;
    Gtk::Separator wine_separator;  // 👈 Create the separator
    Gtk::Box wine_button_box;

    wine_button_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    wine_button_box.set_halign(Gtk::Align::END);

    wine_back_button.set_label("< Back");
    wine_install_button.set_label("Install");

    wine_button_box.append(wine_back_button);
    wine_button_box.append(wine_install_button);

    wine_back_button.signal_clicked().connect([this] {
        on_page_change("Dependencies", {});
    });

    wine_install_button.signal_clicked().connect([this] {
        if (!buttons_blocked) {
            try {
                buttons_blocked = true;
                create_env_async();
            } catch (const std::exception &e) {
                std::cout<<"Error occurred creating wine environment: "<<e.what()<<std::endl;
                wine_install_button.set_label("An error occurred. Please make a github issue.");
                buttons_blocked = false;
            }
        }
    });

    wine_box.set_orientation(Gtk::Orientation::VERTICAL);
    wine_box.set_vexpand();   // Make box expand vertically
    wine_box.set_valign(Gtk::Align::FILL);

    wine_title.set_text("Wine Configuration");
    wine_title.add_css_class("wizard-title");
    wine_title.set_xalign(0);
    wine_box.append(wine_title);

    wine_text.set_text("Please now use the options below to set up the wine environment. It is NOT recommended to change the wine prefix directory. Click next to use default values.\n\nNote: feature not yet implemented. Default prefix name and location will be used.");
    wine_text.set_wrap();
    wine_text.set_xalign(0);
    wine_text.set_vexpand();
    wine_text.set_valign(Gtk::Align::FILL);

    wine_separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    wine_separator.set_margin_top(10);
    wine_separator.set_margin_bottom(10);

    wine_box.append(wine_text);
    wine_box.append(wine_separator);  // 👈 Add it to the box
    wine_box.append(wine_button_box);



    // Software Page
    Gtk::Box soft_box;
    Gtk::Label soft_title;
    Gtk::Label soft_text;
    Gtk::Separator soft_separator; // 👈 Create the separator

    soft_box.set_orientation(Gtk::Orientation::VERTICAL);
    soft_box.set_vexpand(); // Make box expand vertically
    soft_box.set_valign(Gtk::Align::FILL);

    soft_title.set_text("Software");
    soft_title.add_css_class("wizard-title");
    soft_title.set_xalign(0);

    soft_text.set_text(
        "Please use this section to decide what software is to be installed. Any region specific plug ins should be installed in VATUnix once you have tested the core functionalities of these softwares. \n\nIf you can't find the software you want, check the regions tab after install, or use the custom install feature.");
    soft_text.set_wrap();
    soft_text.set_xalign(0);
    soft_text.set_vexpand();
    soft_text.set_valign(Gtk::Align::FILL);

    soft_separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    soft_separator.set_margin_top(10);
    soft_separator.set_margin_bottom(10);

    soft_box.append(soft_title);
    soft_box.append(soft_text);
    soft_box.append(soft_separator); // 👈 Add it to the box
    soft_box.append(soft_wiz_buttons);

    // Software Choices Page
    Gtk::Box schoice_box;
    Gtk::Label schoice_title;
    Gtk::Separator schoice_separator; // 👈 Create the separator

    schoice_cwb.set_orientation(Gtk::Orientation::HORIZONTAL);
    schoice_cwb.set_halign(Gtk::Align::END);
    schoice_cwb.append(schoice_btn_back);
    schoice_cwb.append(schoice_btn_fwd);

    schoice_box.set_orientation(Gtk::Orientation::VERTICAL);
    schoice_box.set_vexpand(); // Make box expand vertically
    schoice_box.set_valign(Gtk::Align::FILL);

    schoice_title.set_text("Choose from below");
    schoice_title.add_css_class("wizard-title");
    schoice_title.set_xalign(0);
    schoice_title.set_margin_top(10);
    schoice_title.set_margin_bottom(10);

    schoice_separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    schoice_separator.set_margin_top(10);
    schoice_separator.set_margin_bottom(10);

    Euroscope es_choice;

    schoice_box.append(schoice_title);
    schoice_box.append(es_choice);
    schoice_box.append(schoice_separator); // 👈 Add it to the box
    schoice_box.append(schoice_cwb);

    schoice_btn_fwd.set_label("Install");
    schoice_btn_back.set_label("< Back");
    schoice_btn_fwd.signal_clicked().connect([this] { // TODO INSTALL LOGIC
        schoice_btn_fwd.set_label("Installing... ⟳");

        schoice_btn_fwd.set_label("Installed. Next >");
    });
    schoice_btn_back.signal_clicked().connect([this] {
        on_page_change("Soft");
    });

    std::string prefix_name = "VATUnixWine";
    prefix_dir = Glib::build_filename(FileUtils::get_vatunix_data_path(), prefix_name);

    start_wiz_buttons.change_signal().connect([this](const std::string& page_name) {
        on_page_change(page_name);
    });

    dep_wiz_buttons.change_signal().connect([this](const std::string& page_name) {
        on_page_change(page_name);
    });

    soft_wiz_buttons.change_signal().connect([this](const std::string& page_name) {
        on_page_change(page_name);
    });

    wizard_stack.add(start_box, "Start", "Start");
    wizard_stack.add(dep_box, "Dependencies", "Dependencies");
    wizard_stack.add(wine_box, "Wine", "Wine");
    wizard_stack.add(soft_box, "Soft", "Soft");
    wizard_stack.add(schoice_box, "SoftChoice", "SoftChoice");
    wizard_stack.set_visible_child("Start");
}

void FTSPage::on_page_change(const std::string& page_name, bool force) {
    std::cout<<"Buttons_blocked: "<<buttons_blocked<<std::endl;
    if (!buttons_blocked || force) {
        std::cout << "Received page change to: " << page_name << std::endl;
        wizard_stack.set_visible_child(page_name);
    } else {
        std::cout<<"Page change blocked"<<std::endl;
    }
}

void FTSPage::check_packages() {

    // TODO: Mechanism to check for non command based libraries (e.g. libcurl or lib32-gnutls)

    for (auto* child : missing_dep_box.get_children()) {
        missing_dep_box.remove(*child);  // Dereference pointer to get the reference
        std::cout << "Removing child"<<std::endl;
    }

    missing_packages.clear();

    for (int i=0; i < required_packages.size(); i++) {
        if (CLIUtils::execute_command(required_packages[i])) {
            std::cout << "unzip package is missing!";
            Gtk::Box dep_row;
            Gtk::Label dep_status;

            dep_row.set_orientation(Gtk::Orientation::HORIZONTAL);
            dep_status.set_markup("<span foreground='red'>"+required_packages[i]+"</span>");
            dep_row.append(dep_status);

            missing_packages.emplace_back(required_packages[i]);

            missing_dep_box.append(dep_row);
        }
    }

    Gtk::Label missing_dep_title;
    missing_dep_title.set_wrap();
    missing_dep_title.set_xalign(0);
    missing_dep_title.set_margin_top(10);
    missing_dep_title.set_margin_bottom(10);
    missing_dep_box.prepend(missing_dep_title);

    if (missing_packages.size() > 0) {
        missing_dep_title.set_markup("<span foreground='red'>The following packages are missing. Please install them using your system's package manager:</span>");

    } else {
        missing_dep_title.set_markup("<span foreground='green'>All packages are installed, click next to continue.</span>");
    }
}

void FTSPage::create_refresh_buttons() {
    if (dynamic_cast<Gtk::Box*>(dep_box.get_last_child())) {
        dep_box.remove(*dep_box.get_last_child());
    }

    if (missing_packages.empty()) {
        dep_box.append(dep_wiz_buttons);
    } else {
        std::cout<<"Creating custom buttons."<<std::endl;
        // Custom Wizard Button Behaviour (refresh)
        dep_box.append(dep_cwb);
    }
}

void FTSPage::create_env_async() {
    dot_count = 0;

    // Start the label animation on UI thread
    label_anim_conn = Glib::signal_timeout().connect(
        sigc::mem_fun(*this, &FTSPage::update_install_label),
        400  // milliseconds
    );

    // Launch background thread
    background_thread = std::thread([this]() {
        wine_utils::create_env(prefix_dir);
        env_created_dispatcher.emit();  // notify when done
    });
}

bool FTSPage::update_install_label() {
    const std::vector<std::string> states = { "Installing .", "Installing ..", "Installing ..." };
    wine_install_button.set_label(states[dot_count % states.size()]);
    dot_count++;

    return true; // keep the timer running
}

void FTSPage::on_env_created() {
    if (label_anim_conn.connected())
        label_anim_conn.disconnect();  // stop the animation

    wine_install_button.set_label("Installed");

    if (background_thread.joinable())
        background_thread.join();  // safely clean up thread

    buttons_blocked = false;
    on_page_change("Soft", {});
}

