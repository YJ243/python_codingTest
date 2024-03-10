/*
 * 2024.03.01
 * 내 풀이
*/

#include <iostream>
#include <queue>
#include <tuple>
#define MAX_N 20
using namespace std;

int n, m, c;                            // n: 격자 크기, m: 승객 수, c: 초기 배터리 충전량
int grid[MAX_N][MAX_N];                 // 0: 도로, 1: 벽
int passenger[MAX_N][MAX_N];            // 양수: 승객 인덱스, 0: 빈 곳
int dist[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
pair<int, int> dest[MAX_N*MAX_N+1];     // 각 승객마다의 도착지 정보
bool visited[MAX_N][MAX_N];

int carX, carY;
queue<pair<int, int> > q;

void Input(){
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    cin >> carX >> carY;
    carX--; carY--;
    for(int i=1; i<=m; i++){
        int sX, sY, eX, eY;
        cin >> sX >> sY >> eX >> eY;
        passenger[sX-1][sY-1] = i;
        dest[i] = make_pair(eX-1, eY-1);
    }
}

void Initialize(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            visited[i][j] = false;
            dist[i][j] = -1;
        }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    // 범위 안에 있고, 길이 도로이고, 아직 방문하지 않은 곳이라면 갈 수 있음
    return InRange(x, y) && grid[x][y] == 0 && !visited[x][y]; 
}

void bfs(){
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        for(int d=0; d<4; d++){
            int nx = curr.first + dirs[d][0], ny = curr.second + dirs[d][1];
            if(CanGo(nx, ny)){
                visited[nx][ny] = true;
                dist[nx][ny] = dist[curr.first][curr.second] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
}

pair<int, int> FindNearestPassenger(){
    // 1. 먼저 현재 자동차 위치로부터 이동할 수 있는 곳까지의 거리를 탐색
    Initialize();
    visited[carX][carY] = true;
    dist[carX][carY] = 0;
    q.push(make_pair(carX, carY));
    bfs();

    // 2. 가장 가까운 승객 찾기
    int targetX = n*n, targetY = n*n, targetD = n*n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(passenger[i][j] > 0 && targetD > dist[i][j]){
                // 승객이 있고, 현재 자동차에서 타겟까지의 거리보다 더 가까운 경우
                targetX = i, targetY = j, targetD = dist[i][j];
            }
        }
    }
    if(dist[targetX][targetY] == -1)
        return make_pair(-1, -1);
    return make_pair(targetX, targetY);
}

int bfs_dest(){
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();

        for(int d=0; d<4; d++){
            int nx = curr.first + dirs[d][0], ny = curr.second + dirs[d][1];
            if(CanGo(nx, ny)){
                visited[nx][ny] = true;
                dist[nx][ny] = dist[curr.first][curr.second] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    return dist[carX][carY];
}

int FindNearestDest(int person){
    // 1. 현재 목적지에서 자동차 위치까지 탐색하기
    Initialize();
    int tX = dest[person].first, tY = dest[person].second;
    visited[tX][tY] = true;
    dist[tX][tY] = 0;
    q.push(make_pair(tX,tY));
    int minD = bfs_dest();
    return minD;
}

bool MoveCar(pair<int, int> target){
    // 1. 현재 연료와 target까지의 최단거리 비교
    int targetDist = dist[target.first][target.second];

    if(c <= targetDist)
        return false;
    // 2. 현재 가지고 있는 연료로 이동할 수 있다면 target으로 이동하기
    carX = target.first, carY = target.second;
    c -= targetDist;

    // 3. target 위치에서 목적지까지 최단거리 찾기
    int person = passenger[target.first][target.second];
    int minDist = FindNearestDest(person);

    if(c < minDist || minDist == -1)    // 도착점까지 가는데 필요한 연료가 충분하지 않거나, 도달 자체가 불가능한 경우
        return false;
    int x = dest[person].first, y = dest[person].second;
    carX = x, carY = y;
    c += minDist;

    passenger[target.first][target.second] = 0;
   
    return true;
    
}

bool Simulate(){
    // Step 1. 현재 (carX, carY)에서 가장 가까운 승객 찾기
    pair<int, int> target = FindNearestPassenger();
    if(target.first == -1)      // 도달 가능한 승객이 없다면
        return false;
    // Step 2. 차량을 이동시키기
    bool IsMovable = MoveCar(target);
    if(!IsMovable)
        return false;
    return true;
}

int main() {
    // 입력 받기
    Input();

    // 시뮬레이션 진행
    bool Movable = true;
    int moveCnt = 0;
    while(moveCnt < m){
        Movable = Simulate();
        if(!Movable)
            break;
        moveCnt++;
    }

    // 출력하기
    if(!Movable) cout << -1;
    else cout << c;
    return 0;
}