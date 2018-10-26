#include "xdk/lua/vector.h"
#include "xdk/lua/string_view.h"

namespace xdk {
namespace lua {
namespace {
constexpr char kSize[] = "n";

lua_Number getn(lua_State *L, int index, const char *direction) {
  lua_pushstring(L, direction);
  lua_Number n =
      (lua_rawget(L, index) == LUA_TNUMBER) ? lua_tonumber(L, -1) : 0;
  lua_pop(L, 1);
  return n;
}
lua_Number pushn(lua_State *L, int index, const char *direction) {
  lua_pushstring(L, direction);
  if (lua_rawget(L, index) == LUA_TNIL) {
    lua_pop(L, 1);
    lua_pushnumber(L, 0);
  }
  return lua_tonumber(L, -1);
}
} // namespace

void newvector(lua_State *L) {
  lua_newtable(L);
  if (luaL_newmetatable(L, "__vector")) {
    // One time initialization of the metatable.
  }
  lua_setmetatable(L, -2);
}

bool isvector(lua_State *L, int index) {
  if (lua_getmetatable(L, index)) {
    lua_pushstring(L, "__name");
    lua_rawget(L, -2);
    return lua_type(L, -1) == LUA_TSTRING && tostring_view(L, -1) == "__vector";
  }
  return false;
}

void pushback(lua_State *L, int index) {
  index = lua_absindex(L, index);
  const lua_Number n = getn(L, index, kSize);
  lua_pushnumber(L, n + 1);
  lua_insert(L, -2);
  lua_rawset(L, index);
  // Increase n and store it back.
  lua_pushstring(L, kSize);
  lua_pushnumber(L, n + 1);
  lua_rawset(L, index);
}

void popback(lua_State *L, int index) {
  index = lua_absindex(L, index);
  const lua_Number n = pushn(L, index, kSize);
  lua_pushnil(L);
  lua_rawset(L, index);
  // Decrease n and store it back.
  lua_pushstring(L, kSize);
  lua_pushnumber(L, n - 1);
  lua_rawset(L, index);
}

void getback(lua_State *L, int index) {
  index = lua_absindex(L, index);
  pushn(L, index, kSize);
  lua_rawget(L, index);
}

} // namespace lua
} // namespace xdk
