/*
 * 2024.1.14 해설 풀이
각 사람마다 가장 가까운 쉘터를 구하는 문제
=> 각 사람마다 BFS를 돌려서 가장 가까운 쉘터를 구하는 것이 아님!
=> m개의 쉘터를 시작으로 하는 BFS를 한 번 돌리는 것으로 해결이 가능

시작점이 하나일 때 BFS를 돌리면? 그 시작점으로부터 각 격자 칸에 도달하기 위한 최단거리를 구할 수 있음, BFS는 큐를 이용하기 때문에
여러개의 시작점으로 BFS를 돌리면? 각각 시작점으로부터 가장 가까운 정점부터 큐에서 나옴
                                -> 여러 쉘터에 대한 고민하지 않아도 됨
                                -> 각 칸마다 가장 가까운 쉘터까지 거리가 한번의 BFS로 구해지게 됨
                                -> BFS를 한 번만 돌리면 되기 때문에 O(N^2)
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

#define MAX_N 100
#define DIR_NUM 4

using namespace std;

// 전역 변수 선언:
int n, h, m;

int a[MAX_N][MAX_N];

vector<pair<int, int> > s_pos;

// bfs에 필요한 변수들 입니다.
queue<pair<int, int> > q;
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N]; // step[i][j] : 시작점으로부터 
                        // (i, j) 지점에 도달하기 위한 
                        // 최단거리를 기록합니다.

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 격자를 벗어나지 않으면서, 벽도 없고, 아직 방문한 적이 없는 곳이라면
// 지금 이동하는 것이 최단거리임을 보장할 수 있으므로 가야만 합니다. 
bool CanGo(int x, int y) {
    return InRange(x, y) && a[x][y] != 1 && !visited[x][y];
}

// queue에 새로운 위치를 추가하고
// 방문 여부를 표시해줍니다.
// 시작점으로 부터의 최단거리 값도 갱신해줍니다.
void Push(int nx, int ny, int new_step) {
    q.push(make_pair(nx, ny));
    visited[nx][ny] = true;
    step[nx][ny] = new_step;
}

// bfs를 통해 최소 이동 횟수를 구합니다.
void BFS() {
    // queue에 남은 것이 없을때까지 반복합니다.
    while(!q.empty()) {
        // queue에서 가장 먼저 들어온 원소를 뺍니다.
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        q.pop();

        int dx[DIR_NUM] = {-1, 1, 0, 0};
        int dy[DIR_NUM] = {0, 0, -1, 1};

        // queue에서 뺀 원소의 위치를 기준으로 4방향을 확인해봅니다.
        for(int dir = 0; dir < DIR_NUM; dir++) {
            int nx = x + dx[dir], ny = y + dy[dir];

            // 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            // 새로 queue에 넣어줍니다.
            if(CanGo(nx, ny))
                // 최단 거리는 이전 최단거리에 1이 증가하게 됩니다. 
                Push(nx, ny, step[x][y] + 1);
        }
    }
}

int main(){
    // 입력:
    cin >> n >> h >> m;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			cin >> a[i][j];
            if(a[i][j] == 3)
                s_pos.push_back(make_pair(i,j));
        }

    // 비를 피할 수 있는 공간들을 전부 시작점으로 하는
    // bfs를 진행
    // 이는 각 사람마다 가장 가까운 쉘터까지의 거리를 단 한 번의 bfs로 구할 수 있도록 함
    for(int i=0; i<(int) s_pos.size(); i++)
        Push(s_pos[i].first, s_pos[i].second, 0);
    
    BFS();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(a[i][j] != 2)
                cout << 0 << ' ';
            else{
                if(!visited[i][j])
                    cout << -1 << ' ' ;
                else
                    cout << step[i][j] << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}