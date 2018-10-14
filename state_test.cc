#include "xdk/lua/state.h"
#include "gtest/gtest.h"

namespace xdk {
namespace lua {
namespace {

void *FailingAllocator(void *ud, void *ptr, size_t osize, size_t nsize) {
  return nullptr;
}

void *InstrumentedAllocator(void *ud, void *ptr, size_t osize, size_t nsize) {
  (*reinterpret_cast<std::function<void()> *>(ud))();
  if (nsize == 0) {
    free(ptr);
    return nullptr;
  }
  return realloc(ptr, nsize);
}

TEST(StateTest, CanBeAllocatedSimply) {
  auto L = State::New();
  ASSERT_NE(L, nullptr);
}

TEST(StateTest, ReturnsNullIfCannotBeAllocated) {
  auto L = State::New(FailingAllocator);
  ASSERT_EQ(L, nullptr);
}

TEST(StateTest, AllocatorIsInvoked) {
  int n = 0;
  std::function<void()> instrumentation = [&n]() { ++n; };
  auto L = State::New(InstrumentedAllocator, &instrumentation);
  ASSERT_NE(L, nullptr);
  ASSERT_EQ(n, 54);
}

} // namespace
} // namespace lua
} // namespace xdk
