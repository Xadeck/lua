#ifndef XDK_LUA_STRING_VIEW_H_
#define XDK_LUA_STRING_VIEW_H_

#include <string_view>

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// If value at the given index is a string, returns it. Otherwise returns an
// empty string view.
std::string_view tostring_view(lua_State *L, int index) noexcept;
}  // namespace lua
}  // namespace xdk

#endif  // XDK_LUA_STRING_VIEW_H_
