#include "SparseVector.hh"
#include <iostream>
#include<cassert>

// ============== helper function clear ===========
void SparseVector::clear() {
  
  node *curr = _start;
  
  while (curr != 0) {
    node *next = curr->_next;
    delete curr;

    curr = next;
  }
  
  
}

// =============== helper function copyList ===========

void SparseVector::copyList(const SparseVector &sv) {
  _size = sv._size;
  node *otherCurr = sv._start;
  node *prev = 0;
 

  if (otherCurr == 0) // no node in sv
    _start = 0;

  else {
    while (otherCurr != 0) {
      node *curr = new node(otherCurr->_index, otherCurr->_value);
      if (prev == 0)
        _start = curr;  //curr is the firt node in our copy
      else
        prev->_next = curr; // make previous node point to the current

      prev = curr;
      otherCurr = otherCurr->_next;
  }
  }
  
  
  checkListOrder();
  
}

// ================= copy constructor =============
SparseVector::SparseVector(const SparseVector &sv) {

  copyList(sv);
}


// ===============
SparseVector::~SparseVector() {

  clear();
}



// ================

SparseVector & SparseVector::operator=(const SparseVector &sv) {
  if (this != &sv)
  {
    clear();
    copyList(sv);
  }
  return *this;
}

// =============== getter ============

int SparseVector::getElem(int col) const {
  checkListOrder();
   if (_start == 0) return 0;
   else {
     node *curr = _start;
     while (curr != 0 && curr->_index != col) {
       if (curr->_index > col)
         break;

       curr = curr->_next;
     }
 
      if (curr != 0 && curr->_index == col)
       return curr->_value;
     else
       return 0;
   }
}

// =============== settter ============

void SparseVector::removeElem(int index) {

  node *prev = 0;
  node *curr = _start;
  while (curr != 0 && curr->_index != index) {
    if (curr->_index > index)
      break;
    prev = curr;
    curr = curr->_next;
  }

  if (curr->_index == index) {
    // curr at last node
    if (curr->_next == 0)
    {
      prev->_next = 0;
      delete curr;
      curr = 0;
    }
    else if (curr == _start)
      // curr at first node
    {
      if (curr->_next == 0)
        delete _start;
      else {
      _start = curr->_next;
      delete curr;
      }
    }

    // curr in between first and last node
    else  {
      prev->_next = curr->_next;
      delete curr;
    }
    
  }
  // not found, do nothing
  
  checkListOrder();
  
}

void SparseVector::setNonezeroElem(int index, int value) {
  // check if it is a new list, if so, just make it the first one 
  if (_start == 0)
  {
    
    node *newfirst = new node(index, value, 0);
    _start = newfirst;
  }

  //not the new list
  else {
     node *prev = 0;
     node *curr = _start;
    
    while (curr != 0 && curr->_index != index)
    {
      if (curr->_index > index)
        break;
      prev = curr;
      curr = curr->_next;
    }
    // curr is among the list and have the same index, just need to modify the vlaue
    if (curr != 0 && curr->_index == index )
    {
      
        curr->_value = value;
    }
    
    // index in not found, need to add it
    else
    {
      node *tmpnode = new node(index, value, curr);
      if (prev == 0) // curr is the first node
        _start = tmpnode;
       else
         prev->_next = tmpnode;
    
     
  }
  checkListOrder();
  }
}
  



void SparseVector::setElem(int col, int v) {
  if (v == 0)
    removeElem(col);
  else
    setNonezeroElem(col, v);
}

// =========== monitor the health of the node list ===============

void SparseVector::checkListOrder() const {
  node *prev = 0;
  node *curr = _start;
  bool flag = true;
  while (curr != 0)
  {
    if (prev == 0)
    {
    }
    else if (prev->_index > curr->_index)
    {
      flag = false;
      std::cout<<" node out of order at position "<< curr->_index<<" with value of "<< curr->_value<<std::endl;
    }
    else
    {
    }
    prev = curr;
    curr = curr->_next;
  }
  assert (flag);
}

// ============ equality =====================
bool SparseVector::operator==(const SparseVector &sv) const {
  if (_size != sv._size) return false;
  node *otherCurr = sv._start;
  node *curr = _start;
  while (curr != 0 && otherCurr != 0) {
    if (curr->_index != otherCurr->_index || curr->_value != otherCurr->_value)
      return false;
    curr = curr->_next;
    otherCurr = otherCurr->_next;
  }
  if (otherCurr != 0 || curr != 0) return false;
  return true;

}


bool SparseVector::operator!=(const SparseVector &sv) const {
  return !(*this == sv);
}


// helper function for add operation
void SparseVector::addSubVector(const SparseVector &sv, bool add) {

  int sign = (add ? 1 : -1);
  node *prev = 0;
  node *curr = _start;
  node *otherPrev = 0;
  node *otherCurr = sv._start;

  while(curr != 0 && otherCurr != 0)
  {
    if (curr->_index < otherCurr->_index)
    {
      prev = curr;
      curr = curr->_next;

    }
    else if (curr->_index == otherCurr->_index)
    {
      prev = curr;
      //curr->_value+=otherCurr->_value;
      curr->_value = curr->_value + sign * otherCurr->_value;
      curr = curr->_next;
      otherPrev = otherCurr;
      otherCurr = otherCurr->_next;
    }
    else
    {
      node *tmpnode = new node(otherCurr->_index, sign * otherCurr->_value, curr);
      if (prev == 0) // curr is the first node
        _start = tmpnode;
       else
         prev->_next = tmpnode;
      
      otherPrev = otherCurr;
      otherCurr = otherCurr->_next;
      prev = tmpnode; // move prev forward

    }


  }
  if (curr == 0 && otherCurr != 0)
  {
    while(otherCurr != 0)
    {
      node *tmpnode = new node(otherCurr->_index, sign * otherCurr->_value, curr);
      if (prev == 0) // curr is the first node
        _start = tmpnode;
      else
        prev->_next = tmpnode;

      otherPrev = otherCurr;
      otherCurr = otherCurr->_next;
      prev = tmpnode;
    }
  }

  // cleanup the zeros
  removeZeros();
}


 // helper function for removing zeros
void SparseVector::removeZeros() {
  node *curr = _start;
  node *prev = 0;

  while (curr != 0)
  {
    if (curr->_value == 0) 
    {
      if (prev == 0) // start of the list is zero
      {
        curr = curr->_next;
        delete _start;
        _start = curr;
        
        
      }
      else 
      {
        node *newnext = curr->_next;
        delete curr;
        curr = newnext; 
        prev->_next = curr;
      }
      
        
    }
    else {
      prev = curr;
      curr = curr->_next;
    }
    
  }

}


// arithmetric operators
SparseVector & SparseVector::operator+=(const SparseVector &sv) {
  assert (sv._size == _size);
  addSubVector(sv, true);
  return *this;
  

}
SparseVector & SparseVector::operator-=(const SparseVector &sv){
  assert (sv._size == _size);
  addSubVector(sv, false);
  return *this;
}


const SparseVector SparseVector::operator+(const SparseVector &sv) const {
  return SparseVector(*this) += sv;
}

const SparseVector SparseVector::operator-(const SparseVector &sv) const {
  return SparseVector(*this) -= sv;
}



// debug helper to check zeros

void SparseVector::checkZeros()const {

  //node *prev = 0;
  node *curr = _start;
  bool flag = true;
  while (curr != 0)
  {
     if ( curr->_value == 0)
    {
      flag = false;
      std::cout<<" node value zero found, its index is "<< curr->_index<<std::endl;
    }
   
    curr = curr->_next;
  }
  assert (flag);
}


void SparseVector::printVector() const
{
  node *curr = _start;
  while (curr != 0)
  {
    std::cout<<"index: :"<<curr->_index<<", \tvalue: "<<curr->_value<<std::endl;
    curr = curr->_next;
  }
}
