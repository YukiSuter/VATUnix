//
// Created by yukisuter on 6/1/25.
//

#ifndef EUROSCOPE_H
#define EUROSCOPE_H
#include <gtkmm.h>

#include <nlohmann/json.hpp>

class Euroscope : public Gtk::Box {
public:
    Euroscope(bool tick=false, std::string version="Latest");

    std::string get_config();
    void set_config(const nlohmann::json &new_config);

    int uninstall();
    int install();
    int modify();

    bool check_installed(std::string prefix_dir);
    void process_box();
private:
    Gtk::CheckButton check;
    Gtk::Label label;
    Gtk::DropDown dropdown;
    Gtk::Box spacer;  // Spacer
};


#endif //EUROSCOPE_H
