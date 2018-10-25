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
  const Matcher<lua_Number> matcher;

  explicit IsNumberMatcher(const Matcher<lua_Number> &matcher)
      : matcher(matcher) {}

  void DescribeTo(std::ostream *os) const final {
    *os << "is number and ";
    matcher.DescribeTo(os);
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "isn't number or ";
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
    return lua_type(L, index) == LUA_TNUMBER &&
           matcher.MatchAndExplain(lua_tonumber(L, index), result_listener);
  }
};
} // namespace

Matcher<const Stack::Element &> IsNumber(const Matcher<lua_Number> &matcher) {
  return MakeMatcher(new IsNumberMatcher(matcher));
}

} // namespace lua
} // namespace xdk
