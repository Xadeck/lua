#include "xdk/lua/sandbox.h"

namespace xdk {
namespace lua {

int lua_newsandbox(lua_State *L) {
  // Create an empty table. That's where every lookup/assignment done by a
  // function which has the sandbox as its environment will happen.
  lua_newtable(L);
  // Create a metatable that looks up unknown fields in the value that was on
  // the stack when the sandbox is created.
  lua_newtable(L);
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -4);
  lua_rawset(L, -3);
  // Copies the __newindex from base, so one can prevent assignment.
  // The sandbox can then also be sandboxed and _newindex will be propagated.
  lua_getfield(L, -3, "__newindex");
  lua_pushliteral(L, "__newindex");
  lua_insert(L, -2);
  lua_rawset(L, -3);
  // Set that as the metatable
  lua_setmetatable(L, -2);
  // Save in the registry so that it can be retrieved.
  return luaL_ref(L, LUA_REGISTRYINDEX);
}

void lua_getsandbox(lua_State *L, int sandbox) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, sandbox);
}

void lua_closesandbox(lua_State *L, int sandbox) {
  luaL_unref(L, LUA_REGISTRYINDEX, sandbox);
}

} // namespace lua
} // namespace xdk
