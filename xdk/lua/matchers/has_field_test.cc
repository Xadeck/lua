#include "xdk/lua/matchers/has_field.h"

#include "gtest/gtest-spi.h"
#include "xdk/lua/matchers/is_number.h"
#include "xdk/lua/matchers/is_string.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;
using ::testing::Not;
using ::testing::StrEq;

class HasFieldTest : public ::testing::Test {
 protected:
  State L;
};

TEST_F(HasFieldTest, SuccessForString) {
  lua_newtable(L);
  lua_pushnumber(L, 3);
  lua_setfield(L, -2, "x");

  auto element = Stack::Element(L, -1);
  EXPECT_THAT(element, HasField("x", IsNumber(3)));
  EXPECT_THAT(element, Not(HasField("x", IsNumber(5))));
  EXPECT_THAT(element, Not(HasField("y", IsNumber(3))));
  // Using _ matcher returns true, because it maches nil.
  EXPECT_THAT(element, HasField("y", _));
}

TEST_F(HasFieldTest, SuccessForNumber) {
  lua_newtable(L);
  lua_pushnumber(L, 314);
  lua_pushstring(L, "pi");
  lua_settable(L, -3);

  auto element = Stack::Element(L, -1);
  EXPECT_THAT(element, HasField(314, IsString(StrEq("pi"))));
  EXPECT_THAT(element, Not(HasField(314, IsString(StrEq("gamma")))));
  EXPECT_THAT(element, Not(HasField(159, IsString(StrEq("pi")))));
  // Using _ matcher returns true, because it maches nil.
  EXPECT_THAT(element, HasField(159, _));
}

TEST_F(HasFieldTest, FailureForString) {
  lua_pushstring(L, "dark ground");
  lua_newtable(L);
  lua_pushnumber(L, 3);
  lua_setfield(L, -2, "x");

  // Case where it's a table where the field is not good.
  auto element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, HasField("x", IsNumber(5))),
                          R"(Expected: has field 'x' which is number and is equal to 5)");
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, Not(HasField("x", IsNumber(3)))),
      R"(Expected: doesn't have field 'x' or isn't number or isn't equal to 3)");
  // Test when not accessing a table
  element = Stack::Element(L, 1);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, HasField("x", IsNumber(3))),
                          R"(Expected: has field 'x' which is number and is equal to 3)");
}

TEST_F(HasFieldTest, FailureForNumber) {
  lua_pushstring(L, "dark ground");
  lua_newtable(L);
  lua_pushnumber(L, 314);
  lua_pushstring(L, "pi");
  lua_settable(L, -3);

  // Case where it's a table where the field is not good.
  auto element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, HasField(314, IsString(StrEq("gamma")))),
                          R"(Expected: has field 314 which is string and is equal to "gamma")");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, Not(HasField(314, IsString(StrEq("pi"))))),
                          R"(doesn't have field 314 or isn't string or isn't equal to "pi")");
  // Test when not accessing a table
  element = Stack::Element(L, 1);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, HasField(314, IsString(StrEq("pi")))),
                          R"(has field 314 which is string and is equal to "pi")");
}

TEST_F(HasFieldTest, RecursivelyWorks) {
  lua_newtable(L);
  lua_newtable(L);
  lua_pushnumber(L, 3);
  lua_setfield(L, -2, "x");
  lua_setfield(L, -2, "p");

  EXPECT_THAT(Stack::Element(L, -1), HasField("p", HasField("x", IsNumber(3))));
}

TEST_F(HasFieldTest, MatcherFailure) {
  lua_newtable(L);
  lua_pushnumber(L, 3);
  lua_setfield(L, -2, "x");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(4))),
                          "Field   :   2 [number ] 3");
}

}  // namespace
}  // namespace lua
}  // namespace xdk
