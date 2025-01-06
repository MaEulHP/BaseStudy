# 범위와 수명
## 선언과 범위
- 선언은 어떤 범위에 그 이름을 알림
    - 지역 범위(local scope): 
        - 함수나 람다에 선언된 이름을 지역명(local name)이라고 함
        - 블록(block)은 { } 쌍으로 구분
        - 함수 인수명은 지역명으로 간주
    - 클래스 범위(class scope):
        - 클래스 안이나 함수, 람다, enum class 밖에 정의된 이름을 멤버명(member name)이라고 함
        - 선언을 감싸는 여는 {부터 닫는}까지가 범위
    - 네임스페이스 범위(namespace scope):
        - 함수나 람다, 클래스, enum class 밖 네임스페이스 안에 정의된 이름을 네임스페이스 멤버명(namespace member name)이라고 함
        - 선언 지점부터 그 네임스페이스 끝까지가 범위
- 어떤 구조체 안에도 선언되지 않은 이름: 전역명(global name)
    - 전역 네임스페이스에 속한다고 말함

## new
- `new`로 생성한 템포러리와 객체: 이름이 없음
```
vector<int> vec;
void fct(int arg)
{
    string motto {"Who dares wins"};
    auto p = new Record{"Hume"}; // p는 아직 명명되지 않은 Record를 가리킴
    // ...
}

struct Record {
    string name;
    // ...
};
```
- 객체는 사용하기 전에 반드시 생성돼야(초기화돼야) 하며 범위의 끝에서 소멸
- 네임스페이스 객체의 경우 소멸 지점은 프로그램의 끝
- 객체의 멤버의 경우 소멸 지점은 그 객체가 소멸되는 시점
- `new`로 생성한 객체는 `delete`로 소멸시킬 때까지