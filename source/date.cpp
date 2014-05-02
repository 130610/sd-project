#include <iostream>
#include <algorithm> // for transform()
#include <string>
#include "date.h"

using namespace std;

Date::Date(unsigned m, unsigned d, unsigned y) // given date
{
  month = m; day = d; year = y;
}

Date::Date()
{
  /* find a random date -- ask Bryan how it works */
}

bool Date::isLeapYear(unsigned month, unsigned day, unsigned year)
{
  if( (month == 2) && (day == 29) && (year % 4) )
    return false;
  if( (month == 2) && (day == 29) && (not year % 4) )
    if( !(year % 100) && (year % 400) )
      return false;
  return true;
}

bool Date::compareDay(unsigned dayToCheck)
{
  unsigned correctCode;
  unsigned monthCode, dayCode, yearCode, centuryCode;

  unsigned yearMinusCentury = year % 100;
  unsigned century = year / 100;

  monthCode = monthCodes[month];
  dayCode = day;
  yearCode = ( (yearMinusCentury / 12) +
               (yearMinusCentury % 12) +
               (yearMinusCentury % 12)/4 );
  centuryCode = (5*(century%4));
  correctCode = (monthCode + dayCode + yearCode + centuryCode) % 7;

  cerr << correctCode << endl;

  if ( correctCode == dayToCheck )
    return true;
  else
    return false;
}

unsigned convertDayToNumber(string s)
{
  /* returns day # from 0-6, or 9 if invalid */

  // http://stackoverflow.com/questions/313970/stl-string-to-lower-case
  transform(s.begin(), s.end(), s.begin(), ::tolower);

  if (s == "sunday") return 0;
  if (s == "monday") return 1;
  if (s == "tuesday") return 2;
  if (s == "wednesday") return 3;
  if (s == "thursday") return 4;
  if (s == "friday") return 5;
  if (s == "saturday") return 6;
  return 9;
}
