#pragma once

#include <gtkmm.h>
#include <thread>
#include <vector>
#include <string>

#include "../src/FTS/start_page.h"
#include "../src/FTS/dependencies_page.h"
#include "../src/FTS/wine_page.h"
#include "../src/FTS/software_page.h"
#include "../src/FTS/software_choice_page.h"

class FTSPage : public Gtk::Box {
public:
    FTSPage();

private:
    Gtk::Stack wizard_stack;

    StartPage start_page;
    DependenciesPage dep_page;
    WinePage wine_page;
    FTSSoftwarePage soft_page;
    SoftwareChoicePage soft_choice_page;

    std::vector<std::string> required_packages = {
        "unzip", "wine", "winetricks", "wineserver", "grep", "wget"
    };
    std::vector<std::string> missing_packages;

    bool buttons_blocked = false;
    int dot_count = 0;

    Glib::Dispatcher env_created_dispatcher;
    std::thread background_thread;
    sigc::connection label_anim_conn;

    void on_page_change(const std::string& page_name, bool force = false);
    void check_packages();
    void create_refresh_buttons();
    void create_env_async();
    bool update_install_label();
    void on_env_created();
};
