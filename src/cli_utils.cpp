//
// Created by yukisuter on 5/29/25.
//

#include "cli_utils.h"

#include <iostream>

namespace CLIUtils {
    int execute_command(std::string cmd) {
        std::string cmd2 = cmd + " --version";
        cmd += " -h";

        try {
            int ret = std::system(cmd.c_str());
            int ret2 = std::system(cmd2.c_str());

            if (ret != 0 && ret2 != 0) {
                std::cout << "Package " << cmd << " not found." << std::endl;
                return 1;
            }
            std::cout << "Package " << cmd << " was found." << std::endl;
            return 0;
        } catch (const std::exception &e) {
            std::cout << "Package " << cmd << " could not be found." << std::endl;
            return 1;
        }
    }
}
