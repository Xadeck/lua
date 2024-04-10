#ifndef XDK_LUA_RAWFIELD_H_
#define XDK_LUA_RAWFIELD_H_

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
void rawgetfield(lua_State *L, int index, const char *k);
void rawsetfield(lua_State *L, int index, const char *k);

void rawsetfieldnil(lua_State *L, int index, const char *k);
void rawsetfieldnewtable(lua_State *L, int index, const char *k);
void rawsetfieldstring(lua_State *L, int index, const char *k, const char *s);
void rawsetfieldnumber(lua_State *L, int index, const char *k, lua_Number d);

}  // namespace lua
}  // namespace xdk

#endif  // XDK_LUA_RAWFIELD_H_
