#include <iostream>

using namespace std;
// 앞서 계산된 결과를 저장하기 위한 DP 테이블 초기화
long long d[100];

int main(){
    // 첫 번째 피보나치 수와 두 번째 피보나치 수는 1
    d[1]=1;
    d[2]=1;
    int n = 50; // 50번째 피보나치 수 계산

    // 피보나치 함수 반복문으로 구현(보텀업 DP)

    for(int i=3; i<=n; i++){
        d[i] = d[i-1]+d[i-2];
    }

    cout<<d[n] << '\n';
    return 0;
}