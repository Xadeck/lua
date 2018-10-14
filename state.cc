#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
State::Ptr State::New(lua_Alloc alloc, void *ud) {
  lua_State *L = (alloc != nullptr) ? lua_newstate(alloc, ud) : luaL_newstate();
  return (L != nullptr) ? Ptr(L, lua_close) : Ptr(nullptr, [](lua_State *) {});
}
} // namespace lua
} // namespace xdk
