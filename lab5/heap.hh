#ifndef __HEAP_HH__
#define __HEAP_HH__

#include<cassert>
#include<stdexcept>

template <typename T, int maxsize>
class Heap
{
 private:
  int num_values;
  T values[maxsize];
  void sift_down( int index);
  void sift_up( int index);
  void swap_values( int i, int j);
  inline  int left_child(int index) { return 2 * index + 1; }
  inline  int right_child(int index) {return 2 * index + 2; }
  inline int parent(int index) {return (index - 1)/2; }

 public:
  // constructors
  Heap();
  // Heap(const Heap &hp);

  // destructor
  ~Heap() {};
  // general methods
  T get_first_value();
  void add_value(T newval);
  
};

#endif /*__HEAP_H_H__*/


//  ================== definitions / implementations ================

// default consturctor 
template<typename T, int maxsize>
Heap<T, maxsize>::Heap() : num_values(0){ }

template<typename T, int maxsize>
T Heap<T, maxsize>::get_first_value() {

  T result;

  // assert(num_values > 0);

  if (num_values <=0)
    throw std::underflow_error("empty heap!!!");
  
  result = values[0];

  num_values--;
  if(num_values != 0)
  {
    values[0] = values[num_values];
    sift_down(0);
  }

  return result;
}

template<typename T, int maxsize>
void Heap<T, maxsize>::add_value(T newval) {

  int index;
  assert( num_values >= 0);
  if (num_values >= maxsize)
    throw std::underflow_error("heap full!!!");
  //assert(num_values < maxsize);

  index = num_values;
  values[index] = newval;
  num_values++;

  if (index != 0)
    sift_up(index);
}





template<typename T, int maxsize>
void Heap<T, maxsize>::sift_down(int index) {
  assert(index < num_values);
  int leftChild = left_child(index);
  int rightChild = right_child(index);

  if (leftChild >= num_values)
    /* If the left child's index is past the end of the heap
     * then this value has no children.  We're done.
     */
    return;

  if (rightChild >= num_values)
  {
    // only have a left chile
    
    /* Left child value is smaller.  Swap this value and the
       * left child value.
       */    
    if (values[leftChild] < values[index])
      swap_values(index, leftChild);

    /* Don't need to call sift_down again, because if this
       * node only has a left child, we are at the bottom of
       * the heap.
       */
  }
  else // This value has a left and right child. 
  {
    T left_val = values[leftChild];
    T right_val = values[rightChild];
    int swap_child;

    if (left_val < values[index] || right_val < values[index])
    {
      /* Need to swap this node with one of its children.  Pick
       * the smaller of the two children, since this is a min-heap
       * and that will preserve the heap properties.
       */
      if (left_val < right_val)
        swap_child = leftChild;
      else
        swap_child = rightChild;

      swap_values(index, swap_child);
      sift_down(swap_child);
    }
  }
}

/*
 * Given a heap and an index, sift_up checks to see if the value
 * at that index needs to be "sifted upward" in the heap, to
 * preserve the heap properties.  Specifically, a value needs to
 * be moved up in the heap if it is less than its parent value.
 * (This is just the "order" property; the "shape" property is
 * not affected by sifting a value up.)
 */
template<typename T, int maxsize>
void Heap<T, maxsize>::sift_up(int index) {

  int parent_index = parent(index);

  /* If the index to sift up is the root, we are done. */
  if (index == 0)
    return;

  assert(parent_index >= 0);
  assert(parent_index != index);  /* Parent of index 0 = 0... that's bad. */

  /* If the specified value is smaller than its parent value then
   * we have to swap the value and its parent.
   */
  if (values[index] < values[parent_index])
  {
    /* Swap the value with its parent value. */
    swap_values( index, parent_index);

    /* If we haven't gotten to the root, we might have to
     * sift up again.
     */
    if (parent_index != 0)
      sift_up(parent_index);
  }
}


/*
 * Helper function to handle the onerous task of swapping two
 * values in the value array of a heap.
 */
template<typename T, int maxsize>
void Heap<T, maxsize>::swap_values( int i, int j)
{
  T  tmp;

 
  assert(i >= 0 && i < num_values);
  assert(j >= 0 && j < num_values);
  assert(i != j);

  tmp = values[i];
  values[i] = values[j];
  values[j] = tmp;
}



  
