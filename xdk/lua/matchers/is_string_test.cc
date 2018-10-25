#include "xdk/lua/matchers/is_string.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"
#include "gtest/gtest-spi.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;
using ::testing::HasSubstr;
using ::testing::Not;

class IsStringTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(IsStringTest, Success) {
  lua_pushstring(L, "blue sky");

  auto element = Stack::Element(L, -1);
  EXPECT_THAT(element, Not(IsString("dark ground")));
  EXPECT_THAT(element, IsString("blue sky"));
  EXPECT_THAT(element, Not(IsString(HasSubstr("ground"))));
  EXPECT_THAT(element, IsString(HasSubstr("sky")));
  EXPECT_THAT(element, IsString(_));
}
TEST_F(IsStringTest, Failure) {
  lua_pushstring(L, "blue sky");

  auto element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, IsString("dark ground")),
      R"(Expected: is string and is equal to "dark ground")");
  EXPECT_NONFATAL_FAILURE(
      EXPECT_THAT(element, Not(IsString("blue sky"))),
      R"(Expected: isn't string or isn't equal to "blue sky")");

  element = Stack::Element(L, 2);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, IsString(_)),
                          R"(gettop L:   1)");
}

} // namespace
} // namespace lua
} // namespace xdk
