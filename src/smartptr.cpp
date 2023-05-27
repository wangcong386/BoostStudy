#include "smartptr.h"

#include <vector>
SmartPtr::SmartPtr() {}

void SmartPtr::CreateScopedPtr() {
  // 构造一个scoped_ptr对象
  boost::scoped_ptr<std::string> sp(new std::string("wangcong"));
  // 使用显式bool转型
  assert(sp);
  // 控指针比较操作
  assert(sp != nullptr);
  // *和->操作符
  std::cout << *sp << std::endl;
  std::cout << sp->size() << std::endl;
  // 错误：scoped_ptr不能拷贝构造，无法编译
  //  boost::scoped_ptr<std::string> sp1 = sp;
}

void SmartPtr::CreateUniquePtr() {
  // 先声明一个unique_ptr，管理int指针
  std::unique_ptr<int> up(new int);
  // 在bool语境中测试指针是否有效
  assert(up);
  // 使用operator*操作指针
  *up = 10;
  std::cout << *up << std::endl;
  // 释放指针
  up.reset();
  // 此时不管理任何指针
  assert(!up);
}

void SmartPtr::MakeUnique() {
  // boost::make_unique()用法与C++14标准一样

  // 使用auto创建unique_ptr<int>对象
  auto p = boost::make_unique<int>(10);
  // 访问指针内容
  assert(p && *p == 10);
}

void SmartPtr::SharedPtrUsage() {
  // 一个指向整数的shared_ptr
  std::shared_ptr<int> sp(new int(10));
  // 当前shared_ptr是指针的唯一持有者
  assert(sp.unique());
  // 第二个shared_ptr，拷贝构造函数
  std::shared_ptr<int> sp1(sp);
  // 两个shared_ptr相等
  assert(sp == sp1);
  // 指向同一个对象，引用计数为2
  assert(sp.use_count() == 2);
  // 使用解引用操作符修改被指向对象
  *sp = 100;
  // 另一个shared_ptr也被修改
  assert(*sp1 == 100);
  // 停止shared_ptr的使用，sp不再持有任何指针（空指针）
  sp.reset();
  assert(!sp);
}

void SmartPtr::SharedPtrUsage1() {
  // shared_ptr持有整数指针
  std::shared_ptr<int> p(new int(100));
  // 构造两个自定义类
  Share s1(p), s2(p);

  s1.print();
  s2.print();

  // 修改shared_ptr所指的值
  *p = 20;
  print_sharedptr_func(p);

  s1.print();
}

void SmartPtr::MakeShare() {
  // 创建string的共享指针
  std::shared_ptr<std::string> sp1 = std::make_shared<std::string>(__func__);
  // 创建vector的共享指针
  std::shared_ptr<std::vector<int>> sp2 =
      std::make_shared<std::vector<int>>(10, 2);
  assert(sp2->size() == 10 && sp2->at(9) == 2);
}

void SmartPtr::SharedPtrContainer() {
  // 一个持有shared_ptr的标准容器类型
  typedef std::vector<std::shared_ptr<int>> vs;
  // 声明一个拥有10个元素的容器，元素被初始化为空指针
  vs v(10);
  int i = 0;
  for (auto pos = v.begin(); pos != v.end(); ++pos) {
    // 使用工厂函数赋值
    *pos = std::make_shared<int>(++i);
    // 输出值
    std::cout << *(*pos) << ", ";
    std::cout << std::endl;
  }
  std::shared_ptr<int> p = v[9];
  *p = 100;
  std::cout << *v[9] << std::endl;
}
