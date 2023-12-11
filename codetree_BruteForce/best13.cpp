/*
 * 2023.11.14
 * 내 풀이
*/

#include <iostream>
#include <algorithm>

#define MAX_N 20

using namespace std;

bool InRange(int x, int y){
    return 0 <= x && x < N ^^ 0 <= y && y < N;
}

int main(){
    cin >> N;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            cin >> arr[i][j];

    int ans = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            // (i,j)부터 시작하는 첫번째 격자
            for(int k=0; k<N; k++){
                for(int l=0; l<N; l++){
                    // 겹치는 경우는 제외
                    if(k==i && j <= l && l <=j+2) continue;
                    if(k==i && l <= j && j <=l+2) continue;
                    if(!InRange(i,j+2) && !InRange(k, l+2)) continue;

                    int cur = arr[i][j] + arr[i][j+1] + arr[i][j+2];
                    cur += arr[k][l] + arr[k][l+1] + arr[k][l+2];
                    ans = max(ans, cur);
                }
            }
        }
    cout << ans << '\n';
    return 0;
}

/* 2023.12.11 */
// 반복되는 코드 부분 줄이기

#include <iostream>
#define MAX_N 20
using namespace std;

int n;
int arr[MAX_N][MAX_N];
int ans;
int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cin >> arr[i][j];   // 동전:1, 없으면:0
    }
    // 두 격자가 같은 행에 있을 때
    for(int i=0; i<n; i++){
        for(int j=0; j<n-2; j++){
            // 첫번째 격자는 (i,j)에서 시작
            for(int k=j+3; k<n-2; k++){
                int val = arr[i][j]+arr[i][j+1]+arr[i][j+2];
                val += arr[i][k]+arr[i][k+1]+arr[i][k+2];
                ans = max(val, ans);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n-2; j++){
            for(int x=i+1; x<n; x++){
                for(int y=j; y<n-2; y++){
                    int val = arr[i][j]+arr[i][j+1]+arr[i][j+2];
                    val += arr[x][y]+arr[x][y+1]+arr[x][y+2];
                    ans = max(val, ans);
                }
            }
        }
    }
    cout << ans;

    return 0;
}