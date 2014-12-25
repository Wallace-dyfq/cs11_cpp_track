#include<iostream>
#include "Point.hh"

using namespace std;

int main()
{
  Point p1(0, 2, 3);
  Point p2;
  p2.setX(5);

  cout<<"Point 1 is ("<<p1.getX()<<", "<<p1.getY()<<", "<<p1.getZ()<<")"<< endl;
  cout<<"Point 2 is ("<<p2.getX()<<", "<<p2.getY()<<", "<<p2.getZ()<<")"<< endl;

  return 0;

}
