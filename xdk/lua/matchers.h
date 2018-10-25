#ifndef XDK_LUA_MATCHERS_H
#define XDK_LUA_MATCHERS_H

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &>
IsNumber(const ::testing::Matcher<lua_Number> &matcher);
::testing::Matcher<const Stack::Element &>
IsString(::testing::Matcher<absl::string_view> matcher);

::testing::Matcher<const Stack::Element &>
HasField(const char *name, ::testing::Matcher<const Stack::Element &> matcher);

::testing::Matcher<const Stack &>
Element(int index,
        const ::testing::Matcher<const Stack::Element &> &inner_matcher);
} // namespace lua
} // namespace xdk

#endif
