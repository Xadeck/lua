#include "xdk/lua/matchers/top_is.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"
#include "gtest/gtest-spi.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;
using ::testing::Gt;
using ::testing::Not;

class TopIsTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(TopIsTest, Success) {
  lua_pushinteger(L, 3);
  lua_pushstring(L, "deep blue");

  EXPECT_THAT(Stack(L), TopIs(2));
  EXPECT_THAT(Stack(L), Not(TopIs(3)));
  EXPECT_THAT(Stack(L), TopIs(Gt(1)));
  EXPECT_THAT(Stack(L), TopIs(_));
}

TEST_F(TopIsTest, Failure) {
  lua_pushinteger(L, 3);

  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack(L), TopIs(2)),
                          R"(Expected:  top is equal to 2)");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack(L), Not(TopIs(1))),
                          R"(Expected: top isn't equal to 1)");
}

} // namespace
} // namespace lua
} // namespace xdk
