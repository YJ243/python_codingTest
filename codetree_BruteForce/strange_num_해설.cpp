/*
 * 2023.12.09
 * 이진수의 가장 왼쪽 자릿수부터 차례대로 바꾸고 값 비교
 * 자릿수를 바꾼 뒤에는 원래대로 돌려놓아야 함
*/

#include <iostream>
#include <climits>

using namespace std;

int main(){
    // 변수 선언 및 입력
    string binary;
    cin >> binary;

    // 각 i번째 자릿수를 바꾸었을 때 십진수 값을 구해주기
    int ans = INT_MIN;
    for(int i=0; i<(int) binary.size(); i++){
        // i번째 자릿수를 바꾸기
        binary[i] = '0' + '1' - binary[i];

        // 십진수로 변환
        int num = 0;
        for(int j=0; j<(int) binary.size(); j++)
            num = num * 2 + (binary[j] - '0');

        // 가능한 십진수 값 중 최대를 구하기
        ans = max(ans, max);

        // i번째 자릿수를 원래대로 돌려놓기
        binary[i] = '0' + '1' - binary[i];
    }

    // 출력
    cout << ans;
    return 0;
}