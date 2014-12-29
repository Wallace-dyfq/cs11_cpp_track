#include "expression.hh"
class BinaryOperator : public Expression {
 private:
  Expression *plhs;
  Expression *prhs;
  
 public:
  BinaryOperator(Expression *pLHS, Expression *pRHS): plhs(pLHS), prhs(pRHS) {
    assert (plhs != 0);
    assert (prhs != 0);
  }
  ~BinaryOperator() {
    if (plhs != 0)
      delete plhs;
    if (prhs != 0)
      delete prhs;
  }
  // accessor

  Expression * getLHS_p () const {
    return plhs;
  }

  Expression * getRHS_p() const {
    return prhs;
  }
};
