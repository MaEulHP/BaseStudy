# 테스트
- C++는 선택과 반복을 표현하는 편리한 명령문 집합 제공
    - if
    - switch
    - while
    - for
    - 등등
```
bool accept()
{
    cout << "Do you want to proceed (y or n)?\n";
    char answer = 0;
    cin >> answer;

    switch (answer){
        case 'y':
            return true;
        case 'n':
            return false;
        default:
            cout << "I'll take that for a no.\n";
            return false;
    }
}
```
- `answer`는 미리 하지 않고 정확히 필요한 시점에 정의
### switch
- 값을 상수 집합과 비교하며 테스트
- case 레이블의 상수는 각각 고유한 값
    - 테스트 값과 일치하는 레이블이 없으면 `default`를 수행
    - 일치하는 값이 없고 `default`가 제공되지 않으면 아무 동작도 수행 X
- 함수 반환으로 case를 종료하지 않을 경우
    - 뒤에 나오는 명령을 계속 수행
    - `break`를 이용해 switch문을 종료

### if
- if문 안에 변수를 넣어서 확인 가능
```if(auto n = v.size(); n!=0){ // ... }```
    - n은 if문 안에서만 사용될 목적으로 정의
    - 변수의 범위를 제한하여 가독성을 높이고 오류를 최소화
- 대부분 변수가 0(이나 `nullptr`)인지 테스트
    ```if(auto n = v.size()){ // ... n!=0이면 여기를 수행 }```
- 간결하고 단순하게 코딩이 가능 