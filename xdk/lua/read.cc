#include "xdk/lua/read.h"

#include <string_view>

namespace xdk {
namespace lua {

std::string Read(lua_Reader reader, lua_State *L, void *data) {
  std::string result;
  size_t size;
  while (const char *read = reader(L, data, &size)) {
    std::string_view sv{read, size};
    result.append(sv.begin(), sv.end());
    if (!size)
      break;
  }
  return result;
}

} // namespace lua
} // namespace xdk
