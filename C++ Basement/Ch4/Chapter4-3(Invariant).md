# 불변식(Invariant)
## 예제에 대한 예외 처리
- 예외를 사용해 `out_of_range` 접근을 알리는 방식
    - 인수를 검사, 기본 가정(전제 조건)이 성립하지 않았을 때 동작을 거절
    - Vector의 첨자 지정 연산자의 기본 가정: "인덱스는 [0:size()) 범위에 속해야 한다"
        - [a:b): a는 속하고, b는 속하지 않는 범위
- 함수를 정의할 때는 항상 그 함수의 전제 조건이 무엇인가, 테스트가 필요한가 생각
## 그래서 불변식이 무엇인가?
- 예제: Vector 타입 객체에 대한 operator[]()를 수행
    - Vector의 멤버가 "적절한 값"이 아니면 계산이 불가능
    - `elem`은 `sz`개의 `double`로 된 배열
- Class Invariant(또는 Invariant)
    - 객체가 정상적인 상태(유효한 상태)에 있을 때 반드시 성립해야 하는 조건
        - 클래스가 항상 만족해야 하는 논리적 조건
    - 클래스 내부의 논리적 일관성을 유지하는 데에 중요
- 생성자의 역할
    - 클래스의 불변식을 정립
    - 함수가 종료될 때까지 멤버 함수가 그 불변식을 유지하도록 하는 것 
    - 예제는 부분적으로만 완수
        - Vector의 멤버를 적절히 초기화, 전달 받은 인수가 타당한지 검사X
        - `Vector v(-27)` 가능?
```
Vector::Vector(int s)
{
    if(s<0)
        throw length_error{ "Vector constructor: negative size" };
    elem = new double[s];
    sz = s;
}
```
- `new` 연산자에서 할당할 메모리를 찾을 수 없음: `std::bad_alloc`을 던짐
```
void test(int n)
{
    try {
        Vector v(n);
    }
    catch (std::length_error& err) {
        // ...
    }
    catch (std::bad_alloc& err) {
        // ...
    }
}
void run()
{
    test(-27); // length_error를 던진다
    test(1000000000); // bad_alloc을 던질 것이다
    test(10); // 아마 Ok
}
```
- 메모리 고갈
    - 머신이 제공하는 것보다 많은 메모리를 요청
    - 이미 메모리 대부분을 소비했으나 그 제한을 넘어 요청
    - 최신 운영체제는 물리적 메모리보다 많은 공간을 제공
        - `bad_alloc` 이전에 심각한 속도 저하
- 예외를 던지고 할당된 작업을 완료하지 못하는 경우가 종종 있음
    - 최소한의 지역 해제(clean-up)를 수행하고 예외를 다시 던짐
```
void test(int n)
{
    try {
        Vector v(n);
    }
    catch (std::length_error& err) { // 무언가 하고 다시 던짐
        cerr << "test failed: length_error\n";
        throw;
    }
    catch (std::bad_alloc& err) { // 메모리 고갈을 처리할 수 없어요
        std::terminate(); // 종료
    }
}
```
## 결론
- 불변식은 클래스 디자인의 핵심
- 전제 조건은 함수 디자인에서 불변식과 비슷한 역할을 함
- 불변식 수립은 정확히 무엇을 하고 싶은지 명확히 해줌
- 불변식을 통해 구체적으로 바뀜. 코드를 더 정확하게 바꿀 기회를 제공 