#include "xdk/lua/sandbox.h"

namespace xdk {
namespace lua {

void newsandbox(lua_State *L, int index) noexcept {
  index = lua_absindex(L, index);
  // Create an empty table. That's where every lookup/assignment done by a
  // function which has the sandbox as its environment will happen.
  lua_newtable(L);
  // Create a metatable that looks up unknown fields in the value that was on
  // the stack when the sandbox is created.
  lua_newtable(L);
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, index);
  lua_rawset(L, -3);
  // Copies the __newindex from base, so one can prevent assignment.
  // The sandbox can then also be sandboxed and _newindex will be propagated.
  lua_getfield(L, index, "__newindex");
  lua_pushliteral(L, "__newindex");
  lua_insert(L, -2);
  lua_rawset(L, -3);
  // Set that as the metatable
  lua_setmetatable(L, -2);
}

} // namespace lua
} // namespace xdk
