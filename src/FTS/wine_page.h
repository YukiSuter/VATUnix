#pragma once
#include <gtkmm.h>

class WinePage : public Gtk::Box {
public:
    WinePage();
    Gtk::Button& get_install_button();
    Gtk::Button& get_back_button();

private:
    Gtk::Label title, text;
    Gtk::Separator separator;
    Gtk::Button install_button, back_button;
    Gtk::Box button_box;
};