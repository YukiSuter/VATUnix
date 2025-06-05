#pragma once
#include <gtkmm.h>
#include "wizard_buttons.h"

class StartPage : public Gtk::Box {
public:
    StartPage();
    WizardButtons& get_nav_buttons();
private:
    Gtk::Label title, text;
    Gtk::Separator separator;
    WizardButtons nav_buttons;
};