/*
 * 2024.1.16
 * 내 풀이
*/

#include <iostream>
#define MAX_N 20

using namespace std;
int n;                      // 격자 크기
int grid[MAX_N][MAX_N];     // 격자
int dirs[4][2] = {{-1,1},{-1,-1},{1,-1},{1,1}}; // 반시계 순회 방
int ans;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int GetSum(int x, int y, int distX, int distY){
    int curX = x, curY = y;
    int curSum = grid[curX][curY];
    bool canGo = true;

    for(int d=0; d<4; d++){
        int dirCnt = 0;
        if(d % 2 == 0) dirCnt = distX;
        else dirCnt = distY;

        
        for(int i=1; i<=dirCnt; i++){
            curX += dirs[d][0]; curY += dirs[d][1];
            if(!InRange(curX, curY)){
                return -1;
            }
            curSum += grid[curX][curY];
        }
    }
    curSum -= grid[curX][curY];
    return curSum;
}

int main() {
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // (i,j)가 기울어진 직사각형의 시작점
            for(int k=1; k<=n-2; k++){
                for(int l=1; l<=n-2; l++){
                    // k는 1번 3번 방향이 움직일 개수
                    // l은 2번 4번 방향이 움직일 개수
                    int curr = GetSum(i,j,k,l);
                    if(curr != -1){
                        ans = max(ans, curr);
                    }
                }
            }
        }
    }    
    cout << ans;
    return 0;
}