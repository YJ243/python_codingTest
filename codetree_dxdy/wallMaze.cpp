/*
 * 2024.1.22
 * 내 풀이
 * 시간복잡도는 한 격자당 많아야 4번씩 올 수 있으므로
 * 격자의 크기에 해당하는 O(N^2)
*/


#include <iostream>
#include <string>
#define MAX_N 100
#define DIR_NUM 4
using namespace std;
int n;
char grid[MAX_N][MAX_N];
int r, c, curD;
int ans;
int dirs[DIR_NUM][2] = {{0,1},{-1,0},{0,-1},{1,0}};

bool InRange(int x, int y){                     // (x,y)가 범위 안에 있는지 확인
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){                       // (x,y)가 벽이 아닐 때 갈 수 있음
    return grid[x][y] != '#';
}

void Simulation(){                              // 조건에 맞춰 움직이는 함수
    int turn_cnt = 0;                           // 움직인 턴수 (처음에 자기 자리에서 네 번 돌기만 하는 경우 생각)
    int firstX = r, firstY = c, firstD = curD;  // 초기 위치와 방향 저장
    while(true){
        if(turn_cnt >= DIR_NUM){                // 만약 돌기만 했다면 빠져나갈 수 없으니 정답에 -1 저장
            ans = -1;
            break;
        }
        // 여러 칸을 돌아서 처음으로 온 경우 격자를 빠져나갈 수 없는 경우
        if(ans != 0 && firstD == curD && r == firstX && c == firstY){
            ans = -1;
            break;
        }

        // 현재 방향으로 이동했을 때 다음 좌표
        int nx = r + dirs[curD][0], ny = c + dirs[curD][1];
        if(!InRange(nx,ny)){    // 이동할 곳이 격자 밖인 경우 탈출 가능
            ans++;
            break;              // 반복문 빠져나오고 미로 탈출
        }
        else{                   // 이동할 곳이 격자 안인 경우
            if(!CanGo(nx,ny)){   // 만약 이동할 곳에 벽이 있는 경우 (갈 수 없는 경우)
                curD = (curD+1) % DIR_NUM;  // 반 시계 방향으로 90'만큼 방향 바꾸기
                turn_cnt++;
            }
            else{               // 만약 이동할 곳에 벽이 없어서 비어있다면
                ans++;          // 시간 증가
                turn_cnt = 0;   // 움직였으니 turn count 0으로 만들기
                int wall_dir = (curD+DIR_NUM - 1) % DIR_NUM;    // 벽이 있는지 확인하기 위해 시계방향으로 90도 회전
                int wallX = nx+dirs[wall_dir][0], wallY = ny+dirs[wall_dir][1];     // 벽이 있는 격자
                // 만약 해당 방향 기준으로 오른쪽에 짚을 벽이 있다면
                if(grid[wallX][wallY] == '#'){
                    r = nx, c = ny;             // 현재 위치 업데이트
                }
                else{
                    // 만약 오른쪽에 짚을 벽이 없다면
                    curD = wall_dir;
                    ans++;
                    r = wallX, c = wallY;       // 시계방향으로 90도 회전한 이후 이동
                }
            }
        }
    }
}

int main() {
    // 입력:
    cin >> n;
    cin >> r >> c;
    r--; c--;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        for(int j=0; j<n; j++){
            grid[i][j] = s[j]; 
        }
    }
    // 조건에 맞춰 움직여보기
    Simulation();

    // 출력:
    cout << ans;
    return 0;
}