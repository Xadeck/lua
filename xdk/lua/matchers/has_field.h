#ifndef XDK_LUA_MATCHERS_HAS_FIELD_H_
#define XDK_LUA_MATCHERS_HAS_FIELD_H_

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> HasField(
    const char *key, ::testing::Matcher<const Stack::Element &> matcher);

::testing::Matcher<const Stack::Element &> HasField(
    lua_Number key, ::testing::Matcher<const Stack::Element &> matcher);

}  // namespace lua
}  // namespace xdk

#endif
