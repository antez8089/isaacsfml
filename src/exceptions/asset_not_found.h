#ifndef ASSET_NOT_FOUND_H
#define ASSET_NOT_FOUND_H
#include <stdexcept>

class AssetNotFoundException : public std::runtime_error
{
    public:
        AssetNotFoundException(std::string message);
};

#endif
