#include "xdk/lua/stack.h"

#include <iomanip>

namespace xdk {
namespace lua {

std::ostream &operator<<(std::ostream &os, const Stack::Element &element) {
  lua_State *L = element.L;
  int index = element.index;
  os << std::setw(3) << std::right << index << " [" << std::setw(7) << std::left
     << lua_typename(L, lua_type(L, index)) << "]";
  switch (lua_type(L, index)) {
  case LUA_TNIL:
    return os;
  case LUA_TNUMBER:
    return os << ' ' << lua_tonumber(L, index);
  case LUA_TBOOLEAN:
    return os << ' ' << (lua_toboolean(L, index) ? "true" : "false");
  case LUA_TSTRING:
    return os << ' ' << std::quoted(lua_tostring(L, index));
  case LUA_TTABLE:
    return os << " {...}";
  case LUA_TFUNCTION:
    return os << " fn";
  case LUA_TUSERDATA:
    return os << ' ' << lua_touserdata(L, index);
  case LUA_TTHREAD:
    return os << ' ' << lua_tothread(L, index);
  case LUA_TLIGHTUSERDATA:
    return os << ' ' << lua_touserdata(L, index);
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Stack &stack) {
  lua_State *L = stack.L;
  os << "---\n";
  for (int index = 1; index <= lua_gettop(L); ++index) {
    os << Stack::Element(L, index);
    os << '\n';
  }
  return os;
}

} // namespace lua
} // namespace xdk
