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



  

Matrix& Matrix::operator= (const Matrix &aa) {

  // std::cout<<"call operator ="<<std::endl;
  if (this != &aa) {
    cleanup();
    copy(aa);
  }
  return *this;
}

void Matrix::cleanup() {
   if (row !=0 || col !=0)
    delete[] elem ;
}

void Matrix::copy(const Matrix & aa) {
  //row = aa.getrows();
  row = aa.row;
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

Matrix & Matrix::operator+= (const Matrix &aa) {
  assert(aa.getrows() == row);
  assert(aa.getcols() == col);
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc)
      elem[rr * col + cc] += aa.getelem(rr, cc);
  return *this;

}
  
Matrix & Matrix::operator-= (const Matrix &aa) {

  assert(aa.getrows() == row);
  assert(aa.getcols() == col);
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc)
      elem[rr * col + cc] -= aa.getelem(rr, cc);
  return *this;
}

Matrix & Matrix::operator*= (const Matrix &aa) {
  Matrix tempResult(row, aa.getcols());

  for (int r = 0; r < row; ++r)
    for (int c = 0; c < aa.getcols(); ++c)
    {
      int tmp = 0;
      for (int k = 0; k < col; ++k)
        tmp += getelem(r,k) * aa.getelem(k, c);
      tempResult.setelem(r, c, tmp);
    }

  // copy tempResult to *this
  cleanup();
  copy(tempResult);
  return *this;
}
      
  


const Matrix Matrix::operator+ (const Matrix &aa) const {
  return Matrix(*this) += aa;
}

const Matrix Matrix::operator- (const Matrix &aa) const {
  return Matrix(*this) -= aa;
}

const Matrix Matrix::operator* (const Matrix &aa) const {
  Matrix result = *this;
  result *= aa;
  return result;
}

bool Matrix::operator== (const Matrix &aa) const {
  if (aa.getcols() != col || aa.getrows() != row) return false;
  
  for (int rr = 0; rr < row; ++rr)
    for (int cc = 0; cc < col; ++cc) {
      
      if (elem[rr * col + cc] != aa.getelem(rr, cc))
        return false;
    }
  return true;


}

bool Matrix::operator!= (const Matrix &aa) const {
  return !(*this == aa);

}
