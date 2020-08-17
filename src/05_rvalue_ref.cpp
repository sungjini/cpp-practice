/*
 * rvalue reference를 사용하여, rvalue에 대한 복사가 아닌 이동의 구현이 가능하게 됨
 *
 * l-value를 r-value로 취급하게 바꿔주는 함수 : move semantic
 * - rvalue()로 casting
 */
#include <iostream>

class A
{
 private:
  int data_;

 public:
  A(int data) : data_(data)
  {
    std::cout << "일반 생성자 호출!" << std::endl;
  }

  A(const A& a) : data_(a.data_) {
    std::cout << "복사 생성자 호출!" << std::endl;
  }
};

int main()
{
  A a(1);
  A b(a);

  /*
   * copy elision 발생 : 컴파일러 opt가 복사를 생략해버리는 작업
   */
  A c(A(2));
}
