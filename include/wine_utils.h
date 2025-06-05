//
// Created by yukisuter on 6/2/25.
//

#ifndef WINE_UTILS_H
#define WINE_UTILS_H
#include <string>


namespace wine_utils {
    int install_msi(std::string msi, bool quiet, std::string logfile="");
    int install_libraries(std::string libs);
    bool create_env(bool override=true);
    std::string execute(const std::string &command);
};



#endif //WINE_UTILS_H
