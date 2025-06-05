#include "start_page.h"

StartPage::StartPage() : nav_buttons(0, "Dependencies") {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_vexpand();
    set_valign(Gtk::Align::FILL);

    title.set_text("Welcome");
    title.add_css_class("wizard-title");
    title.set_xalign(0);

    text.set_text("VATUnix is software used to manage the Euroscope and associated software on systems without official support.");
    text.set_wrap();
    text.set_xalign(0);
    text.set_vexpand();
    text.set_valign(Gtk::Align::FILL);

    separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    separator.set_margin_top(10);
    separator.set_margin_bottom(10);

    append(title);
    append(text);
    append(separator);
    append(nav_buttons);
}

WizardButtons& StartPage::get_nav_buttons() {
    return nav_buttons;
}