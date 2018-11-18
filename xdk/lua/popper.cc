#include "xdk/lua/popper.h"

namespace xdk {
namespace lua {

Popper::Popper(lua_State *L, int n) : L(L), n(n) {}
Popper::~Popper() { lua_pop(L, n); }

} // namespace lua
} // namespace xdk
