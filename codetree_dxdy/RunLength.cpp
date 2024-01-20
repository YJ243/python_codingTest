/*
 * 2024.1.18
 * 내 풀이
*/

#include <iostream>
#include <string>

#define MAX_N 10

using namespace std;

int n;
string s;
int ans = MAX_N*2;

void RightShift(){
    string tmp = s;
    // 오른쪽으로 shift
    for(int i=0; i<n; i++)
        tmp[i+1] = s[i];
    tmp[0] = s[n-1];

    // 다시 원래 문자열로 붙여넣기
    s = tmp;
}

void RunLength(){
    char cur = s[0];
    int curCnt = 1;
    int encodingLength = 0;
    for(int i=1; i<n; i++){
        // cur에 대해서 같은 문자열 탐색
        if(cur == s[i]){
            curCnt++;
        }
        else{
            encodingLength += 2;
            curCnt = 1;
            cur = s[i];
        }
    }
    // 맨 마지막에 대해서 처리해주기
    if(curCnt == 10)
        encodingLength = 3;
    else
        encodingLength += 2;
    ans = min(ans, encodingLength);
}

int main() {
    cin >> s;
    n = (int)s.size();
    for(int i=0; i<n; i++){
        // i번 shift
        RightShift();
        RunLength();
    }
    cout << ans;

    return 0;
}