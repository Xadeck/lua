#include "xdk/lua/matchers.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"
#include "xdk/lua/vector.h"

#include "gtest/gtest.h"

namespace xdk {
namespace lua {
namespace {
class VectorTest : public ::testing::Test {
protected:
  State L;
};

TEST_F(VectorTest, NewAndIsWorks) {
  lua_newtable(L);
  newvector(L);
  ASSERT_FALSE(isvector(L, -2));
  // Check that isvector did not pollute the stack.
  ASSERT_EQ(lua_gettop(L), 2);

  ASSERT_TRUE(isvector(L, -1));
  // Same for when it returns true.
  ASSERT_EQ(lua_gettop(L), 2);
}

TEST_F(VectorTest, BackIsNilOnEmptyVector) {
  newvector(L);
  getback(L, -1);
  ASSERT_THAT(Stack::Element(L, -1), IsNil());
}

TEST_F(VectorTest, BackWorks) {
  newvector(L);
  for (const char *fruit : {"apple", "banana", "pear"}) {
    lua_pushstring(L, fruit);
    pushback(L, -2);
    // Check pushback has consummed the elements.
    ASSERT_EQ(lua_gettop(L), 1);
  }
  for (const char *fruit : {"pear", "banana", "apple"}) {
    // Get the back element and check its value.
    getback(L, -1);
    ASSERT_THAT(Stack::Element(L, -1), IsString(fruit));
    lua_pop(L, 1);
    // Then remove it from the back.
    popback(L, -1);
  }
}

TEST_F(VectorTest, PushbackWorksOnTable) {
  lua_newtable(L);
  lua_pushstring(L, "tomato");
  pushback(L, -2);
  lua_pushstring(L, "potato");
  pushback(L, -2);
  ASSERT_THAT(Stack::Element(L, -1), HasField("n", IsNumber(2)));
  ASSERT_THAT(Stack::Element(L, -1), HasField(1, IsString("tomato")));
  ASSERT_THAT(Stack::Element(L, -1), HasField(2, IsString("potato")));
}

TEST_F(VectorTest, GetbackReturnsNilOnTable) {
  lua_newtable(L);
  getback(L, -1);
  ASSERT_EQ(lua_gettop(L), 2);
  ASSERT_THAT(Stack::Element(L, -1), IsNil());
}

TEST_F(VectorTest, PopbackDoesNothingOnTable) {
  lua_newtable(L);
  popback(L, -1);
}
} // namespace
} // namespace lua
} // namespace xdk
