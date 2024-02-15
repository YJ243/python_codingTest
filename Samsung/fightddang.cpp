/*
 * 2024.02.14
 * 해설 참고 안하고, 전체 코드 작성 1시간, 디버깅 1시간 반으로 해결함
 * 실수 1: 문제를 제대로 안 읽고, 격자 한 칸에 총이 하나만 존재하는 식으로 풀었음
 * 실수 2: 플레이어 수를 MAX_M+1이 아니라 MAX_N으로 두었음
 * 실수 3: 충돌하는지 확인하기 전에 플레이어 위치를 업데이트하고 했어야 하는데 안했음 
*/
#include <iostream>
#include <tuple>
#include <vector>

#define MAX_N 20
#define MAX_M 30

using namespace std;

int n, m, k;                                        // n: 격자 크기, m: 플레이어의 수, k: 라운드 수
vector<int> grid[MAX_N][MAX_N];                     // 각 칸은 총의 공격력들을 담음
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};       // 상,우,하,좌 방향
tuple<int, int, int, int, int> players[MAX_M+1];    // players[i]: i번 플레이어의 (x,y) 위치, d:방향, s: 초기능력, p: 가지고 있는 총의 공격력
int points[MAX_M+1];                                // 각 플레이어들이 획득한 포인트

void Input(){                   // 입력값을 받는 함수
    cin >> n >> m >> k;         // 격자 크기, 플레이어 수, 라운드 수 입력받음
    for(int i=0; i<n; i++){     // 전체 격자 크기에 대해서
        for(int j=0; j<n; j++){ // 총의 공격력 입력받기
            int x;
            cin >> x;
            grid[i][j].push_back(x);    // 0: 빈칸, 0보다 크면 총의 공격력

        }
    }
    for(int i=0; i<m; i++){     // 전체 플레이어에 대해서
        int x, y, d, s;         // (x,y) 플레이어 위치, d: 방향, s: 초기 능력
        cin >> x >> y >> d >> s;
        players[i] = make_tuple(x-1, y-1, d, s, 0);     // 가지고 있는 총 공격력 0을 추가해서 넣기
    }
}

bool InRange(int x, int y){     // (x,y)가 격자 내에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

pair<bool, int> IsCollide(int idx, int x, int y){  // (idx)번 플레이어가 (x,y)로 이동하려는데, 그 위치에서 충돌이 일어나는지 확인하는 함수
    for(int i=0; i<m; i++){     // 모든 플레이어들을 확인하면서
        if(i == idx) continue;  // idx번 플레이어가 아닌 다른 플레이어들 확인
        int cur_x, cur_y;
        tie(cur_x, cur_y, ignore, ignore, ignore) = players[i];
        if(cur_x == x && cur_y == y){    // 만약 움직이려는 곳에 다른 플레이어가 존재한다면
            return {true, i};            // 충돌하므로 {true, 충돌하는 플레이어 인덱스} 반환
        }
    }
    return {false, -1};   // 이동하려는 곳에 다른 플레이어가 없으므로 {false, -1} 반환
}

void Process_loser(int idx, int cx, int cy){        // idx번 루저를 (cx, cy)에서 다음 위치로 이동시키는 함수
    int d, s, p;        // 방향, 초기 능력치, 가지고 있는 총 공격력
    tie(ignore, ignore, d, s, p) = players[idx];
    
    // Step 1. 총 내려놓기
    if(p != 0){         // 만약 총을 가지고 있다면
        // 본인이 가지고 있는 총을 해당 격자에 놓기
        grid[cx][cy].push_back(p);
        p = 0;
    }
    // Step 2. 해당 플레이어가 원래 향하고 있던 방향대로 한 칸 이동
    int nx = cx+dirs[d][0], ny = cy+dirs[d][1];
    while(true){
        // 2-1. 다음 위치가 범위를 벗어나거나, 범위 안에 있어도 다른 플레이어가 있다면 회전
        if(!InRange(nx,ny) || (InRange(nx,ny) && IsCollide(idx, nx, ny).first)){    
            d = (d+1)%4;        // 오른쪽으로 90도 회전
            nx = cx+dirs[d][0], ny = cy+dirs[d][1];
        }
        // 2-2. 범위 안에 있고, 다른 플레이어가 없다면
        else{
            break;
        }
    }

    // Step 3. 이동할 칸에 있는 총 줍기
    // (nx, ny)는 idx번이 이동할 빈칸임
    // 해당 칸에 총이 있다면 
    if((grid[nx][ny].size() == 1 && grid[nx][ny][0] != 0) || grid[nx][ny].size() >= 2){
        int max_power = 0, max_idx = 0;
        for(int g=0; g<(int)grid[nx][ny].size(); g++){
            // 해당 총을 획득하기
            if(max_power < grid[nx][ny][g]){    // 공격력이 제일 센 총 찾기
                max_power = grid[nx][ny][g];
                max_idx = g;
            } 
        }
        if(max_power != 0){         // 총을 찾았다면 총 획득
            p = max_power;
            grid[nx][ny].erase(grid[nx][ny].begin() + max_idx);
        }
    }
            
    players[idx] = make_tuple(nx, ny, d, s, p);
}

void Process_winer(int idx, int cx, int cy){    // idx번 위너의 정보를 (cx, cy)에서 업데이트하는 함수 
    int d, s, p;            // 방향, 초기 능력치, 가지고 있는 총 공격력
    tie(ignore, ignore, d, s, p) = players[idx];
    
    // 승리한 칸에 떨어져 있는 총들과 원래 들고 있던 총 중 가장 공격력이 높은 총을 획득
    if((grid[cx][cy].size() == 1 && grid[cx][cy][0] != 0) || grid[cx][cy].size() >= 2){
        int max_power = 0, max_idx = 0;
        for(int g=0; g<(int)grid[cx][cy].size(); g++){
            if(p < grid[cx][cy][g]){   // 가지고 있는 총보다 공격력이 더 센 총을 만난 경우
                // 해당 총을 획득하기
                if(max_power < grid[cx][cy][g]){
                    max_power = grid[cx][cy][g];
                    max_idx = g;
                }
            }
        }
        if(max_power != 0){     // 총을 주울 수 있다면 총 교환
            int tmp = p;
            p = max_power;
            grid[cx][cy].erase(grid[cx][cy].begin() + max_idx);
            grid[cx][cy].push_back(tmp);
        }
    }
    players[idx] = make_tuple(cx, cy, d, s, p);
}

void do_fight(int a, int b, int x, int y){    // a플레이어가 (x,y)에 있는 b플레이어와 겨루는 함수
    int a_d, a_s, a_p; // a플레이어의 방향, 체력, 총의 공격력
    tie(ignore, ignore, a_d, a_s, a_p) = players[a];
    int b_d, b_s, b_p; // b플레이어의 방향, 체력, 총의 공격력
    tie(ignore, ignore, b_d, b_s, b_p) = players[b];

    int win_idx, lose_idx;
    if(a_s + a_p > b_s + b_p || ((a_s+a_p == b_s+b_p) && a_s > b_s)){
        // a플레이어의 초기 능력치와 가지고 있는 총의 공격력의 합이 더 크거나, 만약 같으면서 초기 능력치가 더 크다면
        win_idx = a;
        lose_idx = b;
    }
    else{
        // b플레이어 초기 능력치와 가지고 있는 총의 공격력의 합이 더 크다나, 만약 같으면서 초기 능력치가 더 크다면
        win_idx = b;
        lose_idx = a;
    }

    // 포인트 업데이트
    int winner_d, loser_d, winner_s, winner_p, loser_s, loser_p;
    tie(ignore, ignore, winner_d, winner_s, winner_p) = players[win_idx];
    tie(ignore, ignore, loser_d, loser_s, loser_p) = players[lose_idx];
    int plus_point = winner_s+winner_p - loser_s-loser_p;               // 승리자가 가져가는 포인트 
    points[win_idx] += plus_point;
    players[win_idx] = make_tuple(x, y, winner_d, winner_s, winner_p);  // 루저 처리 전 승리자의 정보 업데이트

    // 싸움에서 진 루저와 위너 처리하기 
    Process_loser(lose_idx, x, y);
    Process_winer(win_idx, x, y);
}

void Move(int idx){     // idx번 플레이어를 움직이기
    int x, y, d, s, p;
    tie(x, y, d, s, p) = players[idx];

    // (nx,ny)는 다음에 이동할 위치
    int nx = x+dirs[d][0], ny = y+dirs[d][1];   // 해당 플레이어가 움직일 다음 위치
    if(!InRange(nx,ny)){                        // 만약 다음 이동할 위치가 격자를 벗어난다면
        d = (d + 2) % 4;                        // 정반대 방향으로 방향을 바꾸어서 1만큼 이동하기
        nx = x+dirs[d][0], ny = y+dirs[d][1];
    }

    // 만약 이동한 방향에 플레이어가 있다면
    pair<bool, int> fight_info = IsCollide(idx, nx, ny); 
    if(fight_info.first){
        players[idx] = make_tuple(nx, ny, d, s, p);     // 방향과 좌표 업데이트 하고
        do_fight(idx, fight_info.second, nx, ny);       // 싸움 처리 
    }

    // 이동한 방향에 플레이어가 없다면
    else{
        // 해당 칸에 총이 있다면
        if((grid[nx][ny].size() == 1 && grid[nx][ny][0] != 0) || grid[nx][ny].size() >= 2){
            int max_power = 0, max_idx = 0;
            for(int g=0; g<(int)grid[nx][ny].size(); g++){
                if(p < grid[nx][ny][g]){   // 가지고 있는 총보다 공격력이 더 센 총을 만난 경우
                    // 해당 총을 획득하기
                    if(max_power < grid[nx][ny][g]){
                        max_power = grid[nx][ny][g];
                        max_idx = g;
                    } 
                }
            }
            if(max_power != 0){         // 총을 주었다면
                int tmp = p;
                p = max_power;
                grid[nx][ny].erase(grid[nx][ny].begin() + max_idx);
                grid[nx][ny].push_back(tmp);
            }
        }
        players[idx] = make_tuple(nx, ny, d, s, p);
    }
    
}

void Simulate(){
    // 각 플레이어를 차례로 보면서 움직이기
    for(int i=0; i<m; i++){
        Move(i);    // i번 플레이어 움직이기
    }
}


void Output(){      // 정답을 출력하는 함수
    for(int i=0; i<m; i++){
        cout << points[i] << ' ';
    }
    cout << '\n';
}

int main() {
    // 입력받기
    Input();

    // k라운드 동안 시뮬레이션 진행
    while(k--){
        Simulate();

    }

    // 출력하기
    Output();
    return 0;
}