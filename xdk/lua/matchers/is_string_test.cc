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
#ifdef FOO
TEST_F(IsStringTest, Failure) {
  lua_pushinteger(L, 3);

  auto element = Stack::Element(L, -1);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, IsString("dark ground")),
                          R"(Expected: is number and is equal to 5)");
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, Not(IsString("blue sky"))),
                          R"(Expected: isn't number or isn't equal to 3)");

  element = Stack::Element(L, 2);
  EXPECT_NONFATAL_FAILURE(EXPECT_THAT(element, IsString(_)),
                          R"(gettop L:   1)");
}
#endif

} // namespace
} // namespace lua
} // namespace xdk
