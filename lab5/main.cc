#include<iostream>
//#include<random>
#include<cstdlib>

#include "heap.hh"

using namespace std;
int main(int argc, char **argv)
{
  int maxsize = 32;
  Heap<int, 32> h;
  int i;

  int lastval;

  rand();

  for (i = 0; i < maxsize; ++i)
  {
    try{
      h.add_value(rand() % 1000);
    }
    catch (overflow_error &e) {
      cerr<<"Error:\t"<<e.what()<<endl;
    }
  }

  lastval = h.get_first_value();
  cout<<"Value 0 = "<< lastval<<endl;

  for (i = 1; i < maxsize; ++i) {
    int val;
    try {
      val = h.get_first_value();
    }
    catch (underflow_error &e) {
      cerr<<"Error:\t"<<e.what()<<endl;
    }
    
    cout<< "Value "<<i<<" = "<< val<<endl;

    if (val < lastval)
      cerr<<"\tERROR: OUT OF ORDER\n";
    lastval = val;
  }

  return 0;
  
}

