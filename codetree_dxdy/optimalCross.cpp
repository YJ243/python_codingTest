/*
 * 2024.1.21
 * 내 풀이
*/
#include <iostream>
#include <algorithm>

#define MAX_N 50
using namespace std;

int n;
int grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];
int last[MAX_N][MAX_N];
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int ans;

bool InRange(int x, int y){
    return 0 <= x && x < n & 0 <= y && y < n;
}

void CopytoTemp(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            temp[i][j] = grid[i][j];
}

void DoGravity(){
    // 1. last 배열 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            last[i][j] = 0;
    
    // 2. temp에서 중력 작용시키기
    for(int j=0; j<n; j++){
        // j열 단위로 보기
        int lastIdx = n-1;
        for(int i=n-1; i>=0; i--){
            if(temp[i][j]){
                last[lastIdx--][j] = temp[i][j];
            }
        }
    }
}

void Bomb(int x, int y){
    // 1. temp배열에 grid 복사해서 초기화시키기
    CopytoTemp();       
    // 2. (x,y)위치에서 폭탄 터뜨리기
    int bombL = temp[x][y]-1;
    temp[x][y] = 0;
    for(int l=1; l<=bombL; l++){
        for(int d=0; d<4; d++){
            int nx = x+dirs[d][0]*l, ny = y+dirs[d][1]*l;
            if(InRange(nx,ny)){
                temp[nx][ny] = 0;
            }
        }
    }
    // 3. temp배열에서 중력 작용한 것을 last에 저장하기
    DoGravity();
}

void CheckSameNumbers(){
    // last 배열에서 먼저 각 행단위로 보면서 확인하기
    int sameCnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if(last[i][j] == 0) continue;
            if(last[i][j] == last[i][j+1])  sameCnt++;
        }
    }
    // last 배열에서 각 열단위로 보면서 확인하기
    for(int j=0; j<n; j++){
        for(int i=0; i<n-1; i++){
            if(last[i][j] == 0) continue;
            if(last[i][j] == last[i+1][j])  sameCnt++;
        }
    }
    ans = max(ans, sameCnt);
}

int main() {
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // Step 1. 각 칸에 대해서 폭탄을 선택해 폭발한 뒤 중력작용하기
            Bomb(i,j);
            // Step 2. 모든 칸에 대해 2개씩 붙어있는 값이 있는지 확인
            CheckSameNumbers();
        }
    }
    cout << ans;    
    
    return 0;
}