#ifndef XDK_LUA_MATCHERS_ELEMENT_H_
#define XDK_LUA_MATCHERS_ELEMENT_H_

#include "gmock/gmock.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack &> Element(
    int index, const ::testing::Matcher<const Stack::Element &> &matcher);

}
}  // namespace xdk

#endif  // XDK_LUA_MATCHERS_ELEMENT_H_
