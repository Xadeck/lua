#ifndef XDK_LUA_STATE_H
#define XDK_LUA_STATE_H

#include <memory>

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
class State final {
public:
  State(lua_Alloc alloc = nullptr, void *ud = nullptr);
  State(State &&) = default;
  State &operator=(State &&state) = default;

  operator lua_State *() const { return ptr_.get(); }

private:
  State(lua_State *L);

  std::unique_ptr<lua_State, void (*)(lua_State *)> ptr_;
};
} // namespace lua
} // namespace xdk

#endif
