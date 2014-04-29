#include "quit.h"
#include <iostream>
using namespace std;

Date::Date(unsigned m, unsigned d, unsigned y)
{
  month = m; day = d; year = y;
}

bool Date::compareDay(unsigned dayToCheck)
{
  unsigned correctCode;
  unsigned monthCode, dayCode, yearCode, centuryCode;

  unsigned yearMinusCentury = year % 100;
  unsigned century = year / 100;

  monthCode = monthCodes[month];
  dayCode = day % 7;
  yearCode = ( (yearMinusCentury / 12) +
               (yearMinusCentury % 12) +
               (yearMinusCentury % 12)/4
             ) % 7;
  centuryCode = ( (5*(century%4)) % 7 );
  correctCode = (monthCode + dayCode + yearCode + centuryCode) % 7;

  cerr << correctCode << endl;

  if ( correctCode == dayToCheck )
    return true;
  else
    return false;
}
