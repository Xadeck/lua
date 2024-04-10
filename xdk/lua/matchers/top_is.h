#ifndef XDK_LUA_MATCHERS_TOP_IS_H_
#define XDK_LUA_MATCHERS_TOP_IS_H_

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack &> TopIs(::testing::Matcher<int> matcher);

}  // namespace lua
}  // namespace xdk

#endif  // XDK_LUA_MATCHERS_TOP_IS_H_
