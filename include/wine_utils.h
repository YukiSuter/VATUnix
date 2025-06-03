//
// Created by yukisuter on 6/2/25.
//

#ifndef WINE_UTILS_H
#define WINE_UTILS_H
#include <string>


namespace wine_utils {
    bool install_msi(std::string msi);
    bool create_env(std::string prefix_dir, bool override=true);
    std::string execute(const std::string &command);
};



#endif //WINE_UTILS_H
