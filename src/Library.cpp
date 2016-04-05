#include "Library.h"

Library::Library(const std::string &name, const std::string &readGroup)
    : name(name),
      readGroups({readGroup}),
      meanInsertSize(-1),
      insertSizeSd(-1)
{
}
