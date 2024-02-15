/*
 * 2024.02.09
 * 내 풀이
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define MAX_N 50
#define ASCII_NUM 128
#define BLANK make_tuple(-1,-1,-1)

using namespace std;

typedef tuple<int, int, int> marble;        // (id, w, d)
marble grid[MAX_N][MAX_N];
marble next_grid[MAX_N][MAX_N];
int n, m, t;

int mapper[ASCII_NUM];
int dirs[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};   // 상, 좌, 우, 하

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Collide(int x, int y, marble newMarble){       // (x,y) 자리에서 newMarble과의 충돌을 처리하는 함수
    int new_id, new_w, new_d;
    tie(new_id, new_w, new_d) = newMarble;
    int old_id, old_w, old_d;
    tie(old_id, old_w, old_d) = next_grid[x][y];

    // 가장 큰 번호를 갖게되는 구슬을 따라가기
    if(new_id > old_id){
        next_grid[x][y] = make_tuple(new_id, new_w+old_w, new_d);
    }
    else{
        next_grid[x][y] = make_tuple(old_id, new_w+old_w, old_d);
    }
}

void MoveMarble(int x, int y, marble newMarble){    //(x,y) 자리로 newMarble을 옮기는 함수
    int id, w, d;
    tie(id, w, d) = newMarble;
    if(next_grid[x][y] == BLANK){
        next_grid[x][y] = newMarble;
    }
    else{
        Collide(x, y, newMarble);
    }
}

void Move(int x, int y){    // 격자에서 (x,y)에 있는 구슬 옮기기
    int id, w, d;
    tie(id, w, d) = grid[x][y];
    int nx = x+dirs[d][0], ny = y+dirs[d][1];
    // 만약 범위 안에 있다면
    if(InRange(nx,ny)){
        // 그 다음 칸으로 이동
        MoveMarble(nx,ny,grid[x][y]);
    }
    // 만약 범위를 벗어난다면
    else{
        d = 3-d;
        if(next_grid[x][y] == BLANK){
            next_grid[x][y] = make_tuple(id,w,d);   // 다음 격자 배열에 바로 집어넣기
        }
        else{   // 방향을 바꾸고 보니 그 자리에 다른 구슬이 있었다면
            MoveMarble(x,y,make_tuple(id, w, d));   // 원래 자리로 움직이기
        }
    }

}

void Initialize(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            next_grid[i][j] = BLANK;
        }
    }
}

void Simulate(){
    // 중간 정보를 저장할 배열 초기화
    Initialize();
    // 모든 구슬을 보면서 움직이기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] != BLANK)     // 만약 구슬이 있다면 움직이기
                Move(i,j);
        }
    }
    // next_grid를 grid로 옮기기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = next_grid[i][j];
            next_grid[i][j] = BLANK;
        }
    }
}

int main() {
    mapper['U'] = 0;
    mapper['L'] = 1;
    mapper['R'] = 2;
    mapper['D'] = 3;
    // 맨 처음에 구슬 정보를 저장할 격자 배열 초기화
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = BLANK;
        }
    }
    cin >> n >> m >> t;
    for(int i=1; i<=m; i++){
        int r, c, w; char d;
        cin >> r >> c >> d >> w;
        grid[r-1][c-1] = make_tuple(i, w, mapper[d]);
    }

    while(t--){
        Simulate();
    }
    int marble_cnt = 0, max_weight = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int w;
            tie(ignore, w, ignore) = grid[i][j];
            if(w > 0){
                marble_cnt++;
                max_weight = max(max_weight, w);
            }
        }
    }
    cout << marble_cnt << ' ' << max_weight << '\n';
    
    return 0;
}