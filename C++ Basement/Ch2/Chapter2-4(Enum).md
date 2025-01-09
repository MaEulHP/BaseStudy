# 열거
- 코드와 함께 보기
```
enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };

Color col = Color::red;
Traffic_light light = Traffic_light::red;
```
- 열거자(enumerator)
    - 각 `enum class` 범위에 속함
    - 다른 `enum class`에 혼란 없이 반복적으로 사용 가능
    - 예: `Color::red`와 `Traffic_light::red`는 다름

- 사용
    - 작은 정수 값 집합 표현
    - 상징적인 열거자 이름 사용: 코드 가독성 상향

- 왜 `class`?
    - 열거가 강형(strongly-typed)임을 명시
    - 열거자의 범위를 지정
    - 별도의 타입 지정: 우연히 상수를 잘못 사용하는 일 방지
```
Color x1 = red; // error
Color y2 = Traffic_light::red; // error
Color z3 = Color::red; // OK
auto x4 = Color::red; // OK
```
    - 정수 값도 암묵적으로 섞이지 않음
```
int i = Color::red; // error: Color::red는 int가 아님
Color c = 2; // 초기화 error: 2는 Color가 아님
```
- 내부 타입과 enum
    - 변환하려는 시도는 오류인가? 아님
    - 대개 enum의 내부 타입 값(기본값 int)으로 enum을 초기화하려 함
        - 허용됨
    - 내부 타입을 enum으로 명시적으로 변환할 때도 같음
```
Color x = Color{5};
Color y {6};
int x = int(Color::red);
```
- enum 연산
    - 기본 연산: 할당, 초기화, 비교
    - 열거는 사용자 정의 타입
        - 사용할 연산을 정의할 수 있음
```
Traffic_light& operator++(Traffic_light)
{
    switch(t) {
        case Traffic_light::green: return t=Traffic_light::yellow;
        case Traffic_light::yellow: return t=Traffic_light::red;
        case Traffic_light::red: return t=Traffic_light::green;
    }
}
auto signal = Traffic_light::red;
Traffic_light next = ++signal;
```
- 코드가 너무 길어요!
    - 범위 내에서 줄여쓰기
```
Traffic_light& operator++(Traffic_light)
{
    using enum Traffic_light; // 이 범위에서는 Traffic_light를 사용한다
    switch(t) {
        case green: return t=yellow;
        case yellow: return t=red;
        case red: return t=green;
    }
}
auto signal = Traffic_light::red;
Traffic_light next = ++signal;
```
## 일반적인 enum
- 열거자 이름을 한정하지 않겠다(명시적인 변환이 필요없도록)
    - 열거자 값은 int가 됨
- `enum class`가 아닌 그냥 `enum` 사용
- 암묵적으로 해당하는 정숫값으로 변환됨
- C++(C) 초창기부터 지원한 기능
    - 동작이 매끄럽지 못함 