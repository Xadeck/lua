#ifndef XDK_LUA_MATCHERS_HAS_FIELD_H_
#define XDK_LUA_MATCHERS_HAS_FIELD_H_

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &>
HasField(const char *name, ::testing::Matcher<const Stack::Element &> matcher);

} // namespace lua
} // namespace xdk

#endif
