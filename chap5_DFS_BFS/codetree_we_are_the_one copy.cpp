/*
 * 2024.1.3
 * backtracking으로 선택하는 부분을 잘 몰라서 오래 걸린 문제
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <queue>

#define MAX_N 8
#define MAX_DIR 4
using namespace std;

int n, k, u, d;             // n: 격자 크기, k: 고를 도시의 수, u이상 d이하의 높이 차
int grid[MAX_N][MAX_N];     // 격자

queue<pair<int, int> > q;
bool visited[MAX_N][MAX_N]; // 방문 확인 배열
int ans;                    // k개의 도시를 골라서 갈 수 있는 서로 다른 도시의 수 중 최댓값
int cur_cnt;                // 현재 턴에서의 갈 수 있는 서로 다른 도시의 수
int dirs[MAX_DIR][2] = {{1,0},{-1,0},{0,1},{0,-1}};
vector<pair<int, int> > selected_city;

void Initialize(){                      // 탐색을 위해 초기화하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }
    cur_cnt = 0;
}

bool InRange(int x, int y){             // 범위 내에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int fromX, int fromY, int toX, int toY){ // 이동할 수 있는지 확인하는 함수
    // 범위 내에 있고, 방문한 적이 없으며, 두 도시간의 높이의 차가 u이상 d이하인 경우
    return InRange(toX, toY) && !visited[toX][toY] && 
        (u <= abs(grid[fromX][fromY] - grid[toX][toY]) && abs(grid[fromX][fromY] - grid[toX][toY]) <= d);
}

void bfs(){                                 // 갈 수 있는 서로 다른 도시의 수 탐색
    // 탐색을 돌기 전에 초기화하기
    Initialize();

    // 선택된 도시들을 시작점으로 하기 위해 큐에다가 담기
    for(int i=0; i<(int)selected_city.size(); i++){
        q.push(make_pair(selected_city[i].first, selected_city[i].second));
        visited[selected_city[i].first][selected_city[i].second] = true;
        cur_cnt++;
    }

    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();

        for(int d=0; d<MAX_DIR; d++){
            int nx = curr.first + dirs[d][0] , ny = curr.second + dirs[d][1];
            if(CanGo(curr.first, curr.second, nx,ny)){
                // 만약 갈 수 있다면?
                cur_cnt++;
                visited[nx][ny] = true;
                q.push(make_pair(nx,ny));
            }
        }
    }
    // 탐색으로 얻어진 도시 수와 정답을 비교해서 답 갱신하기

    ans = max(ans, cur_cnt);    
}

// 백트래킹으로 고르기
void choose_city(int idx, int x, int y){    // selected_city의 idx번째 도시를 선택, 현재 인덱스는(0,0) 
    if(selected_city.size() == k){
        // 만약 k개 도시를 다 골랐다면
        // k개의 도시를 시작점으로 갈 수 있는 도시의 개수 구하기
        bfs();
        return;
    }

    for (int i = x; i < n; i++) {
        for (int j = (i == x ? y : 0); j < n; j++) {
            selected_city.push_back(make_pair(i, j));
            choose_city(idx + 1, i, j + 1);
            selected_city.pop_back();
        }
    }
}

int main() {
    // 입력:
    cin >> n >> k >> u >> d;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }

    // k개의 도시 고르기
    choose_city(0,0,0);

    cout << ans;
    return 0;
}