/*
 * 2024.1.16
 * 내 풀이
 * 양수 인데 코드가 0 이상으로 처리되도록 해서 틀림!!!!
 * 문제 제대로 읽고 하나하나 정신차리고 풀기!!
*/

#include <iostream>
#include <algorithm>
#define MAX_NM 20

using namespace std;
int n, m;
int grid[MAX_NM][MAX_NM];
int ans=-1;        // 최대 크기의 양수 직사각형

int GetPositiveCnt(int x, int y, int k, int l){
    int cnt = 0;
    for(int i=x; i<=x+k; i++){
        for(int j=y; j<=y+l; j++){
            if(grid[i][j] <= 0)
                return -1;
            cnt++;
        }
    }
    return cnt;
}
int main() {
    cin >> n >> m;    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> grid[i][j];
    

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            for(int k=0; k<n; k++)
                for(int l=0; l<m; l++){
                    // 만약 범위를 벗어나면 무시
                    if(i + k >= n || j + l >= m) continue;
                    // 양수 직사각형 크기 구하기
                    ans = max(ans, GetPositiveCnt(i,j,k,l));
                }
    cout << ans;
    return 0;
}