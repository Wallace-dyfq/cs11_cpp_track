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
