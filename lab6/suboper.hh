#include "binaryoperator.hh"

class SubOper : public BinaryOperator {
  // private:

 public:
  
  SubOper(Expression *pLHS, Expression *pRHS): BinaryOperator(*pLHS, *pRHS) {}
  
  double evaluate(const Environment &env) const {
    double l = plhs->evaluate(env);
    double r = prhs->evaluate(env);
    return l-r;

  }

};
