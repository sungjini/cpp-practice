/**
 * [Class]
 * 구조체 불편함
 * 1) 함수호출시 객체를 넘겨줘야 함
 * play(list[play_with]) => list[play_with]->play() 
 * 대신 각 변수 자신의 함수를 호출하는 식으로 변경하면,
 * 함수들마다 인자 넘길 필요도 없고
 * 함수 내부에서도 ->, .을 사용하여 접근할 필요가 없어짐 (좋네...)
 *
 * play가 list(play하는데 animal이 한다)를 하는 것이 아닌, anminal이 play 한다가 더 읽기 쉬움
 *
 * 2) 할당 다음에 만들시 초기화를 해줘야 하는 경우 보장하기 힘듬
 * list[animal_num] = num Animal;
 * create_animal(list[animal_num]); 이후에 play  사용해야 함
 * 
 * 생성자 내부에서 초기화 처리 해주면 사용이 간단해짐
 *
 * [new와 malloc의 차이]
 * new는 동적 할당 이후, constructor를 호출한다.
 *
 * [initializer list]
 * 초기화 리스트를 사용하는 것은 생성과 초기화를 동시에 한다.
 * 즉, initializer list는 복사 생성자가 호출되고, 
 * consturctor 초기화는 default 생성자가 호출된 뒤 assign이 수행.
 * 
 * reference와 const는반드시 생성과 동시에 초기화되어야 한다. 
 * 그래서, intializer list를 사용해야 한다.
 *
 * [constant member function]
 * 이 함수는 다른 변수의 값을 바꾸지 않는 함수라고 프로그래머에게 명시해줌
 * 상수 함수내에서는 객체들의 '읽기'만이 수행되며,
 * 상수 함수내에서는 다른 상수함수만 호출할 수 있다.
 * getXXX()에서 사용
 */

