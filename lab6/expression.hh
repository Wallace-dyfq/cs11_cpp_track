class Expression {
  //private:


 public:

  double evaluate(const Environment &env) const = 0;
  virtual  ~Expression(){};
};


