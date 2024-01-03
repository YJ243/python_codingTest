/*
 * 2023.12.20
 * A의 사용 횟수를 먼저 정하고, 그에 따라 가능한 B의 최대 사용 횟수를 구해서
 * C보다 작은 합의 최댓값을 구하기
 * A와 B를 각각 몇 번씩 더해야 C보다 작으면서 최대가 되는지? => 일일이 완전 탐색
 * C보다 작은 범위 내에서 A의 사용 횟수를 점차 늘려가면서,
 * 각 A의 사용 횟수에 따라 최대로 사용 가능한 B의 개수를 구하기
 * 그 때 나올 수 있는 합의 최댓값 구하면 됨
*/
#include <iostream>
#include <algorithm>

using namespace std;

int a,b,c;

int main(){
    // 입력
    cin >> a >> b >> c;
    int ans = 0;

    // a를 몇 회 사용할 지 전부 시도해보기
    // 모든 경우의 수에 대해 최대가 되도록 하는 수를 계산
    for(int i=0; i*a <= c; i++){
        // a를 i회 사용
        int cnt = a*i;

        // 값을 최대로 하기 위해 b를 몇 회 사용해야 하는지 계싼
        int num_b = (c-cnt)/b;
        cnt += num_b * b;
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}