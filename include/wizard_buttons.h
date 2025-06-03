//
// Created by yukisuter on 5/28/25.
//

#ifndef WIZARD_BUTTONS_H
#define WIZARD_BUTTONS_H
#include <gtkmm.h>



class WizardButtons: public Gtk::Box {
public:
    WizardButtons(int both = 0, std::string n_page = "", std::string n_label = "Next >", std::string b_page = "", std::string b_label = "< Back");

    sigc::signal<void(std::string)>& change_signal();
private:
    Gtk::Button btn_fwd, btn_back;

    sigc::signal<void(std::string)> change_sig;
};



#endif //WIZARD_BUTTONS_H
