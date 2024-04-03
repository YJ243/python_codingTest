/*
 * 2024.03.29
 * 생명과학부 랩 인턴
 * 내 풀이
*/

#include <iostream>
#include <tuple>
#define MAX_NM 100
#define EMPTY make_tuple(-1, -1, -1)
using namespace std;

int n, m, k;            // n, m: 격자판 크기, k: 곰팡이 수
tuple<int, int, int> grid[MAX_NM][MAX_NM];        // grid[i][j]: (i,j)에 있는 곰팡이 크기, 방향, 속력  
tuple<int, int, int> next_grid[MAX_NM][MAX_NM];   // 곰팡이 이동한 다음 격자판 
int dirs[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};    // 위, 아래, 오, 왼
int collected_mold;
void Init(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            grid[i][j] = EMPTY;
        }
    }
    for(int i=0; i<k; i++){
        int x, y, s, d, b;      // (x,y) 곰팡이 위치, s: 1초동안 움직이는 거리, d: 이동 방향, b: 곰팡이 크기
        cin >> x >> y >> s >> d >> b;
        grid[x-1][y-1] = make_tuple(b, d-1, s);
    }

}

void CollectMold(int col_idx){
    for(int i=0; i<n; i++){     // 해당 열을 위에서 아래로 내려가며 탐색 진행
        if(grid[i][col_idx] != EMPTY){      // 만약 곰팡이를 만났다면
            int mold_size;
            tie(mold_size, ignore, ignore) = grid[i][col_idx];
            collected_mold += mold_size;
            grid[i][col_idx] = EMPTY;
            return;
        }
    }
}

void Initialize_next_grid(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            next_grid[i][j] = EMPTY;
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

void MoveMold(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] == EMPTY) continue;
            int size, dir, len;
            tie(size, dir, len) = grid[i][j];
            int x = i, y = j;
            for(int k=0; k<len; k++){
                int nx = x + dirs[dir][0], ny = y + dirs[dir][1];
                if(!InRange(nx, ny)){
                    dir = (dir % 2 == 0) ? dir+1: dir-1;
                    nx = x + dirs[dir][0], ny = y + dirs[dir][1];
                }
                x = nx, y = ny;
            }
            if(next_grid[x][y] == EMPTY){
                next_grid[x][y] = make_tuple(size, dir, len);
            }
            else{
                int origin_size;
                tie(origin_size, ignore, ignore) = next_grid[x][y];
                if(origin_size > size)
                    continue;
                else
                    next_grid[x][y] = make_tuple(size, dir, len);
            }
        }
    }
}

void Simulate(int col_idx){
    // Step 1. 곰팡이 채취하기
    CollectMold(col_idx);

    // Step 2. 곰팡이 이동 시작
    Initialize_next_grid();

    MoveMold();

    // Step 3. next_grid에서 grid로 바꿔주기
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            grid[i][j] = next_grid[i][j];
        }
    }


}

int main() {
    // 입력 받기:
    Init();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int b, d, s;
            tie(b, d, s) = grid[i][j];
        }
    }
    // 시뮬레이션
    for(int i=0; i<m; i++){ // m개의 열을 차례대로 보면서 검사하기
        Simulate(i);
    }
    
    cout << collected_mold;
    return 0;
}