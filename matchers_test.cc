#include "xdk/lua/matchers.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"
#include "gtest/gtest-spi.h"

namespace xdk {
namespace lua {
namespace {

class MatchersTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(MatchersTest, Works) {
  lua_pushinteger(L, 3);
  lua_newtable(L);
  lua_pushinteger(L, 4);
  lua_setfield(L, -2, "x");
  EXPECT_THAT(Stack::Element(L, 1), IsNumber(3));
  EXPECT_THAT(Stack(L), Element(1, IsNumber(3)));
}

} // namespace
} // namespace lua
} // namespace xdk
