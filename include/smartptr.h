#ifndef SMARTPTR_H
#define SMARTPTR_H
#include <boost/smart_ptr/make_unique.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <iostream>
#include <string>
// 示范shared_ptr较为复杂的用法
// 一个拥有shared_ptr的类
class Share {
 private:
  std::shared_ptr<int> p;

 public:
  // 构造函数初始化shared_ptr
  Share(std::shared_ptr<int> p_) : p(p_) {}
  // 输出shared_ptr的引用计数和指向的值
  void print() {
    std::cout << "count:" << p.use_count() << " v=" << *p << std::endl;
  }
};
// 使用shared_ptr作为函数参数同样输出引用计数和指向的值
inline void print_sharedptr_func(std::shared_ptr<int> p) {
  std::cout << "count:" << p.use_count() << " v=" << *p << std::endl;
}
class SmartPtr {
 public:
  SmartPtr();
  void CreateScopedPtr();
  void CreateUniquePtr();
  void MakeUnique();
  void SharedPtrUsage();
  void SharedPtrUsage1();
  void MakeShare();
  // 示范了将shared_ptr应用于标准容器的方式
  void SharedPtrContainer();

 private:
  // 本类持有scoped_ptr的成员变量，因此无法被拷贝或赋值
  boost::scoped_ptr<int> m_scpPtr;
};

#endif  // SMARTPTR_H
