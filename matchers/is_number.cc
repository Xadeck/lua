#include "xdk/lua/matchers/is_number.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

namespace {
struct IsNumberMatcher final
    : public ::testing::MatcherInterface<const Stack::Element &> {
  const lua_Number value;

  explicit IsNumberMatcher(lua_Number value) : value(value) {}

  void DescribeTo(std::ostream *os) const final {
    *os << "is number " << value << " ";
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "is not number " << value << " ";
  }

  bool MatchAndExplain(const Stack::Element &element,
                       MatchResultListener *result_listener) const final {
    lua_State *L = element.L;
    int index = element.index;
    if (!lua_isnumber(L, index)) {
      *result_listener << "expected LUA_NUMBER, got "
                       << lua_typename(L, lua_type(L, index));
      return false;
    }
    lua_Number actual_value = lua_tonumber(L, index);
    if (actual_value != value) {
      *result_listener << "expected " << value << ", got " << actual_value;
      return false;
    }
    return true;
  }
};
} // namespace

Matcher<const Stack::Element &> IsNumber(lua_Number value) {
  return MakeMatcher(new IsNumberMatcher(value));
}

} // namespace lua
} // namespace xdk
