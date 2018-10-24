#ifndef XDK_LUA_SANDBOX_H_
#define XDK_LUA_SANDBOX_H_

#include "lua.hpp"

namespace xdk {
namespace lua {

// In lua, a function *environment* is a table that defines the globals
// that can get/set during the evaluation of a chunk of code.
//
// A sandbox is a wrapper around such a table, called *base*, that:
// - has the same key/values
// - can override key/values without modifying the base table:
//   * you can't re-assign a base key
//   * you can't assign a new base key
//   * BUT you can change fields of a base key, which is the mechanism
//     to use for sandboxed code to "communicate back".
// - respects the base's __newindex, which can be used to prevent
//   certain or all assignments.
// - is stored in the lua registry for easy retrieval from closure.
//

// Takes the table at `index` on the stack, and creates a sandbox. Returns a
// reference that can be used by lua_getsandbox() to retrieve that sandbox.
int newsandbox(lua_State *L, int index);
// Retrieve a sandbox that was created by lua_newsandbox(L).
void getsandbox(lua_State *L, int sandbox);
// Frees the reference held by sandbox. After that, calling lua_getsandbox()
// will return 0.
void closesandbox(lua_State *L, int sandbox);

} // namespace lua
} // namespace xdk

#endif // XDK_LUA_SANDBOX_H_
