/*
 * 2024.1.26
 * 내 풀이
*/
#include <iostream>
#include <algorithm>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int n;
int grid[MAX_N][MAX_N];
int dirs[DIR_NUM][2] = {{1,0},{-1,0},{0,1},{0,-1}};  // 아래로/위로/오/왼
int ans;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(int sx, int sy, int sd){   // (sx,sy)에서 sd 방향으로 시작
    int t = 0;
    int curX = sx, curY = sy, curD = sd;    // 현재 위치와 방향 넣기
    while(true){
        t++;    // 시간 증가
        curX = curX + dirs[curD][0], curY = curY + dirs[curD][1];
        // 1. 만약 격자를 빠져나왔다면
        if(!InRange(curX, curY)){
            ans = max(ans, t);  // 정답 업데이트
            return;             // 리턴하기
        }
        // 2. 격자안이라면
        // 2-1. 다음 격자가 /모양이라면
        if(grid[curX][curY] == 1){
            // 방향 바꾸기(아래<>왼, 위<>오)
            curD = (DIR_NUM-1)-curD;
        }
        // 2-2. 다음 격자가 \모양이라면
        else if(grid[curX][curY] == 2){
            // 방향바꾸기(아래<>오, 위<>왼)
            curD = (curD+2)%DIR_NUM;
        }
    }
    ans = max(ans, t);
}

int main() {
    // 입력:
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    
    // 1. 맨 윗단/맨 아랫단을 시작 위치로
    for(int j=0; j<n; j++){
        Simulate(-1,j,0);
        Simulate(n,j,1);
    }
    
    // 2. 맨 왼쪽/맨 오른쪽을 시작 위치로
    for(int i=0; i<n; i++){
        Simulate(i,-1,2);
        Simulate(i,n,3);
    }

    cout << ans;
    return 0;
}