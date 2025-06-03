//
// Created by yukisuter on 5/28/25.
//

#include "wizard_buttons.h"


WizardButtons::WizardButtons(int both, std::string n_page, std::string n_label, std::string b_page, std::string b_label) {
    set_orientation(Gtk::Orientation::HORIZONTAL);
    set_halign(Gtk::Align::END);

    btn_back.set_label(b_label);
    btn_fwd.set_label(n_label);

    if (both) {
        append(btn_back);
    }
    append(btn_fwd);

    btn_back.signal_clicked().connect([this, b_page] {
        change_sig.emit(b_page);
    });

    btn_fwd.signal_clicked().connect([this, n_page] {
        change_sig.emit(n_page);
    });
}

sigc::signal<void(std::string)>& WizardButtons::change_signal() {
    return change_sig;
}