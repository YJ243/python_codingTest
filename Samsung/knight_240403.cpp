/*
 * 2024.04.03
 * 내 풀이
 * 자잘한 실수 줄이자.
 * (1,1)에서 시작하는 격자를 (0,0)에서 시작하도록 -1하는 것.
 * 문제 제대로 보고 모든 조건 빠지지 않게!!! 명령을 받은 기사는 움직이지 않도록!!
*/

#include <iostream>
#include <tuple>
#include <queue>

#define MAX_L 40
#define MAX_N 30
using namespace std;

int L, N, Q;            // L: 체스판 크기, N: 기사들 수, Q: 명령 수
int grid[MAX_L][MAX_L];
tuple<int, int, int, int, int, int> knights[MAX_N+1];        // 기사들 정보: (r,c,h,w,k,damage)
int temp_grid[MAX_L][MAX_L];
bool IsMoving[MAX_N+1];     // 이번 턴에 움직이는 기사인지 확인하는 변수
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

queue<int> q;       // 탐색을 위한 큐

void Input(){       // 입력을 받는 함수
    cin >> L >> N >> Q;     // L: 체스판 크기, N: 기사들 수, Q: 명령 수
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            cin >> grid[i][j];      // 체스판 입력 받기, 0: 빈칸/ 1: 함정/ 2: 벽
        }
    }
    for(int i=1; i<=N; i++){
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        r--; c--;
        knights[i] = make_tuple(r, c, h, w, k, 0);
    }
}

void Initialize_before_search(){
    for(int i=0; i<L; i++){         // 기사들 격자 0으로 초기화
        for(int j=0; j<L; j++){
            temp_grid[i][j] = 0;
        }
    }
    for(int i=1; i<=N; i++){        
        IsMoving[i] = false;        // 현재 턴에 움직이는 기사 초기화하기
        int r, c, h, w, k, damage;
        tie(r, c, h, w, k, damage) = knights[i];
        if(k > 0){          // 만약 현재 격자에 남아있는 기사라면
            for(int x=r; x<r+h; x++){
                for(int y=c; y<c+w; y++){
                    temp_grid[x][y] = i;        // 격자에 기사 표시하기
                }
            }
        }
    }

    while(!q.empty()){          // 큐 비워주기 
        q.pop();
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < L && 0 <= y && y < L;
}

void Move(int id, int d){
    // 1. 먼저 탐색 전에 초기화하기
    Initialize_before_search();
    IsMoving[id] = true;
    q.push(id);

    while(!q.empty()){
        int cur = q.front(); q.pop();
        int r, c, h, w, k, damage;
        tie(r, c, h, w, k, damage) = knights[cur];

        for(int x = r; x < r+h; x++){
            for(int y=c; y < c+w; y++){
                int a = x, b = y;
                while(true){
                    a += dirs[d][0]; b += dirs[d][1];
                    if(!InRange(a, b))                  // 범위를 벗어나면 벽을 만난 것이니 움직일 수 없음 -> 리턴
                        return;
                    if(temp_grid[a][b] == 0){           // 만약 빈칸을 만났음
                        if(grid[a][b] == 2){            // 그런데 벽을 만났으면
                            return;                     // 움직일 수 없으니 리턴
                        }
                        break;                          // 그게 아니면 빈칸에 도달했으니 반복문 나가기
                    }
                    if(!IsMoving[temp_grid[a][b]]){
                        // 만약 새로운 기사를 만났다면
                        IsMoving[temp_grid[a][b]] = true;        // 움직이는 기사에 표시하기
                        q.push(temp_grid[a][b]);
                    }
                }
            }
        }
    }
    // 탐색을 끝냈으면 기사들 움직이기
    for(int i=1; i<=N; i++){
        if(!IsMoving[i]) continue;                  // 이번 턴에 움직여야 하는 기사들만 보기
        int r, c, h, w, k, damage;
        tie(r, c, h, w, k, damage) = knights[i];
        r += dirs[d][0]; c += dirs[d][1];           // d방향으로 한 칸 움직이기
        if(i != id){
            for(int x=r; x < r+h; x++){
                for(int y=c; y<c+w; y++){
                    if(grid[x][y] == 1){                // 만약 함정을 만났다면
                        damage++;           // 데미지 증가
                        k--;                // 체력 감소
                    }
                }
            }
        }
        
        knights[i] = make_tuple(r, c, h, w, k, damage);     // 기사들 정보 저장하기
    }
}

void Pro(){     // 왕의 명령 진행하는 함수
    while(Q--){
        int id, d, k;
        cin >> id >> d;         // id번 기사에게 d 방향으로 한 칸 이동하라는 명령
        tie(ignore,ignore,ignore,ignore,k,ignore) = knights[id];
        if(k <= 0)  continue;       // 만약 사라진 기사 번호라면 넘어가기
        Move(id, d);            // id번 움직이기
    }

}

void Output(){
    int ans = 0;
    for(int i=1; i<=N; i++){
        int r, c, h, w, k, damage;
        tie(r, c, h, w, k, damage) = knights[i];
        if(k <= 0) continue;
        ans += damage;
    }
    cout << ans;
}

int main() {
    // 입력 받기:
    Input();
    
    // 명령 진행하기
    Pro();

    // 출력하기
    Output();
    return 0;
}