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

TEST_F(StackTest, DebugWorks) {
  std::ostringstream os;
  os << Stack::Debug(L);
  ASSERT_EQ(os.str(), R"(---
 -6:     nil=nil
 -5:   table={...}
 -4:  number=3
 -3:  number=1.2
 -2:  string="some \"quoted\" text"
 -1: boolean=true)");
}

TEST_F(StackTest, ValuesWorks) {
  std::ostringstream os;
  os << Stack::Values(L);
  ASSERT_EQ(os.str(), R"(nil, {...}, 3, 1.2, "some \"quoted\" text", true)");
}

} // namespace
} // namespace lua
} // namespace xdk
