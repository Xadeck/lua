#ifndef XDK_LUA_MATCHERS_IS_NIL_H
#define XDK_LUA_MATCHERS_IS_NIL_H

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack::Element &> IsNil();

}  // namespace lua
}  // namespace xdk

#endif
