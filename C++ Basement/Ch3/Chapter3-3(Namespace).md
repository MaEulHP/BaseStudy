# 네임스페이스
- 여러 선언을 한데 묶어 서로의 이름이 충돌하지 않도록 표현하는 메커니즘
- 예시: 사용자 정의 복소수 타입 실험
```
namespace My_code {
    class complex {
        // ...
    };
    complex sqrt(complex);
    // ...
    int ();
}
int My_code::main()
{
    complex z {1, 2};
    auto z2 = sqrt(z);
    std::cout << '{' << z2.real() << ',' << z2.imag() << '}\n';
    // ...
}
int main()
{
    return My_code::main();
}
```
- My_code 네임스페이스와 std 네임스페이스 내 표준 라이브러리 이름은 충돌하지 않는다

- 다른 네임스페이스 내 이름에 접근할 때는 네임스페이스명으로 그 이름을 한정하는 방법이 가장 간단
    - 위의 코드에서 `std::cout` 이나 `My_code::main` 같은 경우
    - 다만 이름을 반복적으로 한정하면 코드가 장황하고 산만해질 수 있음
    - using 선언을 통해 해결
```
void my_code(vector<int>& x, vector<int>& y){
    using std::swap;
    // ...
    swap(x,y); // std::swap
    other::swap(x,y); // 다른 swap
}
```
- using 선언
    - 네임스페이스 이름을 그 이름이 나타난 범위에 선언된 것처럼 사용할 수 있게 함
    - 위의 코드에서 `using std::swap` 이후 `swap`은 `my_code()` 내에 선언된 것으로 간주
- using 디렉티브
    - 그 디렉티브를 둔 범위 안에서는 한정자 없이 명명한 네임스페이스에 접근이 가능
    - `using namespace std;` 디렉티브 이후에는 `std::cout`이 아닌 `cout` 만 작성해도 가능
    - 해당 모듈에 지역적인 사용
        - 모듈의 사용자에게 영향을 미치지 않음
    - 디렉티브 사용 시, 선언과 달리 네임스페이스 내의 이름을 선택적으로 사용이 불가능
        - 신중히 사용
        - 보통 `std`와 같이 흔한 라이브러리에 많이 사용
    - 주로 라이브러리와 같은 더 큰 프로그램 컴포넌트 구성에 사용
        - 별도 개발된 부분을 프로그램으로 구성할 때보다 간소화