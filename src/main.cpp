#include "VATUnix.h"

int main(int argc, char* argv[]) {
    auto app = VATUnix::create();
    return app->run(argc, argv);
}

