#include "quit.h"
#include <iostream>
using namespace std;

int main() {
  Date date(5,5,2024);
  bool isTrue = date.compareDay(0);
  cerr << isTrue << endl;
}
