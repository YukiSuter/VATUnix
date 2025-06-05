#include "wine_page.h"

WinePage::WinePage() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_vexpand();
    set_valign(Gtk::Align::FILL);

    title.set_text("Wine Configuration");
    title.add_css_class("wizard-title");
    title.set_xalign(0);

    text.set_text("Please now use the options below to set up the wine environment. Default values will be used.");
    text.set_wrap();
    text.set_xalign(0);
    text.set_vexpand();
    text.set_valign(Gtk::Align::FILL);

    separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    separator.set_margin_top(10);
    separator.set_margin_bottom(10);

    button_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    button_box.set_halign(Gtk::Align::END);
    back_button.set_label("< Back");
    install_button.set_label("Install");
    button_box.append(back_button);
    button_box.append(install_button);

    append(title);
    append(text);
    append(separator);
    append(button_box);
}

Gtk::Button& WinePage::get_install_button() { return install_button; }
Gtk::Button& WinePage::get_back_button() { return back_button; }