/*
https://www.codetree.ai/missions/5/problems/taking-a-taxi-in-the-middle-of-the-marathon-2?&utm_source=clipboard&utm_medium=text
처음과 마지막 체크포인트를 제외한 나머지 모든 체크포인트를 순서대로 하나씩 건너뛰었을 때 거리 구하기
*/

#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdlib>

#define MAX_N 100

using namespace std;

int n;
int x[MAX_N], y[MAX_N];

int main(){
    // 변수 선언 및 입력
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> x[i] >> y[i];
    
    // 각 i번째 체크포인트를 건너 뛰었을 때의 거리를 구하기
    int ans = INT_MAX;
    for(int i=1; i<n-1; i++){
        // 거리를 구하기
        int dist = 0;
        int prev_idx = 0;
        for(int j=1; j<n; j++){
            if(j == i) continue;
            dist += abs(x[prev_idx]-x[j]) +abs(y[prev_idx]-y[j]);
            prev_idx = j;
        }

        // 가능한 거리 중 최솟값을 구해주기
        ans = min(ans,dist);
    }

    // 출력
    cout << ans;
    return 0;
}