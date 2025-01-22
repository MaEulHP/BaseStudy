# 구체 타입
- 기본 개념: 내장 타입과 완전히 똑같이 동작
    - 복소수, 무한 정밀도 정수: `int`
    - `vector`, `string`: 배열
- 구체 타입의 특징을 정의한다 -> 표현을 정의에 넣는다
- 구체 타입 표현은 다음이 가능
    - 구체 타입의 객체를 스택, 정적으로 할당된 메모리, 다른 객체 내에 둘 수 있음
    - 객체를 직접 참조할 수 있음
    - 객체를 즉시 그리고 완전하게 초기화할 수 있음
    - 객체를 복사하고 이동할 수 있음
- 표현은 프라이빗, 멤버 함수를 통해서만 접근이 가능
    - 하지만 분명히 존재
    - 표현이 눈에 띄게 바뀌게 되면 다시 컴파일이 필요
        - 완전히 내장 타입처럼 동작시키는 대가
- 구체 타입을 사용하는 때: 명확성과 효율성을 제공하는 타입      
- 유연성을 높이기 위해 표현은 대부분 동적 메모리, 힙에 두고 객체 자체에 저장된 부분을 통해 접근
## 산술 타입
- 전형적인 사용자 정의 산술 타입의 예: `complex`
- `complex`의 단순화 버전
```
class complex {
    double re, im;
public:
    complex(double r, double i) :re{r}, im{i} {}
    complex(double r) :re{r}, im{0} {}
    complex() :re{0}, im{0} {}

    double real() const { return re; }
    void real(double d) { re=d; }
    double imag() const { return im; }
    void imag(double d) { im=d; }

    complex& operator+=(complex z)
    {
        re+=z.re;
        im+=z.im;
        return *this;
    }
    complex& operator-=(complex z)
    {
        re-=z.re;
        im-=z.im;
        return *this;
    }

    complex& operator*=(complex);
    complex& operator/=(complex);
};
```
    - 표현에 필요한 연산만 포함
    - 간단하고 매우 평범
- 구현하는 클래스
    - 효율적이어야 함. 왜?
    - 그렇지 않으면 사용할 이유가 없음
- 효율적이게 구현하려면?
    - 간단한 연산은 인라인 함수
    - 즉, 함수 호출 없이 기계 코드로 구현

- 복사 할당과 복사 초기화는 암묵적으로 정의

- 기본 생성자: 인수 없이 호출이 가능한 생성자
    - 기본 생성자를 정의하면 그 타입의 초기화 되지 않은 변수가 생길 가능성이 사라짐
- 함수의 const 지정자: 호출한 객체를 수정하지 않겠다
    - const 멤버 함수: const와 비const 객체 모두 호출 가능
    - 비const 멤버 함수: 비const 객체만 호출 가능
- 사용자 정의 연산자(위의 `operator+=`등)
    - 신중하게, 관례에 따라서 사용
