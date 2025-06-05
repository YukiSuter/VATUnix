#pragma once
#include <gtkmm.h>
#include "wizard_buttons.h"

class DependenciesPage : public Gtk::Box {
public:
    DependenciesPage();
    Gtk::Box& get_missing_dep_box();
    WizardButtons& get_nav_buttons();
    Gtk::Box& get_custom_button_box();
    Gtk::Button& get_refresh_button();
    Gtk::Button& get_back_button();

private:
    Gtk::Label title, text;
    Gtk::Separator separator;
    Gtk::Box missing_dep_box;
    Gtk::Box custom_button_box;
    Gtk::Button back_button, refresh_button;
    WizardButtons nav_buttons;
};