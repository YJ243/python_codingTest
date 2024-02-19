/*
 * 2024.02.16
 * 내 풀이
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <tuple>

#define MAX_N 99
using namespace std;
int n, m, h, k;                                 
int grid[MAX_N][MAX_N];
vector<tuple<int, int, int> > runaway;          // 도망자, [(x,y), 방향] 저장
vector<tuple<int, int, int> > next_runaway;     // 다음턴에 격자에 남아있는 도망자
pair<int, int> seeker;      // 술래 위치
int seeker_dir;             // 술래가 바라보는 방향
int moving_dist=1;            // 술래가 현재 가야할 칸 수
int cur_dist;               // 술래가 moving_dist 안에서 움직인 횟수
bool IsDecreasing;          // 술래 방향이 -1씩 감소하는지 그리고 개수도 감소하는지 
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};   // 상,우,하,좌 순으로


int total_score;    // 술래가 얻게 되는 총 점수

void Input(){       // 입력을 받는 함수
    cin >> n >> m >> h >> k; // n: 격자 크기, m: 도망자 수, h: 나무 개수, k: 반복 턴수
    for(int i=0; i<m; i++){
        int x, y, d;        
        cin >> x >> y >> d; // (x,y)에서 d방향으로 서있음(d가 1이면 좌우로, 2면 상하로 움직임)
        int d_idx;          // 1이면 오른쪽, 2면 아래쪽으로 집어넣기
        if(d == 1) d_idx = 1;
        else       d_idx = 2;
        runaway.push_back(make_tuple(x-1, y-1, d_idx));     // 도망자 수 입력받기
    }
    while(h--){                 // 나무 위치 입력받기
        int x, y;
        cin >> x >> y;
        grid[x-1][y-1] = 1;     // 나무 위치에 1 넣기

    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int idx){     // idx번째 도망자 이동시키기
    int x, y, d;
    tie(x, y, d) = runaway[idx];
    int nx = x + dirs[d][0], ny = y + dirs[d][1];
    if(!InRange(nx, ny)){
        // 만약 범위 안에 있지 않으면 반대 방향 확인
        d = (d+2) % 4;
        nx = x + dirs[d][0], ny = y + dirs[d][1];
    }
    if(make_pair(nx, ny) != seeker){
        // 만약 이동하려는 칸에 술래가 없다면 이동시키기
        next_runaway.push_back(make_tuple(nx, ny, d));
    }
    else{
        // 만약 이동하려는 칸에 술래가 있다면 이동하지 않기
        next_runaway.push_back(make_tuple(x, y, d));
    }

}

void MoveSeeker(){      // 술래를 바라보고 있는 방향으로 한 칸 이동시키는 함수
    int nx = seeker.first + dirs[seeker_dir][0], ny = seeker.second + dirs[seeker_dir][1];
    cur_dist++;     // 한 칸 움직임
    if((nx == 0 && ny == 0) || (nx == n/2 && ny == n/2)){
        // 만약 양 끝에 해당하는 위치에 도달하게 된다면 방향 틀어줘야함
        seeker_dir = (seeker_dir + 2)%4;    // 방향 반대로 틀어주기
        cur_dist = 0;
        if(!IsDecreasing) {
            moving_dist = n-1;
            IsDecreasing = true;
        }
        else {
            moving_dist = 1;
            IsDecreasing = false;
        }
    }
    seeker = make_pair(nx, ny);
    if(cur_dist == moving_dist){
        // 현재 해당 방향대로 움직여야 되는 횟수만큼 움직였다면
        if(!IsDecreasing){
            seeker_dir = (seeker_dir + 1)%4;        // 방향 바꿔주기
            cur_dist = 0;
            if(seeker_dir % 2 == 0){
                // 그런데 다음 방향이 위아래 중 하나라면
                moving_dist++;
            }
        }
        else{
            //cout << "감소하는데, 첫번째로 방향을 바꿔야 함" << nx << ' ' << ny << ' ' << cur_dist << ' ' << moving_dist << '\n';
            seeker_dir = (seeker_dir-1 + 4) % 4;
            cur_dist = 0;
            if(seeker_dir % 2 == 1){
                moving_dist--;
            }
            if(nx == n-1 && ny == 0)
                moving_dist++;
        }
    }

}

void Simulate(int turn){
    // 1. 격자에 있는 도망자 이동
    for(int i=0; i<(int)runaway.size(); i++){
        int x, y, d;
        tie(x, y, d) = runaway[i];
        int dist = abs(x-seeker.first) + abs(y-seeker.second);  // 술래와 도망자의 거리
        if(dist <= 3){      // 술래와 거리가 3 이하인 아이들만 이동할 수 있음
            Move(i);        // i번째 사람 이동
        }
        else{               // 술래와 거리가 3보다 크다면 격자에 그대로 남아있음
            next_runaway.push_back(make_tuple(x, y, d));
        }
    }

    // 2. 술래 달팽이 모양으로 한 칸 이동
    MoveSeeker();
    // 3. 술래 자기 포함 3칸 내에 사람이 있는지 확인
    int caught_cnt = 0;

    for(int i=0; i<3; i++){
        int cx = seeker.first + dirs[seeker_dir][0]*i;
        int cy = seeker.second + dirs[seeker_dir][1]*i;
        if(InRange(cx, cy) && grid[cx][cy] == 0){   // 만약 범위 안에 있고, 나무가 없다면
            // (cx, cy)에 있는 참가자수 증가
            for(int j=0; j < (int)next_runaway.size(); j++){
                int x, y; tie(x, y, ignore) = next_runaway[j];
                if(x == cx && y == cy){     // 만약 참가자가 여기에 있다면
                    caught_cnt++;       // 잡은 사람 명수 증가
                    next_runaway[j] = make_tuple(-1, -1, -1);
                }
            }
        }
    }
    // next_runaway에서 runaway로 옮겨주기
    runaway.clear();
    for(int i=0; i<(int)next_runaway.size(); i++){
        int x, y, d;
        tie(x, y, d) = next_runaway[i];
        if(x == -1 && y == -1)
            continue;
        runaway.push_back(make_tuple(x, y, d));
    }
    next_runaway.clear();
    // 5. 해당 턴에 얻게 되는 점수 업데이트
    total_score += turn * caught_cnt;
}

int main() {
    // 입력:
    Input();
    seeker.first = n/2, seeker.second = n/2; // 술래 위치 초기화
    // k번에 걸쳐 시뮬레이션 시작

    for(int i=1; i<=k; i++){
        Simulate(i);
        //cout << seeker.first << ' ' << seeker.second << '\n';
    }
    // 출력:
    cout << total_score << '\n';
    return 0;
}