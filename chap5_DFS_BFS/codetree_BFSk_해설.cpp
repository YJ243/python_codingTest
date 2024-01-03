/*
 * 2024.1.2
 * 해설 풀이
 * 최대 k번 움직임, 각 이동을 위해 BFS를 통해 모든 격자 최대 1번씩 탐색=> O(K*N^2)
 * BFS를 이용하면 현재 칸으로부터 도달 가능한 모든 칸의 위치를 구할 수 있음
 * 그 후 (숫자, -행, -열) 순으로 가장 우선순위가 높은 위치를 구해 이동시켜주기 
*/

#include <iostream>
#include <tuple>
#include <queue>

#define MAX_N 100
#define DIR_NUM 4
#define NOT_EXISTS make_pair(-1,-1)

using namespace std;

int n, k;                       // n: 격자 크기, k: 반복할 횟수
int grid[MAX_N][MAX_N];         // 격자
pair<int, int> cur_cell;        // 현재 위치
queue<pair<int, int> > q;       // bfs를 위한 큐
bool visited[MAX_N][MAX_N];     // 방문 확인 배열


bool InRange(int x, int y){         // 범위 안에 있는지 확인
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int val){  // 범위 안에 있고, 방문하지 않았고, 시작 위치보다 작은 값으로 이동 가능
    return InRange(x,y) && !visited[x][y] && grid[x][y] < val;
}

void initialize(){                  // 방문 배열 초기화
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }
}

void bfs(){               // 조건을 만족하는 곳으로 탐색 진행
    int dx[DIR_NUM] = {0,1,0,-1};
    int dy[DIR_NUM] = {1,0,1,-1};
    int curr_x, curr_y;
    tie(curr_x, curr_y) = curr_cell;
    visited[curr_x][curr_y] = true;
    q.push(curr_cell);
    int target_num = grid[curr_x][curr_y];

    // bfs 탐색 수행 
    while(!q.empty()){
        pair<int, int> cur_pos= q.front();
        int curr_x, curr_y;
        tie(curr_x, curr_y) = cur_pos;
        q.pop();

        for(int dir = 0; dir<DIR_NUM; dir++){
            int nx = curr_x + dx[i];
            int ny = curr_y + dy[i];
            if(CanGo(nx,ny, target_num)){
                visited[nx][ny] = true;
                q.push(make_pair(nx,ny));
            }
        }
    }
}

// best 위치를 새로운 위치로 바꿔줘야 하는지를 판단
bool NeedUpdate(pair<int, int> best_pos, pair<int, int> new_pos){
    // 첫 도달 가능한 위치라면 update 필요
    if(best_pos == NOT_EXISTS) return true;

    int best_x, best_y;
    tie(best_, best_y) = best_pos;

    int new_x, new_y;
    tie(new_x, new_y) = new_pos;

    // 숫자, -행, -열 순으로 더 큰 곳이 골라져야 함
    return make_tuple(grid[new_x][new_y], -new_x, -new_y) > make_tuple(grid[best_x][best_y], -best_x, -best_y);
}


// 가장 우선순위가 높은 위치를 찾아 위치를 이동
bool Move(){
    // BFS 탐색을 위한 초기화 작업 수행
    initialize();
    // Step1. bfs를 진행해 갈 수 있는 모든 위치를 탐색
    bfs();

    // Step 2. 도달 할 수 있는 위치들 중 가장 우선순위가 높은 위치를 구하기
    pair<int, int> best_pos = NOT_EXISTS;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            // 도달이 불가능하거나 현재 위치는 건너뜀
            if(!visited[i][j] || make_pair(i,j) == curr_cell) continue;

            pair<int, int> new_pos = make_pair(i,j);
            if(NeedUpdate(best_pos, new_pos))
                best_pos = new_pos;
        }
}
int main() {
    cin >> n >> k;              // n: 격자 크기, k: 반복할 횟수
    for(int i=0; i<n; i++){     // 격자에다가 숫자 채우기
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    cin >> r >> c;      // 시작 위치 담기
    r--; c--;
    curr_cell = make_pair(r, c);

    while(k--){         // k번에 걸쳐 움직이는 것을 반복
        bool is_moved = Move();

        // 움직이지 못했다면 바로 종료
        if(!is_moved) break;
    }
    int final_x, final_y;
    tie(final_x, final_y) = curr_cell;
    cout << final_x+1 << " " << final_y+1;
    return 0;
}