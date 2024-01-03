/*
 * 2023.1.3
 * 도저히 풀이 방법이 생각나지 않아서 해설을 참고하고 처음부터 다시 풀었음
 * (0,0)에서 탐색 시작 -> 0을 만나면 visited 표시
 * 모든 격자를 돌면서 1이고 옆에 visited표시된 물이 있는지 확인
 * 있으면 0으로 바꾸기
 * 빙하가 다 녹는데 길어야 max(N,M)시간이 걸림, 해당 시간동안 빙하에 둘러싸여 있지 않은 물을 찾기 위해 BFS를 계속 수행해야함: O(N*M*max(N,M)) 시간복잡도
*/

#include <iostream>
#include <queue>

#define MAX_N 200
#define MAX_M 200
#define MAX_DIR 4
using namespace std;
int n, m;
int grid[MAX_N][MAX_M];
queue<pair<int, int> > q;       
bool visited[MAX_N][MAX_M];
int curr_melted;
int dirs[MAX_DIR][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int time_sec;
bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanGo(int x, int y){
    return InRange(x,y) && !visited[x][y] && !grid[x][y]; 
}

void bfs(){
    while(!q.empty()){
        // q가 빌 때까지
        pair<int, int> curr = q.front();
        q.pop();
        for(int i=0; i<MAX_DIR; i++){
            int nx = curr.first + dirs[i][0];
            int ny = curr.second + dirs[i][1];
            if(CanGo(nx,ny)){
                visited[nx][ny] = true;
                q.push(make_pair(nx,ny));
            }
        }

    }
}

bool IsFinish(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]) return false;
        }
    }
    return true;
}

void Initialize(){
    // 1. 방문 배열 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            visited[i][j] = false;
    
    // 2. 현재 녹은 빙하 개수 초기화
    curr_melted = 0;
}

void Melt(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]){
                // 만약 빙하라면
                for(int d=0; d<MAX_DIR; d++){
                    int nx = i+dirs[d][0], ny = j+dirs[d][1];
                    if(InRange(nx,ny) && grid[nx][ny] == 0 && visited[nx][ny]){
                        grid[i][j] = 0;
                        curr_melted++;
                        break;
                    }
                }
            }
        }
    }
}

void Simulate(){
    time_sec++;
    // Step 0. 시뮬레이션을 돌리기 전에 먼저 초기화하기
    Initialize();
    // Step 1. 먼저 bfs 탐색을 돌면서 빙하로 둘러싸이지 않은 물을 파악하기
    visited[0][0] = true;
    q.push(make_pair(0,0));
    bfs();

    // Step 2. 모든 격자를 돌면서 녹일 수 있는 빙하는 녹이기
    Melt();

}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> grid[i][j];
    
    while(true){
        // 모든 격자가 0이 된다면 break;
        if(IsFinish()) break;
        Simulate();
    }
    
    cout << time_sec << ' ' << curr_melted << '\n';
    return 0;
}

/*
 * 해설 풀이 1
*/
#include <iostream>
#include <queue>
#include <algorithm>

enum ELEMENT {
    WATER,
    GLACIER
};

#define DIR_NUM 4
#define MAX_N 200
#define MAX_M 200

using namespace std;

// 전역 변수 선언:
int n, m;

int a[MAX_N][MAX_M];

// bfs에 필요한 변수들
queue<pair<int, int> > q;
bool visited[MAX_N][MAX_M];
int cnt;

int dx[DIR_NUM] = {1,-1,0,0};
int dy[DIR_NUM] = {0,0,1,-1};

// 소요 시간과 가장 마지막으로 녹은 빙하의 수를 저장
int elapsed_time, last_melt_cnt;

// visited 배열을 초기화함
void Initialize(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            visited[i][j] = 0;
        }
    }
}

// 범위가 격자 안에 들어가는지 확인
bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 범위를 벗어나지 않으면서 물이여야 하고 방문한 적이 없어야 갈 수 있음
bool CanGo(int x, int y){
    return InRange(x,y) && a[x][y] == WATER && !visited[x][y]; 
}

// 빙하에 둘러쌓여 있지 않은 물들을 전부 구해주는 BFS
// 문제에서 가장자리는 전부 물로 주어지기 때문에 항상 (0,0)에서 시작해서 탐색 진행
// 그러면 빙하에 둘러쌓여 있지 않은 물들은 전부 visited 처리가 됨
void BFS(){
    // BFS 함수가 여러번 호출되므로
    // 사용하기 전에 visited 배열을 초기화해줌
    Initialize();

    // 항상 (0,0)에서 시작함
    q.push(make_pair(0,0));
    visited[0][0] = true;

    while(!q.empyt()){
        // queue에서 가장 먼저 들어온 원소를 빼기
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        q.pop();

        // queue에서 뺀 원소의 위치를 기준으로 4방향 확인
        for(int dir= 0; dir<DIR_NUM; dir++){
            int nx = x + dx[dir], ny + y + dy[dir];
            

            // 더 갈 수 있는 곳이라면 queue에 추가
            if(CanGo(nx,ny)){
                q.push(make_pair(nx,ny));
                visited[nx][ny] = true;
            }
        }
    }
}

// 현재 위치를 기준으로 인접한 영역에 빙하에 둘러쌓여 있지 않은 물이 있는지 판단하기
bool OutsideWaterExistInNeighbor(int x, int y){
    for(int dir=0; dir<DIR_NUM; dir++){
        int nx = x+dx[dir], ny = y+dy[dir];
        if(InRange(nx,ny) && visited[nx][ny])
            return true;
    }
    return false;
}

// 인접한 영역에 빙하에 둘러쌓여 있지 않은 물이 있는 빙하를 찾아 녹여주기
void Melt(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == GLACIER &&
                OutsideWaterExistInNeighbor(i,j)){
                    a[i][j] = WATER;
                    last_melt_cnt++;
                }
        }
    }

}

// 빙하를 한 번 녹임
void Simulate(){
    elapsed_time++;
    last_melt_cnt = 0;

    // 빙하에 둘러쌓여 있지 않은 물의 위치를 전부 visited로 체크
    BFS();

    // 인접한 영역에 빙하에 둘러쌓여 있지 않은 ㅁ루이 있는 빙하를 찾아 녹여주기
    Melt();
}

// 빙하가 아직 남아있는지 확인
bool GlacierExist(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == GLACIER)
                return true;
        }
    }
    return false;
}

int main(){
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    do{
        // 빙하를 한 번 녹입니다.
        Simulate();
    } while(GlacierExist()); // 빙하가 존재하는 한 계속 반복하기

    // 출력:
    cout << elapsed_time << " "  << last_melt_cnt;

    return 0;
}