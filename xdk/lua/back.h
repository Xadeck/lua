#ifndef XDK_LUA_BACK_H
#define XDK_LUA_BACK_H

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// Sets t[n+1] = k and t["n"] = n+1, where t is the table at given index, n is
// the numeric value of t["n"] or 0 if it is not a number.
void pushback(lua_State *L, int index);
// Sets t[n] = nil and t["n"] = n-1, where t is the table at given index, n is
// the numeric value of t["n"] or 0 if it is not a number.
void popback(lua_State *L, int index);
// Pushes onto the stack t[n], where t is the table at given index, n is the
// numeric value of t["n"] or 0 if it is not a number.
void getback(lua_State *L, int index);

} // namespace lua
} // namespace xdk

#endif
