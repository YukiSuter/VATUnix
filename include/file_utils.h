#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

#include "json.hpp"

namespace FileUtils {
    // Ensures ~/Documents/VATUnix exists
    void ensure_vatunix_data_folder();

    // Optional: returns the path to ~/Documents/VATUnix
    std::string get_vatunix_data_path();
    std::string get_settings_path();

    nlohmann::json load_settings();
    void save_settings(const nlohmann::json& j);

    template<typename T>
    T get_setting(const std::string& key, const T& fallback);

    template<typename T>
    void set_setting(const std::string& key, const T& value);
}

#endif // FILE_UTILS_H
