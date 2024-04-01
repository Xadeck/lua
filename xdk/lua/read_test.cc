#include "xdk/lua/read.h"

#include <list>

#include "gtest/gtest.h"
#include "xdk/lua/state.h"

namespace xdk {
namespace lua {
namespace {

const char *NextChunkOrNull(lua_State *L, void *data, size_t *size) {
  auto *chunks = reinterpret_cast<std::list<const char *> *>(data);
  if (chunks->empty()) {
    return nullptr;
  }
  const char *chunk = chunks->front();
  *size             = strlen(chunk);
  chunks->pop_front();
  return chunk;
}
const char *NextChunkOrSizeZero(lua_State *L, void *data, size_t *size) {
  auto *chunks = reinterpret_cast<std::list<const char *> *>(data);
  if (chunks->empty()) {
    *size = 0;
    return "not null";
  }
  const char *chunk = chunks->front();
  *size             = strlen(chunk);
  chunks->pop_front();
  return chunk;
}

TEST(Read, WorksWhenReaderReturnsNull) {
  std::list<const char *> chunks{"Hello", " world!", " How are you?"};
  State                   L;
  EXPECT_EQ(Read(NextChunkOrNull, L, &chunks), "Hello world! How are you?");
}

TEST(Read, WorksWhenReaderReturnsSizeZero) {
  std::list<const char *> chunks{"Hello", " world!", " How are you?"};
  State                   L;
  EXPECT_EQ(Read(NextChunkOrSizeZero, L, &chunks), "Hello world! How are you?");
}

}  // namespace
}  // namespace lua
}  // namespace xdk
