#ifndef XDK_LUA_MATCHERS_ELEMENT_H
#define XDK_LUA_MATCHERS_ELEMENT_H

#include "xdk/lua/stack.h"
#include "gmock/gmock.h"

namespace xdk {
namespace lua {

::testing::Matcher<const Stack &>
Element(int index, const ::testing::Matcher<const Stack::Element &> &matcher);

}
} // namespace xdk

#endif
