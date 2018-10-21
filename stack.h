#ifndef XDK_LUA_STACK_H
#define XDK_LUA_STACK_H

#include <iostream>
#include <lua.hpp>

namespace xdk {
namespace lua {

class Stack final {
public:
  static Stack Debug(lua_State *L);
  static Stack Values(lua_State *L);

private:
  friend std::ostream &operator<<(std::ostream &os,
                                  const ::xdk::lua::Stack &debug);
  Stack(lua_State *L, bool show_header, bool show_type, const char *separator)
      : L_(L), show_header_(show_header), show_type_(show_type),
        separator_(separator) {}
  lua_State *const L_;
  const bool show_header_;
  const bool show_type_;
  const char *const separator_;
};

} // namespace lua
} // namespace xdk

// std::ostream &operator<<(std::ostream &os, const ::xdk::lua::Stack &debug);

#endif
