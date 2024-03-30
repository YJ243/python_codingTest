#include <iostream>
#include <climits>
#include <tuple>

#define MAX_N 50
#define MAX_P 30
#define ELIMINATED make_pair(-1, -1)

using namespace std;

int n, m, p, C, D;      // n: 격자판 크기, m: 턴 수, p: 산타 수, C: 루돌프 힘, D: 산타 힘
pair<int, int> santa_loc[MAX_P+1]; // santa_loc[i]: i번째 산타의 위치
int score[MAX_P+1];     // score[i]: i번째 산타의 점수
int faint[MAX_P+1];     // faint[i]: i번째 산타가 기절해있는 시간
pair<int, int> rudolf;  // 루돌프 위치

int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,1},{1,1},{1,-1},{-1,-1}};   // 8방향, 0~3까지는 상우하좌 우선순위

void Input(){           // 입력을 받는 함수
    cin >> n >> m >> p >> C >> D;   // n: 격자판 크기, m: 턴 수, p: 산타 수, C: 루돌프 힘, D: 산타 힘

    int r, c;
    cin >> r >> c;
    rudolf = make_pair(r-1, c-1);   // 루돌프 위치

    for(int i=0; i<p; i++){
        int num, r, c;
        cin >> num >> r >> c;   r--; c--;
        santa_loc[num] = make_pair(r,c);
    }
}

int GetDist(int x1, int y1, int x2, int y2){
    return (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int MoveRudolf(){
    // 1. 가장 가까운 산타를 찾기
    int rx = rudolf.first, ry = rudolf.second;
    int minDist = INT_MAX, targetX= -1, targetY= -1;

    for(int i=1; i<=p; i++){
        if(santa_loc[i] == ELIMINATED) continue;                // 게임에서 탈락하지 않은 산타들만 고려
        int sx = santa_loc[i].first, sy = santa_loc[i].second;  // 현재 고려하는 산타 좌표
        int curDist = GetDist(sx, sy, rx, ry);                  // 루돌프에서 현재 산타까지 거리
        if(make_tuple(minDist, -targetX, -targetY) > make_tuple(curDist, -sx, -sy)){
            minDist = curDist, targetX = sx, targetY = sy;
        }
    }
    // 2. 그 산타와 가장 가까워지는 방향으로 1칸 돌진
    int direction = 0; minDist = INT_MAX;
    for(int d=0; d<8; d++){     // 인접한 8방향 중 하나로 돌진 가능
        int nx = rx + dirs[d][0], ny = ry + dirs[d][1];
        if(!InRange(nx, ny)) continue;
        int curDist = GetDist(nx, ny, targetX, targetY);
        if(minDist == INT_MAX || minDist > curDist){
            minDist = curDist, direction = d;
        }
    }

    // 3. 루돌프 direction 방향으로 이동시키기
    rudolf = make_pair(rx + dirs[direction][0], ry + dirs[direction][1]);

    // 해당 방향 리턴
    return direction;
}


void Bump(int arrive_x, int arrive_y, int direction, int diff, int turn){   // turn에 (arrive_x, arrive_y)로 direction방향으로 왔을 때 충돌 처리, diff만큼 움직이기
    for(int i=1; i<=p; i++){
        if(santa_loc[i] == ELIMINATED) continue;    // 게임에서 탈락한 산타는 제외시키기
        
        int sx = santa_loc[i].first, sy = santa_loc[i].second;
        if(arrive_x == sx && arrive_y == sy){
            //cout << i << "번 산타 이동해야 함 " << arrive_x << ' ' << arrive_y << '\n';
            // 그럼 (sx, sy) 산타는 (nx, ny)로 이동해야 함        
            int nx = arrive_x + dirs[direction][0]*diff, ny = arrive_y + dirs[direction][1]*diff;
            Bump(nx, ny, direction, 1, turn);        // (nx, ny) 자리 비워주기

            // 이제 비워졌으니 (nx, ny) 위치로 i번 산타 옮기기
            santa_loc[i] = make_pair(nx, ny);

            if(rudolf.first == arrive_x && rudolf.second == arrive_y){
                //cout << "점수 plus 되는 인덱스: " << i << '\n';
                //cout << rudolf.first << ' ' << rudolf.second << ' ' << arrive_x << ' ' <<arrive_y << '\n';
                faint[i] = turn+1;
                score[i] += diff;
            }
            if(!InRange(nx, ny)){           // 그런데 그 위치가 만약 범위를 벗어난다면
                santa_loc[i] = ELIMINATED;  // 탈락되었다고 표시하기
            }
        }
    }
}

bool ExsitSanta(int x, int y){
    for(int i=1; i<=p; i++){
        if(santa_loc[i] == ELIMINATED) continue;
        if(santa_loc[i].first == x && santa_loc[i].second == y){
            return true;
        }
    }
    return false;
}

int MoveSanta(int idx){
    // Step 1. 루돌프와 거리가 가장 가까워 지는 방향으로 1칸 이동하기
    int sx = santa_loc[idx].first, sy = santa_loc[idx].second;
    int minDist = GetDist(sx, sy, rudolf.first, rudolf.second), direction = -1;
    for(int d=0; d<4; d++){
        int nx = sx + dirs[d][0], ny = sy + dirs[d][1];
        if(InRange(nx, ny) && !ExsitSanta(nx, ny)){
            int curDist = GetDist(nx, ny, rudolf.first, rudolf.second);
            if(minDist > curDist){
                minDist = curDist, direction = d;
            }
        }
    }

    // Step 2. 산타 이동시키기
    if(direction != -1){
        santa_loc[idx] = make_pair(sx + dirs[direction][0], sy + dirs[direction][1]);
    }
        
    return direction;
}

bool Simulate(int turn){    // 시뮬레이션을 진행하고 게임이 끝났는지 여부를 리턴하는 함수
    // Step 1. 먼저 루돌프를 이동한다
    int rudolf_direction = MoveRudolf();
    //cout << "rudolf: " << rudolf.first << ' ' << rudolf.second << '\n';
    // Step 1-1. 충돌처리하기
    Bump(rudolf.first, rudolf.second, rudolf_direction, C,  turn);

    // Step 2. 1부터 p까지 번호를 가진 산타를 보면서 하나씩 이동한다.
    for(int i=1; i<=p; i++){
        if(santa_loc[i] == ELIMINATED) continue;    // 탈락한 산타는 넘어가기
        if(faint[i] >= turn) continue;              // 현재 turn <= 기절하는 시간
        
        int santa_direction = MoveSanta(i);                         // i번 산타 이동시키기
        if(santa_direction == -1) continue;
        // Step 2-1. 충돌 처리하기
        Bump(rudolf.first, rudolf.second, santa_direction ^ 2, D, turn);

    }

    // Step 3. 아직 탈락하지 않은 산타들에게 1점씩 부과한다.
    int remain_santa = 0;       // 남은 산타 수 
    for(int i=1; i<=p; i++){
        //cout << "AA" << '\n';
        if(santa_loc[i] != ELIMINATED){     // 만약 아직 탈락하지 않은 산타라면
            remain_santa++;                 // 산타 수 증가
            score[i]++;                     // 점수 1 증가
        }
    }
    if(remain_santa > 0)        // 만약 1명이라도 남아있다면
        return false;           // 아직 끝나지 않음
    return true;                // 끝났다는 의미로 true 반환

}

void Output(){      // 최종 점수를 출력하는 함수
    for(int i=1; i<=p; i++){    // 각 산타가 얻은 최종 점수 출력
        cout << score[i] << ' ';
    }
    cout << '\n';
}

int main() {
    // 입력 받기:
    Input();

    // m번의 턴에 걸쳐서 시뮬레이션 진행
    for(int i=1; i<=m; i++){
        //cout << i << ' ';
        bool IsFinish = Simulate(i);
        //cout << "Rudolf: " << rudolf.first << ' ' << rudolf.second << '\n';
        //cout << i << "번 시뮬레이션 진행 후 산타 위치" << '\n';
        //for(int i=1; i<=p; i++){
            //cout << i<<"번: ";
            //cout << santa_loc[i].first << ' ' <<santa_loc[i].second << '\n';
        //}
        if(IsFinish)
            break;
    }

    // 출력하기:
    Output();
    return 0;
}
