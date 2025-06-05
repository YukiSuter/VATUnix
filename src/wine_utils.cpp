//
// Created by yukisuter on 6/2/25.
//

#include <array>
#include <filesystem>
#include <iostream>
#include <memory>
#include <giomm/file.h>
#include <glibmm/fileutils.h>


namespace wine_utils {
    std::string wineBin;

    std::string execute(const std::string& cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        // Remove trailing newline if present
        if (!result.empty() && result.back() == '\n') {
            result.pop_back();
        }
        return result;
    }

    bool create_env(std::string prefix_dir, bool override) {
        try {
            if (override) {
                if (Glib::file_test(prefix_dir, Glib::FileTest::IS_DIR)) {
                    std::cout<<"Found existing directory. Overwriting..."<<std::endl;
                    std::filesystem::remove_all(prefix_dir);
                }
            }

            // Get path to wine binary
            wineBin = execute("command -v wine");
            std::cout << "Detected wine at: " << wineBin << std::endl;

            // Kill any running wineserver instance
            int kill_result = std::system("wineserver --kill");
            if (kill_result != 0) {
                std::cerr << "Warning: wineserver --kill returned non-zero (might be fine)\n";
            }

            std::cout<<("WINEPREFIX=\"" + prefix_dir + "\" wine wineboot --init").c_str()<<std::endl;
            std::system(("WINEPREFIX=\"" + prefix_dir + "\" wine wineboot --init").c_str());
            std::system(("WINEPREFIX=\"" + prefix_dir + "\" wine winecfg -v win7").c_str());

            std::string cmd = "WINEPREFIX=\"" + prefix_dir + "\" " + wineBin + " winecfg -v";
            std::system(cmd.c_str());

            return true;

        } catch (const std::exception& e) {
            std::cerr << "Error running wine setup: " << e.what() << std::endl;
            return 0;
        }
    }

    int install_msi(std::string prefix_dir, std::string msi, bool quiet, std::string logfile="") {
        try {
            std::string args;

            if (quiet) args+=" /q";

            if (logfile.length() >0) {
                args += " /l "+logfile;
            }

            int rt = std::system(("WINEPREFIX=\"" + prefix_dir + "\" wine msiexec" + args + " /i "+msi).c_str());
            return rt;
        } catch (const std::exception& e) {
            std::cerr << "Error installing msi: " << e.what() << std::endl;
            return 1;
        }

    }

    int install_libraries(std::string prefix_dir, std::string libs)  {
        try {
            int rt = std::system(("WINEPREFIX=\"" + prefix_dir + "\" winetricks --unattended " + libs).c_str());
            return rt;
        } catch (const std::exception& e) {
            std::cerr << "Error installing libraries: " << e.what() << std::endl;
            return 1;
        }
    }


}


#include "../include/wine_utils.h"
