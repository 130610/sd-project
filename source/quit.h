#ifndef _QUITTER_
#define _QUITTER_

class Date {
private:
  unsigned month, day, year; // months start at 1
  bool isLeapYear();

  // 0's are unused
  unsigned monthCodes[13] = {0, 6,2,2,5,0,3,5,1,4,6,2,4};
  unsigned monthDays[13] = {0, 31,29,31,30,31,30,31,31,30,31,30,31};

public:
  Date(unsigned m, unsigned d, unsigned y);
  bool compareDay(unsigned dayToCheck);
};

#endif
