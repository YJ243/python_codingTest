/*
 * 2024.03.03
 * 해설 참고해서 다시 풀었음. 1시간 15분 안에 풀어냄 
 */

#include <iostream>
#define MAX_N 6
#define MAX_M 4
#define TILE_NUM 3
#define COLOR_CNT 2
using namespace std;

int k;
int n = MAX_N, m = MAX_M;
int grid[COLOR_CNT][MAX_N][MAX_M];  // 0: 노란색, 1: 빨간색
int tile[TILE_NUM+1][2][2] = {
    {},
    {{1,0},     // 1x1 타일
     {0,0}},
    {{1,1},     // 1x2 타일
     {0,0}},
    {{1,0},     // 2x1 타일
     {1,0}}
};

int total_score;
int total_block;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanGo(int x, int y, int c){
    return InRange(x, y) && !grid[c][x][y];     // 범위 안에 있고, 타일이 없어야 함
}

void Put(int t, int c, int x, int y){           // t번 타일을 c컬러 블록에 (x,y)에서 시작해서 놓기
    for(int dx = 0; dx < 2; dx++){
        for(int dy = 0; dy < 2; dy++){
            if(tile[t][dx][dy]){
                int nx = x + dx, ny = y + dy;
                grid[c][nx][ny] = 1;
            }
        }
    }

}

void PutTile(int t, int c, int y){      // t번 타일을 c번 컬러 블록의 y번 열에 두는 함수
    for(int i=1; i<=n; i++){                     // 위에서부터 차례대로 보기 시작, 현재 보고 있는 좌상단은 (i,y)
        for(int dx = 0; dx < 2; dx++){
            for(int dy = 0; dy < 2; dy++){
                if(tile[t][dx][dy]){
                    // 만약 타일이 존재한다면
                    int nx = i+dx, ny = y+dy;
                    if(!CanGo(nx, ny, c)){    // (nx, ny) 자리에 놓을 수 없다면
                        // 이전 줄에 놓고 break;
                        Put(t, c, i-1, y);
                        return;
                    }
                }
            }
        }
    }
}

bool IsFilled(int c, int x){        // c컬러 블록의 x행이 꽉차있는지 확인하기
    bool IsFilled = true;
    for(int j=0; j<m; j++){
        if(grid[c][x][j] == 0)
            IsFilled = false;
    }
    return IsFilled;
}

void DownOneRow(int c, int start_x){
    for(int i=start_x; i >= 1; i--){
        for(int j=0; j<m; j++){
            grid[c][i][j] = grid[c][i-1][j];
        }
    }
}

void ProcessDark(){
    // 모두 채워져 있는 행이 있는지 확인하기
    for(int c=0; c<2; c++){     // 노란색, 빨간색 차례대로 확인하기
        int i = n-1;
        while(i >= 2){          // 진한 부분만 확인하기
            if(IsFilled(c, i)){
                // 만약 채워져 있다면
                total_score++;      // 점수 증가시키고
                DownOneRow(c, i);   // 한칸씩 내리기
            }
            else{
                i--;                // 해당 행은 꽉차있지 않으니 위로 인덱스 올리기
            }
        }

    }
}

void ProcessLight(){
    // 밝은색 부분에 타일이 있는지 확인
    for(int c=0; c<2; c++){
        int existCnt = 0;
        for(int i=0; i<2; i++){
            for(int j=0; j<m; j++){
                if(grid[c][i][j]){
                    existCnt++;
                    break;
                }
            }
        }
        
        while(existCnt){
            DownOneRow(c, n-1);
            existCnt--;
        }
        for(int i=0; i<2; i++){
            for(int j=0; j<m; j++){
                grid[c][i][j] = 0;
            }
        }
    }
}

void Simulate(int t, int x, int y){     // t번 타일이 (x,y)에 주어졌을 때 타일 위치시키기
    // Step 1. 노란색 블록에 이동시키기
    PutTile(t, 0, y);
    // Step 2. 빨간색 블록에 이동시키기
    if(t == 1)
        PutTile(t, 1, m-1-x);
    else if(t == 2)
        PutTile(t+1, 1, m-1-x);
    else
        PutTile(t-1, 1, m-1-x-1);
    
    // Step 3. 진한 부분 처리하기
    ProcessDark();
    // Step 4. 연한 부분 처리하기   
    ProcessLight();
}

void Output(){
    cout << total_score << '\n';
    for(int c=0; c<2; c++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                total_block += grid[c][i][j];
            }
        }
    }
    cout << total_block << '\n';
}

int main() {
    cin >> k;
    while(k--){
        int t, x, y;
        cin >> t >> x >> y;
        Simulate(t, x, y);
    }    
    // 출력하기
    Output();
    return 0;
}