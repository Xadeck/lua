#ifndef XDK_LUA_STATE_H
#define XDK_LUA_STATE_H

#include <lua.hpp>
#include <memory>

namespace xdk {
class State final {
  using Ptr = std::unique_ptr<lua_State, void (*)(lua_State *)>;

public:
  static Ptr New(lua_Alloc alloc = nullptr, void *ud = nullptr);
  operator lua_State *() const { return ptr_.get(); }

private:
  State(Ptr ptr) : ptr_(std::move(ptr)) {}
  const Ptr ptr_;
};
} // namespace xdk

#endif
