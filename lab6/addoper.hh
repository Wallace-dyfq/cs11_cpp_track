#include "binaryoperator.hh"
class AddOper : public BinaryOperator {
  // private:

 public:
  AddOper(Expression *pLHS, Expression *pRHS): BinaryOperator(*pLHS, *pRHS) {}
  double evaluate(const Environment &env) const {
    double l = plhs->evaluate(env);
    double r = prhs->evaluate(env);
    return l+r;

  }

};
