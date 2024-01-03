/*
 * 2024.1.3
 * backtracking을 이용해 주어진 도시 중 시작점이 될 k개의 도시를 선택하고,
 * 각 선택마다 k개의 시작점을 처음 queue에 전부 집어넣어 시작점이 여러 개인 경우의 bfs 탐색 진행
 * *** Backtracking의 n개 중에 m개 고르기 문제 풀기 ***
 * 시작점이 여러 개인 BFS: 처음 모든 시작점을 전부 queue에 넣은 뒤 bfs를 한 번 진행하는 것으로 해결하기
 * C(N^2, K)개의 조합에 대해서  
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <queue>

#define DIR_NUM 4
#define MAX_N 8

using namespace std;

// 전역 변수 선언:
int n, k, u, d;
int a[MAX_N][MAX_N];

int ans;

vector<pair<int, int> > s_pos;
vector<pair<int, int> > pos;

// bfs에 필요한 변수들
queue<pair<int, int> > q;
bool visited[MAX_N][MAX_N];

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int target){
    if(!InRange(x,y) || visited[x][y])
        return false;

    int diff = abs(target - a[x][y]);
    return u <= diff && diff <= d;
}

void BFS() {
    // queue에 남은 것이 없을때까지 반복합니다.
    while(!q.empty()) {
        // queue에서 가장 먼저 들어온 원소를 뺍니다.
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        q.pop();

        int dx[DIR_NUM] = {1, -1, 0, 0};
        int dy[DIR_NUM] = {0, 0, 1, -1};

        // queue에서 뺀 원소의 위치를 기준으로 4방향을 확인해봅니다.
        for(int dir = 0; dir < DIR_NUM; dir++) {
            int nx = x + dx[dir], ny = y + dy[dir];

            // 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            // 새로 queue에 넣어주고 방문 여부를 표시해줍니다. 
            if(CanGo(nx, ny, a[x][y])){
                q.push(make_pair(nx, ny));
                visited[nx][ny] = true;
            }
        }
    }
}


int Calc(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = 0;

    // bfs 를 이용해서 k개의 시작점으로부터 도달 가능한 지점 탐색
    // 모든 시작점을 queue에 넣고 시작하면
    // 단 한번의 탐색으로 모든 도달 가능한 위치를 구할 수 있음
    for(int i=0; i<k; i++)
    {
        q.push(s_pos[i]);
        visited[s_pos[i].first][s_pos[i].second] = true;
    }

    BFS();

    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(visited[i][j]) cnt++;
        }
    }
    return cnt;
}

void FindMax(int idx, int cnt){
    if(cnt > k)
        return;

    if(idx == n*n){
        if(cnt == k)
            ans = max(ans, Calc());
        return;
    }

    s_pos.push_back(pos[idx]);
    FindMax(idx+1, cnt+1);
    s_pos.pop_back();

    FindMax(idx+1, cnt);
}

int main(){
    // 입력:
    cin >> n >> k >> u >> d;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            pos.push_back(make_pair(i,j));
        }
    FindMax(0,0);

    cout << ans;
    return 0;
}
