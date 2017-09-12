#include <poincare/dynamic_hierarchy.h>
extern "C" {
#include <assert.h>
#include <stdlib.h>
}

namespace Poincare {

DynamicHierarchy::DynamicHierarchy() :
  Hierarchy(0),
  m_operands(nullptr)
{
}

DynamicHierarchy::DynamicHierarchy(Expression ** operands, int numberOfOperands, bool cloneOperands) :
  Hierarchy(numberOfOperands)
{
  assert(operands != nullptr);
  assert(numberOfOperands >= 2);
  m_operands = new Expression * [numberOfOperands];
  for (int i=0; i<numberOfOperands; i++) {
    assert(operands[i] != nullptr);
    if (cloneOperands) {
      m_operands[i] = operands[i]->clone();
    } else {
      m_operands[i] = operands[i];
    }
  }
}

DynamicHierarchy::~DynamicHierarchy() {
  if (m_operands != nullptr) {
    for (int i = 0; i < m_numberOfOperands; i++) {
      delete m_operands[i];
    }
  }
  delete[] m_operands;
}

int DynamicHierarchy::numberOfOperands() const {
  return m_numberOfOperands;
}

const Expression * DynamicHierarchy::operand(int i) const {
  assert(i >= 0);
  assert(i < m_numberOfOperands);
  return m_operands[i];
}

Expression ** DynamicHierarchy::operands() {
  return m_operands;
}

void DynamicHierarchy::stealOperandsFrom(DynamicHierarchy * sibling) {
  assert(this->type() == sibling->type()); // Could work, but wouldn't make much sense

  int resultingSize = this->numberOfOperands() + sibling->numberOfOperands();
  Expression ** operands = new Expression * [resultingSize];

  for (int i=0; i<numberOfOperands(); i++) {
    operands[i] = m_operands[i];
  }
  for (int j=0; j<sibling->numberOfOperands(); j++) {
    operands[numberOfOperands()+j] = sibling->operands()[j];
  }

  delete[] m_operands;
  m_operands = operands;
  m_numberOfOperands = resultingSize;

  sibling->setNumberOfOperand(0); // Stolen!
}

void DynamicHierarchy::setNumberOfOperand(int numberOfOperand) {
  m_numberOfOperands = 0;
}

}
