#ifndef VALKYRIE_VERSION_H_INCLUDED
#define VALKYRIE_VERSION_H_INCLUDED

#include "valkyrie.h"

namespace valkyrie
{

// provides a simple versioning info for the API
class DLL_HIDDEN Version
{
public:
    static const int getMajor();
    static const int getMinor();
    static const int getPatch();
    static const char *getVersion();
    static const bool isAtLeast(int major, int minor, int patch);
};//~cl:Version

}//~ ns:valkyrie

#endif /* VALKYRIE_VERSION_H_INCLUDED */
