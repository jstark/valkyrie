#include "valkyrie.h"
#include "version.h"

using valkyrie::Version;

const int Version::getMajor()
{
    return VK_API_MAJOR;
}

const int Version::getMinor()
{
    return VK_API_MINOR;
}

const int Version::getPatch()
{
    return VK_API_PATCH;
}

const char *Version::getVersion()
{
    return VK_API_VERSION;
}

const bool Version::isAtLeast(int major, int minor, int patch)
{
    if (getMajor() > major)
    {
        return true;
    } else if (getMajor() == major)
    {
        if (getMinor() > minor)
        {
            return true;
        } else if (getMinor() == minor)
        {
            if (getPatch() >= patch)
            {
                return true;
            } else
            {
                return false;
            }
        } else
        {
            return false;
        }
    }
    return false;
}

extern "C" int VKApiMajorVersion(void)
{
    return Version::getMajor();
}

extern "C" int VKApiMinorVersion(void)
{
    return Version::getMinor();
}

extern "C" int VKApiPatchVersion(void)
{
    return Version::getPatch();
}

extern "C" int VKApiVersionIsAtLeast(int major, int minor, int patch)
{
    return Version::isAtLeast(major, minor, patch) ? 1 : 0;
}

extern "C" const char *VKApiVersion(void)
{
    return Version::getVersion();
}
