#ifndef XDK_LUA_MATCHERS_IS_NUMBER_H_
#define XDK_LUA_MATCHERS_IS_NUMBER_H_

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> IsNumber(const ::testing::Matcher<lua_Number> &matcher);

}  // namespace lua
}  // namespace xdk

#endif  // XDK_LUA_MATCHERS_IS_NUMBER_H_
