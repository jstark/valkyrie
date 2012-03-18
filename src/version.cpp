#include "version.h"

using valkyrie::Version;

int Version::getMajor()
{
    return -1;
}

int Version::getMinor()
{
    return -1;
}

int Version::getPatch()
{
    return -1;
}

const std::string Version::getVersion()
{
    return "__api_error__";
}

bool Version::isAtLeast(int major, int minor, int patch)
{
    return false;
}
