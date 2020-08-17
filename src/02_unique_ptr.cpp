#include <iostream>
#include <memory>
#include <vector>

/*
 * reference : https://modoocode.com/229
 */

class A
{
  int *data;

 public:
  A() {
    std::cout << "resource acquistion\n";
    data = new int[100];
  }

  void some() {
    std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl;
  }

  void do_some(int a) {
    std::cout << "무언가를 한다!" << std::endl;
    data[0] = a;
  }

  ~A() {
    std::cout << "resource release\n";
    delete[] data;
  }
};

void do_something()
{
  // 직접 생성하는 대신unique_ptr 이용 
  // A* pc = new A();
  /*
   * uniqut_ptr 변수인 pa는 stack 변수라 do_something 종료시 메모리 자동 해제됨
   * (소멸자 호출)
   */
  std::unique_ptr<A> pa(new A());
  std::cout << "pa : ";
  pa->some();
  
  /*
   * 아래 코드는 에러남 (attempting to reference a deleted function
   * 이유는 unique_ptr의 경우 copy constructor에 대해 delete 로 구현했기 때문에
   */
  //std::unique_ptr<A> pb = pa;

  /*
   * error: use of deleted function
   * unique_ptr의 copy constructor는 명시적으로 삭제되어있음
   * 왜냐하면, 어떤 객체를 유일하게 소유하도록 구현되어있기 때문에
   * (double free 문제 방지 위해)
   * 
   * [소유권 이전으로]
   * uniqu_ptr은 복사되지 않고, 소유권 이전할 수 있다.
   * - move constructor는 정의되어 있음
   * 
   */
  std::unique_ptr<A> pb = std::move(pa);
  std::cout << "pb : ";
  pb->some();
}

/*
 * 방법 1) 다른 함수에 unique_ptr 전달하기. 
 * 
 * reference로 전달하면 함수내에서 유일한 소유권이 있음을 보장하지 못한다.
 * (unique_ptr은 소유권을 의미한다는 원칙에 위배됨)
 * 
 * reference가 아닌 pointer 주소를 넘겨주면 됨
 * 이것의 의미는 소유권이라는 의미는 버린 채, 단지함수 내부에서 객체 접근 권한을 주는것임
 *
 * 방법 2) 소유권을 전달하기 위해서는 move 하면 됨
 */
void do_function(A* ptr)
{
  ptr->do_some(3);
}

void do_function2(std::unique_ptr<A> ptr) {
  ptr->do_some(4);
}

int main() {
  // step 1. unique_ptr 개념 이해
  do_something();

  // step 2. unique_ptr 함수에 전달하는 방법
  // unique_ptr을 reference 함수에 전달하는 것은 소유권이 함수내에서도 있게 됨
  // unique_ptr이 소유권이라는 의미를 망각한채 단순히 포인터 wrapper로 사용하는 것임


  // 소유권은 이동하지 않고, 함수내에서 일시적으로 접근하고 싶을 때,
  // unique_ptr은 caller의 stack이 끝날 때 release 됨
  std::unique_ptr<A> pa(new A());
  do_function(pa.get());

  // 소유권을 이동 시키면서 사용하는 방법
  do_function2(std::move(pa));
  std::cout << "이전 후 : " << pa.get() << std::endl;

  auto pb = std::make_unique<A>();
  std::vector<std::unique_ptr<A>> vec;

  /*
   * 아래는 unique_ptr의 복사 생성자에 접근하기 때문에 에러가 발생한다.
   * 그래서 rvalue를 받는 생성자가 호출되도록 수정
   */
  //vec.push_back(pb);
  /*
   * error: use of deleted function
   * 삭제된 unique_ptr의 copy constructor에 접근했기 때문에 발생
   * 방안 1) 명시적으로 vector 안으로 이동시켜줘야 한다.
   * (rvalue reference를 받는 push_back이 호출될 수 있도록)
   */
  vec.push_back(std::move(pb));

  /*
   * 방안 2) emplace_back은 perfect forwarding을 통해
   * unique_ptr<A> 객체를 직접 생성하기 떄문에, move 연산이 필요없게 됨
   * ※ 가장 효율적인 방안임
   */
  vec.emplace_back(std::make_unique<A>());
  vec.back()->some();
}
