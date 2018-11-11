#ifndef XDK_LUA_STRING_VIEW_H
#define XDK_LUA_STRING_VIEW_H

#include "absl/strings/string_view.h"
#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// If value at the given index is a string, returns it. Otherwise returns an
// empty string view.
absl::string_view tostring_view(lua_State *L, int index) noexcept;
} // namespace lua
} // namespace xdk

#endif
