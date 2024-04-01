#ifndef XDK_LUA_MATCHERS_IS_STRING_H
#define XDK_LUA_MATCHERS_IS_STRING_H

#include <string_view>

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> IsString(::testing::Matcher<std::string_view> matcher);

}  // namespace lua
}  // namespace xdk

#endif
