#include "xdk/lua/matchers/is_number.h"

#include "gtest/gtest-spi.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::Not;

class IsNumberTest : public ::testing::Test {
 protected:
  State L;
};

TEST_F(IsNumberTest, Success) {
  lua_pushinteger(L, 3);

  auto element = Stack::Element(L, -1);
  EXPECT_THAT(element, Not(IsNumber(5)));
  EXPECT_THAT(element, IsNumber(3));
  EXPECT_THAT(element, Not(IsNumber(Lt(0))));
  EXPECT_THAT(element, IsNumber(Gt(0)));
  EXPECT_THAT(element, IsNumber(_));
}

TEST_F(IsNumberTest, Failure) {
  lua_pushinteger(L, 3);

  auto element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, IsNumber(5)),
                          R"(Expected: is number and is equal to 5)");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, Not(IsNumber(3))),
                          R"(Expected: isn't number or isn't equal to 3)");
  // Test that when the index is out of range, stack size is printed.
  element = Stack::Element(L, 2);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, IsNumber(5)), R"(gettop L:   1)");
  // Check that the matcher does not work on non-number, even with _.
  lua_pushstring(L, "blue sky");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack::Element(L, -1), IsNumber(_)),
                          R"(Actual:  -1 [string ] "blue sky")");
}

}  // namespace
}  // namespace lua
}  // namespace xdk
