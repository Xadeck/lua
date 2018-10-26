#ifndef XDK_LUA_VECTOR_H
#define XDK_LUA_VECTOR_H

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// Creates a new vector and pushes it on the stack.
void newvector(lua_State *L);
// Return if the value at the given index is a vector.
bool isvector(lua_State *L, int index);
// Pushes the value on the top of the stack at the back of vector at the
// given index.
//
// Does nothing if !isvector(L, index).
void pushback(lua_State *L, int index);
// Pops the last value pushed value at the back of the vector at the given
// index.
//
// Does nothing if !isvector(L, index).
void popback(lua_State *L, int index);

void getback(lua_State *L, int index);

} // namespace lua
} // namespace xdk

#endif
