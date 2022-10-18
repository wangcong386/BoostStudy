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

void TimeDate::DatePeriod() {
  // 构造方式1：起始日期+时间长度
  boost::gregorian::date_period DatePeriod1(
      boost::gregorian::day_clock::local_day(), boost::gregorian::days(7));
  // 构造方式2：起始日期+终止日期
  boost::gregorian::date_period DatePeriod2(boost::gregorian::date(2021, 4, 2),
                                            boost::gregorian::date(2022, 4, 2));
  // 构造方式1：起始日期晚于终止日期，无效
  boost::gregorian::date_period DatePeriod3(boost::gregorian::date(2022, 4, 2),
                                            boost::gregorian::date(2021, 4, 2));
  // 构造方式2：时间长度为负数，无效
  boost::gregorian::date_period DatePeriod4(
      boost::gregorian::day_clock::local_day(), boost::gregorian::days(-8));

  std::cout << "DatePeriod1 " << DatePeriod1 << std::endl;
  std::cout << "DatePeriod2 " << DatePeriod2 << std::endl;
  std::cout << "DatePeriod3 " << DatePeriod3 << std::endl;
  std::cout << "DatePeriod4 " << DatePeriod4 << std::endl;

  // begin/last返回日期区间两个端点
  std::cout << "DatePeriod1 begin " << DatePeriod1.begin() << std::endl;
  std::cout << "DatePeriod1 last " << DatePeriod1.last() << std::endl;
  // is_null左大右小端点或日期长度为0
  assert(DatePeriod3.is_null() == true);
  // end返回last后的一天(逾尾的一天)
  std::cout << "DatePeriod1 end " << DatePeriod1.end() << std::endl;
  // length返回日期区间长度，单位是天
  std::cout << "DatePeriod2 length " << DatePeriod2.length() << std::endl;
  // 全序比较，比较第一区间end和第二区间begin，若有相交或包含则比较无意义
  boost::gregorian::date_period DatePeriod5(boost::gregorian::date(2022, 4, 3),
                                            boost::gregorian::date(2022, 4, 5)),
      DatePeriod6(boost::gregorian::date(2022, 4, 4),
                  boost::gregorian::date(2022, 4, 6));
  //  assert(DatePeriod5 < DatePeriod6);  // 断言失败
  // shift平移区间n天长度不变
  std::cout << "DatePeriod5 before shift " << DatePeriod5 << std::endl;
  DatePeriod5.shift(boost::gregorian::days(5));
  std::cout << "DatePeriod5 after shift " << DatePeriod5 << std::endl;
  // expand将日期区间向两端延伸n天，日期长度变为2n天
  DatePeriod5.expand(boost::gregorian::days(2));
  std::cout << "DatePeriod5 after expand 2 days " << DatePeriod5 << std::endl;

  // 日期区间是否在日期前/后
  std::cout << "DatePeriod5 is after 2022/01/01 "
            << DatePeriod5.is_after(boost::gregorian::date(2022, 1, 1))
            << std::endl;
  std::cout << "DatePeriod5 is before 2023/01/01 "
            << DatePeriod5.is_before(boost::gregorian::date(2023, 01, 01))
            << std::endl;
  // 日期区间是否包含另一个日期或区间
  std::cout << "DatePeriod5 contains 2022/03/04 "
            << DatePeriod5.contains(boost::gregorian::date(2022, 03, 04))
            << std::endl;
  std::cout << "DatePeroid5 contains DatePeriod6 "
            << DatePeriod5.contains(DatePeriod6) << std::endl;
  // 两日期区间是否存在交集
  std::cout << "DatePeriod5 intersects DatePeriod6 "
            << DatePeriod5.intersects(DatePeriod6) << std::endl;
  // 返回两日期区间交集
  std::cout << "intersection between DatePeriod5 and DatePeriod6 "
            << DatePeriod5.intersection(DatePeriod6) << std::endl;

  // 两日期区间是否相邻
  std::cout << "DatePeriod5 is adjacent with DatePeriod6 "
            << DatePeriod5.is_adjacent(DatePeriod6) << std::endl;

  // 两个日期区间的并集，若无交集或不相邻，返回无效区间，
  // 打印出来的日期区间将是起始日期大于结束日期
  std::cout << "DatePeriod5 merge with DatePeriod6 "
            << DatePeriod5.merge(DatePeriod6).is_null() << std::endl;
  std::cout << "DatePeriod1 merge with DatePeriod2 "
            << DatePeriod1.merge(DatePeriod2).is_null() << std::endl;
  // 合并两个日期区间以及之间的间隔，广义的merge
  std::cout << "DatePeriod5 span with DatePeriod6 "
            << DatePeriod5.span(DatePeriod6) << std::endl;
}

void TimeDate::DateIterator() {
  boost::gregorian::date Date1(2022, 03, 20);
  boost::gregorian::day_iterator it_day(Date1);
  // 递增1天
  std::cout << "Date1 = it_day " << (it_day == Date1) << std::endl;
  ++it_day;
  std::cout << "Date1 fater one day = it_day "
            << (it_day == boost::gregorian::date(2022, 03, 21)) << std::endl;

  // 递增步长为10年
  boost::gregorian::year_iterator it_year(*it_day, 10);
  std::cout << "it_year == Date1 + 1 day "
            << (it_year == Date1 + boost::gregorian::days(1)) << std::endl;
  // 递增10年
  ++it_year;
  std::cout << "it_year = Date1 + 1 day + 10 years "
            << (it_year ==
                Date1 + boost::gregorian::days(1) + boost::gregorian::years(10))
            << std::endl;

  // 迭代器并非标准，无法完成+=等方法调用，除非定义相关内部类
  boost::gregorian::day_iterator it_day_other =
      boost::gregorian::day_clock::local_day();
  ++it_day_other;  // 正确
  //  it_day_other += 2;    // 错误，无法编译
  //  std::advance(it_day_other, 2);  // 错误，无法编译
}

void TimeDate::OtherUse() {
  // 是否闰年
  std::cout << "2017 is leap "
            << boost::gregorian::gregorian_calendar::is_leap_year(2008)
            << std::endl;
  // 某月最后一天
  std::cout << "last day of 2022/02 "
            << boost::gregorian::gregorian_calendar::end_of_month_day(2022, 02)
            << std::endl;
}
