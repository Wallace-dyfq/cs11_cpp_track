#include "expression.hh"
class Value: public Expression {
 private:
  double value;


 public:
  Value(double v): value(v) {}
  double evaluate(const Environment &env) {
    return value;
  }
  ~Value() {}

};
