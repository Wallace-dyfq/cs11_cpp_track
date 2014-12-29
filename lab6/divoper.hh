#include<stdexcept>
#include "binaryoprator.hh"
class DivOper : public BinaryOperator {
  // private:

 public:
  
  DivOper(Expression *pLHS, Expression *pRHS): BinaryOperator(*pLHS, *pRHS) {}
  
  double evaluate(const Environment &env) const {
   
    double r = prhs->evaluate(env);
    
    if (r == 0)
      throw std::runtime_error("divided by zero!");
    
    double l = plhs->evaluate(env); 
    return l/r;

  }

};
