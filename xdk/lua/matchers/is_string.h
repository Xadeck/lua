#ifndef XDK_LUA_MATCHERS_IS_STRING_H
#define XDK_LUA_MATCHERS_IS_STRING_H

#include "absl/strings/string_view.h"
#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &>
IsString(::testing::Matcher<absl::string_view> matcher);

} // namespace lua
} // namespace xdk

#endif
