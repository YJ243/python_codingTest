/*
 * 2024.03.29
 * 처음에 시간초과가 나오게 풀어서 고친 풀이
*/

#include <iostream>
#include <queue>
#include <cmath>
#include <vector>
#define MAX_N 50

using namespace std;

int n, L, R;                    // 토스트 틀 크기, L이상 R이하의 차이
int grid[MAX_N][MAX_N];         // 토스트 계란 양
int next_grid[MAX_N][MAX_N];    // 다음 계란 양
int count_num = -1;             // 그룹 번호

queue<pair<int, int> > q;       // bfs 탐색을 위한 큐
bool visited[MAX_N][MAX_N];     // 방문했는지 확인하는 배열

int total_cnt;          // 현재 보고 있는 계란 그룹의 개수
int total_sum;          // 현재 보고 있는 계란 그룹의 계란 양 합
vector<int> numbers;    // 각 그룹에 들어가야 할 계란 양

int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
bool IsMoved = false;   // 이번 턴에 이동했는지 확인하는 변수

void Input(){           // 입력을 받는 함수
    cin >> n >> L >> R;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
}

void Initialize_before_search(){        // 탐색 전 초기화하는 변수
    IsMoved = false;                    // 이동 여부 초기화
    for(int i=0; i<n; i++)              // 매 칸마다 방문 여부, 다음 칸 초기화
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            next_grid[i][j] = -1;
        }
    numbers.clear();                    // 칸에 들어갈 숫자들 초기화
}

void Push(int x, int y){                // (x,y)를 push
    visited[x][y] = true;
    next_grid[x][y] = count_num;
    q.push(make_pair(x, y));
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int prior_value){      // (x,y)로 갈 수 있는지 확인하는 함수
    // 이전 계란틀에 있는 계란의 양과 차이가 L이상 R이하일 때 갈 수 있음
    int diff = abs(grid[x][y] - prior_value);
    return InRange(x, y) && !visited[x][y] && (L <= diff && diff <= R); 
}

void bfs(){
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first, y = curr.second;

        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            if(CanGo(nx, ny, grid[x][y])){
                Push(nx, ny);
                total_cnt++;
                total_sum += grid[nx][ny];
            }
        }
    }
}

void MakeNextEgg(){     // 새로운 계란 만들기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int idx = next_grid[i][j];
            grid[i][j] = numbers[idx];
        }
    }
}

void Simulate(){        // 계란 이동 시뮬레이션 함수
    // 1. 먼저 이동 전 움직인 여부 초기화하기
    Initialize_before_search();

    // 2. 매 칸마다 확인하면서 탐색 진행
    count_num = -1;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j]) continue;     // 만약 이미 탐색을 진행한 곳이라면 넘어가기
            count_num++;
            Push(i, j);
            total_cnt = 1;
            total_sum = grid[i][j];
            bfs();
            numbers.push_back(total_sum / total_cnt);

            if(total_cnt > 1)   
                IsMoved = true;
        }
    }

    MakeNextEgg();

}

int main() {
    // 입력 받기:
    Input();

    // 계란 이동 시작하기
    int cnt = 0;
    while(true){
        Simulate();
        if(IsMoved)
            cnt++;
        else
            break;
    }
    cout << cnt;
    return 0;
}