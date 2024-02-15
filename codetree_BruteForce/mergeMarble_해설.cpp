/*
 * 2024.02.09
 * 해설
*/

#include <iostream>
#include <algorithm>
#include <tuple>

#define MAX_N 50
#define ASCII_NUM 128
#define DIR_NUM 4
#define EMPTY make_tuple(0,0,0)

using namespace std;

int n, m, t;
tuple<int, int, int> grid[MAX_N][MAX_N];
tuple<int, int, int> next_grid[MAX_N][MAX_N];

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> NextPos(int x, int y, int move_dir){
    int dx[DIR_NUM] = {-1,0,0,1};
    int dy[DIR_NUM] = {0,1,-1,0};

    int nx = x+dx[move_dir], ny = y+dy[move_dir];
    if(!InRange(nx,ny))
        move_dir = 3-move_dir;
    else{
        x = nx; y = ny;
    }
    return make_tuple(x, y, move_dir);
}

// (x,y) 위치에 새로운 구슬이 들어왔을 때 갱신을 진행
void Update(int x, int y, tuple<int, int, int> new_marble){
        // 기존 구슬 정보입니다.
    int num, weight, move_dir;
    tie(num, weight, move_dir) = next_grid[x][y];
    
    // 새롭게 들어온 구슬 정보입니다.
    int new_num, new_weight, new_dir;
    tie(new_num, new_weight, new_dir) = new_marble;
    
    // 새로 들어온 구슬이 더 우선순위가 높다면
    // 번호와 방향은 새로운 구슬을 따르게 됩니다.
    if(new_num > num) 
        next_grid[x][y] = make_tuple(new_num, weight + new_weight, new_dir);
    // 기존 구슬의 우선순위가 더 높다면
    // 무게만 더해집니다.
    else
        next_grid[x][y] = make_tuple(num, weight + new_weight, move_dir);
}

void Move(int x, int y){
    int num, weight, move_dir;
    tie(num, weight, move_dir) = grid[x][y];

    // Step 1. 현재 구슬의 다음 위치와 방향을 구하기
    int nx, ny, next_dir;
    tie(nx, ny, next_dir) = NextPos(x, y, move_dir);

    // Step 2. 구슬을 옮겨주기
    Update(nx, ny, make_tuple(num, weight, next_dir));
}

void Simulate(){
    // Step 1. next_grid를 초기화하기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_grid[i][j] = EMPTY;

    // Step 2. 각 구슬들을 한 칸씩 움직여주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(grid[i][j] != EMPTY)
                Move(i,j);
    
    // Step 3. next_grid값을 grid로 옮겨주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = nextx_grid[i][j];
}
int GetMarbleNum() {
    int cnt = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
            if(grid[i][j] != EMPTY)
                cnt++;
    
    return cnt;
}

int GetMaxWeight() {
    int max_weight = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
            if(grid[i][j] != EMPTY) {
			    int weight;
			    tie(ignore, weight, ignore) = grid[i][j];
			    max_weight = max(max_weight, weight);
		    }

    return max_weight;
}

int main(){
    cin >> n >> m >> t;

    int dir_mapper[ASCII_NUM];
    dir_mapper['U'] = 0;
    dir_mapper['R'] = 1;
    dir_mapper['L'] = 2;
    dir_mapper['D'] = 3;

    for(int i=0; i<m; i++){
        int r, c, w; char d;
        cin >> r >> c >> d >> w;
        grid[r-1][c-1] = make_tuple(i+1, w, dir_mapper[d]);
    }

    // t초에 걸쳐 시뮬레이션을 진행
    while(t--){
        Simulate();
    }

    int marble_num = GetMarbleNum();
    int max_weight = GetMaxWeight();

    cout << marble_num << ' ' << max_weight;
    return 0;
}