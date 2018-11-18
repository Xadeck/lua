#ifndef XDK_LUA_POPPER_H
#define XDK_LUA_POPPER_H

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {

struct Popper {
  Popper(lua_State *L, int n);
  ~Popper();
  lua_State *const L;
  const int n;
};

} // namespace lua
} // namespace xdk

#endif
