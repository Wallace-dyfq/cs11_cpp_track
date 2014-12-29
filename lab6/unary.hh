#include "expression.hh"

class UnaryOperator : public Expression {
 private:
  Expression * exp;

 public:
  UnaryOperator(Expression * e): exp(e) {}
  ~UnaryOperator() {
    if (exp != 0)
      delete exp;
  }

  Expression * getExp_p() const {
    return exp;
  }

};
