#ifndef SMARTPTR_H
#define SMARTPTR_H
#include <boost/smart_ptr.hpp>
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

// 示范应用于桥接模式
// 类sample，向外界暴露最小细节
class sample {
 private:
  // 不完整的内部类声明
  class impl;
  // shared_ptr成员变量
  boost::shared_ptr<impl> p;

 public:
  // 构造函数
  sample();
  // 提供给外界的接口
  void print();
};

// 示范应用于工厂模式用法
// 接口类定义
class abstract {
 public:
  virtual void f() = 0;
  virtual void g() = 0;

 protected:
  // 注意这里，定义为被保护的，除了它自己和它的子类，任何其他对象都无权调用delete删除之
  virtual ~abstract() = default;
};

// 定义abstract的实现子类
class impl : public abstract {
 public:
  impl() = default;
  virtual ~impl() = default;

 public:
  virtual void f() { std::cout << "class impl f" << std::endl; }
  virtual void g() { std::cout << "class impl g" << std::endl; }
};

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
  // 示范应用于桥接模式
  void Pimpl();
  // 示范应用于工厂模式
  boost::shared_ptr<abstract> FactoryCreate();
  void FactoryMode();

 private:
  // 本类持有scoped_ptr的成员变量，因此无法被拷贝或赋值
  boost::scoped_ptr<int> m_scpPtr;
};

#endif  // SMARTPTR_H
