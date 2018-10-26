#include "xdk/lua/state.h"
#include "xdk/lua/string_view.h"

#include "gmock/gmock.h"

namespace xdk {
namespace lua {
namespace {
TEST(StringView, Works) {
  State L;
  lua_pushstring(L, "blue sky");
  lua_pushstring(L, "deep sea");
  lua_pushinteger(L, 3);
  lua_newtable(L);
  EXPECT_EQ(tostring_view(L, 1), "blue sky");
  EXPECT_EQ(tostring_view(L, 2), "deep sea");
  EXPECT_EQ(tostring_view(L, 3), "3");
  EXPECT_EQ(tostring_view(L, 4), "");
}
} // namespace
} // namespace lua
} // namespace xdk
