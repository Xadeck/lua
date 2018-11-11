#ifndef XDK_LUA_SANDBOX_H_
#define XDK_LUA_SANDBOX_H_

#include "xdk/lua/lua.hpp"

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

// Takes table at `index` on the stack, and pushes a sandbox wrapping it.
void newsandbox(lua_State *L, int index) noexcept;

} // namespace lua
} // namespace xdk

#endif // XDK_LUA_SANDBOX_H_
