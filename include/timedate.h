#ifndef TIMEDATE_H
#define TIMEDATE_H
#undef BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
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

template <typename Clock = boost::posix_time::second_clock>
class basic_ptimer {
 public:
  basic_ptimer() {
    // 初始化起始时间
    restart();
  }
  void restart() { _start_time = Clock::local_time(); }
  void elapsed() const {
    std::cout << Clock::local_time() - _start_time << std::endl;
  }
  ~basic_ptimer() {
    // 析构函数自动输出时间
    elapsed();
  }

 private:
  // 保存计时开始时间
  boost::posix_time::ptime _start_time;
};

typedef basic_ptimer<boost::posix_time::microsec_clock> ptimer;
typedef basic_ptimer<boost::posix_time::second_clock> sptimer;

// 计算工作时间：表示工作日工作时间：上班前/上午/中午/下午/下班后，根据
// 当前时间给用户一个友好的提示信息
class work_time {
 public:
  // time_period 可以用来比较大小，因此可以作为map的Key
  typedef std::map<boost::posix_time::time_period, std::string> map_t;
  work_time() { init(); }
  // 使用for遍历map容器，判断时间点是否在某个时间区间内，如果是则输出对应的问候语
  void greeting(const boost::posix_time::ptime& t) {
    for (auto& x : m_mapTs) {
      if (x.first.contains(t)) {
        std::cout << x.second << std::endl;
        break;
      }
    }
  }

 private:
  // 保存时间段与问候语的关系
  map_t m_mapTs;
  // 初始化时间与问候语，向Map插入数据
  void init() {
    // 获得当天的日期，零点
    boost::posix_time::ptime p(boost::gregorian::day_clock::local_day());
    // 到9：00
    m_mapTs[boost::posix_time::time_period(p, boost::posix_time::hours(9))] =
        "太早了，请休息！\n";
    p += boost::posix_time::hours(9);
    // 到12：30
    m_mapTs[boost::posix_time::time_period(
        p, boost::posix_time::hours(3) + boost::posix_time::minutes(30))] =
        "上午时间，请努力工作！\n";
    p += boost::posix_time::hours(3) + boost::posix_time::minutes(30);
    // 到13:30
    m_mapTs[boost::posix_time::time_period(p, boost::posix_time::hours(1))] =
        "午餐时间，您饿了吗？\n";
    p += boost::posix_time::hours(1);
    // 到18：00
    m_mapTs[boost::posix_time::time_period(
        p, boost::posix_time::hours(4) + boost::posix_time::minutes(30))] =
        "下午时间，准备下班！\n";
    p += boost::posix_time::hours(4) + boost::posix_time::minutes(30);
    // 18：00以后
    m_mapTs[boost::posix_time::time_period(p, boost::posix_time::hours(6))] =
        "您还在上班吗？您需要休息。\n";
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
  // 时间精确度
  // 定义宏BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG时间分辨率将精确到纳秒
  void TimePrecision();
  // 时间点定义
  void TimePoint();
  // 时间区间
  void TimePeriod();
  // 时间迭代器
  void TimeIterator();
  // 格式化时间
  void TimeFormat();
  // 本地时间
  void TimeLocal();

 private:
  boost::timer m_BoostTimer;
  ptimer m_ptimer;
  sptimer m_sptimer;
};

#endif  // TIMEDATE_H
