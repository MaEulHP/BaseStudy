# 상수
- C++는 두 가지 불변성 표기법을 지원
    - `const`
        - 이 값을 바꾸지 않겠다 -> 인터페이스를 명시할 때 주로 사용
        - 수정될 염려 없이 포인터와 참조를 사용해 함수에 데이터를 전달하기 위함
        - 컴파일러는 `const`로 명시한 약속을 이행
        - `const` 값은 런타임에 계산 가능 
    - `constexpr`
        - 컴파일 타임에 평가된다
        - 상수를 명시, 읽기 전용 메모리 내 데이터, 성능 향상이 주 목적
        - 컴파일러가 계산해야 함
```
constexpr int dmv = 17;
int var = 17;
const double sqv = sqrt(var);

double sum(const vector<double>&);

vector<double> v {1.2, 3.4, 4.5};
const double s1 = sum(v); // 가능: 런타임에 평가
constexpr double s2 = sum(v); // 에러: sum(v)는 상수식이 아님 
```

- 상수식(컴파일러가 평가할 식)에 함수를 사용하려면 그 함수를 `constexpr`이나 `consteval`로 정의해야 함
```
constexpr double square(double x) { return x*x; }

constexpr double max1 = 1.4*square(17); // 가능: 상수식
constexpr double max2 = 1.4*square(var); // 에러: var이 상수가 아님. square(var)는 상수식이 아님

const double max3 = 1.4*square(var); // 가능: 런타임에 평가 
```

- 상수가 아닌 인수에 `constexpr` 사용 가능 -> 결과는 상수식이 아님
    - `constexpr`함수에서 상수식이 필요하지 않은 상황: 상수식이 아닌 인수로 호출
    - 본질적으로 같은 함수를 상수식에 하나, 변수에 하나 또는 두 번 정의하지 않아도 됨
- 함수를 컴파일 타임 평가에만 사용하고 싶다: `consteval`
```
consteval double square2(double x) { return x*x; }

constexpr double max1 = 1.4*square2(17);
const double max3 = 1.4*square2(var);
```

- `constexpr` 또는 `consteval`로 선언한 함수: 순수 함수(pure function) 개념
    - 부수 효과(side effect)가 발생하지 않음
    - 인수로 전달되는 정보만 이용
    - 지역이 아닌 변수를 수정할 수 없음 -> 루프로 자신만의 지역변수를 사용 가능
```
constexpr double nth(double x, int n)
{
    double res = 1;
    int i = 0;
    while(i<n) {
        res *= x;
        ++i;
    }
    return res;
}
```

- 몇 가지 언어 규칙에 상수식이 필요
    - 배열 범위
    - case 레이블
    - 템플릿 값 인수
    - constexpr로 선언한 상수
- 컴파일 타임 평가가 성능에 중요할 때가 존재
    - 제외하더라도 불변성은 중요한 디자인 관심사 