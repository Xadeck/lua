#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
State::State(lua_Alloc alloc, void *ud)
    : State((alloc != nullptr) ? lua_newstate(alloc, ud) : luaL_newstate()) {}

State::State(lua_State *L)
    : ptr_(L, L != nullptr ? lua_close : [](lua_State *) {}) {}

} // namespace lua
} // namespace xdk
