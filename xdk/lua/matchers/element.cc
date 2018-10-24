#include "xdk/lua/matchers/element.h"

namespace xdk {
namespace lua {

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;

namespace {
struct ElementMatcher final : public MatcherInterface<const Stack &> {
  const int index;
  Matcher<const Stack::Element &> inner_matcher;
  explicit ElementMatcher(int index,
                          const Matcher<const Stack::Element &> &inner_matcher)
      : index(index), inner_matcher(inner_matcher) {}

  void DescribeTo(std::ostream *os) const override {
    *os << "element at index " << index << " ";
    inner_matcher.DescribeTo(os);
  }

  void DescribeNegationTo(std::ostream *os) const final {
    *os << "element at index " << index << " ";
    inner_matcher.DescribeNegationTo(os);
  }

  bool
  MatchAndExplain(const Stack &stack,
                  testing::MatchResultListener *result_listener) const final {
    return inner_matcher.MatchAndExplain(Stack::Element(stack.L, index),
                                         result_listener);
  }
};

} // namespace

Matcher<const Stack &>
Element(int index, const Matcher<const Stack::Element &> &inner_matcher) {
  return MakeMatcher(new ElementMatcher(index, inner_matcher));
}

} // namespace lua
} // namespace xdk
