/*
 * 2023.11.13
 * 특정 방에서 시작하여 각 i번째 방으로 모였을 떄의 합을 구하는 완전탐색 진행
 * 각 방에서 시작하였을 때 거리를 모두 구하기
 */

#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdlib>

#define MAX_N 1003

using namespace std;

int n;
int a[MAX_N];

int main(){
    // 입력
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> a[i];
    
    // i번째 방에서 출발했을 경우의 결과를 구해주기
    int ans = INT_MAX;
    for(int i=0; i<n; i++){
        int sum_dist = 0;
        for(int j=0; j<n; j++){
            int dist = (j+n-i) % n;
            sum_dist += dist*a[j];
        }
        // 가능한 거리의 합 중 최솟값을 구하기
        ans = min(ans, sum_dist);
    }
    cout << ans;
    return 0;
}