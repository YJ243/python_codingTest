/*
 * 2024.03.22
 * 내 풀이
 * 수행시간이 길게 나와서 고침
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 12
#define MAX_K 4
using namespace std;
int ans;
int k, n, m;    // k개의 말, n번의 턴, m개 숫자
int turns[MAX_N];
int result[MAX_K];

int Calc(){
    // k개의 말을 보면서 점수 계산하기 
    int ret = 0;
    for(int i=0; i<k; i++){
        ret += (result[i] >= m-1);
    }
    return ret;
}

void Choose(int idx){
    ans = max(ans, Calc());
    if(idx == n){
        return;
    }

    for(int i=0; i<k; i++){
        if(result[i] >= m-1)
            continue;
        result[i] += turns[idx];    // idx번째 턴에 i번 말 움직이기
        Choose(idx+1);              // idx+1번째 선택하러 가기
        result[i] -= turns[idx];
    }
}

int main() {
    // 입력 받기
    cin >> n >> m >> k;
    for(int i=0; i<n; i++)
        cin >> turns[i];
    
    Choose(0);  // 0번째 턴에 움직일 말의 수 선택
    cout << ans;
    return 0;
}