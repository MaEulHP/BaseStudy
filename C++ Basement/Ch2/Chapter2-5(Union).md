# 공용체(union)
- `struct`의 일종: 모든 멤버를 같은 주소에 할당
- 그 `union`에서 가장 큰 멤버의 크기만큼 공간 차지
- 1번에 딱 한 멤버의 값만 저장 가능
```
enum class Type { ptr, num };

struct Entry {
    string name;
    Type t;
    Node* p;
    int i;
};
void f(Entry* pe);
{
    if(pe->t == Type::num) cout << pe->i;
}
```
- 멤버 `p`와 `i`를 동시에 저장할 일 없음: 공간 낭비!!!
```
union Value {
    Node* p;
    int i;
};
```
- `Value::p`와 `Value::i`는 같은 `Value` 객체 메모리 주소에 저장
- 언어에서 별도로 `union`에 어떤 종류 값이 저장되지 관리하지 않음
    - 프로그래머가 직접 하기
```
struct Entry{
    string name;
    Type t;
    Value v;
};
```
- `Type t`는 `v`를 결정하는 판별자(discriminant; 태그, 타입필드)
    - `union`에 저장할 타입 간 관련성을 유지해야 함
    - 오류가 발생하기 쉬움
        - 공용체와 타입 필드를 클래스 내에 캡슐화
        - 공용체를 사용하는 멤버 함수로만 접근하도록
- 태깅된 공용체를 이용해 추상화하는 방법
    - 일반적이며 유용함
    - '노출된' `union`은 가장 적게 쓰는 방법
## variant
- 표준 라이브러리 타입
- 여러 타입 집합 중 하나의 값을 저장
- 공용체를 직접 사용하지 않아도 됨
```
struct Entry {
    string name;
    variant<Node*, int> v;
};
```
- 공용체가 많은 경우 `union`보다 `variant`가 간단하고 안전 