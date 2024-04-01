#include "xdk/lua/rawfield.h"

#include "gtest/gtest.h"
#include "xdk/lua/matchers.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::StrEq;

int getvar(lua_State *L) {
  float *const var = reinterpret_cast<float *>(lua_touserdata(L, lua_upvalueindex(1)));
  lua_pushnumber(L, *var);
  return 1;
}
int setvar(lua_State *L) {
  float *const var = reinterpret_cast<float *>(lua_touserdata(L, lua_upvalueindex(1)));
  *var             = lua_tonumber(L, 3);
  return 0;
}

class TableTest : public ::testing::Test {
 protected:
  TableTest() {
    lua_newtable(L);
    // Create a metatable
    lua_newtable(L);
    lua_pushlightuserdata(L, &var_);
    lua_pushcclosure(L, getvar, 1);
    lua_setfield(L, -2, "__index");
    lua_pushlightuserdata(L, &var_);
    lua_pushcclosure(L, setvar, 1);
    lua_setfield(L, -2, "__newindex");
    lua_setmetatable(L, -2);
  }
  lua::State L;
  float      var_ = 0;
};

TEST_F(TableTest, GetFieldUsesMetamethod) {
  var_ = 1.0;
  lua_getfield(L, -1, "x");
  ASSERT_THAT(Stack::Element(L, -1), IsNumber(1.0));
  lua_pop(L, 1);
}

TEST_F(TableTest, SetFieldUsesMetamethod) {
  lua_pushnumber(L, 2.0);
  lua_setfield(L, -2, "y");
  ASSERT_EQ(var_, 2.0);
}

TEST_F(TableTest, RawGetFieldWorks) {
  lua_pushstring(L, "z");
  lua_pushnumber(L, 3.0);
  lua_rawset(L, -3);
  ASSERT_EQ(var_, 0.0);  // no metamethod triggered.

  rawgetfield(L, -1, "z");
  ASSERT_THAT(Stack::Element(L, -1), IsNumber(3.0));
}

TEST_F(TableTest, RawSetFieldWorks) {
  lua_pushnumber(L, 3.0);
  rawsetfield(L, -2, "z");
  ASSERT_EQ(var_, 0.0);  // no metamethod triggered.

  lua_pushstring(L, "z");
  lua_rawget(L, -2);
  ASSERT_THAT(Stack::Element(L, -1), IsNumber(3.0));
}

TEST_F(TableTest, RawSetFieldNilWorks) {
  rawsetfieldnil(L, -1, "w");
  rawgetfield(L, -1, "w");
  ASSERT_THAT(Stack::Element(L, -1), IsNil());
}

TEST_F(TableTest, RawSetFieldNewtableWorks) {
  rawsetfieldnewtable(L, -1, "w");
  rawgetfield(L, -1, "w");
  ASSERT_TRUE(lua_istable(L, -1));
}

TEST_F(TableTest, RawSetFieldStringWorks) {
  rawsetfieldstring(L, -1, "w", "text");
  rawgetfield(L, -1, "w");
  ASSERT_THAT(Stack::Element(L, -1), IsString(StrEq("text")));
}

TEST_F(TableTest, RawSetFieldNumberWorks) {
  rawsetfieldnumber(L, -1, "w", 3.0);
  rawgetfield(L, -1, "w");
  ASSERT_THAT(Stack::Element(L, -1), IsNumber(3.0));
}

}  // namespace
}  // namespace lua
}  // namespace xdk
