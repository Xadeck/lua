#ifndef XDK_LUA_MATCHERS_H
#define XDK_LUA_MATCHERS_H

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> IsNumber(lua_Number value);

::testing::Matcher<const Stack &>
Element(int index,
        const ::testing::Matcher<const Stack::Element &> &inner_matcher);
} // namespace lua
} // namespace xdk

#endif
