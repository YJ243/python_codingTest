/*
 * 2024.04.04
 * 코드트리 빵
*/

#include <iostream>
#include <queue>
#include <climits>
#include <tuple>
#define MAX_N 15
#define BEFORE_START make_pair(-1,-1)
using namespace std;
int n, m;       // n: 격자 크기, m: 사람 수
int grid[MAX_N][MAX_N];
// grid[i][j]: 격자 정보
// 0: 빈 공간
// 1: 베이스 캠프
// 2: 아무도 갈 수 없는 곳
// 음수: -를 한 값이 각 사람의 번호이고, 그 사람의 편의점 위치
// 만약 베이스캠프, 편의점 도착하면 0으로 바꾸기
pair<int, int> person_loc[MAX_N*MAX_N+1];   // person_loc[i]: i번 사람 위치
bool IsArrived[MAX_N*MAX_N+1];              // 도착했는지 여부

queue<pair<int, int> > q;
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];
pair<int, int> fromStep[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};    // ↑, ←, →, ↓  우선순위
int elapsed_time;
void Input(){
    cin >> n >> m;  // n: 격자 크기, m: 사람 수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];      // 격자 정보 입력받기
        }
    }
    for(int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        grid[x-1][y-1] = -i;
        person_loc[i] = BEFORE_START;
    }
}

bool IsFinished(){      // 움직임이 끝났는지 확인하는 함수
    for(int i=1; i<=m; i++){
        if(!IsArrived[i])   // 한 명이라도 도착하지 않았다면 끝나지 않음 
            return false;
    }
    return true;
}

void Initialize_before_search(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            step[i][j] = 0;
            fromStep[i][j] = BEFORE_START;
        }
    }
    while(!q.empty())
        q.pop();
}

bool InRange(int x, int y){     // (x,y)가 범위 안에 있는지 확인하는 함수 
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){       // (x,y)로 이동할 수 있는지 확인하는 함수
    return InRange(x, y) && grid[x][y] != 2 && !visited[x][y] ;
}

void bfs(){     // 최단거리 탐색 시작
    while(!q.empty()){
        pair<int, int> curr = q.front(); q.pop();
        int x = curr.first, y = curr.second;
        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            if(CanGo(nx, ny)){
                visited[nx][ny] = true;
                q.push(make_pair(nx, ny));
                step[nx][ny] = step[x][y]+1;
            }
        }
    }
}

int bfs_for_move(int idx){
    int ret;
    bool IsFind = false;
    while(!q.empty()){
        pair<int, int> curr = q.front(); q.pop();
        
        int x = curr.first, y = curr.second;
        if(grid[x][y] == -idx){     // 확인을 여기서 해야함! 그럼 정확해!
            ret = fromStep[x][y].first;     // 만약 편의점에 도착했다면 거리 저장
            IsFind = true;                  // 편의점 찾았다고 표시하기
            break;
        }
        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            if(CanGo(nx, ny)){
                visited[nx][ny] = true;
                q.push(make_pair(nx, ny));
                fromStep[nx][ny] = make_pair(fromStep[x][y].first, fromStep[x][y].second+1);

            }
        }
        if(IsFind) break;
        
    }
    return ret;
}

void MovePerson(int idx){       // 격자에 있는 idx번 사람을 한 칸 이동시키는 수
    int x = person_loc[idx].first, y = person_loc[idx].second;      // 사람의 위치
    // 현재 위치로부터 편의점까지 최단거리 방향으로 한 칸 움직이기
    Initialize_before_search();
    visited[x][y] = true;
    
    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(CanGo(nx, ny)){
            visited[nx][ny] = true;
            q.push(make_pair(nx, ny));
            fromStep[nx][ny] = make_pair(d, 1);     // d번 방향에서 시작했고, 거리가 1임
        }
    }
    int d = bfs_for_move(idx);  // 최단거리를 만들어줄 d방향 찾기
    x += dirs[d][0]; y += dirs[d][1];
    person_loc[idx] = make_pair(x, y);
}

void ProcessConvenient(){       // 편의점 도착한 사람 처리하는 함수
    for(int i=1; i<=m; i++){
        int x = person_loc[i].first, y = person_loc[i].second;
        if(grid[x][y] == -i && !IsArrived[i]){
            IsArrived[i] = true;
            grid[x][y] = 2;         // 못 지나간다 표시하기
        }
    }
}

void GoCamp(int idx){           // idx번 사람이 격자 밖에서 출발시간이 되어 베이스 캠프로 들어가도록 하는 함수
    // idx의 편의점과 가장 가까이 있는 베이스 캠프 찾기
    // 1. 먼저 탐색 전 초기화하기
    Initialize_before_search();
    // 2. idx번 편의점 찾아서 큐에 넣기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == -idx){
                visited[i][j] = true;
                q.push(make_pair(i, j));
            }
        }
    }
    // 3. 탐색 시작
    bfs();

    // 4. 최단거리, r, c가 작은 베이스 캠프 찾기
    int minL = INT_MAX, minR = INT_MAX, minC = INT_MAX;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 1 && visited[i][j]){
                if(make_tuple(minL, minR, minC) > make_tuple(step[i][j], i, j)){
                    minL = step[i][j], minR = i, minC = j;
                }
            }
        }
    }
    person_loc[idx] = make_pair(minR, minC);
    grid[minR][minC] = 2;       // 지나가지 못한다는 표시로 2
}

void Simulate(){        // 시뮬레이션 진행
    // Step 1. 격자에 있는 사람들 이동
    for(int i=1; i<=m; i++)
        if(elapsed_time > i && !IsArrived[i])   // 현재 시간보다 인덱스가 크고(격자에 있음), 아직 도착하지 않았다면 움직이기
            MovePerson(i);

    // Step 2. 편의점 도착시 멈춤
    ProcessConvenient();

    // Step 3. elapsed_time <= m을 만족한다면 t번 사람 베이스 캠프 들어가기
    for(int i=1; i<=m; i++)
        if(i == elapsed_time)
            GoCamp(i);
}

int main() {
    // 입력 받기:
    Input();   
    while(true){
        if(IsFinished())
            break;
        elapsed_time++;
        Simulate();
    }
    cout << elapsed_time;
    return 0;
}