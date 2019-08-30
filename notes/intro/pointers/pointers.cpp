#include <iostream>

using namespace std;

// 8/30/2019

void display_array(int array[], const int length) {
  cout << "[";
  if (length > 0) {
    cout << array[0];
  }
  for (int i = 1; i < length; ++i) {
    cout << ", " << array[i];
  }
  cout << "]" << endl;
}

void display_array_ptr(int array[], const int length) {
  cout << "[";
  int *ptr = array;
  if (length > 0) {
    cout << *ptr;
  }
  ptr++;
  for (int *end = array + length; ptr < end; ++ptr) {
    cout << ", " << *ptr;
  }
  cout << "]" << endl;
}

// primitives (makes a copy)
void pass_by_value(int x) {
  x = 10;
}

// disliked by c++ people
void pass_by_pointer(int *x) {
  *x = 10;
}

// big objects - doesn't make a copy
void pass_by_reference(int &x) {
  x = 10;
}

int main() {
  // * used for pointer declaration as well as to dereference pointer
  // get memory address with &
  int x = 5, y = 6, *z = &x;
  cout << z << endl; // get hex memory address
  cout << *z << endl;
  // you need to use all variables
  cout << "x = " << x << ", y = " << y << endl;

  *z = 7;
  cout << "x = " << x << ", y = " << y << endl;

  // z = sets the memory address
  // &y gets the memory address for the value
  // *z = sets the value of the memory address

  // int *p;
  // integers are 4 bytes
  // p++; // goes up by 4 bytes

  z = &y;
  *z = 7;
  cout << "x = " << x << ", y = " << y << endl;

  // cancer:
  // delete z;
  /*
  cout << ++z << endl; // bad idea - not sure what z points to now
  cout << *z << endl; // get random memory address

  z += 30000; // terrible idea - z points to the address space of this process
  *z = 30; // assigning a value to the place where z points will cause a segmentation fault
  */

  // see in gdb: run - see error, bt - backtrack (stacktrace)
  // [stack ->       <- heap]
  // array represents memory access, stack starts at the top and goes down, heap starts at the
  // bottom and goes up
  // big things should go on the heap (like an array), small things on stack
  // when in doubt, put it on the heap

  // valgrind ./pointers.o // used for checking if stuff is deleted

  // when program is done, the stack is popped, but the heap stays (memory leak if not deleted)
  // *values puts it on the heap.
  int *values = new int[y];
  // always free memory at the end
  for (int i = 0; i < y; ++i)
    values[i] = i;
  display_array(values, y);
  display_array_ptr(values, y);
  delete[] values;
  x = 5;
  pass_by_value(x);
  cout << "x = " << x << endl; // 5
  x = 5;
  pass_by_pointer(&x);
  cout << "x = " << x << endl; // 10
  x = 5;
  pass_by_reference(x);
  cout << "x = " << x << endl; // 10
  return 0;
}
