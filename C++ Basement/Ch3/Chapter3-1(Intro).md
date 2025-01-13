# 모듈성 - 소개
- C++ 프로그램 구성
    - 함수
    - 사용자 정의 타입
    - 클래스 계층 구조
    - 템플릿
    - 등등
- 많은 부분을 관리하는 핵심: 서로의 인터랙션을 명확하게 정의
- 가장 중요한 것 중 첫 번째: 한 요소 내에서 인터페이스와 구현을 구분
- C++는 언어 수준에서 선언으로 인터페이스 표현
    - 선언: 함수나 타입 사용에 필요한 요소를 전부 나열
```
double sqrt(double);

class Vector {
    public:
        Vector(int s);
        double& operator[](int i);
        int size();
    private:
        double* elem;
        int sz;
};
```
- 핵심: 함수 본문(함수 정의)가 '다른 곳'에 있음
```
double sqrt(double d)
{
    // 
}
```
- 표준 라이브러리에 sqrt는 존재 (std::sqrt)
```
Vector::Vector(int s)
    :elem{new double[s]}, sz {s}
{    
}
double& Vector::operator[](int i)
{
    return elem[i];
}
int Vector::size()
{
    return sz;
}
```
- Vector의 함수를 전부 정의해야 함
- 함수 등의 엔티티에 대해 선언은 여러 개일 수 있음
    - 정의는 딱 하나임