# 구조체
- 새 타입을 만드는 첫 번째 단계
- 타입에 필요한 요소를 묶는 것
```
struct Vector{
    double* elem;
    int sz;
};
void vector_init(Vector& v, int s){
    v.elem = new double[s];
    v.sz = s;
}
```
- 첫 번째 `Vector` 버전은 int와 double*로 구성
- Vector 타입의 변수는 `Vector v;`와 같이 정의
- v의 elem 멤버는 new 연산자가 생성한 포인터
- v의 sz 멤버는 원소 수를 받음
- `Vector&`: const가 아닌 참조로 v를 전달
    - 전달받은 벡터를 수정이 가능
- `new`연산자 : 자유공간(free store)이라 부르는 영역의 메모리 할당
    - 자유 공간에 할당된 객체는 생성된 범위와 독립적
    - `delete` 연산자로 소멸되기 전까지 살아 있음
- `vector`나 `string`같은 표준 라이브러리 컴포넌트 -> 다시 만들지 말고 가져다 쓰기
    - 다시 만들려면 `vector`에 대해서 완벽히 알아야 함

- 이름(과 참조)을 통해 struct 멤버에 접근 `.`
- 포인터를 통해 struct 멤버에 접근 `->`