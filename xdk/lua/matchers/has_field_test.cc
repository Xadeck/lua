#include "xdk/lua/matchers/has_field.h"
#include "xdk/lua/matchers/is_number.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"
#include "gtest/gtest-spi.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;
using ::testing::Not;

class HasFieldTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(HasFieldTest, Success) {
  lua_newtable(L);
  lua_pushnumber(L, 3);
  lua_setfield(L, -2, "x");

  auto element = Stack::Element(L, -1);
  EXPECT_THAT(element, HasField("x", IsNumber(3)));
  EXPECT_THAT(element, Not(HasField("x", IsNumber(5))));
  EXPECT_THAT(element, Not(HasField("y", IsNumber(3))));
  EXPECT_THAT(element, HasField("y", _));
}

TEST_F(HasFieldTest, Failure) {
  lua_pushstring(L, "dark ground");
  lua_newtable(L);
  lua_pushnumber(L, 3);
  lua_setfield(L, -2, "x");

  // Case where it's a table where the field is not good.
  auto element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, HasField("x", IsNumber(5))),
      R"(Expected: has field 'x' which is number and is equal to 5)");
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, Not(HasField("x", IsNumber(3)))),
      R"(Expected: doesn't have field 'x' or isn't number or isn't equal to 3)");
  return;
  // Test when not accessing a table
  element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, HasField("x", IsNumber(3))),
      R"(Expected: has field 'x' which is number and is equal to 3)");
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, HasField("x", IsNumber(3))),
      R"(Expected: has field 'x' which is number and is equal to 3)");
  element = Stack::Element(L, 2);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, HasField("x", _)),
                          R"(gettop L:   1)");
}

} // namespace
} // namespace lua
} // namespace xdk
