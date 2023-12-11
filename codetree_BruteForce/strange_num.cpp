/*
 * 2023.12.09
 * 내 풀이
*/
#include <iostream>
#include <cmath>

#define MAX_N 10
using namespace std;

string a;

int main(){
    cin >> a;
    int length = (int) a.size();    // a 문자열 길이
    int ans = 0;        // 한 자리수만 바꿨을 때의 최댓값

    for(int i=1; i<length; i++){    // i번째 자리수 바꾸기
        string tmp = a;             // a 문자열 복사
        int cur_number = 0;         // i번째 자리수 바꿨을 때의 10진수 값
        if(tmp[i] == '0')
            tmp[i] = '1';
        else
            tmp[i] = '0';
        
        for(int idx = 0; idx < length; idx++){
            int number = 0; // 해당 자리수 값
            if(tmp[idx] == '0') number = 0;
            else    number = 1;

            cur_number += pow(2, length-1-idx) * number;    // 2^(length-1-idx)*number(앞에서부터)
        }
        ans = max(ans, cur_number);     // 현재까지 바꾼 숫자중에서 최댓값 고르기
    }
    cout << ans << '\n';
    return 0;
}