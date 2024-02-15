/*
 * 2024.02.12
 * 코드트리 빵
 * 마지막에 메모리 초과가 나옴 => bfs 탐색 시 방문하지 않은 곳만 가도록 해야 하는데, 그 조건을 빠뜨렸음!!!
*/

#include <iostream>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <tuple>
#include <queue>

#define MAX_N 15
#define MAX_M 30
using namespace std;

int n, m;   
int grid[MAX_N][MAX_N];                         // 격자 상태
/*
 * grid[i][j]
 * 0: 빈공간
 * -1, -2, ... 음수: 각 칸에 -를 붙인 값은 각 사람에 해당하는 편의점
 * 1: 베이스 캠프
 * 절대 지나갈 수 없는 곳: INT_MIN
*/
// 탐색을 위한 자료구조
queue<tuple<int, int, int, int> > q;            // (x,y), dist, start_dir
queue<tuple<int, int, int, int, int> > campQ;   // (basecamp: start_x, start_y), (cur_x, cur_y), dist;
int visited[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};    // 상, 좌, 우, 하 우선순위
tuple<int, int, bool> people[MAX_M+1];          // 사람들 정보, [(x,y),isArrived]: 위치, 도착 유무 

int elapsed_time;                               // 진행 시간
void Input(){
    cin >> n >> m;      // 격자 크기, 사람 수 입력받기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
    for(int i=1; i<=m; i++){    // m명의 편의점 위치 입력받기
        int x, y;
        cin >> x >> y;
        grid[x-1][y-1] = -i;    // 편의점 번호 넣기(-를 취한 값이 각 사람의 번호)

    }
}

void Output(){                  // 편의점에 모두 도달하기까지 걸리는 시간 출력
    cout << elapsed_time << '\n';
}

bool InRange(int x, int y){     // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Initialize_before_search(){    // 탐색 전 초기화를 위한 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }

    while (!q.empty()) {
        q.pop();
    }
    while(!campQ.empty()){
        campQ.pop();
    }
}

int bfs(int target_x, int target_y){      // 탐색을 통해 해당 목표 지점(target_x, target_y)까지 도착해야 될 다음 방향을 반환
    int ret = -1;
    while(!q.empty()){      // 큐가 빌 때까지
        int curX, curY, curDist, startDir;
        tie(curX, curY, curDist, startDir) = q.front();
        q.pop();
        if(curX == target_x && curY == target_y){
            // 만약 도달해야 하는 지점에 도착했다면
            ret = startDir;
            return ret;
        }
        for(int d=0; d<4; d++){
            int nx = curX+dirs[d][0], ny = curY+dirs[d][1];
            if(InRange(nx,ny) && !visited[nx][ny] && grid[nx][ny] != INT_MIN){
                // 범위 안에 있고, 지나가지 못하는 자리가 아니라면
                visited[nx][ny] = true;
                q.push(make_tuple(nx,ny,curDist+1, startDir));
            }
        } 
    }
    return ret;
}

pair<int, int> FindTargetLoc(int idx){      // idx번 편의점 위치를 반환하는 함수 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == -idx)
                return {i,j};
        }
    }
}

void MovePeopleInGrid(){                    // 격자 안의 사람들을 이동하는 함수
    for(int i=1; i<=min(elapsed_time-1, m); i++){      // 1번부터 모든 사람 확인하기
        int x, y; bool isArrived = false;
        tie(x, y, isArrived) = people[i];
        if(!isArrived){     // 만약 아직 편의점에 도착하지 못했다면, 이동하기
            // 1. 탐색 전 초기화
            Initialize_before_search();
            // 2. 현재 위치로부터 편의점까지의 최단 거리 탐색, 해당 방향으로 이동하기
            for(int d=0; d<4; d++){
                int nx = x + dirs[d][0], ny = y + dirs[d][1];
                if(InRange(nx,ny) && grid[nx][ny] != INT_MIN){
                    // 현재 위치로부터 인접해 있는 네 곳이 격자 내에 있고, 이동할 수 있는 곳이라면
                    visited[nx][ny] = true;             // 방문 표시
                    q.push(make_tuple(nx,ny, 1, d));    // (위치, 이동거리, 시작 방향) 큐에 넣기
                }
            }
            pair<int, int> target = FindTargetLoc(i);           // 현재 보고 있는 사람이 가야할 편의점 좌표 
            int next_dir = bfs(target.first, target.second);    // bfs 탐색을 통해 네 방향 중 다음에 이동할 방향을 찾기
            x = x+dirs[next_dir][0], y = y+dirs[next_dir][1];   // 해당 방향으로 사람 이동시켜주기
            if(grid[x][y] == -i){   // 만약 편의점에 도착했다면
                isArrived = true;   // 도착했다는 것을 참으로 바꾸기
            }
            people[i] = make_tuple(x,y,isArrived);      // 사람 정보에 현재 위치, 도착 여부를 집어넣기
        }
    }
}

void CheckArriveToStore(){      // 모든 사람이 이동한 후에 절대 지나갈 수 없는 곳을 표시하는 함수
    for(int i=1; i<=m; i++){
        // 모든 사람에 대해서 확인해보기
        int x, y; bool isArrived = false;
        tie(x, y, isArrived) = people[i];
        if(isArrived){
            // 만약 도착했다면
            grid[x][y] = INT_MIN;   // 지나갈 수 없는 곳임을 표시하기
        }
    }
}

pair<int, int> bfs_basecamp(){      // 격자 밖에 있는 사람이 처음으로 이동할 베이스 캠프 위치를 찾아주는 함수
    int toX, toY;
    while(!campQ.empty()){
        int startX, startY, curX, curY, dist;
        tie(startX, startY, curX, curY, dist) = campQ.front();
        campQ.pop();

        if(grid[curX][curY] == -elapsed_time){
            toX = startX, toY = startY;
            return make_pair(toX, toY);
        }
        for(int d=0; d<4; d++){
            int nx = curX+dirs[d][0], ny = curY+dirs[d][1];
            if(InRange(nx,ny) && !visited[nx][ny] && grid[nx][ny] != INT_MIN){
                visited[nx][ny] = true;
                campQ.push(make_tuple(startX, startY, nx, ny, dist+1));
            }
        }
    }
    return make_pair(toX, toY);
}

void MoveOnePerson(){       // 격자 밖의 사람 중 현재 시간을 번호로 갖는 사람을 이동시키는 함수
    // elapsed_time번 번호를 가진 사람 이동시키기
    int x, y; bool isArrived = false;
    tie(x, y, isArrived) = people[elapsed_time];
    // 1. 탐색 전 초기화
    Initialize_before_search();
    pair<int, int> target = FindTargetLoc(elapsed_time);    // 해당 사람이 가야할 편의점 위치
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 모든 베이스 캠프를 시작점으로 삼기
            if(grid[i][j] == 1){
                visited[i][j] = true;
                campQ.push(make_tuple(i,j,i,j,0));          // 큐에다가 (시작 위치, 현재 위치, 이동거리) 넣기
            }
        }
    }
    pair<int, int> next_loc = bfs_basecamp();       // bfs 탐색을 통해 다음에 이동할 베이스 캠프 위치 찾기

    people[elapsed_time] = make_tuple(next_loc.first, next_loc.second, isArrived);      // 사람 정보에 집어넣기
    grid[next_loc.first][next_loc.second] = INT_MIN;        // 이동한 이후에 해당 베이스 캠프는 절대 지나갈 수 없는 곳으로 표시하기
}

void Simulation(){
    elapsed_time++;     // 시간 증가
    // 1. 현재 elapsed_time보다 작은 인덱스들 먼저 이동시키기
    MovePeopleInGrid();
    // 2. 모두 이동한 뒤 편의점에 도착한 사람들 칸을 절대 지나갈 수 없는 칸으로 표시하기
    CheckArriveToStore();
    // 3. t<=m이면 격자 밖에 있는 사람, 현재 초를 번호로 가지고 있는 해당 사람을 이동시키기
    if(elapsed_time <= m){
        MoveOnePerson();
    }
}

bool IsFinish(){        // 프로그램이 종료됐는지 확인하는 함수
    for(int i=1; i<=m; i++){
        // m명에 사람이 모두 탈출에 성공했다면
        bool isArrived = false;
        tie(ignore, ignore, isArrived) = people[i];
        if(!isArrived)  // 한 명이라도 도착하지 않았다면 false 리턴
            return false;
    }
    return true;
}

int main() {
    // 입력:
    Input();
    
    // 시뮬레이션 시작
    while(true){
        if(IsFinish())  // 만약 모든 사람이 편의점에 도착했다면
            break;
        Simulation();
    }
    
    // 출력:
    Output();
    return 0;
}