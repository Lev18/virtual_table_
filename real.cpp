#include <iostream>

class A {
private:
  std::string m_name;
public:
  A () : m_name{"A"} {}

  void sf() {
    std::cout << m_name << std::endl;
  }

  virtual void vf() {
    std::cout << "mello" << std::endl;
  }
};

class B {
private:
  std::string cl_name;
public:
  B() : cl_name{"B"} {}
  
  void vf()  {
    std::cout << "hello" << std::endl;
  }

  virtual void nf() {
    std::cout << "chmello" << std::endl;
  }

};
class C : public A{
private:
 int s;
public:
  void vf() override {
    std::cout << "C virtual func" << std::endl;
  }
};

int main() {
  A ob;
  B obj;
  C obc;
}
