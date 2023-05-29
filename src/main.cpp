#include <QApplication>
#include <QDebug>
#include <boost/config.hpp>
#include <boost/version.hpp>

#include "boosttestwin.h"
#include "smartptr.h"
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
  // timeDate.Print();
  // timeDate.ProgressTimerPrint();
  // timeData.DateDefineCompare();
  // timeDate.DayClockTest();
  // timeDate.SpecialDay();
  // timeDate.AccessOfDate();
  // timeDate.DateOutput();
  // timeDate.CTransform();
  // timeDate.DateDuration();
  // timeDate.DatePeriod();
  // timeDate.DateIterator();
  // timeDate.OtherUse();
  // timeDate.ShowMonth();
  // timeDate.SimpleDateCalc();
  // timeDate.CreditCardFreeDaysCalc();
  // timeDate.OperateTimeDuration();
  // timeDate.TimePrecision();
  // timeDate.TimePoint();
  // timeDate.TimePeriod();
  // timeDate.TimeIterator();
  // work_time类使用
  // work_time wt;
  // wt.greeting(boost::posix_time::second_clock::local_time());
  // timeDate.TimeFormat();
  // timeDate.TimeLocal();

  // 智能指针测试
  SmartPtr smtPtr;
  // smtPtr.CreateScopedPtr();
  // 错误：scoped_ptr未定义递增操作符
  // smtPtr++;
  // 错误：scoped_ptr未定义递减操作符
  // std::prev(smtPtr);
  // 错误：SmartPtr类持有scoped_ptr的成员变量，因此无法被拷贝或赋值，以下两行均无法编译成功
  // SmartPtr smtPtr1(smtPtr);
  // SmartPtr smtPtr2 = smtPtr;
  // smtPtr.CreateUniquePtr();
  // smtPtr.MakeUnique();
  // smtPtr.SharedPtrUsage();
  // smtPtr.SharedPtrUsage1();
  // smtPtr.MakeShare();
  // smtPtr.SharedPtrContainer();
  // smtPtr.Pimpl();
  smtPtr.FactoryMode();
  QApplication a(argc, argv);
  BoostTestWin w;
  w.show();
  return a.exec();
}
