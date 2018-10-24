#ifndef XDK_LUA_MATCHERS_IS_NUMBER_H
#define XDK_LUA_MATCHERS_IS_NUMBER_H

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> IsNumber(lua_Number value);

} // namespace lua
} // namespace xdk

#endif
