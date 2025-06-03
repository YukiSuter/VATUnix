//
// Created by yukisuter on 6/1/25.
//
#include "euroscope.h"
#include <gtkmm.h>
#include <iostream>

#include <nlohmann/json.hpp>
#include "file_utils.h"

extern std::vector<Glib::ustring> version_labels = {"Latest", "3.2.9"};
extern std::string latest_version = "3.2.9";

Euroscope::Euroscope(bool tick, std::string version): dropdown(version_labels), spacer(Gtk::Orientation::HORIZONTAL) {
    check.set_active(tick);
    label.set_text("Euroscope");
    label.set_margin_start(5);

    // Make spacer expand to push dropdown to the right
    spacer.set_hexpand(true);

    // Optional alignment tweaks (not required, but clean)
    label.set_halign(Gtk::Align::START);
    dropdown.set_halign(Gtk::Align::END);

    append(check);
    append(label);
    append(spacer);     // Spacer pushes dropdown to the right
    append(dropdown);
}

std::string Euroscope::get_config() {
    std::map<std::string, std::string> config = {};

    int choice_index = dropdown.get_selected();
    std::string version_string = std::string(version_labels[choice_index]);

    config.insert({"chosen", check.get_active()? "1":"0"});
    config.insert({"version", version_string});

    nlohmann::json config_json = config;

    return config_json.dump(4);
}

void Euroscope::set_config(const nlohmann::json& new_config) {
    std::map<std::string, std::string> config = new_config.get<std::map<std::string, std::string>>();

    std::string version_string = (config["version"].data());
    auto it = std::find(version_labels.begin(), version_labels.end(), version_string);

    dropdown.set_selected(std::distance(version_labels.begin(), it));
    check.set_active(config["chosen"].data() == "1");
}


int Euroscope::install() {
    // Write code that installs the program. Expect this function to be run using a future.
    try {
        int result = std::system("winetricks --unattended iertutil msls31 msxml6 urlmon vcrun2022 wininet");
        if (result != 0) {
            std::cout << "winetricks failed with code " << result << std::endl;
        }
        Glib::ustring selected_version = version_labels[dropdown.get_selected()];
        Glib::ustring version_to_use = (selected_version == "Latest") ? Glib::ustring(latest_version) : selected_version;
        std::string download_url = "https://euroscope.hu/install/EuroScopeSetup." + version_to_use + ".msi";

        if (FileUtils::download_to_folder(download_url, "DownloadCache/EuroscopeInstaller.msi", 0)) {

        }
    } catch (const std::exception& e) {
        std::cout<<"Failure during Euroscope install attempt: " << e.what() << std::endl;
    }


}

int Euroscope::modify() { // Maybe a map of changes?
    // Write code that modifies the program. Expect this function to be run using a future.
    // Only real modification should be a version change. For this, run the uninstall function then the install function
}

int Euroscope::uninstall() {
    // Write code that uninstalls the program. Expect this function to be run using a future.
}

#include "euroscope.h"
