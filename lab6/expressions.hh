// this file contain all the classes needed, instead of spreading them in different files

#ifndef _EXPRESSIONS_HH_
#define _EXPRESSIONS_HH_

#include<string>
#include<stdexcept>
#include<cassert>
#include "environment.hh"

class Expression {
  //private:


 public:

  virtual double evaluate(const Environment &env) const = 0;
  virtual  ~Expression(){};
};


class Value: public Expression {
 private:
  double value;


 public:
  Value(double v): value(v) {}
  double evaluate(const Environment &env) const {
    return value;
  }
  ~Value() {}

};


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


class Symbol : public Expression {
  string name;

 public:
  Symbol(string s): name(s) {}
  ~Symbol() {}

  double evaluate(const Environment &env) const {

    return env.getSymbolValue(name);
  }
  string getname() const {
    return name;
  }
};

class AddOper : public BinaryOperator {
  // private:

 public:
  AddOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS) {}
  double evaluate(const Environment &env) const {
    double l = getLHS_p()->evaluate(env);
    double r = getRHS_p()->evaluate(env);
    return l+r;

  }

};

class SubOper : public BinaryOperator {
  // private:

 public:
  
  SubOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS) {}
  
  double evaluate(const Environment &env) const {
    double l = getLHS_p()->evaluate(env);
    double r = getRHS_p()->evaluate(env);
    return l-r;

  }

};



class MulOper : public BinaryOperator {
  // private:

 public:
  
  MulOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS) {}
  
  double evaluate(const Environment &env) const {
    double l = getLHS_p()->evaluate(env);
    double r = getRHS_p()->evaluate(env);
    return l*r;

  }

};

class DivOper : public BinaryOperator {
  // private:

 public:
  
  DivOper(Expression *pLHS, Expression *pRHS): BinaryOperator(pLHS, pRHS) {}
  
  double evaluate(const Environment &env) const {
   
    double r = getRHS_p()->evaluate(env);
    
    if (r == 0)
      throw std::runtime_error("divided by zero!");
    
    double l = getLHS_p()->evaluate(env); 
    return l/r;

  }

};


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
class NegOper : public UnaryOperator {
 public:

  NegOper(Expression *ex):UnaryOperator(ex) {}

  double evaluate(const Environment &env) const{
    return -getExp_p()->evaluate(env);
  }  
};


#endif  // _EXPRESSIONS_HH_
