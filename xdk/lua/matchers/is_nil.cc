#include "xdk/lua/matchers/is_nil.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

namespace {
struct IsNilMatcher final
    : public ::testing::MatcherInterface<const Stack::Element &> {
  void DescribeTo(std::ostream *os) const final { *os << "is nil"; }

  void DescribeNegationTo(std::ostream *os) const final { *os << "isn't nil"; }

  bool MatchAndExplain(const Stack::Element &element,
                       MatchResultListener *result_listener) const final {
    lua_State *L = element.L;
    int index = element.index;
    if (lua_gettop(L) < lua_absindex(L, index)) {
      *result_listener << "\ngettop L: " << std::setw(3) << lua_gettop(L)
                       << '\n';
    }
    return lua_isnil(L, index);
  }
};
} // namespace

Matcher<const Stack::Element &> IsNil() {
  return MakeMatcher(new IsNilMatcher());
}

} // namespace lua
} // namespace xdk
