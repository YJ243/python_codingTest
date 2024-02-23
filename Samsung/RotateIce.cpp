/*
 * 2024.02.23
 * 회전하는 빙하
 * 내 풀이
*/

#include <iostream>
#include <queue>
#include <cmath>
#include <tuple>
#include <algorithm>

#define MAX_N 64
using namespace std;

int n, q, N;       // n: 회전 가능 레벨, q: 회전 횟수, N: 격자의 총 크기:2^n
int grid[MAX_N][MAX_N];
int level;
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
queue<pair<int, int> > bfs_q;
bool visited[MAX_N][MAX_N];
int cur_adjacent;
void Input(){
    cin >> n >> q;
    N = pow(2,n);
    for(int i=0; i<N; i++){
        for(int j=0; j < N; j++){
            cin >> grid[i][j];
        }
    }
}

void Rotate(int x, int y, int l){
    // 일단 (x,y)에서 시작하는 정사각형을 tmp의 (0,0)에서 시작하도록 하기
    int temp[l][l];
    for(int i=x; i<x+l; i++){
        for(int j=y; j<y+l; j++){
            temp[i-x][j-y] = grid[i][j];
        }
    }
    // 4등분하여 시계방향으로 회전하기
    int subGrid[l][l];
    // 첫 번째 부분
    for(int i=0; i<l/2; i++){
        for(int j=0; j<l/2; j++){
            subGrid[i][j+l/2] = temp[i][j];
        }
    }
    // 두 번째 부분
    for(int i=0; i<l/2; i++){
        for(int j=l/2; j < l; j++){
            subGrid[i+l/2][j] = temp[i][j];
        }
    }
    // 세 번째 부분
    for(int i=l/2; i < l; i++){
        for(int j=l/2; j < l; j++){
            subGrid[i][j-l/2] = temp[i][j];
        }
    }
    // 네 번째 부분
    for(int i=l/2; i < l; i++){
        for(int j=0; j < l/2; j++){
            subGrid[i-l/2][j] = temp[i][j];
        }
    }

    // subGrid를 원래 grid에다가 집어넣기
    for(int i=x; i<x+l; i++){
        for(int j=y; j<y+l; j++){
            grid[i][j] = subGrid[i-x][j-y];
        }
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}


void MeltIce(){
    int tempGrid[N][N];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            tempGrid[i][j] = grid[i][j];    // 먼저 복사하기
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j] == 0) continue;
            int adjacent_ice = 0;
            for(int d=0; d<4; d++){
                int nx = i+dirs[d][0], ny = j+dirs[d][1];
                if(InRange(nx, ny) && grid[nx][ny] > 0){
                    // 범위 안에 있고, 맞닿은 곳에 빙하가 있다면
                    adjacent_ice++;
                }
            }
            if(adjacent_ice <= 2){
                // 2개 이하가 있다면 녹음
                tempGrid[i][j]--;
            }
        }
    }
    // tempGrid를 다시 grid에 넣기
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            grid[i][j] = tempGrid[i][j];
        }
    }
}

void Simulate(){
    // Step 1. 빙하 회전하기
    int m = pow(2,level);   // 2^level 만큼 잘라서 사각형 회전하기
    
    // 해당 정사각형 크기만큼 회전 진행
    for(int i=0; i<N; i += m){
        for(int j=0; j<N; j += m){
            Rotate(i, j, m);        // (i,j)에서 길이가 m인 정사각형을 회전하는 함수        
        }
    }

    // Step 2. 빙하에 속한 얼음이 녹는다.
    MeltIce();

}

bool CanGo(int x, int y){
    return InRange(x, y) && !visited[x][y] && grid[x][y] > 0;
}

void BFS(){
    while(!bfs_q.empty()){
        pair<int, int> curr = bfs_q.front();
        bfs_q.pop();

        for(int d=0; d<4; d++){
            int nx = curr.first + dirs[d][0], ny = curr.second + dirs[d][1];
            if(CanGo(nx, ny)){
                visited[nx][ny] = true;
                cur_adjacent++;
                bfs_q.push(make_pair(nx, ny));
            }
        }
    }
}

void Output(){
    int total = 0, maxGroup = 0;
    // 남아있는 빙하의 총 양
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j])
                total += grid[i][j];
        }
    }

    // bfs탐색을 통해 가장 큰 빙하의 총 군집을 찾기
    for(int i=0; i < N; i++){
        for(int j=0; j<N; j++){
            if(!visited[i][j] && grid[i][j] > 0){
                cur_adjacent = 1;
                visited[i][j] = true;
                bfs_q.push(make_pair(i,j));
                BFS();
                maxGroup = max(maxGroup, cur_adjacent);
            }
        }
    }
    cout << total << '\n';
    cout << maxGroup << '\n';
}

int main() {
    // 입력 받기:
    Input();
    // q번의 회전에 대해 시뮬레이션 수행
    while(q--){
        cin >> level;
        Simulate();
    }

    // 출력하기
    Output();
    return 0;
}