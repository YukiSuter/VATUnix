#include "about_page.h"
#include "fts_page.h"
#include "software_page.h"

class home_window : public Gtk::Window {
public:
    home_window();

private:
    Gtk::Overlay m_overlay;
    Gtk::Box main_box;
    Gtk::Box button_box;
    Gtk::Stack menu_stack;

    Gtk::ToggleButton btn_about, btn_software, btn_regions, btn_first;

    AboutPage about_page;
    SoftwarePage software_page;
    FTSPage fts_page;
    Gtk::Box s_box;  // placeholder for Software
    Gtk::Box r_box;  // placeholder for Regions
};
