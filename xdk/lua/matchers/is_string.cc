#include "xdk/lua/matchers/is_string.h"
#include "xdk/lua/stack.h"

#include <string_view>

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

namespace {
struct IsStringMatcher final
    : public ::testing::MatcherInterface<const Stack::Element &> {
  const Matcher<std::string_view> matcher;

  explicit IsStringMatcher(const Matcher<std::string_view> &matcher)
      : matcher(matcher) {}

  void DescribeTo(std::ostream *os) const final {
    *os << "is string and ";
    matcher.DescribeTo(os);
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "isn't string or ";
    matcher.DescribeNegationTo(os);
  }

  bool MatchAndExplain(const Stack::Element &element,
                       MatchResultListener *result_listener) const final {
    lua_State *L = element.L;
    int index = element.index;
    if (lua_gettop(L) < lua_absindex(L, index)) {
      *result_listener << "\ngettop L: " << std::setw(3) << lua_gettop(L)
                       << '\n';
    }
    return lua_type(L, index) == LUA_TSTRING &&
           matcher.MatchAndExplain(lua_tostring(L, index), result_listener);
  }
};
} // namespace

Matcher<const Stack::Element &> IsString(Matcher<std::string_view> matcher) {
  return MakeMatcher(new IsStringMatcher(matcher));
}

} // namespace lua
} // namespace xdk
