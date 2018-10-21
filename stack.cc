#include "xdk/lua/stack.h"

#include <iomanip>

#include "absl/strings/escaping.h"

namespace xdk {
namespace lua {

Stack Stack::Debug(lua_State *L) { return Stack(L, true, true, "\n"); }
Stack Stack::Values(lua_State *L) { return Stack(L, false, false, ", "); }

std::ostream &operator<<(std::ostream &os, const ::xdk::lua::Stack &stack) {
  lua_State *L = stack.L_;
  if (stack.show_header_) {
    os << "---\n";
  }
  for (int i = -lua_gettop(L); i < 0; ++i) {
    if (stack.show_type_) {
      os << std::setw(3) << i << ':' << std::setw(8)
         << lua_typename(L, lua_type(L, i)) << "=";
    }
    switch (lua_type(L, i)) {
    case LUA_TNIL:
      os << "nil";
      break;
    case LUA_TNUMBER:
      os << lua_tonumber(L, i);
      break;
    case LUA_TBOOLEAN:
      os << (lua_toboolean(L, i) ? "true" : "false");
      break;
    case LUA_TSTRING:
      os << '"' << absl::CEscape(lua_tostring(L, i)) << '"';
      break;
    case LUA_TTABLE:
      os << "{...}";
      break;
    case LUA_TFUNCTION:
      os << "fn";
      break;
    case LUA_TUSERDATA:
      os << lua_touserdata(L, i);
      break;
    case LUA_TTHREAD:
      os << lua_tothread(L, i);
      break;
    case LUA_TLIGHTUSERDATA:
      os << lua_touserdata(L, i);
      break;
    }
    if (i != -1) {
      os << stack.separator_;
    }
  }
  return os;
}

} // namespace lua
} // namespace xdk
