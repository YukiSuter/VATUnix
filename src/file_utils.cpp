#include "file_utils.h"
#include <glibmm.h>
#include <giomm.h>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "json.hpp"
using json = nlohmann::json;


namespace FileUtils {

    void ensure_vatunix_data_folder() {
        auto docs_path = Glib::get_user_special_dir(Glib::UserDirectory::DOCUMENTS);

        if (docs_path.empty()) {
            std::cerr << "Could not resolve user Documents directory.\n";
            return;
        }

        auto target_path = Glib::build_filename(docs_path, "VATUnix");

        try {
            if (!Glib::file_test(target_path, Glib::FileTest::IS_DIR)) {
                Gio::File::create_for_path(target_path)->make_directory();
                std::cout << "Created directory: " << target_path << std::endl;
            }
        } catch (const Glib::Error& ex) {
            std::cerr << "Failed to create VATUnix directory: " << ex.what() << std::endl;
        }

        auto settings_path = Glib::build_filename(target_path, "settings.json");
        if (!Glib::file_test(settings_path, Glib::FileTest::IS_REGULAR)) {
            nlohmann::json j;
            j["first_launch"] = true;

            std::ofstream out(settings_path);
            out << j.dump(4);
            std::cout << "Created default settings.json\n";
        }
    }

    std::string get_vatunix_data_path() {
        auto docs_path = Glib::get_user_special_dir(Glib::UserDirectory::DOCUMENTS);
        return Glib::build_filename(docs_path, "VATUnix");
    }

    std::string get_settings_path() {
        return Glib::build_filename(get_vatunix_data_path(), "settings.json");
    }

    json load_settings() {
        std::ifstream in(get_settings_path());
        if (!in) {
            std::cerr << "Failed to open settings.json\n";
            return json{};  // return empty object if file missing
        }

        json j;
        try {
            in >> j;
        } catch (const std::exception& e) {
            std::cerr << "Failed to parse settings.json: " << e.what() << "\n";
            return json{};
        }

        return j;
    }

    void save_settings(const json& j) {
        std::ofstream out(get_settings_path());
        if (!out) {
            std::cerr << "Failed to write settings.json\n";
            return;
        }

        out << j.dump(4);  // pretty print with indent
    }

    template<typename T>
    T get_setting(const std::string& key, const T& fallback) {
        json j = load_settings();
        return j.value(key, fallback);
    }

    template<typename T>
    void set_setting(const std::string& key, const T& value) {
        json j = load_settings();
        j[key] = value;
        save_settings(j);
    }

} // namespace FileUtils
