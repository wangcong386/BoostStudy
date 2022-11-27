#ifndef TIMEDATE_H
#define TIMEDATE_H
#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/progress.hpp>
#include <boost/timer.hpp>
#include <sstream>

class CreditCard {
 public:
  // 银行名
  std::string m_sBankName;
  // 记账日
  int m_nBillDayNo;
  // 构造函数
  CreditCard(const char* BankName, int BillDayNo)
      : m_sBankName(BankName), m_nBillDayNo(BillDayNo){};
  // 计算信用卡免息期，根据传入的消费日期得到下一个记账日期，并计算免息期
  int CalcFreeDays(boost::gregorian::date ConsumeDay =
                       boost::gregorian::day_clock::local_day()) const {
    // 得到记账日期
    boost::gregorian::date BillDay(ConsumeDay.year(), ConsumeDay.month(),
                                   m_nBillDayNo);
    // 消费日是否已经过了记账日期
    if (ConsumeDay > BillDay) {
      // 如果过了，则是下个月的记账日
      BillDay += boost::gregorian::months(1);
    }

    // 计算免息期
    return (BillDay - ConsumeDay).days() + 20;
  }
  // 为支持比较操作，还需要增加小于比较操作符重载
  friend bool operator<(const CreditCard& l, const CreditCard& r) {
    return l.CalcFreeDays() < r.CalcFreeDays();
  }
};

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
  // 日期区间
  void DatePeriod();
  // 日期迭代器
  void DateIterator();
  // 其他功能
  void OtherUse();
  // 综合运用：显示月历
  void ShowMonth();
  // 综合运用：简单日期计算
  void SimpleDateCalc();
  // 综合运用：计算信用卡免息期
  void CreditCardFreeDaysCalc();

  // 操作时间长度
  void OperateTimeDuration();

 private:
  boost::timer m_BoostTimer;
};

#endif  // TIMEDATE_H
