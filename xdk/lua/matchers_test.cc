#include "xdk/lua/matchers.h"
#include "xdk/lua/stack.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::AllOf;
using ::testing::StrEq;

TEST(Matchers, WrapUp) {
  State L;
  lua_pushinteger(L, 1);
  lua_pushstring(L, "two");
  lua_newtable(L);
  lua_pushinteger(L, 3);
  lua_setfield(L, -2, "three");
  lua_pushnil(L);
  EXPECT_THAT(Stack(L), AllOf(Element(1, IsNumber(1)),            //
                              Element(2, IsString(StrEq("two"))), //
                              Element(3, HasField("three", IsNumber(3))),
                              Element(4, IsNil())));
}

} // namespace
} // namespace lua
} // namespace xdk
