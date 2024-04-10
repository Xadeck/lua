#ifndef XDK_LUA_READ_H_
#define XDK_LUA_READ_H_

#include <string>

#include "xdk/lua/lua.hpp"

namespace xdk {
namespace lua {
// Invokes `reader` on L and `data` as long as it returns chunks, and returns
// the concatenated chunks.
std::string Read(lua_Reader reader, lua_State *L, void *data);

}  // namespace lua
}  // namespace xdk
#endif  // XDK_LUA_READ_H_
