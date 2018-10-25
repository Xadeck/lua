#ifndef XDK_LUA_MATCHERS_IS_NIL_H
#define XDK_LUA_MATCHERS_IS_NIL_H

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> IsNil();

} // namespace lua
} // namespace xdk

#endif
