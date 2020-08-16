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
  // A* pa = new A();
  /*
   * uniqut_ptr 변수인 pa는 stack 변수라 do_something 종료시 메모리 자동 해제됨
   * (소멸자 호출)
   */
  std::unique_ptr<A> pa(new A());
  std::cout << "pa : ";
  pa->some();
  
  /*
   * error: use of deleted function
   * unique_ptr의 copy constructor는 명시적으로 삭제되어있음
   * 왜냐하면, 어떤 객체를 유일하게 소유하도록 구현되어있기 때문에
   * (double free 문제 방지 위해)
   * 
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
  do_something();

  std::unique_ptr<A> pa(new A());
  do_function(pa.get());

  do_function2(std::move(pa));
  std::cout << "이전 후 : " << pa.get() << std::endl;

  auto pb = std::make_unique<A>();
  std::vector<std::unique_ptr<A>> vec;
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
   */
  vec.emplace_back(std::make_unique<A>());
  vec.back()->some();
}
