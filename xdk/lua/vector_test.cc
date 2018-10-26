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
  ASSERT_TRUE(isvector(L, -1));
}

TEST_F(VectorTest, BackWorks) {
  newvector(L);
  for (const char *fruit : {"apple", "banana", "pear"}) {
    lua_pushstring(L, fruit);
    pushback(L, -2);
    ASSERT_EQ(lua_gettop(L), 1);
  }
  for (const char *fruit : {"pear", "banana", "apple"}) {
    getback(L, -1);
    ASSERT_THAT(Stack::Element(L, -1), IsString(fruit));
    lua_pop(L, 1);
    popback(L, -1);
  }
}

} // namespace
} // namespace lua
} // namespace xdk
