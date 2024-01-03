/*
 * 2023.12.17
 * 입력 받으면서 이긴 횟수를 저장하고
 * 이후에 경기 수랑 같은 경우의 수 구하기
*/

#include <iostream>
#define MAX_K 10
#define MAX_N 20

using namespace std;

int k, n;                       // k: 경기의 수, n: 개발자 수
int play[MAX_K][MAX_N];         // 경기 결과 순위
int win_cnt[MAX_N+1][MAX_N+1];  // win_cnt[i][j]: i번 개발자가 j번 개발자보다 높은 순위
int ans;

int main(){
    cin >> k >> n;      // k번 경기에 대해 n명의 개발자 순위가 주어짐
    for(int i=0; i<k; i++){
        // 입력
        for(int j=0; j<n; j++)
            cin >> play[i][j];
        
        // 이긴 횟수 저장
        for(int j=0; j<n; j++){
            for(int k=j+1; k<n; k++){
                win_cnt[play[i][j]][play[i][k]]++;
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(win_cnt[i][j] == k)  ans++;  // 항상(k번의 경기수에 대해) i가 j보다 높은 순위라면
        }
    }
    cout << ans << '\n';
    return 0;
}