#ifndef TIMEDATE_H
#define TIMEDATE_H
#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/progress.hpp>
#include <boost/timer.hpp>
#include <sstream>

class TimeDate {
 public:
  TimeDate();
  void Print();
  void ProgressTimerPrint();

  void DateDefineCompare();
  void DayClockTest();
  void SpecialDay();
  void AccessOfDate();
  void DateOutput();
  void CTransform();
  void DateDuration();

 private:
  boost::timer m_BoostTimer;
};

#endif  // TIMEDATE_H
