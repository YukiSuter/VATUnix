#ifndef FTS_PAGE_H
#define FTS_PAGE_H

#include <gtkmm.h>
#include <thread>

#include "wizard_buttons.h"

class FTSPage : public Gtk::Box {
public:
    FTSPage();
private:
    Gtk::Stack wizard_stack;
    WizardButtons start_wiz_buttons;
    WizardButtons dep_wiz_buttons;
    WizardButtons wine_wiz_buttons;
    WizardButtons soft_wiz_buttons;

    bool buttons_blocked;

    Gtk::Button dep_btn_fwd,dep_btn_back;
    Gtk::Box dep_cwb;

    Gtk::Button schoice_btn_fwd,schoice_btn_back;
    Gtk::Box schoice_cwb;

    std::vector<std::string> required_packages;
    std::vector<std::string> missing_packages;

    Gtk::Box dep_box;
    Gtk::Box missing_dep_box;
    Gtk::Label dep_title;
    Gtk::Label dep_text;
    Gtk::Separator dep_separator;  // 👈 Create the separator
    Gtk::Button wine_install_button, wine_back_button;

    std::string prefix_dir;

    void on_page_change(const std::string &page_name, bool force=false);
    void check_packages();
    void create_refresh_buttons();
    void create_env_async();

    bool update_install_label();
    void on_env_created();

    std::thread background_thread;
    Glib::Dispatcher env_created_dispatcher;
    sigc::connection label_anim_conn;
    int dot_count = 0;
};

#endif //FTS_PAGE_H
