# 어설션(Assertion)
## 선택적 런타임 테스트
- 불변이나 전제 조건 등: 이를 작성하는 표준은 아직 존재하지 않음
- 현재는 애드혹 메커니즘에 의존
    - 유연하고 보편적이며 비활성화 시 비용이 발생하지 않음
    - 구현과 구상과 기교가 단순
- 예시
```
enum class Error_action { ignore, throwing, terminating, logging }; // 오류 처리 방법

constexpr Error_action default_Error_action = Error_action::throwing; // 기본 방법 

enum class Error_code { range_error, length_error };
string error_code_name[] { "range error", "length error" };

template<Error_action action = default_Error_action, class C>
contexpr void expect(C cond, Error_code x) // 예상 조건 "cond"가 성립하지 않으면 "action"
{
    if constexpr (action == Error_action::logging)
        if (!cond()) std::cerr << "expect() failure: " << int(x) << " " << error_code_name[int(x)] << "\n";
    if constexpr (action == Error_action::throwing)
        if (!cond()) throw x;
    if constexpr (action == Error_action::terminating)
        if (!cond()) terminate();
    // 혹은 어떤 동작도 하지 않는다 
}
```
- 해당 스키마 예시는 요구 사항대로 사용하기 매우 유연하고 명확
```
double& Vector::operator[](int i)
{
    expect([i, this] {return 0<=i && i<size(); }, Error_code::range_error);
    return elem[i];
}
```
- 첨자 지정이 범위에 속하면 기본 동작
- 그렇지 않으면 예외

- `if constexpr` 테스트는 컴파일 타임에 수행
    - 최대 하나의 런타임 테스트가 각 expect() 호출마다 수행

- 많은 시스템에서 `expect()` 같은 어설션 메커니즘은 어설션 실패의 의미를 제어할 단일 지점을 제공해야 함
- 대규모 코드 기반에서 실제 가정을 검사하는 if문을 검색하기란 일반적으로 불가능
## 그래서 어설션이 무엇인가?
- 어설션
    - 특정 조건이 참인지 확인하는 명령문
        - 디버깅 도구임
    - 조건이 거짓이면 프로그램을 종료하거나 오류를 보고
        - 코드의 논리적 오류를 발견하거나
        - 예상치 못한 상황에서 프로그램이 잘못된 상태로 실행되는 것을 방지지
    - 주로 개발 중 디버깅과 테스트를 목적으로 사용
        - 프로덕션 코드에서는 비활성화
        - `#define NDEBUG` 매크로 
- 어설션을 사용하는 이유
    1. 디버깅: 개발 중 논리적 오류를 조기에 발견
    2. 가정 검증: 코드에서 반드시 참이어야 하는 조건을 보장
    3. 코드의 의도를 명확히 표현
    4. 안전성 강화: 잘못된 입력 데이터로 인해 예상치 못한 결과가 발생하는 것을 방지
- 예외 처리와의 차이점 (어설션/예외처리)
    - 목적: 논리적 오류를 조기에 발견/런타임 오류를 처리
    - 사용 시점: 개발 및 디버깅 단계/프로덕션 환경 포함
    - 조건 위반 시: 프로그램이 즉시 종료/오류를 처리하고 프로그램을 계속 실행
    - 비활성화 가능 여부: `NDEBUG`로 비활성화 가능/항상 활성
### assert()
- 표준 라이브러리는 디버그 매크로인 `assert`를 제공
- 런타임에 참이어야 하는 조건을 표명
```
void f(const char* p)
{
    assert(p!=nullptr);
    // ...
}
```
- 다소 조잡하고 유연하지 못함
### 정적 어설션
- 예외는 런타임에 찾은 오류를 보고
- 컴파일 타임에 찾을 수 있는 오류는 미리 찾는게 좋음
    - 사용자 정의 타입의 인터페이스를 명시하는 타입 시스템과 기능이 존재
- 컴파일 타임에 알 수 있는 속성을 간단히 검사, 예상을 벗어난 실패는 오류 메시지로 보고 가능
```
static_assert(4<sizeof(int), "integers are too small");
```
- 조건 위반 시에 "integers are too small"이 출력
- `static_assert` 메커니즘은 상수 표현식으로 표현 가능한 무엇에든 사용이 가능
```
constexpr double C = 299792.458;

void f(double speed)
{
    constexpr double local_max = 160.0/(60*60);

    static_assert(speed<C, "can't go that fast"); // 오류, speed는 상수가 아님
    static_assert(local_max<C, "cant' go that fast");
}
```
- `static_assert(A, S)`
    - A가 참이 아니면 컴파일러 오류 메시지로 S 출력
### noexcept
- 예외를 던지면 안 되는 함수는 `noexcept` 선언
```
void user(int sz) noexcept
{
    Vector v(sz);
    iota(&v[0], &v[sz], 1);
}
```
- user()가 예외를 던지면 `std::terminate()`가 호출돼 프로그램이 즉시 종료

- 아무 생각 없이 함수에 `noexcept`를 남용하면 위험
- 예외를 치명적 오류로 전환 -> 프로그램 종료
- 작성자가 복잡하고 오류가 발생하기 쉽고 비용이 클 수 있는 형태의 오류 코드로 오류를 처리하게 유도