#include "asset_not_found.h"
#include <string>

AssetNotFoundException::AssetNotFoundException(std::string message):
    std::runtime_error(message){}
