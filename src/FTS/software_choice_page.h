#pragma once
#include <gtkmm.h>

class SoftwareChoicePage : public Gtk::Box {
public:
    SoftwareChoicePage();
    Gtk::Button& get_install_button();
    Gtk::Button& get_back_button();

private:
    Gtk::Label title;
    Gtk::Box custom_button_box;
    Gtk::Button back_button, install_button;
    Gtk::Separator separator;
};