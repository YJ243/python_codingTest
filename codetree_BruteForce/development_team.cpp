/*
 * 2023.12.14
 * 처음에 모든 팀의 능력치가 서로 다르게 팀을 묶어야 하는데,
 * 팀 내의 사람들의 능력치가 다르게 해서 틀림
 * 그리고 불가능한 경우 -1을 출력해야 하는데, 이를 빼먹음
*/

#include <iostream>
#include <algorithm>
#include <climits>
#define MAX_N 5

using namespace std;

int arr[MAX_N];
int ans = INT_MAX;

int main(){
    int total = 0;
    for(int i=0; i<MAX_N; i++){
        cin >> arr[i];
        total += arr[i];
    }

    // 2명, 2명, 1명씩 팀 이루기 (먼저 2명, 2명을 구하기)
    for(int i=0; i<MAX_N; i++){
        for(int j=i+1; j<MAX_N; j++){
            for(int k=0; k<MAX_N; k++){
                for(int l=k+1; l<MAX_N; l++){
                    if(i == k || i == l || j == k || j == l) continue;
                    int tmp[3];     // 각 팀의 총 능력치
                    tmp[0] = arr[i]+arr[j];
                    tmp[1] = arr[k]+arr[l];
                    tmp[2] = total-tmp[0]-tmp[1];

                    if(tmp[0] == tmp[1] || tmp[1] == tmp[2] || tmp[2] == tmp[0]) continue;
                    sort(tmp, tmp+3);
                    ans = min(ans, tmp[2]-tmp[0]);
                }
            }
        }
    }
    if(ans == INT_MAX)
        cout << -1 << '\n';
    else
        cout << ans << '\n';
    return 0;
}