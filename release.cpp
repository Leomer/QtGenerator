#include "release.h"

#include <cstdlib>


void createDirectories(std::string path) {

    std::string aux;

    system(("mkdir " + path).c_str());
}
