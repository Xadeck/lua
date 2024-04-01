#ifndef XDK_LUA_MATCHERS_IS_STRING_H
#define XDK_LUA_MATCHERS_IS_STRING_H

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"
#include <string_view>

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &>
IsString(::testing::Matcher<std::string_view> matcher);

} // namespace lua
} // namespace xdk

#endif
