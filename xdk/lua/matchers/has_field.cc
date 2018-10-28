#include "xdk/lua/matchers/has_field.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

namespace {
void Push(lua_State *L, const char *value) { lua_pushstring(L, value); }
void Push(lua_State *L, lua_Number value) { lua_pushnumber(L, value); }
void DescribeKey(std::ostream *os, const char *key) {
  *os << '\'' << key << '\'';
}
void DescribeKey(std::ostream *os, lua_Number key) { *os << key; }

template <typename T>
struct HasFieldMatcher final
    : public ::testing::MatcherInterface<const Stack::Element &> {
  const T key;
  const Matcher<const Stack::Element &> matcher;

  explicit HasFieldMatcher(const T &key,
                           const Matcher<const Stack::Element &> &matcher)
      : key(key), matcher(matcher) {}

  void DescribeTo(std::ostream *os) const final {
    *os << "has field ";
    DescribeKey(os, key);
    *os << " which ";
    matcher.DescribeTo(os);
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "doesn't have field ";
    DescribeKey(os, key);
    *os << " or ";
    matcher.DescribeNegationTo(os);
  }

  bool MatchAndExplain(const Stack::Element &element,
                       MatchResultListener *result_listener) const final {
    lua_State *L = element.L;
    int index = lua_absindex(L, element.index);
    if (lua_type(L, index) != LUA_TTABLE) {
      return false;
    }
    Push(L, key);
    lua_gettable(L, index);
    auto field_element = Stack::Element(L, lua_gettop(L));
    if (!matcher.MatchAndExplain(field_element, result_listener)) {
      *result_listener << "\nField   : " << field_element;
      lua_pop(L, 1);
      return false;
    }
    lua_pop(L, 1);
    return true;
  }
};
} // namespace

Matcher<const Stack::Element &>
HasField(const char *key, Matcher<const Stack::Element &> matcher) {
  return MakeMatcher(new HasFieldMatcher<const char *>(key, matcher));
}

Matcher<const Stack::Element &>
HasField(lua_Number key, Matcher<const Stack::Element &> matcher) {
  return MakeMatcher(new HasFieldMatcher<lua_Number>(key, matcher));
}

} // namespace lua
} // namespace xdk
