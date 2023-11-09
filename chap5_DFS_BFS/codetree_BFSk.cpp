/*
 * 2023.11.04
 * 내 풀이
*/

#include <iostream>
#include <queue>
#define INT_MAX 100     
using namespace std;

int n, k;                       // n: 격자 크기, k: 반복할 횟수
int maze[INT_MAX][INT_MAX];     // 격자, 1이상 INT_MAX 이하의 숫자로 이루어짐
bool visited[INT_MAX][INT_MAX]; // 방문 확인 배열
int r, c;                       // 초기 위치
queue<pair<int, int> > q;       // bfs를 위한 큐
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};   // 방향 배열

bool InRange(int x, int y){         // 범위 안에 있는지 확인
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int val){  // 범위 안에 있고, 방문하지 않았고, 시작 위치보다 작은 값으로 이동 가능
    return InRange(x,y) && !visited[x][y] && maze[x][y] < val;
}

void initialize(){                  // 방문 배열 초기화
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }
}

pair<int, int> bfs(){               // 조건을 만족하는 곳으로 탐색 진행, 최종 위치 리턴
    int min_x=INT_MAX+1, min_y=INT_MAX+1, max_val=0;
    while(!q.empty()){
        pair<int, int> cur_pos= q.front();
        q.pop();
        for(int dir = 0; dir<4; dir++){
            int nx = cur_pos.first+dirs[dir][0];
            int ny = cur_pos.second+dirs[dir][1];
            if(CanGo(nx,ny, maze[r][c])){
                visited[nx][ny] = true;
                q.push(make_pair(nx,ny));
                if((max_val < maze[nx][ny])){   // 도달할 수 있는 칸들에 적혀있는 숫자 중 최댓값
                    min_x = nx; min_y = ny; max_val = maze[nx][ny];
                }
                else if((max_val==maze[nx][ny]) && (nx < min_x or (nx == min_x && ny < min_y))){
                    // 최댓값이 같은 것이 여러 개일 경우, 행번호가 가장 작은 곳->행이 같으면 열번호가 가장 작은 곳 담기
                    min_x = nx; min_y = ny; max_val = maze[nx][ny];
                }
            }
        }
    }
    return make_pair(min_x, min_y);     // 가장 우선순위가 높은 곳의 좌표 반환
}

int main() {
    cin >> n >> k;              // n: 격자 크기, k: 반복할 횟수
    for(int i=0; i<n; i++){     // 격자에다가 숫자 채우기
        for(int j=0; j<n; j++){
            cin >> maze[i][j];
        }
    }
    cin >> r >> c;      // 시작 위치 담기
    r--; c--;

    while(k--){         // k번 반복
        initialize();           // 방문 배열 초기화
        visited[r][c] = true;   // 시작점 방문표시
        q.push(make_pair(r,c)); // 시작점 큐에 넣기
        pair<int, int> new_pos; // 탐색 이후 가장 우선순위가 높은 좌표, 옮겨갈 좌표
        new_pos = bfs();
        if(new_pos.first == INT_MAX+1)  // 더 이상 새로 이동할 위치가 없다면 움직이는 것 종료
            break;
        r = new_pos.first; c = new_pos.second;  // 시작점 이동해주기
    }
    cout << r+1 << ' ' << c+1 << '\n';  // 최종 위치 출력
    return 0;
}