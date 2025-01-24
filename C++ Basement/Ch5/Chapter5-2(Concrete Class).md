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
## 컨테이너
- 원소 묶음을 담아두는 객체(Vector 같은 것들, Vector도 컨테이너 클래스)
- 컨테이너 클래스의 치명적 결함
    - 할당한 원소를 절대 해제하지 않음
    - C++는 가비지 컬렉터를 제공하지 않음
    - 반드시 메모리를 해제할 메커니즘이 필요: 소멸자(destructor)
- ```~Vector() { delete[] elem; }```
- 소멸자 이름에는 클래스 명 앞에 부정 연산자 작성, 생성자와 역할이 반대이기 때문
- 생성자와 소멸자 조합은 여러 정교한 기법의 근간, 특히 자원 관리 기법
    - 생성자는 원소를 할당하고 멤버를 적절히 초기화
    - 소멸자는 원소를 해제
    - 이러한 데이터 처리 모델은 객체의 수명 주기 동안 크기가 다양하게 변할 수 있는 데이터 관리에 일반적으로 사용
    - RAII(Resource Acquisition Is Initialization, 자원획득은 초기화)라고 함
        - 무방비로 쓰이는 `new`연산, `delete`연산을 제거
        - 오류 발생 가능성을 줄이고 자원 누수를 피하기 쉬움
### 컨테이너 초기화
- 컨테이너에 원소 담기: 편한 방법이 없을까?
- 기본: 그냥 처음부터 적절한 숫자로 컨테이너 생성 후 할당
- 더 정교한 방법
    - 초기 리스트 생성자: 원소 리스트로 초기화
    - `push_back()`: 새 원소를 시퀀스 끝에 추가
```
class Vector {
public:
    Vector();
    Vector(std::initializer_list<double>);
    // ...
    void push_back(double);
    // ...
};
```
- 초기 리스트 생성자에 쓰인 std::initializer_list -> 표준 라이브러리 타입
    - `{}` 리스트를 사용해 initializer_list 타입의 객체를 생성한 뒤 프로그램에 넘겨줌
```
Vector::Vector(std::initializer_list<double> lst)
    :elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
{
    copy(lst.begin(), lst.end(), elem);
}
```
- 표준 라이브러리는 `unsigned int` 사용 -> `static_cast`로 형변환
    - 굳이 범위 안벗어나면 안해도 되지 않나요? -> 아님
    - 어떤 오류를 뱉을지 모름
- `static_cast`는 변환 중인 값을 검사하지 않음
    - 항상 옳은 가정이 아니므로, 의심이 될 때 값을 검사하도록 해야함
    - 명시적 타입 변환은 최대한 피하는게 좋으므로, 시스템 최하단에서 확인되지 않은 캐스트를 사용하는 것이 좋음
- 그 밖의 `cast`
    - `reinterpret_cast`, `bit_cast`: 객체를 단순히 바이트 시퀀스로 처리
    - `const_cast`: `const` 제거