#include <QApplication>
#include <QDebug>
#include <boost/config.hpp>
#include <boost/version.hpp>

#include "boosttestwin.h"
#include "timedate.h"

int main(int argc, char *argv[]) {
  // Boost 库版本号信息
  std::cout << "**********boost info**********" << std::endl;
  std::cout << "Boost Version" << BOOST_VERSION << std::endl;
  std::cout << "Boost Lib Version" << BOOST_LIB_VERSION << std::endl;
  std::cout << "Boost platform" << BOOST_PLATFORM << std::endl;
  std::cout << "Boost compiler" << BOOST_COMPILER << std::endl;
  std::cout << "Boost StdLib" << BOOST_STDLIB << std::endl;
  std::cout << "**********boost info end**********" << std::endl;

  // Boost timer测试
  TimeDate timeDate;
  //  timeDate.Print();
  //  timeDate.ProgressTimerPrint();
  //  timeData.DateDefineCompare();
  //  timeDate.DayClockTest();
  //  timeDate.SpecialDay();
  //  timeDate.AccessOfDate();
  //  timeDate.DateOutput();
  //  timeDate.CTransform();
  //  timeDate.DateDuration();
  //  timeDate.DatePeriod();
  //  timeDate.DateIterator();
  //  timeDate.OtherUse();
  //  timeDate.ShowMonth();
  //  timeDate.SimpleDateCalc();
  //  timeDate.CreditCardFreeDaysCalc();
  //  timeDate.OperateTimeDuration();
  //  timeDate.TimePrecision();
  //  timeDate.TimePoint();
  //  timeDate.TimePeriod();
  timeDate.TimeIterator();
  QApplication a(argc, argv);
  BoostTestWin w;
  w.show();
  return a.exec();
}
