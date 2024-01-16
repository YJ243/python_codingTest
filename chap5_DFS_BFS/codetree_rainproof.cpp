/*
 * 2024.1.14
 * bfs에서 시작점이 여러개일 때 큐에 한꺼번에 넣고 돌리면 시간복잡도가 줄어든다는 것을 깜빡함
 * 처음에는 각각 시작점에 대해 bfs를 돌려서 케이스가 커지면 시간초과가 떴었음
 * 그래서 만약 shelter를 만나면 바로 return하도록 바꿨더니 시간초과가 사라짐
*/


#include <iostream>
#include <queue>
#include <climits>

#define MAX_N 100
using namespace std;

int n, h, m;    // n: 격자 크기, h: 사람 명수, m: 비를 피할 수 있는 공간 위치 개수
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int grid[MAX_N][MAX_N];     // 0: 이동 가능, 1: 벽으로 이동 불가, 2: 사람, 3: 비를 피할 수 있는 공간

// 탐색을 위한 자료구조
queue<pair<int, int> > q;
int step[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int curMin = INT_MAX;

int result[MAX_N][MAX_N];   // 0: 사람X, 양수: 비를 피할 수 있는 공간까지 최소 시간, -1: 비를 피할 수 없음 

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    return InRange(x,y) && !visited[x][y] && grid[x][y] != 1;
}

void Initialize(){      // 탐색 전 초기화하는 함수
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            visited[i][j] = false;  // 방문 배열 flase로 초기화
            step[i][j] = 0;         // 움직인 거리 초기화
        }

    curMin = INT_MAX;               // 가장 가까운 쉘터 공간까지의 거리 초기화
    q = queue<pair<int, int> >();
}
void Push(int x, int y, int d){
    q.push(make_pair(x,y));
    visited[x][y] = true;
    step[x][y] = d;
}

void bfs(){
    bool findShelter = false;
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
    
        for(int d=0; d<4; d++){
            int nx = curr.first + dirs[d][0], ny = curr.second + dirs[d][1];
            if(CanGo(nx,ny)){
                Push(nx,ny,step[curr.first][curr.second]+1);
                if(grid[nx][ny] == 3){
                    curMin = min(curMin, step[curr.first][curr.second]+1);
                    findShelter = true;
                    break;
                }
            }
        }
        if(findShelter) break;
    }
}

int main() {
    // 입력:
    cin >> n >> h >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    // 탐색 진행
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 2){    // 만약 사람이 서있다면
                // 탐색 전 초기화하기
                Initialize();
                Push(i,j,0);
                bfs();
                if(curMin!=INT_MAX)
                    result[i][j] = curMin;
                else
                    result[i][j] = -1;
            }
        }
    }

    // 출력
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}