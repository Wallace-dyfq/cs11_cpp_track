class Matrix{
 private:
  int row, col;
  int *elem;
  void  copy(const Matrix &aa);
  void cleanup();
 public:
  // Constructor

  Matrix(); //default constructor create a 0 by 0 matrix
  Matrix(int r, int c);
  Matrix(const Matrix &aa);

  // Destructor
  ~Matrix();

  //getters
  int getrows() const;
  int getcols() const;
  int getelem(int r, int c)const ;

  //setters
  void setelem(int r, int c, int number);

  // Mutator method
  //  void add(Matrix &aa);
  // void subtract(Matrix &aa);
  //bool equals(const Matrix &aa) ;

  // operator overloading
  Matrix& operator=(const  Matrix &aa);

  Matrix & operator+= (const Matrix &aa);
  Matrix & operator-= (const Matrix &aa);
  Matrix & operator*= (const Matrix &aa);
  
  const Matrix operator+ (const Matrix &aa) const;
  const Matrix operator- (const Matrix &aa) const;
  const Matrix operator* (const Matrix &aa) const;

  bool operator== (const Matrix &aa) const;
  bool operator!= (const Matrix &aa) const;
};
