#ifndef XDK_LUA_VECTOR_H
#define XDK_LUA_VECTOR_H

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// Creates a new vector and pushes it onto the stack.
void newvector(lua_State *L);
// Return true iff the value at the given index is a vector.
bool isvector(lua_State *L, int index);
// Adds the value on the top of the stack at the back of vector at the
// given index.
void pushback(lua_State *L, int index);
// Removes the value at the back of the vector at the given index. Does *not*
// put it on the stack. Use getback() before that for that purpose.
void popback(lua_State *L, int index);
// Pushes onto the stack the value at the back of the vector at the given
// index.  Does *not* remove it from the vector. Use popback() afterwards for
// that purpose.
void getback(lua_State *L, int index);

} // namespace lua
} // namespace xdk

#endif
