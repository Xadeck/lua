#include "xdk/lua/state.h"

#include <utility>

#include "gtest/gtest.h"

namespace xdk {
namespace lua {
namespace {

void *FailingAllocator(void *ud, void *ptr, size_t osize, size_t nsize) {
  return nullptr;
}

void *InstrumentedAllocator(void *ud, void *ptr, size_t osize, size_t nsize) {
  int *const n  = reinterpret_cast<int *>(ud);
  *n           -= (ptr ? 1 : 0) * osize;
  *n           += nsize;

  if (nsize == 0) {
    free(ptr);
    return nullptr;
  }
  return realloc(ptr, nsize);
}

TEST(StateTest, CanBeAllocatedAndUsedSimply) {
  State L;
  ASSERT_NE(L, nullptr);
  ASSERT_EQ(lua_gettop(L), 0);
  lua_pushinteger(L, 1);
  ASSERT_EQ(lua_gettop(L), 1);
}

TEST(StateTest, ReturnsNullIfCannotBeAllocated) {
  State L(FailingAllocator);
  ASSERT_EQ(L, nullptr);
}

TEST(StateTest, AllocatorIsInvoked) {
  int n = 0;
  {
    State L(InstrumentedAllocator, &n);
    ASSERT_NE(L, nullptr);
    // Some memory has been allocated for the state.
    // Perform a full garbage collect first to tighten loose ends.
    lua_gc(L, LUA_GCCOLLECT, 0);
    EXPECT_GT(n, 0);
    // Pushing a (long enough) string will allocate more.
    int n_before = n;
    lua_pushstring(L, "a long enough string");
    EXPECT_LT(n_before, n);
  }
  // Once state goes out of scope, all memory is freed.
  EXPECT_EQ(n, 0);
}

TEST(StateTest, StateCanBeMoved) {
  auto func = [](State &&L) {
    EXPECT_EQ(lua_gettop(L), 0);
    lua_pushinteger(L, 5);
    EXPECT_EQ(lua_gettop(L), 1);
  };
  State L;
  func(std::move(L));
}

TEST(StateTest, StateCanBeMoveAssigned) {
  auto L = State();
  ASSERT_EQ(lua_gettop(L), 0);
}

}  // namespace
}  // namespace lua
}  // namespace xdk
