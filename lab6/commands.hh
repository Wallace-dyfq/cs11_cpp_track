#ifndef _COMMAND_HH_
#define _COMMAND_HH_
#include<iostream>
#include "environment.hh"
#include "expressions.hh"

class Command {
 public:
  virtual  void run (Environment & env) =0 ;
  virtual ~Command(){};
};

class PrintCommand : public Command {
 private:
  Expression *e_p;
 public:
  PrintCommand(Expression *e):e_p(e) {}
  ~PrintCommand() {
    if (e_p != 0) delete e_p;
  }
  
  void run(Environment &env ) {
    double v = e_p->evaluate(env);
    std::cout<<" = "<<v<<std::endl;
  }

};

class AssignCommand : public Command {
 private:

  Symbol * sym_p;
  Expression * exp_p;

 public:
  AssignCommand(Symbol * sy, Expression * e) : sym_p(sy), exp_p(e) {}
  ~AssignCommand() {
    if (sym_p != 0)
      delete sym_p;
    if (exp_p != 0)
      delete exp_p;
  }

  void run(Environment &env) {
    double r = exp_p->evaluate(env);
    string n = sym_p->getname();
    env.setSymbolValue(n, r);
    cout<<n<<" = "<< r<<endl;
  }


};

#endif // _COMMAND_HH_
