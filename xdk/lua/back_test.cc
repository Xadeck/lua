#include "xdk/lua/back.h"
#include "xdk/lua/matchers.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"

#include "gtest/gtest.h"

namespace xdk {
namespace lua {
namespace {
class BackTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(BackTest, GetbackIsNilOnEmptyVector) {
  lua_newtable(L);
  getback(L, -1);
  ASSERT_THAT(Stack::Element(L, -1), IsNil());
}

TEST_F(BackTest, BackWorks) {
  lua_newtable(L);
  // Check elements can be pushed.
  for (const char *fruit : {"apple", "banana", "pear"}) {
    lua_pushstring(L, fruit);
    pushback(L, -2);
    // Check pushback has consummed the elements.
    ASSERT_EQ(lua_gettop(L), 1);
  }
  // Check n has increased.
  ASSERT_THAT(Stack::Element(L, -1), HasField("n", IsNumber(3)));
  // Get elements can be get/popped.
  for (const char *fruit : {"pear", "banana", "apple"}) {
    getback(L, -1);
    ASSERT_THAT(Stack::Element(L, -1), IsString(fruit));
    lua_pop(L, 1);
    // Then remove it from the back.
    popback(L, -1);
  }
  // Check n is removed.
  ASSERT_THAT(Stack::Element(L, -1), HasField("n", IsNil()));
}

TEST_F(BackTest, PopbackDoesNothingOnEmptyTable) {
  lua_newtable(L);
  popback(L, -1);
  ASSERT_THAT(Stack::Element(L, -1), HasField("n", IsNil()));
}

TEST_F(BackTest, PushingBackNil) {
  lua_newtable(L);
  lua_pushnil(L);
  pushback(L, -2);
  ASSERT_THAT(Stack::Element(L, -1), HasField("n", IsNumber(1)));
  getback(L, -1);
  ASSERT_THAT(Stack::Element(L, -1), IsNil());
}

} // namespace
} // namespace lua
} // namespace xdk
