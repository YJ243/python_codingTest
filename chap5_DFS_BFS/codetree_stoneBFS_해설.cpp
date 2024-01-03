#include <iostream>
#include <queue>
#include <algorithm>
#define MAX_N 100

using namespace std;

int n, k, m;    // n: 격자 크기, k: 시작점 개수, m: 치울 돌 개수
queue<pair<int, int> > q;

int grid[MAX_N][MAX_N];             // 격자
bool visited[MAX_N][MAX_N];         // 방문 확인 배열
int start[MAX_N*MAX_N][2];          // 모든 시작점
vector<pair<int, int> > stones;     // 돌이 들어있는 좌표들 저장
vector<pair<int, int> > removed;    // 현재 턴에서 치워야할 돌
int ans;                            // 정답, 시작점으로부터 방문이 가능한 서로 다른 칸의 수의 최댓값
int different_stone;                // 현재 턴에서 방문이 가능한 돌 개수

bool InRange(int x, int y){ // 범위 안에 있는지 확인
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){   // 갈 수 있는지 확인
    return InRange(x,y) && !grid[x][y] && !visited[x][y];
}

void do_remove(){           // m개의 돌 치우기
    for(int i=0; i<(int)removed.size(); i++){
        int cx = removed[i].first, cy = removed[i].second;
        grid[cx][cy] = 0;
    }
}

void do_recover(){          // m개의 돌 원상복구
    for(int i=0; i<(int)removed.size(); i++){
        int cx = removed[i].first, cy = removed[i].second;
        grid[cx][cy] = 1;
    }
}

void initialize(){
    // 방문 배열 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = false;

    // 시작점들 큐에 넣기
    for(int i=0; i<k; i++){
        int sx = start[i][0], sy = start[i][1];
        visited[sx][sy] = true;
        q.push(make_pair(sx, sy));
    }
    // 현재 턴에서의 갈 수 있는 서로 다른 돌 개수 초기화
    different_stone = k;
}

void bfs(){
    int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

    while(!q.empty()){
        pair<int,int> curr = q.front();
        q.pop();
        for(int d=0; d<4; d++){
            int nx = curr.first+dirs[d][0];
            int ny = curr.second+dirs[d][1];
            if(CanGo(nx,ny)){
                different_stone++;
                visited[nx][ny] = true;
                q.push(make_pair(nx,ny));
            }
        }
    }

    // 탐색이 끝난후 서로 다른 칸의 최댓값 갱신
    ans = max(ans, different_stone);
}

void Move(){
    initialize();       // 이동하기 전 초기화
    bfs();              // bfs 탐색 진행
}

// 백트래킹
void choose_stone(int t, int index){   // t번째 돌을 고르는 함수, index는 현재 stones 벡터에서 선택할 시작점
    if(t == m){
        // 만약 m개를 다 골랐다면
        do_remove();    // 그 m개 돌들 치우고 
        Move();         // 이동해보기
        do_recover();   // 다시 돌 원상태로 돌려놓기
        return;
    }

    for(int i=index; i<(int) stones.size(); i++){
        // 제거할 돌에다가 하나 선택하여 넣기
        removed.push_back(make_pair(stones[i].first, stones[i].second));
        // 다음 돌 선택
        choose_stone(t+1, i+1);
        // 선택 취소
        removed.pop_back();
    }
}

int main() {
    // 입력:
    cin >> n >> k >> m;         // n: 격자 크기, k: 시작점 수, m: 치워야 할 돌 개수

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];  // 0: 빈칸, 1: 돌
            if(grid[i][j])      // 만약 돌이 있다면 좌표 저장
                stones.push_back(make_pair(i,j));   
        }
    }

    // 시작점 저장
    for(int i=0; i<k; i++){
        cin >> start[i][0] >> start[i][1];
        start[i][0]--; start[i][1]--;       // 0부터 시작하도록 좌표 1 감소
    }

    // stones 중에서 m개 돌을 backtracking으로 고르기
    choose_stone(0,0);    // 0번째 stone 고르는 함수
    
    // 출력
    cout << ans;
    return 0;
}