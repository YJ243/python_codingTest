/*
 * 2024.04.06
 * 해설 풀이
 * 먼저 술래의 이동 경로를 계산한다.
 * 격자의 중심에서 시작하여 달팽이 모양의 경로를 따라 격자의 끝까지 도달하면 다시 중앙으로 이동하는 경로를 구성한다.
 * 이 때 술래의 정방향과 역방향 이동 경로를 각각 계산한다.
 * 그 이후 모든 턴에서 도망자가 술래와의 거리를 고려하여 움직이고, 술래가 이동한다.
 * 이후 술래가 시야 내에 있는 도망자를 잡고 점수를 획득한다.
 * 시간복잡도: 술래와 도망자의 이동을 시뮬레이션 하는데 O(N^2), 이를 k번 반복
 * 총 시간복잡도: O(KN^2)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cstdlib>

#define MAX_N 100
#define DIR_NUM 4

// 변수 선언
int n, m, h, k;
// 각 칸에 있는 도망자 정보를 관리한다.
// 도망자의 방향만 저장하면 충분하다.
vector<int> hiders[MAX_N][MAX_N];
vector<int> next_hiders[MAX_N][MAX_N];
bool tree[MAX_N][MAX_N];

// 정방향 기준으로 현재 위치에서 술래가 움직여야 할 방향을 관리한다.
int seeker_next_dir[MAX_N][MAX_N];
// 역방향 기준으로 현재 위치에서 술래가 움직여야 할 방향을 관리한다.
int seeker_rev_dir[MAX_N][MAX_N];

// 술래의 현재 위치를 나타낸다.
pair<int, int> seeker_pos;

// 술래가 움직이는 방향이 정방향이면 true / 아니라면 false이다.
bool forward_facing = true;

int ans;

// 정중앙으로부터 끝까지 움직이는 경로를 계산해준다.
void InitializeSeekerPath(){
    // 상우하좌 순서대로 넣어준다.
    int dx[DIR_NUM] = {-1,0,1,0};
    int dy[DIR_NUM] = {0,1,0,-1};

    // 시작 위치와 방향, 해당 방향으로 이동할 횟수를 설정한다.
    int curr_x = n/2, curr_y = n/2;
    int move_dir = 0; move_num = 1;
    while(curr_x || curr_y){
        // move_num만큼 이동한다.
        for(int i=0; i<move_num; i++){
            seeker_next_dir[curr_x][curr_y] = move_dir;
            curr_x += dx[move_dir]; curr_y += dy[move_dir];
            seeker_rev_dir[curr_x][curr_y] = (move_dir < 2) ? move_dir+2: move_dir-2;

            // 이동하는 도중 (0,0)으로 오게 되면, 움직이는 것을 종료한다.
            if(!curr_x && !curr_y)
                break;
        }

        // 방향을 바꾼다.
        move_dir = (move_dir+1) % 4;
        // 만약 현재 방향이 위 혹은 아래가 된 경우에는
        // 특정 방향으로 움직여야 할 횟수를 1 증가시킨다.
        if(move_dir == 0 || move_dir == 2)
            move_num++;
    }
}

// 격자 내에 있는지를 판단합니다.
bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

void HiderMove(int x, int y, int move_dir){
    // 좌우하상 순서대로 넣어준다. (처음에 1: 좌우(우방향), 2:상하(하방향))
    int dx[DIR_NUM] = {0,0,1,-1};
    int dy[DIR_NUM] = {-1,1,0,0};

    int nx = x + dx[move_dir], ny = y + dy[move_dir];

    // Step 1. 만약 격자를 벗어난다면 우선 방향을 틀어준다.
    if(!InRange(nx, ny)){
        // 0 <-> 1, 2 <-> 3이 되어야 한다.
        movd_dir = (move_dir < 2) ? (1-move_dir) : (5-move_dir);
        nx = x + dx[move_dir]; ny = y + dy[move_dir];
    }

    // Step 2. 그 다음 위치에 술래가 없다면 움직여준다.
    if(make_pair(nx, ny) != seeker_pos)
        next_hiders[nx][ny].push_back(move_dir);
    // 술래가 있다면 더 움직이지 않는다.
    else
        next_hiders[x][y].push_back(move_dir);
}

int DistFromSeeker(int x, int y){
    // 현재 술래의 위치를 불러온다.
    int seeker_x, seeker_y;
    tie(seeker_x, seeker_y) = seeker_pos;

    return abs(seeker_x - x) + abs(seeker_y - y);
}


void HiderMoveAll(){
    // Step 1. next hider를 초기화해준다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_hiders[i][j].clear();
    
    // Step 2. hider를 전부 움직여준다.
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 술래와의 거리가 3 이내인 도망자드렝 대해서만 움직여준다.
            if(DistFromSeeker(i, j) <= 3){
                for(int k=0; k<(int)hiders[i][j].size(); k++)
                    HiderMove(i, j, hiders[i][j][k]);
            }
            // 그렇지 않다면 현재 위치 그대로 넣어준다.
            else{
                for(int k=0; k<(int)hiders[i][j].size(); k++)
                    next_hiders[i][j].push_back(hiders[i][j][k]);
            }
        }
    }

    // Step 3. next hider 값을 옮겨준다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            hiders[i][j] = next_hiders[i][j];
}

// 현재 술래가 바라보는 방향을 가져온다.
int GetSeekerDir(){
    // 현재 술래의 위치를 불러온다.
    itn x, y;
    tie(x, y) = seeker_pos;

    // 어느 방향으로 움직여야 하는지에 대한 정보를 가져온다.
    int move_dir;
    if(forward_facing)
        move_dir = seeker_next_dir[x][y];
    else
    {
        move_dir = seeker_rev_dir[x][y];
    }
    return move_dir;
}

void CheckFacing(){
    // Case 1. 정방향으로 끝에 다다른 경우라면, 방향을 바꿔준다.
    if(seeker_pos == make_pair(0,0) && forward_facing)
        forward_facing = false;
    // Case 2. 역방향으로 끝에 다다른 경우여도, 방향을 바꿔준다.
    if(seeker_pos == make_pair(n/2, n/2) && !forward_facing)
        forward_facing = true;
}

void SeekerMove(){
    int x, y;
    tie(x, y) = seeker_pos;

    // 상우하좌 순서대로 넣어준다.
    int dx[DIR_NUM] = {-1,0,1,0};
    int dy[DIR_NUM] = {0,1,0,-1};

    int move_dir = GetSeekerDir();

    // 술래를 한 칸 움직여준다.
    seeker_pos = make_pair(x + dx[move_dir], y + dy[move_dir]);

    // 끝에 도달했다면 방향을 바꿔줘야 한다.
    CheckFacing();
}

void GetScore(int t){

}

void Simulate(int t){
    // 도망자가 움직인다.
    HiderMoveAll();

    // 술래가 움직인다.
    SeekerMove();

    // 점수를 얻는다.
    GetScore(t);    
}

int main(){
    // 입력:
    cin >> n >> m >> h >> k;

    // 술래 정보를 입력받는다.
    while(m--){
        int x, y, d;
        cin >> x >> y >> d;
        hinders[x-1][y-1].push_back(d);
    }
    // 나무 정보를 입력받는다.
    while(h--){
        int x, y;
        cin >> x >> y;
        tree[x-1][y-1] = true;
    }

    // 술래의 처음 위치를 설정한다.
    seeker_pos = make_pair(n/2, n/2);

    // 술래잡기 시작 전에 구현상의 편의를 위해 술래 경로 정보를 미리 계산한다.
    InitializeSeekerPath();

    // k번에 걸쳐 술래잡기를 진행한다.
    for(int t=1; t <= k; t++)
        Simulate(t);

    cout << ans;
    return 0;
}