#ifndef POINCARE_SIMPLIFY_SELECTOR_H
#define POINCARE_SIMPLIFY_SELECTOR_H

#include <poincare/expression.h>

namespace Poincare {

class Combination;

class Selector {
public:
  constexpr Selector(int captureIndex = -1, const Selector * const * children = nullptr, int numberOfChildren = 0) :
    m_captureIndex(captureIndex),
    m_children(children),
    m_numberOfChildren(numberOfChildren)
  {
  };

  virtual bool acceptsLocationInCombination(const Combination * combination, int location) const = 0;
  virtual bool immediateMatch(const Expression * e) const = 0;
  bool match(const Expression * e, Expression ** captures) const;
private:
  int m_captureIndex;
  const Selector * const * m_children;
  int m_numberOfChildren;
};

}

#endif
