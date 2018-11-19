#include "xdk/lua/rawfield.h"

namespace xdk {
namespace lua {

void rawsetfield(lua_State *L, int index, const char *k) {
  index = lua_absindex(L, index);
  lua_pushstring(L, k);
  lua_insert(L, -2);
  lua_rawset(L, index);
}

void rawgetfield(lua_State *L, int index, const char *k) {
  index = lua_absindex(L, index);
  lua_pushstring(L, k);
  lua_rawget(L, index);
}

void rawsetfieldnil(lua_State *L, int index, const char *k) {
  index = lua_absindex(L, index);
  lua_pushnil(L);
  rawsetfield(L, index, k);
}

void rawsetfieldnewtable(lua_State *L, int index, const char *k) {
  index = lua_absindex(L, index);
  lua_newtable(L);
  rawsetfield(L, index, k);
}

void rawsetfieldstring(lua_State *L, int index, const char *k, const char *s) {
  index = lua_absindex(L, index);
  lua_pushstring(L, s);
  rawsetfield(L, index, k);
}

void rawsetfieldnumber(lua_State *L, int index, const char *k, lua_Number d) {
  index = lua_absindex(L, index);
  lua_pushnumber(L, d);
  rawsetfield(L, index, k);
}

} // namespace lua
} // namespace xdk
