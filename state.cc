#include "state.h"

namespace xdk {
State::Ptr State::New(lua_Alloc alloc, void *ud) {
  lua_State *L = (alloc != nullptr) ? lua_newstate(alloc, ud) : luaL_newstate();
  return (L != nullptr) ? Ptr(L, lua_close) : Ptr(nullptr, [](lua_State *) {});
}
} // namespace xdk
