#pragma once
#include <gtkmm.h>
#include "wizard_buttons.h"

class FTSSoftwarePage : public Gtk::Box {
public:
    FTSSoftwarePage();
    WizardButtons& get_nav_buttons();

private:
    Gtk::Label title, text;
    Gtk::Separator separator;
    WizardButtons nav_buttons;
};