/*
 * 2024.03.26
 * 바이러스 백신
 * 해설 풀이
 * backtracking + 선택된 병원을 시작으로 BFS
 * 시간복잡도: 모든 M개의 병원을 뽑는 경우에 대해 BFS를 오직 한 번만 돌리면 되기 때문에
 * O(C(R, M) * N * M)
*/

#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

#define DIR_NUM 4
#define MAX_N 50

using namespace std;

// 전역 변수 선언:
int n, m;
int a[MAX_N][MAX_N];
vector<pair<int, int> > hospitals;
vector<pair<int, int> > selected_hos;

// bfs에 필요한 변수들
queue<pair<int, int> > q;
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];

int ans = INT_MAX;

// 범위가 격자 안에 들어가는지 확인한다.
bool InRange(int x, int y){         // (x, y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 범위를 벗어나지 않으면서 벽이 아니고, 방문한 적이 없어야 갈 수 있다.
bool CanGo(int x, int y){           // (x, y)로 이동할 수 있는지 확인하는 함수
    return InRange(x, y) && !visited[x][y] && grid[x][y] != 1; 
}

// queue에 새로운 위치를 추가하고
// 방문 여부를 표시해준다.
// 시작점으로부터의 최단거리 값도 갱신해준다.
void Push(int x, int y, int new_step){
    q.push(make_pair(x, y));
    visited[x][y] = true;
    step[x][y] = new_step;
}

// visited, step 배열을 초기화한다.
void Initialized(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = step[i][j] = 0;
}

// bfs를 통해 선택된 병원들로부터 가장 거리가 먼 바이러스까지의 거리를 구한다.
int FindMaxDist(){
    // queue에서 가장 먼저 들어온 원소를 뺀다.
    while(!q.empty()){
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        q.pop();

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        // queue에서 뺀 원소의 위치를 기준으로 4방향을 확인한다.
        for(int dir = 0; dir < DIR_NUM; dir++){
            int nx = x + dx[dir], ny = y + dy[dir];

            // 더 갈 수 있는 곳이라면 Queue에 추가한다.
            if(CanGo(nx, ny))
                // 최단 거리는 이전 최단거리에 1이 증가하게 된다.
                Push(nx, ny, step[x][y] + 1);
        }
    }

    // 바이러스들까지의 거리들 중 가장 먼 거리를 기록한다.
    int max_dist = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            // 바이러스인 경우에만 거리를 갱신한다.
            if(a[i][j] == 0){
                if(visited[i][j])
                    max_dist = max(max_dist, step[i][j]);
                // 만약 선택한 병원 조합으로는 해당 바이러스에 도달이 불가능하다면
                // 도달이 불가능하다는 표시로 INT_MAX_를 넣어준다.
            }
            else
            {
                max_dist = INT_MAX;
            }
        }
    return max_dist;
}

// 선택된 병원으로부터 모든 바이러스를 없애기 위해 걸리는 시간을 계산한다.
int ElapsedTimeToKillAllVirus(){
    // BFS를 다시 돌리기 전에 visied, step 배열을 초기화한다.
    Initialize();

    // 선택된 병원들을 시작으로 하여 BFS를 1번 돌린다.
    for(int i=0; i<(int)selected_hos.size(); i++){
        Push(selected_hos[i].first, seleced_hos[i].second, 0);
    }
    int max_elapsed_time = FindMaxDist();
    return max_elapsed_time;
}

// backtracking을 이용하여 m개의 병원을 전부 선택해 봐서
// 그 중 모든 바이러스를 없애는 데 걸리는 시간 중 최소 시간을 구한다.
void FindMinTime(int curr_idx, int cnt){
    if(cnt == m){
        // 선택된 병원으로부터 모든 바이러스를 없애기 위해 걸리는 시간을 계산해
        // 답보다 더 좋은 경우 갱신해준다.
        ans = min(ans, ElapsedTimeToKillAllVirus());
        return;
    }

    if(curr_idx == (int) hospitals.size())
        return;

    FindMinTime(curr_idx+1, cnt);

    selected_hos.push_back(hospitals[curr_idx]);
    FindMinTime(curr_idx+1, cnt+1);
    selected_hos.pop_back();
}

int main(){
    // 입력:
    cin >> n >> m;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin >> a[i][j];

            // backtracking을 선택할 병원 index를 기준으로 쉽게 돌리기 위해
            // 병원 위치만 따로 저장한다.
            if(a[i][j] == 2)
                hospitals.push_back(make_pair(i,j));
        }
    
    // 최소 시간을 구한다.
    FindMinTime(0, 0);

    // 출력:
    if(ans == INT_MAX)
        ans = -1;
    cout << ans;

    return 0; 
}