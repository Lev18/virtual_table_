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
    std::cout << "virtual function" << std::endl;
  }
};

class B {
private:
  std::string cl_name;
public:
  B() : cl_name{"B"} {}
  
  void vf()  override{
    std::cout << "override virtual function" << std::endl;
  }

  virtual void nf() {
    std::cout << "B virtual function" << std::endl;
  }

};
class C : public B{
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
