#include "expression.hh"
#include <string>
class Symbol : public Expression {
  string name;

 public:
  Symbol(string s): name(s) {}
  ~Symbol() {}

  double evaluate(const Environment &env) const {

    return env.getSymbolValue(name);
  }
};
