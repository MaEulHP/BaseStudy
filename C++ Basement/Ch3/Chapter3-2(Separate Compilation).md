# 분리 컴파일(Separate Compilation)
- 사용자 코드에 대해서
    - 사용할 타입
    - 함수의 선언
    - 두 가지만 보여지는 개념
- 방법
    - 헤더 파일: 헤더 파일이라는 별개의 파일에 선언을 작성
        - 이후 선언이 필요한 곳에서 헤더 파일명으로 `#include`
    - 모듈: module 파일을 정의해 별도로 컴파일
        - 이후 필요한 곳에서 `import`
        - 명시적으로 `export`한 선언만이 그 모듈을 `import`한 코드에 보여짐
- 프로그램을 반독립적인 코드 조각 집합으로 조직
- 분리를 통해 컴파일 횟수가 최소화
- 논리적으로 구분된 프로그램의 여러 부분이 분리
    - 오류 가능성 최소화
- 라이브러리: 별도로 컴파일된 코드 조각
- C++ 20부터 `module`이 새로 나옴
## 헤더 파일
- 인터페이스를 명시한 선언은 그 용도를 나타내는 이름
```
// Vector.h:
class Vector {
    public:
        Vector (int s);
        double operator[](int i);
        int size();
    private:
        double* elem;
        int sz;
};
```
- 해당 선언을 `Vector.h` 파일에 작성
- 사용자는 `Vector.h` 파일을 `#include`해 인터페이스에 접근
```
// user.cpp:
#include "Vector.h"
#include <iostream>

double sqrt_sum(const Vector& v)
{
    double sum = 0;
    for (int i=0; i!=v.size(); ++i){
        sum += std::sqrt(v[i]);
    }
    return sum;
}
```
- Vector를 구현한 .cpp 파일에도 인터페이스를 제공하는 .h파일을 인클루드
```
// Vector.cpp
#include "Vector.h"

Vector::Vector(int s)
    :elem{new double{s}}, sz{s}
{}
...
```
- user.cpp와 Vector.cpp 코드는 Vector.h의 Vector 인터페이스 정보를 공유
- 그 외에는 독립적, 별개로 컴파일 가능
- 프로그램을 조직하는 가장 좋은 방법
    - 종속성을 잘 정의한 모듈집합으로 프로그램을 보는 것
    - 헤더 파일을 통해 이러한 모듈성을 나타낼 수 있음
    - 분리 컴파일을 통해 이러한 모듈성을 활용
- 독립적으로 컴파일되는 .cpp 파일을 변역 단위라고 부름
### 단점
- 컴파일 시간:
    - `header.h`를 100개의 번역단위(.cpp 파일)에서 `#include`
    - 컴파일러는 `header.h`의 텍스트를 100번 처리
- 순서 종속성:
    - `header2.h`보다 `header1.h`를 먼저 `#include`
    - `header1.h`의 선언과 매크로가 `header2.h` 내 코드 의미를 변경할 수도 있음
    - 먼저 선언한 헤더 파일이 이후 헤더 파일 내 코드에 영향
- 비일관성:
    - 타입이나 함수 같은 엔티티를 한 파일에 정의
    - 조금 다르게 다른 파일에 정의
    - 고장 또는 알아채기 어려운 오류 
    - 우연히 혹은 고의로
- 이행성:
    - 헤더 파일 내 선언 표현에 필요한 모든 코드는 그 헤더 파일에 제시
        - 헤더 파일이 다른 헤더를 `#include`하지 않도록
    - 헤더가 헤더를 계속 include: 코드가 거대해짐

## 모듈
- C++20부터 지원한 방식
- 예제: Vector 코드 작성
```
export module Vector;

export class Vector{
    public:
        Vector(int s);
        double& operator[](int s);
        int size();
    private:
        double* elem;
        int sz;
};
Vector::Vector(int s)
    :elem{new double[s]}, sz{s}
{}
double& Vector::operator[](int i){
    return elem[i];
}
int Vector::size(){
    return sz;
}
export bool operator==(const Vector& v1, const Vector& v2){
    if(v1.size()!=v2.size()) return false;
    for(int i=0; i<v1.size(); ++i)
        if(v1[i]!=v2[i]) return false;
    return true;
}
```
- 해당 코드는 Vector 모듈을 정의
    - Vector 클래스
    - 클래스의 모든 함수
    - == 연산자를 정의하는 비멤버 함수
- 모듈을 사용하려면 필요한 곳에서 `import`
```
import Vector;
#include <cmath>

double sqrt_sum(Vector& v){
    double sum = 0;
    for(int i=0; i!=v.size(); ++i){
        sum+=std::sqrt(v[i]);
    }
    return sum;
}
```
- `#include`와 `import`를 동시에 사용 가능
- 헤더와 모듈의 차이점
    - 모듈은 딱 한번 컴파일(헤더는 번역 단위)
    - 두 모듈은 의미에 영향을 주지 않음
        - 어떤 순서로도 임포트 가능
    - 모듈로 `import`하거나 `#include`하면 모듈의 사용자는 암묵적으로 그 모듈에 접근할 수 없음
        - 즉, `import`는 이행적이지 않음
- "Hello, World!" 프로그램 측정: 모듈이 헤더보다 10배 빠름
    - 근데 `#include <iostream>`보다 `import std`의 정보량이 10배 가량 많음
    - 왜 이런 결과가 나오는가?
- 헤더는 직, 간접적으로 포함하는 것을 전부 컴파일러에 전달
    - 모듈은 인터페이스만 export
- 모듈은 선언과 정의를 별도의 파일로 분리하지 않음
    - `export` 지정자로 명시
    - 컴파일러가 지정자를 통해 인터페이스와 세부 구현을 분리
    - 인터페이스를 명시적으로 명명하지 않아도 컴파일러가 생성
- 모듈은 `export`된 선언으로의 접근 권한만 부여
```
export module vector_printer;

import std;

export
template<typename T>
void print(std::vector<T>& v)
{
    cout << "{\n";
    for (const T& val : v)
        std::cout << " " << val << "\n";
    cout << "}";
}
```
- 평범한 모듈을 `import`
    - 모든 표준 라이브러리에 접근이 불가능
    - 왜?
        - `import std`는 모듈 내부에 있음
        - 모듈 외부로 export하지 않았기 때문에 사용할 수 없음 