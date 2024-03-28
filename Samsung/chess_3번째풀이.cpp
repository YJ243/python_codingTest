/*
 * 2024.03.27
 * 해설 보고 처음부터 다시 품
*/
#include <iostream>
#include <algorithm>
#include <tuple>

#define MAX_N 4
#define MAX_DIR 8
#define EMPTY make_pair(-1,-1)
#define TAGGER make_pair(-2,-2) 

using namespace std;

int n = 4;
pair<int, int> grid[MAX_N][MAX_N];
int dirs[MAX_DIR][2] = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};   // 상부터 반시계방향으로

int max_score;

void Input(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num, d;
            cin >> num >> d;
            grid[i][j] = make_pair(num, d-1);
        }
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool TaggerCanGo(int x, int y){
    return InRange(x, y) && grid[x][y] != EMPTY;
}

bool IsFinish(int x, int y, int d){
    for(int i=1; i<n; i++){
        int nx = x + dirs[d][0]*i, ny = y + dirs[d][1]*i;
        if(TaggerCanGo(nx, ny))     // 만약 술래가 갈 수 있는 곳이 남아 있다면
            return false;
    }
    return true;
}

bool ThiefCanGo(int x, int y){      // 도둑이 (x,y)로 갈 수 있는지 확인
    return InRange(x, y) && grid[x][y] != TAGGER;
}

pair<int, int> ThiefNextLoc(int x, int y, int d){       // 현재 (x,y)에서 d방향을 가지고 있는 도둑이 다음으로 이동할 위치 반환
    int cx = x, cy = y, cd = d;
    for(int i=0; i<8; i++){
        int nx = cx + dirs[(cd+i)%MAX_DIR][0], ny = cy + dirs[(cd+i)%MAX_DIR][1];
        if(ThiefCanGo(nx, ny)){
            cx = nx, cy = ny, cd = (cd+i)%MAX_DIR;
            break;
        }
    }
    grid[x][y] = make_pair(grid[x][y].first, cd);
    return make_pair(cx, cy);
}

void Swap(int x, int y, int nx, int ny){        // (x,y)와 (nx,ny)에 있는 도둑 각각 바꾸기
    pair<int, int> temp = grid[x][y];
    grid[x][y] = grid[nx][ny];
    grid[nx][ny] = temp;
}

void MoveThief(){
    for(int num=1; num<=16; num++){
        bool IsMoved = false;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                int cur_num, cur_dir;
                tie(cur_num, cur_dir) = grid[i][j];     // 현재 보고 있는 칸에서의 번호와 방향
                if(cur_num == num){     // 만약 현재 이동하려는 번호를 찾았다면
                    int next_x, next_y;
                    tie(next_x, next_y) = ThiefNextLoc(i, j, cur_dir);
                    //out << num << ' ' << next_x << ' ' << next_y << '\n';
                    Swap(i, j, next_x, next_y);
                    IsMoved = true;
                    break;
                }
            }
            if(IsMoved)
                break;
        }
    }
}

void FindNextLoc(int x, int y, int d, int score){
    if(IsFinish(x, y, d)){
        max_score = max(max_score, score);
        return;
    }
    
    for(int i=1; i<n; i++){     // 현재 술래가 바라보는 방향으로 움직일 수 있는 곳 찾기
        int nx = x + dirs[d][0]*i, ny = y + dirs[d][1]*i;
        if(!TaggerCanGo(nx, ny)) continue;

        // backtracking 전 이전 정보 저장해두기
        pair<int, int> tmp[MAX_N][MAX_N];
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                tmp[i][j] = grid[i][j];

        // (nx, ny)로 술래 이동하기
        int plus_score, next_dir;
        tie(plus_score, next_dir) = grid[nx][ny];
        grid[nx][ny] = TAGGER;
        grid[x][y] = EMPTY;

        // 도둑들 차례대로 이동하기
        MoveThief();

        // 술래 다음 위치 찾기
        FindNextLoc(nx, ny, next_dir, score+plus_score);

        // 돌아와서는 이전 정보 다시 복구하기
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                grid[i][j] = tmp[i][j];
    }
    
}

int main() {
    // 입력 받기:
    Input();

    // 1. 초기에 (0,0) 에 있는 도둑말 잡기 
    int plus_score, next_dir;
    tie(plus_score, next_dir) = grid[0][0];
    grid[0][0] = TAGGER;
    // 2. 도둑말 차례대로 이동하기
    MoveThief();

    // 3. 술래가 다음으로 이동할 위치 찾기
    FindNextLoc(0, 0, next_dir, plus_score);        // (0,0)에서 next_dir방향을 가진 술래가 다음 이동할 위치를 탐색
    cout << max_score;
    return 0;
}