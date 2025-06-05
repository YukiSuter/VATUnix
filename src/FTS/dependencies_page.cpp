#include "dependencies_page.h"

DependenciesPage::DependenciesPage() : nav_buttons(1, "Wine", "Next >", "Start") {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_vexpand();
    set_valign(Gtk::Align::FILL);

    title.set_text("Dependencies");
    title.add_css_class("wizard-title");
    title.set_xalign(0);

    text.set_text("VATUnix requires some dependencies to run correctly. Depending on the installation method not all may be installed.");
    text.set_wrap();
    text.set_xalign(0);
    text.set_vexpand();
    text.set_valign(Gtk::Align::FILL);

    missing_dep_box.set_orientation(Gtk::Orientation::VERTICAL);

    separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    separator.set_margin_top(10);
    separator.set_margin_bottom(10);

    custom_button_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    custom_button_box.set_halign(Gtk::Align::END);
    back_button.set_label("< Back");
    refresh_button.set_label("Refresh");
    custom_button_box.append(back_button);
    custom_button_box.append(refresh_button);

    append(title);
    append(text);
    append(missing_dep_box);
    append(separator);
    append(custom_button_box);
}

Gtk::Box& DependenciesPage::get_missing_dep_box() { return missing_dep_box; }
Gtk::Box& DependenciesPage::get_custom_button_box() { return custom_button_box; }
WizardButtons& DependenciesPage::get_nav_buttons() { return nav_buttons; }
Gtk::Button& DependenciesPage::get_refresh_button() { return refresh_button; }
Gtk::Button& DependenciesPage::get_back_button() { return back_button; }