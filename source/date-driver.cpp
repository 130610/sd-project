#include "date.h"
#include <iostream>
using namespace std;

int main() {
  Date date(5,5,2024);
  string s = "Foosball";
  int i = convertDayToNumber(s);
  cerr << "day #: " << i << endl;
  bool isTrue = date.compareDay(0);
  cerr << isTrue << endl;
  Date d;
  cout << d.month << endl;
  cout << d.day << endl;
  cout << d.year << endl;

  cerr << validateDate(2,29,2005) << endl;
}
