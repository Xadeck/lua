#include "xdk/lua/state.h"

namespace xdk {
namespace lua {

State::State(lua_Alloc alloc, void *ud) noexcept
    : State((alloc != nullptr) ? lua_newstate(alloc, ud) : luaL_newstate()) {}

State::State(lua_State *L) noexcept
    : ptr_(L, [](lua_State *L) {
        if (L != nullptr) lua_close(L);
      }) {}

}  // namespace lua
}  // namespace xdk
