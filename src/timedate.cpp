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

void TimeDate::ShowMonth() {
  boost::gregorian::date d(2017, 1, 23);

  // 当月第一天
  boost::gregorian::date month_start(d.year(), d.month(), 1);
  // 当月最后一天
  boost::gregorian::date month_end = d.end_of_month();
  // 构造日期迭代器
  for (boost::gregorian::day_iterator d_iter(month_start); d_iter != month_end;
       ++d_iter) {
    // 输出日期和星期
    std::cout << *d_iter << " " << d_iter->week_number() << std::endl;
  }
}

void TimeDate::SimpleDateCalc() {
  /** 计算一个人18岁生日是星期几，当月几个星期天，当年多少天
   *  */
  // 声明一个日期对象
  boost::gregorian::date Date(2017, 1, 23);

  // 18岁生日日期
  boost::gregorian::date Date18YearOld = Date + boost::gregorian::years(18);
  std::cout << "此人18岁生日是星期" << Date18YearOld.day_of_week() << std::endl;

  // 星期天计数器
  int nSundayCnt = 0;
  // 迭代器统计星期天数量
  // 当月第一天
  boost::gregorian::date FirstDayOfMonth18YearsOld(Date18YearOld.year(),
                                                   Date18YearOld.month(), 1);
  for (boost::gregorian::day_iterator d_iter(FirstDayOfMonth18YearsOld);
       d_iter != Date18YearOld.end_of_month(); ++d_iter) {
    if (d_iter->day_of_week() == boost::gregorian::Sunday) {
      ++nSundayCnt;
    }
  }
  std::cout << "当月有" << nSundayCnt << "个星期天" << std::endl;

  // 当年天数计数器
  int nDayOfYearCnt = 0;
  // 当年第一天
  boost::gregorian::date FirstDayOfYear18YearsOld(Date18YearOld.year(), 1, 1);
  boost::gregorian::date FirstDayOfYear19YearsOld(Date18YearOld.year() + 1, 1,
                                                  1);
  // 构造月迭代器，按月统计每月天数
  for (boost::gregorian::month_iterator m_iter(FirstDayOfYear18YearsOld);
       m_iter < FirstDayOfYear19YearsOld; ++m_iter) {
    // 累加每月天数
    nDayOfYearCnt += m_iter->end_of_month().day();
  }
  std::cout << "当年有" << nDayOfYearCnt << "天" << std::endl;
  // 或者直接判断当年是否是闰年
  std::cout << "当年有"
            << (boost::gregorian::gregorian_calendar::is_leap_year(
                    Date18YearOld.year())
                    ? 366
                    : 365)
            << "天" << std::endl;
}

void TimeDate::CreditCardFreeDaysCalc() {
  // 创建两个信用卡对象，比较免息期
  CreditCard card1("A Bank", 25);
  CreditCard card2("B Bank", 15);
  CreditCard tmp = std::max(card1, card2);
  std::cout << "应当使用信用卡" << tmp.m_sBankName << "它的免息期为"
            << tmp.CalcFreeDays() << "天" << std::endl;
}

void TimeDate::OperateTimeDuration() {
  // 构造函数指定时/分/秒/微秒
  boost::posix_time::time_duration TD(1, 10, 10, 1000);

  // 子类更直观创建时间长度
  boost::posix_time::hours h(1);
  boost::posix_time::minutes m(10);
  boost::posix_time::seconds s(10);
  boost::posix_time::millisec ms(1000);
  boost::posix_time::time_duration TD1 = h + m + s + ms;

  // 也可直接赋值
  boost::posix_time::time_duration TD2 =
      boost::posix_time::hours(10) + boost::posix_time::minutes(19);

  // 使用工厂函数可以从字符串创建，冒号隔开
  boost::posix_time::time_duration TD3 =
      boost::posix_time::duration_from_string("1:10:30:001");

  // 时/分/秒可以使用如下函数访问
  boost::posix_time::time_duration TD4(1, 10, 30, 1000);
  assert(TD4.hours() == 1 && TD4.minutes() == 10 && TD4.seconds() == 30);
  // total_xx返回时间长度的总秒数/毫秒数/微秒数
  assert(TD4.total_seconds() == 1 * 3600 + 10 * 60 + 30);
  assert(TD4.total_milliseconds() == TD4.total_seconds() * 1000 + 1);
  // fractional_seconds以long返回微秒数
  assert(TD4.fractional_seconds() == 1000);

  // 时间长度可以取负值
  boost::posix_time::hours h1(-10);
  assert(h1.is_negative());
  boost::posix_time::time_duration TD5 = h1.invert_sign();
  assert(!TD5.is_negative() && TD5.hours() == 10);

  // 赋值特殊时间值
  boost::posix_time::time_duration TD6(boost::posix_time::not_a_date_time);
  assert(TD6.is_special() && TD6.is_not_a_date_time());
  boost::posix_time::time_duration TD7(boost::posix_time::neg_infin);
  assert(TD7.is_negative() && TD7.is_neg_infinity());

  // 字符串表示
  boost::posix_time::time_duration TD8(1, 10, 40, 100);
  std::cout << boost::posix_time::to_simple_string(TD8) << std::endl;
  std::cout << boost::posix_time::to_iso_string(TD8) << std::endl;
}
