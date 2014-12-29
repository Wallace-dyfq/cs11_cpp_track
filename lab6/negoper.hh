#include "unary.hh"
class NegOper : public UnaryOperator {
 public:

  NegOper(Expression *ex):UnaryOperator(exp) {}

  double evaluate(const Environment &env) const{
    return -exp->evaluate(env);
  }  
};
