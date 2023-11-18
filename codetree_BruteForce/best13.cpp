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