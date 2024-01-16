/*
 * 2024.1.14
 * 조합을 만들면서 첫 번째 그룹에 속하는 경우에는 해당 원소를 더해주고,
 * 두 번째 그룹에 속하는 경우 해당 원소를 빼주는 식으로 동시에 결과값을 계산
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>

#define MAX_N 10
using namespace std;

int n;
int num[2*MAX_N];

int ans = INT_MAX;

void FindMin(int idx, int cnt, int diff){
    if(idx == 2*n){
        if(cnt == n)
            ans = min(ans, abs(diff));
        return;
    }
    // 현재 숫자를 더하는 역할로 사용한 경우
    FindMin(idx+1, cnt+1, diff+num[idx]);
    // 현재 숫자를 빼는 역할로 사용한 경우
    FindMin(idx+1, cnt, diff-num[idx]);
}
int main(){
    cin >> n;

    for(int i=0; i<2*n; i++)
        cin >> num[i];
    
    FindMin(0,0,0);

    cout << ans;
    return 0;
}