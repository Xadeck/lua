#ifndef XDK_LUA_STATE_H
#define XDK_LUA_STATE_H

#include <memory>

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// C++ wrapper around the C-style lua_State class, so that deallocation is
// automatically handled, particularly in the case of multiple exit paths,
// as in the example below.
//
//   lua::State L;
//
//   // ... some code using L
//   lua_getboolean(L, 0);
//
//   // Early exit path, L is properly deleted.
//   if (some_condition) {
//     return fale;
//   }
//
//   // Other exit path, L is deleted too.
//   return true;
class State final {
 public:
  State(lua_Alloc alloc = nullptr, void *ud = nullptr) noexcept;

  operator lua_State *() const noexcept { return ptr_.get(); }

 private:
  explicit State(lua_State *L) noexcept;

  std::unique_ptr<lua_State, void (*)(lua_State *)> ptr_;
};
}  // namespace lua
}  // namespace xdk

#endif
