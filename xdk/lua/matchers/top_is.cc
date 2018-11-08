#include "xdk/lua/matchers/top_is.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

namespace {
struct TopIsMatcher final : public ::testing::MatcherInterface<const Stack &> {
  const Matcher<int> matcher;

  explicit TopIsMatcher(const Matcher<int> &matcher) : matcher(matcher) {}

  void DescribeTo(std::ostream *os) const final {
    *os << " top ";
    matcher.DescribeTo(os);
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "top ";
    matcher.DescribeNegationTo(os);
  }

  bool MatchAndExplain(const Stack &stack,
                       MatchResultListener *result_listener) const final {
    return matcher.MatchAndExplain(lua_gettop(stack.L), result_listener);
  }
};
} // namespace

Matcher<const Stack &> TopIs(Matcher<int> matcher) {
  return MakeMatcher(new TopIsMatcher(matcher));
}

} // namespace lua
} // namespace xdk
