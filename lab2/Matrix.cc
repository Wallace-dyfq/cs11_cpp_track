#include "Matrix.hh"
#include<cassert>
#include<iostream>

Matrix::Matrix():row(0), col(0) {
  
}


Matrix::Matrix(int r, int c): row(r), col (c) {

  elem = new int[row*col];
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc)
      setelem(rr, cc, 0);

}

Matrix::Matrix( const Matrix &aa) {

  copy(aa);
    
}

Matrix::~Matrix() {
  cleanup();

}

int Matrix::getrows() const {
  return row;
}

int Matrix::getcols() const {
  return col;
}

int Matrix::getelem(int r, int c) const {
  assert (r <= row);
  assert (c <= col);
  return elem[r*col + c];
}

void Matrix::setelem(int r, int c, int number)
{
  assert (r <= row);
  assert (c <= col);
  elem[r * col + c] = number;
}


void Matrix::add(Matrix &aa) {
  assert(aa.getrows() == row);
  assert(aa.getcols() == col);
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc)
      elem[rr * col + cc] += aa.getelem(rr, cc);

}
  

void Matrix::subtract(Matrix &aa) {
  assert(aa.getrows() == row);
  assert(aa.getcols() == col);
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc)

      elem[rr * col + cc] -= aa.getelem(rr, cc);

}


bool Matrix::equals(const Matrix &aa)  {
  if (aa.getcols() != col || aa.getrows() != row) return false;
  
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc) {
      
      if (elem[rr * col + cc] != aa.getelem(rr, cc))
        return false;
    }
  return true;

}
  

Matrix& Matrix::operator= (const Matrix &aa) {

  std::cout<<"call operator ="<<std::endl;
  cleanup();
  copy(aa);
  row = aa.getrows();
  std:: cout<< "aa rows = "<<aa.getrows()<<std::endl;
  col = aa.getcols();
  std::cout<< "aa cols = "<<aa.getcols()<<std::endl;
    
  return *this;
}

void Matrix::cleanup() {
   if (row !=0 || col !=0)
    delete[] elem ;
}

void Matrix::copy(const Matrix & aa) {
  row = aa.getrows();
  col = aa.getcols();
  int elenumber = row * col;

  elem = new int[elenumber];

  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc) {
      //    elem[col*rr + cc] = aa.getelem(rr, cc);
      int tmp = aa.getelem(rr, cc);
      setelem(rr, cc, tmp);
    }

}
