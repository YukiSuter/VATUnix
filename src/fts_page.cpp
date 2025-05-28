#include "fts_page.h"

FTSPage::FTSPage()
{
    set_margin_start(50);
    set_margin_end(50);
    set_margin_top(20);
    set_margin_bottom(20);
    set_orientation(Gtk::Orientation::VERTICAL);

    append(wizard_stack);


    // Start Page

    Gtk::Box start_box;
    Gtk::Label start_title;
    Gtk::Label start_text;
    Gtk::Separator separator;  // 👈 Create the separator

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

    separator.set_orientation(Gtk::Orientation::HORIZONTAL);
    separator.set_margin_top(10);
    separator.set_margin_bottom(10);
    start_box.append(separator);  // 👈 Add it to the box


    wizard_stack.add(start_box, "Start", "Start");
    wizard_stack.set_visible_child("Start");
}
