class SparseVector {

 private:
  
  struct node {
    int _index;
    int _value;
    node *_next;

    // Node  constructor - simply initializes the data-members
    node(int i, int v, node *n = 0): _index(i), _value(v), _next(n) {}

  };

  node *_start;

  int _size;

  // helper functions

  void clear();
  void copyList(const SparseVector &sv);

  // helper functoin for setters
  void removeElem(int index);

  void  setNonezeroElem(int index, int value);

  // monirot the health of the list nodes
  void checkListOrder()const;

  void checkZeros() const;

  // helper functions for add operation
  void addSubVector(const SparseVector &sv, bool add);

  // helper function for removing zeros
  void removeZeros();
      
 public:

  inline  SparseVector(int size):_size(size){
  _start = 0;
  }
  SparseVector(const SparseVector &sv);
  ~SparseVector();
  inline  int getSize() const {return _size;}
  int getElem(int col) const;
  void setElem(int col, int v);

  // operator overloading

  SparseVector & operator=(const SparseVector &sv);
  bool operator==(const SparseVector &sv) const;
  bool operator!= (const SparseVector &sv) const;

  // arithmetric operators
  SparseVector & operator+=(const SparseVector &sv);
  SparseVector & operator-=(const SparseVector &sv);
  const SparseVector operator+(const SparseVector &sv) const;
  const SparseVector operator-(const SparseVector &sv) const;

  // print sparcity vector
  void printVector() const;
  
};
