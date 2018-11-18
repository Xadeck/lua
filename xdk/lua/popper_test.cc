#include "xdk/lua/popper.h"
#include "xdk/lua/state.h"
#include "gtest/gtest.h"

namespace xdk {
namespace lua {
namespace {

TEST(PopperTest, Works) {
  State L;
  lua_pushstring(L, "a");
  {
    Popper popper(L, 2);
    lua_pushstring(L, "b");
    lua_pushstring(L, "c");
  }
  EXPECT_EQ(lua_gettop(L), 1);
}

} // namespace

} // namespace lua
} // namespace xdk
