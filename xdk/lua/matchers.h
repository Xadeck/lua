#ifndef XDK_LUA_MATCHERS_H_
#define XDK_LUA_MATCHERS_H_

#include <string_view>

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack &> TopIs(::testing::Matcher<int> matcher);

::testing::Matcher<const Stack::Element &> IsNumber(const ::testing::Matcher<lua_Number> &matcher);
::testing::Matcher<const Stack::Element &> IsString(::testing::Matcher<std::string_view> matcher);
::testing::Matcher<const Stack::Element &> IsNil();

::testing::Matcher<const Stack::Element &> HasField(
    const char *key, ::testing::Matcher<const Stack::Element &> matcher);
::testing::Matcher<const Stack::Element &> HasField(
    lua_Number key, ::testing::Matcher<const Stack::Element &> matcher);

::testing::Matcher<const Stack &> Element(
    int index, const ::testing::Matcher<const Stack::Element &> &inner_matcher);

}  // namespace lua
}  // namespace xdk

#endif  // XDK_LUA_MATCHERS_H_
