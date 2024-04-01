#include "xdk/lua/sandbox.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "xdk/lua/matchers.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

using ::testing::_;
using ::testing::HasSubstr;
using ::testing::StrEq;

class SandboxTest : public testing::Test {
 protected:
  SandboxTest() {
    // Create a table with field x=3
    lua_newtable(L);
    lua_pushnumber(L, 3);
    lua_setfield(L, -2, "x");
  }

  State L;
};

TEST_F(SandboxTest, CanBeCreatedAtAnyIndex) {
  lua_pushliteral(L, "filling the stack");
  lua_pushliteral(L, "so table is at -3");
  // Test the sandbox can be created on the table
  // using both relative and absolute indices.
  for (int index : {-3, 1}) {
    SCOPED_TRACE(index);
    newsandbox(L, -3);
    ASSERT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(3)));
    lua_pop(L, 1);
  }
}

TEST_F(SandboxTest, HasNoStandardFunctions) {
  newsandbox(L, -1);

  for (const char *name :
       {"require", "print", "setmetatable", "getmetatable", "rawset", "rawget"}) {
    ASSERT_THAT(Stack::Element(L, -1), HasField(name, IsNil()));
  }
}

TEST_F(SandboxTest, BaseFieldsCanBeAccessedAndOverridden) {
  newsandbox(L, -1);
  // Checks we can access 'x' from the base.
  ASSERT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(3)));
  // Checks we can set it to a different value.
  lua_pushnumber(L, 4);
  lua_setfield(L, -2, "x");
  // If we access it, we get the new value.
  ASSERT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(4)));
  // But if we pop the sandbox (so the initial table is now on top) and try to
  // get x, then we have the old value.
  lua_pop(L, 1);
  ASSERT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(3)));
}

TEST_F(SandboxTest, BaseTablesAreModifiable) {
  // Creates an empty base 'data' table.
  lua_newtable(L);
  lua_setfield(L, -2, "data");
  // Create a sandbox, access base 'data' and set y=5 in it.
  newsandbox(L, -1);
  lua_getfield(L, -1, "data");
  lua_pushnumber(L, 5);
  lua_setfield(L, -2, "y");
  // Pops 'data' and the sandbox, and check that base has x=5.
  lua_pop(L, 2);
  EXPECT_EQ(lua_gettop(L), 1);  // To make sure we check base.
  ASSERT_THAT(Stack::Element(L, -1), HasField("data", HasField("y", IsNumber(5))));
}

TEST_F(SandboxTest, WorksAsChunkEnvironment) {
  newsandbox(L, -1);
  // Loads a chunk of code.
  const char source[] = "x = x + 5";
  ASSERT_EQ(luaL_loadstring(L, source), 0);
  // Sets a sandbox as its upvalue, and evaluates.
  lua_pushvalue(L, -2);
  lua_setupvalue(L, -2, 1);
  ASSERT_EQ(lua_pcall(L, 0, 0, 0), 0) << lua_tostring(L, -1);
  // Check that x is unmodified in the default environment.
  ASSERT_THAT(Stack::Element(L, -2), HasField("x", IsNumber(3)));
  // But if we get the sandbox, then we can see it has the right value.
  ASSERT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(8)));
}

int Source(lua_State *L) {
  lua_pushvalue(L, lua_upvalueindex(1));
  lua_getfield(L, -1, "x");
  lua_pushnumber(L, lua_tonumber(L, -1) + 5);
  lua_setfield(L, -3, "x");
  return 0;
}

TEST_F(SandboxTest, WorksAsClosureEnvironment) {
  newsandbox(L, -1);
  // Pushes a C closure with the sandbox as its upvalue and evaluates it.
  lua_pushvalue(L, -1);
  lua_pushcclosure(L, &Source, 1);
  ASSERT_EQ(lua_pcall(L, 0, 0, 0), 0) << lua_tostring(L, -1);
  // Checks that x is unmodified in the default environment.
  ASSERT_THAT(Stack::Element(L, -2), HasField("x", IsNumber(3)));
  // But if we get the sandbox, then we can see it has the right value.
  ASSERT_THAT(Stack::Element(L, -1), HasField("x", IsNumber(8)));
}

int NoAssignment(lua_State *L) {
  lua_pushstring(L, "Assignement not allowed");
  return lua_error(L);
}

TEST_F(SandboxTest, NewIndexCanBeUsedToControlAssignements) {
  lua_pushcclosure(L, NoAssignment, 0);
  lua_setfield(L, -2, "__newindex");
  ASSERT_EQ(lua_gettop(L), 1);
  // It is possible to set a field from C code.  with rawset (trying to use
  // setfield would PANIC crash).
  newsandbox(L, -1);
  lua_pushstring(L, "y");
  lua_pushnumber(L, 3);
  lua_rawset(L, -3);
  // But from lua code you can't do it, and rawset is not available (see
  // HasNoStandardFunctions test). Note we use z and not y` ....
  {
    const char source[] = "z = 4";
    ASSERT_EQ(luaL_loadstring(L, source), 0);
    lua_pushvalue(L, -2);
    lua_setupvalue(L, -2, 1);
    ASSERT_NE(lua_pcall(L, 0, 0, 0), 0);
    ASSERT_THAT(Stack::Element(L, -1), IsString(HasSubstr("Assignement not allowed")));
    lua_pop(L, 1);
  }
  // ...because it would work for y since it already exists in the table
  // so the metatable is not invoked.
  {
    const char source[] = "y = 5";
    ASSERT_EQ(luaL_loadstring(L, source), 0);
    lua_pushvalue(L, -2);
    lua_setupvalue(L, -2, 1);
    ASSERT_EQ(lua_pcall(L, 0, 0, 0), 0) << lua_tostring(L, -1);
    ASSERT_THAT(Stack::Element(L, -1), HasField("y", IsNumber(5)));
  }
  // So if you want to prevent the modification of existing y, you must stack
  // sandboxes. NOTE: This works because metamethod __newindex is propagated.
  {
    lua_pushvalue(L, -1);
    newsandbox(L, -1);
    const char source[] = "y = 6";
    ASSERT_EQ(luaL_loadstring(L, source), 0);
    lua_pushvalue(L, -2);
    lua_setupvalue(L, -2, 1);
    ASSERT_NE(lua_pcall(L, 0, 0, 0), 0);
    ASSERT_THAT(Stack::Element(L, -1), IsString(StrEq("Assignement not allowed")));
    lua_pop(L, 2);  // sandbox and error message.
  }
}

}  // namespace
}  // namespace lua
}  // namespace xdk
