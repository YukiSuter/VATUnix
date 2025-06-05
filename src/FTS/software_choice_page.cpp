#include "software_choice_page.h"
#include "../softwares/euroscope.h"

SoftwareChoicePage::SoftwareChoicePage() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_vexpand();
    set_valign(Gtk::Align::FILL);

    title.set_text("Choose from below");
    title.add_css_class("wizard-title");
    title.set_xalign(0);
    title.set_margin_top(10);
    title.set_margin_bottom(10);

    Euroscope es_choice;

    separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    separator.set_margin_top(10);
    separator.set_margin_bottom(10);

    custom_button_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    custom_button_box.set_halign(Gtk::Align::END);
    back_button.set_label("< Back");
    install_button.set_label("Install");

    custom_button_box.append(back_button);
    custom_button_box.append(install_button);

    append(title);
    append(es_choice);
    append(separator);
    append(custom_button_box);
}

Gtk::Button& SoftwareChoicePage::get_install_button() { return install_button; }
Gtk::Button& SoftwareChoicePage::get_back_button() { return back_button; }