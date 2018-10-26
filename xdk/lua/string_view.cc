#include "xdk/lua/string_view.h"
namespace xdk {
namespace lua {
absl::string_view tostring_view(lua_State *L, int index) {
  return lua_tostring(L, index);
}
} // namespace lua
} // namespace xdk
