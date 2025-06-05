#include "software_page.h"

FTSSoftwarePage::FTSSoftwarePage() : nav_buttons(1, "SoftChoice", "Next >", "Wine") {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_vexpand();
    set_valign(Gtk::Align::FILL);

    title.set_text("Software");
    title.add_css_class("wizard-title");
    title.set_xalign(0);

    text.set_text("Please use this section to decide what software is to be installed...");
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

WizardButtons& FTSSoftwarePage::get_nav_buttons() {
    return nav_buttons;
}