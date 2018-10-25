#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"

#include "gtest/gtest.h"

namespace xdk {
namespace lua {
namespace {
class StackTest : public ::testing::Test {
protected:
  StackTest() {
    lua_pushnil(L);
    lua_newtable(L);
    lua_pushinteger(L, 3);
    lua_pushnumber(L, 1.2);
    lua_pushstring(L, R"(some "quoted" text)");
    lua_pushboolean(L, true);
  }
  State L;
};

TEST_F(StackTest, StackElementIsStreamable) {
  std::ostringstream os;
  os << Stack::Element(L, 1);
  EXPECT_EQ(os.str(), "  1 [nil    ] ");
}

TEST_F(StackTest, StackElementOutsideRangeWorks) {
  std::ostringstream os;
  os << Stack::Element(L, 13);
  EXPECT_EQ(os.str(), " 13 [no value] ");
}

TEST_F(StackTest, StackIsStreamable) {
  std::ostringstream os;
  os << Stack(L);
  EXPECT_EQ(os.str(), R"(---
  1 [nil    ] 
  2 [table  ] {...}
  3 [number ] 3
  4 [number ] 1.2
  5 [string ] "some \"quoted\" text"
  6 [boolean] true
)");
}

} // namespace
} // namespace lua
} // namespace xdk
