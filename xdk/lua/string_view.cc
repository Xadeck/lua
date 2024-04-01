#include "xdk/lua/string_view.h"

#include <string_view>

namespace xdk {
namespace lua {
std::string_view tostring_view(lua_State *L, int index) noexcept {
  const char *s = lua_tostring(L, index);
  return s != nullptr ? std::string_view(s) : std::string_view();
}

}  // namespace lua
}  // namespace xdk
