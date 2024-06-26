#ifndef XDK_LUA_STACK_H_
#define XDK_LUA_STACK_H_

#include <iostream>

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {

struct Stack {
  explicit Stack(lua_State *L) : L(L) {}

  struct Element {
    Element(lua_State *L, int index) : L(L), index(index) {}
    lua_State *L;
    int        index;
  };

  lua_State *L;
};

std::ostream &operator<<(std::ostream &os, const Stack::Element &element);
std::ostream &operator<<(std::ostream &os, const Stack &stack);

}  // namespace lua
}  // namespace xdk

#endif  // XDK_LUA_STACK_H_
