#include "xdk/lua/matchers/is_nil.h"

#include "gtest/gtest-spi.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::Not;

class IsNilTest : public ::testing::Test {
 protected:
  State L;
};

TEST_F(IsNilTest, Success) {
  lua_pushstring(L, "blue sky");
  lua_pushnil(L);

  EXPECT_THAT(Stack::Element(L, -2), Not(IsNil()));
  EXPECT_THAT(Stack::Element(L, -1), IsNil());
}

TEST_F(IsNilTest, Failure) {
  lua_pushstring(L, "blue sky");
  lua_pushnil(L);

  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack::Element(L, -2), IsNil()), R"(Expected: is nil)");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack::Element(L, -1), Not(IsNil())),
                          R"(Expected: isn't nil)");
  // Test that when the index is out of range, stack size is printed.
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack::Element(L, 3), IsNil()), R"(gettop L:   2)");
}

}  // namespace
}  // namespace lua
}  // namespace xdk
