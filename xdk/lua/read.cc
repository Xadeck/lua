#include "xdk/lua/read.h"
#include "absl/strings/str_cat.h"

namespace xdk {
namespace lua {

std::string Read(lua_Reader reader, lua_State *L, void *data) {
  std::string result;
  size_t size;
  while (const char *read = reader(L, data, &size)) {
    absl::StrAppend(&result, absl::string_view(read, size));
    if (!size)
      break;
  }
  return result;
}

} // namespace lua
} // namespace xdk
