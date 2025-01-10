// 각 자리가 숫자(0~9)인 문자열 입력
// 숫자 사이에 + 또는 *
// 가장 큰 수 만들기
// 0 또는 1: 더하기
// 2~9: 곱하기
#include <iostream>
#include <string>
// #include <sstream>
#include <stack>
using namespace std;

int main()
{
    string str;
    cin >> str;

    // 문자열을 정수로 변환하기
    // 1. <string>
    try {
        int num1 = stoi(str);

        int result = 0;
        stack<int> IntStack;
        while(num1 > 0){
            IntStack.push(num1%10);
            num1 /= 10;
        }
        result += IntStack.top();
        IntStack.pop();
        while(!IntStack.empty()) {
            if(IntStack.top() > 1){
                result *= IntStack.top();
                IntStack.pop();
            }else {
                result += IntStack.top();
                IntStack.pop();
            }
        }
        cout << result;
    } catch(const invalid_argument& e){
        cerr << "유효하지 않은 숫자 문자열" << endl;
    } catch (const out_of_range& e){
        cerr << "범위 초과" << endl;
    }

    // 2. <sstream>
    // stringstream ss(str);
    // int num2;
    // ss >> num2;
    // if(ss.fail()){
    //     cerr << "변환 실패" << endl;
    // }

    // 3. <charconv> C++ 14 이상
    // int num3;
    // auto result = from_chars(str.data(), str.data()+str.size(), num3);
    cin >> str;
    return 0;
}
// gpt 코드
// #include <iostream>
// #include <string>

// using namespace std;

// int main() {
//     string str;
//     cin >> str;

//     // 예외 처리: 입력 문자열이 유효한 숫자인지 확인
//     for (char c : str) {
//         if (!isdigit(c)) {
//             cerr << "유효하지 않은 숫자 문자열입니다." << endl;
//             return 1;
//         }
//     }

//     // 계산 시작
//     int result = str[0] - '0'; // 첫 번째 문자를 정수로 변환
//     for (size_t i = 1; i < str.size(); ++i) {
//         int num = str[i] - '0'; // 현재 문자를 정수로 변환
//         if (result <= 1 || num <= 1) {
//             result += num; // 0이나 1인 경우 더하기
//         } else {
//             result *= num; // 그 외의 경우 곱하기
//         }
//     }

//     cout << "가장 큰 수: " << result << endl;
//     return 0;
// }
