#include "xdk/lua/matchers/has_field.h"
#include "xdk/lua/stack.h"

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

namespace {
struct HasFieldMatcher final
    : public ::testing::MatcherInterface<const Stack::Element &> {
  const std::string name;
  const Matcher<const Stack::Element &> matcher;

  explicit HasFieldMatcher(const char *name,
                           const Matcher<const Stack::Element &> &matcher)
      : name(name), matcher(matcher) {}

  void DescribeTo(std::ostream *os) const final {
    *os << "has field '" << name << "' which ";
    matcher.DescribeTo(os);
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "doesn't have field '" << name << "' or ";
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
    if (lua_type(L, index) != LUA_TTABLE) {
      *result_listener << "\nProblem: element ist not a table\n";
      return false;
    }
    lua_getfield(L, index, name.c_str());
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
HasField(const char *name, Matcher<const Stack::Element &> matcher) {
  return MakeMatcher(new HasFieldMatcher(name, matcher));
}

} // namespace lua
} // namespace xdk
