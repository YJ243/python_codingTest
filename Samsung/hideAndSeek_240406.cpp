/*
 * 2024.04.06
 * 내 풀이
 * 달팽이 처리때문에...........시간이 너무 오래 걸림
 * 달팽이 어떻게 풀어냈는지 까먹었음
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>

#define MAX_N 99
#define CAUGHT make_tuple(-1, -1, -1)

using namespace std;

int n, m, h, k;                         // n: 격자 칸 수, m: 도망자 수, h: 나무 수, k: 턴수
bool tree[MAX_N][MAX_N];                // tree[i][j]: (i,j)에 나무가 있는지 여부
vector<tuple<int, int, int> > runner;   // 도망자 정보: 위치, 방향
vector<tuple<int, int, int> > next_runner;
int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};    // 0<->1, 2<->3 (하상, 우좌)
int seeker_dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}; // 상우하좌
int progress = 1;
pair<int, int> seeker;                           // 술래의 위치
int have_to_be_moved = 1;
int MovingCur;
int sd;
int score;  // 술래가 얻게되는 총 점수

void Init(){
    cin >> n >> m >> h >> k; // n: 격자 칸 수, m: 도망자 수, h: 나무 수, k: 턴수
    for(int i=0; i<m; i++){
        int x, y, d;
        cin >> x >> y >> d;
        if(d == 1) d=2;     // d가 1: 좌우이고, 오른쪽으로 시작하도록 하기
        else d = 0;         // d가 2: 상하이고, 아래부터 시작하도록 하기
        runner.push_back(make_tuple(x-1, y-1, d));
    }
    for(int i=0; i<h; i++){ // 나무 위치 표시하기
        int x, y;
        cin >> x >> y;
        tree[x-1][y-1] = true;
    }
    seeker = make_pair(n/2, n/2);   // 술래 위치 가운데로
    sd = 0;
}

bool InRange(int x, int y){     // (x, y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

void MoveAll(){     // 도망자를 동시에 움직이는 함수
    for(int i=0; i<(int)runner.size(); i++){
        int x, y, d;
        tie(x, y, d) = runner[i];   // i번 도망자의 위치와 방향
        if((abs(x - seeker.first) + abs(y-seeker.second)) > 3 ) continue;
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(!InRange(nx, ny)){   // 만약 격자를 벗어난다면
            d = (d % 2 == 0) ? d+1: d-1;    // 방향 반대로 틀어주기
            nx = x + dirs[d][0], ny = y + dirs[d][1];
        }
        if(nx == seeker.first && ny == seeker.second){   // 움직이려는 칸에 술래가 있다면 움직이지 않음
            runner[i] = make_tuple(x, y, d);    // 방향만 바뀐채 업데이트해주기
        }
        else{   // 술래가 있지 않다면 이동하기
            runner[i] = make_tuple(nx, ny, d);
        }
    }
}

void MoveSeeker(){
    int nx = seeker.first + seeker_dirs[sd][0], ny = seeker.second + seeker_dirs[sd][1];
    // step 1. 1칸 이동
    MovingCur++;
    
    if((nx == 0 && ny == 0) || (nx == n/2 && ny == n/2)){
        sd = (sd+2)%4;
        MovingCur = 0;
        if(progress == 1){
            have_to_be_moved = n-1;
        }
        else
            have_to_be_moved = 1;
        progress = -progress;
    }
    seeker = make_pair(nx, ny);
    if(MovingCur == have_to_be_moved){
        MovingCur = 0;
        if(progress == 1){
            sd = (sd+1)%4;
            if(sd % 2 == 0)
                have_to_be_moved++;
        }
        else{
            sd = (sd-1+4) % 4;
            if(sd % 2 == 1)
                have_to_be_moved--;
            if(seeker == make_pair(n-1, 0))
                have_to_be_moved++;
        }
    }
    
}

void CatchRunner(int turn){
    int cnt = 0;
    int x = seeker.first , y = seeker.second;

    for(int i=0; i<3; i++){
        int nx = x + seeker_dirs[sd][0]*i, ny = y + seeker_dirs[sd][1]*i;
        if(tree[nx][ny]) continue;
        for(int j=0; j<(int)runner.size(); j++){
            int rx, ry;
            tie(rx, ry, ignore) = runner[j];
            if(rx == nx && ry == ny){
                cnt++;
                runner[j] = CAUGHT;
            }
        }
    }

    score += (turn*cnt);
    vector<tuple<int, int, int> > tmp;   // 도망자 정보: 위치, 방향
    for(int i=0; i<(int)runner.size(); i++){
        if(runner[i] != CAUGHT)
            tmp.push_back(runner[i]);
    }
    runner = tmp;
}

void Simulate(int turn){
    // Step 1. m명 동시에 움직이기
    MoveAll();

    // Step 2. 술래 이동하기
    MoveSeeker();

    // Step 3. 도망자 잡기
    CatchRunner(turn);
}

int main() {
    // 입력받기:
    Init();    

    // k번의 턴 동안 시뮬레이션 진행하기
    for(int i=1; i <= k; i++){
        Simulate(i);    
    }
    cout << score;
    return 0;
}