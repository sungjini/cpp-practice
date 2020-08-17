/*
 * Dangling reference 예제
 * 
 * reference return 이유
 * 큰 구조체가 있을 때, 구조체 변수를 리턴하면
 * 전체 복사를 해야해서 시간이 오래걸림
 * (reference return은 주소값만 복사함)
 *
 * 함수에서 레퍼런스 리턴하기
 * 
 * return by value
 * return by address
 * - 동적 할당된 메모리 및 주소로 전달된 매개 변수를 반환할 때 사용
 * - 참조로 전달된 구조체나 클래스 반환활 때, return by address 사용
 * 
 * return by reference
 * - 함수 내에서 소멸하지 않는 구조체나 클래스를 반환할 때
 * - 함수에 전달된 배열 요소(ref)를 반환할 때
 * - 함수내에서 선언된 local 변수 반환(return by value) 사용
 * - 기본 배열이나 포인터 값을 반환할 때 (return by address) 사용
 * 
 * https://modoocode.com/169
 * https://boycoding.tistory.com/219
 * 
 * pass by value의 단점
 * - 배열, 구조체, 클래스 전달할 때, 복사가 발생해 비용이 듬
 * - 내부에서 변경 및 반환할 수 없음
 *
 * => pass by reference 
 * 반환대신, 인수를 수정하는 것이 더 명확하고 효율적일 수 있음
 * 만약 인수가 읽기 전용이라면 pass by const reference 사용
 * - 함수내에서 변경시 컴파일에러 및 프로그래머에게 알려줌
 * - const가 아닌 인수에 const 변수를 넘길 수 없지만, const 인수는 둘다 받을 수 있다.
 * ※ 규칙 : 참조로 인수를 전달할 때 인수 값을 변경해야 하는 경우가 아니면 항상 const 참조를 사용하자
 * 
 * pass by address
 * - array, pointer를 전달해야 할 때 사용한다. (반드시, null 체크를 해줘야 함)
 * ※ reference로 전달하는 것이 address로 전달하는 것보다 대부분 안전하다.
 */

#include <iostream>

int function() {
  int a = 5;
	return a;
}

/*
 * local 변수의 주소값을 넘김 : danging ref
 */
int& function_ref() {
  int a = 2;
  return a;
}

int main() {
  // 1.
  //int b = function_ref();
  //b = 3;

  /*
   * 2.
   * error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
   * 함수 종료후 값이 사라지는데, 주소를 지정하면 c는 danging ref가 됨
   */
  //int& c = function();

  /*
   * 3.
   * caller에서const reference로 리턴값을 받게되면 해당 리턴값의 생명이 연장됨
   * (레퍼런스가 사라질 때까지 연장됨)
   */
  const int& c = function();
  std::cout << "c: " << c << std::endl;

  /*
   * 4.
   * 사용할 경우는,
   * 
   */
  int& ref = function_ref();
  std::cout << "d: " << ref << std::endl;

  return 0;
}
