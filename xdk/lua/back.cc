#include "xdk/lua/back.h"

namespace xdk {
namespace lua {
namespace {
constexpr char kSize[] = "n";

lua_Number getn(lua_State *L, int index) {
  lua_pushstring(L, kSize);
  lua_Number n = (lua_rawget(L, index) == LUA_TNUMBER) ? lua_tonumber(L, -1) : 0;
  lua_pop(L, 1);
  return n;
}
lua_Number pushn(lua_State *L, int index) {
  lua_pushstring(L, kSize);
  if (lua_rawget(L, index) == LUA_TNIL) {
    lua_pop(L, 1);
    lua_pushnumber(L, 0);
  }
  return lua_tonumber(L, -1);
}
}  // namespace

void pushback(lua_State *L, int index) noexcept {
  index              = lua_absindex(L, index);
  const lua_Number n = getn(L, index);
  lua_pushnumber(L, n + 1);
  lua_insert(L, -2);
  lua_rawset(L, index);
  // Increase n and store it back.
  lua_pushstring(L, kSize);
  lua_pushnumber(L, n + 1);
  lua_rawset(L, index);
}

void popback(lua_State *L, int index) noexcept {
  index              = lua_absindex(L, index);
  const lua_Number n = pushn(L, index);
  lua_pushnil(L);
  lua_rawset(L, index);
  // Decrease n and store it back.
  lua_pushstring(L, kSize);
  if (1 < n) {
    lua_pushnumber(L, n - 1);
  } else {
    lua_pushnil(L);
  }
  lua_rawset(L, index);
}

void getback(lua_State *L, int index) noexcept {
  index = lua_absindex(L, index);
  pushn(L, index);
  lua_rawget(L, index);
}

}  // namespace lua
}  // namespace xdk
