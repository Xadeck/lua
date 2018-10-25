#include "xdk/lua/matchers/element.h"
#include "xdk/lua/matchers/is_number.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"
#include "gtest/gtest-spi.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;

class ElementTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(ElementTest, Success) {
  lua_pushinteger(L, 3);

  Stack stack(L);
  EXPECT_THAT(stack, Element(-1, IsNumber(3)));
  EXPECT_THAT(stack, Not(Element(-1, IsNumber(5))));
  EXPECT_THAT(stack, Element(-1, _));
}

TEST_F(ElementTest, Failure) {
  lua_pushinteger(L, 3);

  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(Stack(L), Element(-1, IsNumber(5))),
      R"(Expected: element at index -1 is number and is equal to 5)");
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(Stack(L), Not(Element(-1, IsNumber(3)))),
      R"(Expected: element at index -1 isn't number or isn't equal to 3)");
}

} // namespace
} // namespace lua
} // namespace xdk
