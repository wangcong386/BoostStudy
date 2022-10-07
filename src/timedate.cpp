#include "timedate.h"

#include <QDebug>

TimeDate::TimeDate() {}

void TimeDate::Print() {
  qDebug() << __PRETTY_FUNCTION__ << "可度量最大时间(h)"
           << m_BoostTimer.elapsed_max() / 3600 << "h";
  qDebug() << __PRETTY_FUNCTION__ << "可度量最小时间(s)"
           << m_BoostTimer.elapsed_min() << "s";
  qDebug() << __PRETTY_FUNCTION__ << "已流逝时间(s)" << m_BoostTimer.elapsed()
           << "s";
}

void TimeDate::ProgressTimerPrint() {
  std::stringstream ss1;
  std::stringstream ss2;
  { boost::progress_timer proTimer1(ss1); }
  std::cout << "ss1 " << ss1.str() << std::endl;

  { boost::progress_timer proTimer2(ss2); }
  std::cout << "ss2 " << ss2.str() << std::endl;
}

void TimeDate::DateDefineCompare() {
  boost::gregorian::date date1;
  boost::gregorian::date date2(2022, 8, 26);
  boost::gregorian::date date3(2022, boost::gregorian::Aug, 26);
  boost::gregorian::date date4(date3);

  boost::gregorian::date date5 = boost::gregorian::from_string("2022-9-10");
  boost::gregorian::date date6(boost::gregorian::from_string("2022/9/10"));
  boost::gregorian::date date7 =
      boost::gregorian::from_undelimited_string("20220908");

  assert(date1 == boost::gregorian::date(boost::gregorian::not_a_date_time));
  assert(date2 == date3);
  assert(date3 < date4);
}

void TimeDate::DayClockTest() {
  std::cout << "local_day" << boost::gregorian::day_clock::local_day()
            << std::endl;
  std::cout << "universal_day" << boost::gregorian::day_clock::universal_day()
            << std::endl;
}

void TimeDate::SpecialDay() {
  boost::gregorian::date d1(boost::gregorian::neg_infin);
  boost::gregorian::date d2(boost::gregorian::pos_infin);
  boost::gregorian::date d3(boost::gregorian::not_a_date_time);
  boost::gregorian::date d4(boost::gregorian::max_date_time);
  boost::gregorian::date d5(boost::gregorian::min_date_time);

  std::cout << d1 << std::endl;
  std::cout << d2 << std::endl;
  std::cout << d3 << std::endl;
  std::cout << d4 << std::endl;
  std::cout << d5 << std::endl;
  assert(d1.is_infinity());
  assert(d1.is_neg_infinity());
  assert(d2.is_pos_infinity());
  assert(d3.is_not_a_date());
  assert(d3.is_special());
  assert(!boost::gregorian::date(2017, 5, 31).is_special());
}

void TimeDate::AccessOfDate() {
  boost::gregorian::date da = boost::gregorian::day_clock::local_day();
  std::cout << "year " << da.year() << " month " << da.month() << " day "
            << da.day() << std::endl;
  boost::gregorian::date::ymd_type ymd = da.year_month_day();
  std::cout << "ymd year " << ymd.year << " ymd month " << ymd.month
            << " ymd day " << ymd.day << std::endl;
  std::cout << "day of week " << da.day_of_week() << std::endl;
  std::cout << "day of year " << da.day_of_year() << std::endl;
  std::cout << "end of month " << da.end_of_month() << std::endl;
}

void TimeDate::DateOutput() {
  boost::gregorian::date da = boost::gregorian::day_clock::universal_day();
  std::cout << boost::gregorian::to_simple_string(da) << std::endl;
  std::cout << boost::gregorian::to_iso_string(da) << std::endl;
  std::cout << boost::gregorian::to_iso_extended_string(da) << std::endl;

  std::cin >> da;
  std::cout << da << std::endl;
}

void TimeDate::CTransform() {
  // date to tm
  boost::gregorian::date da = boost::gregorian::day_clock::universal_day();
  std::tm t = boost::gregorian::to_tm(da);
  std::cout << "std tm hour " << t.tm_hour << std::endl;
  std::cout << "std tm min " << t.tm_min << std::endl;
  std::cout << "std tm year " << t.tm_year << std::endl;
  std::cout << "std tm mday " << t.tm_mday << std::endl;

  // tm to date
  boost::gregorian::date daBack = boost::gregorian::date_from_tm(t);
  std::cout << "daBack " << daBack << std::endl;
}

void TimeDate::DateDuration() {
  boost::gregorian::days d1(2);
  boost::gregorian::date_duration d2(-999);
  boost::gregorian::date_duration d3(266);

  assert(d1 > d2 && d2 < d3);
  assert(d1 + d2 == boost::gregorian::days(-997));
  assert((d1 + d3).days() == 268);
  assert(d1 / 3 == boost::gregorian::days(0));

  boost::gregorian::years y(1);
  boost::gregorian::months m(2);
  boost::gregorian::weeks w(3);

  boost::gregorian::months m1 = y + m;
  std::cout << m1.number_of_months() << std::endl;
  std::cout << y.number_of_years() << std::endl;
  assert(w.days() == 21);

  boost::gregorian::date date1 = boost::gregorian::day_clock::local_day();
  boost::gregorian::date date2(2021, 4, 2);
  std::cout << "days I am employed " << date1 - date2 << std::endl;

  date1 += boost::gregorian::days(19);
  std::cout << "the date after 19 days "
            << boost::gregorian::to_iso_extended_string(date1) << std::endl;

  date2 += boost::gregorian::years(1);
  std::cout << date2 << std::endl;
}
