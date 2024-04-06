/*
 * 2024.02.14
 * 해설 풀이
 * 시뮬레이션은 플레이어가 한 명씩 순서대로 움직이면서 아래의 단계를 수행
 * 1. 다음 칸으로 이동할 때 한 칸을 움직이되, 격자 밖으로 나가는 경우 반대 방향으로 한 칸 움직임
 * 2. 이동한 위치에 총이 있으면 충을 주음. 현재 보유한 총과 비교해서 공격력이 더 높으면 바꾸기
 * 3. 이동한 위치에 이미 다른 플레이어가 있는 경우, 해당 위치에서 싸움을 진행함.
 *    싸움의 결과는 플레이어의 초기 능력치 + 보유한 총의 공격력을 합한 수치로 결정됨
 * 4. 싸움에서 이긴 플레이어는 상대방과 자신이 보유한 총 중 가장 강력한 총을 선택하여 보유하고, 나머지 총은 원래 위치에 둠
 *
 * 시간복잡도: 라운드수 K, 플레이어 수 M, 이동 및 계산에 걸리는 시간 고려할 때 대략 O(k*m)
 * 각 플레이어의 움직임 및 싸움 처리는 O(1) 시간에 처리됨.
 * 그러나 플레이어 간에 싸움이 일어나 복잡한 계산을 수행하거나, 총을 선택하는 과정에서 정렬 등의 추가적인 계산이 이루어질 경우 시간복잡도에 영향을 줄 수 있음
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

#define MAX_N 20
#define MAX_M 30
#define DIR_NUM 4
#define Player tuple <int, int, int, int, int, int>
#define EMPTY make_tuple(-1, -1, -1, -1, -1, -1)

using namespace std;

// 변수 선언
int n, m, k;                                        // n: 격자 크기, m: 플레이어의 수, k: 라운드 수

// 각 칸마다 놓여있는 총 목록을 관리
vector<int> gun[MAX_N][MAX_N];                     // 각 칸은 총의 공격력들을 담음

// 각 칸마다 플레이어 정보를 관리
// 순서대로 (num, x, y, d, s, a) 정보를 관리한다.
// (x, y) 위치에서 방향 d를 보고 있으며
// 초기 능력치가 s인 num번 플레이어가
// 공격력이 a인 총을 들고 있음을 뜻한다.
// 총이 없으면 a는 0임
Player players[MAX_M];

// 입력으로 주어지는 방향 순서대로 dx, dy를 정의하기
// 상, 우, 하, 좌 방향
int dx[DIR_NUM] = {-1, 0, 1,  0};
int dy[DIR_NUM] = { 0, 1, 0, -1};

// 플레이어들의 포인트 정보를 기록하기
int points[MAX_M];

// (x,y)가 격자를 벗어나는지 확인하기
bool InRange(int x, int y){     
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Input(){                   // 입력값을 받는 함수
    cin >> n >> m >> k;         // 격자 크기, 플레이어 수, 라운드 수 입력받음
    for(int i=0; i<n; i++){     // 전체 격자 크기에 대해서
        for(int j=0; j<n; j++){ // 총의 공격력 입력받기
            int x;
            cin >> x;

            // 총이 놓여 있는 칸
            if(x != 0)
                gun[i][j].push_back(x);
        }
    }

    // 플레이어 정보를 입력받기
    for(int i=0; i<m; i++){     // 전체 플레이어에 대해서
        int x, y, d, s;         // (x,y) 플레이어 위치, d: 방향, s: 초기 능력
        cin >> x >> y >> d >> s;
        players[i] = make_tuple(i, x-1, y-1, d, s, 0);     // 가지고 있는 총 공격력 0을 추가해서 넣기
    }
}


// 현재 (x,y) 위치에서 방향 d를 보고 있을 때
// 그 다음 위치와 방향을 찾아주기
tuple<int, int, int> GetNext(int x, int y, int d){
    int nx = x + dx[d], ny = y + dy[d];
    // 격자를 벗어나면
    // 방향을 뒤집어 반대 방향으로 한 칸 이동하기
    if(!InRange(nx, ny)){
        // 반대 방향 : 0 <-> 2 / 1 <-> 3
        d = (d < 2) ? (d + 2) : (d - 2);
        nx = x + dx[d], ny = y +dy[d];
    }
    return make_tuple(nx, ny, d);
}

// 해당 칸에 있는 Player를 찾아주기
// 없다면 EMPTY를 반환
Player FindPlayer(pair<int, int> pos){
    for(int i=0; i<m; i++){
        int x, y;
        tie(ignore, x, y, ignore, ignore, ignore) = players[i];

        if(pos == make_pair(x,y))
            return players[i];
    }
    return EMPTY;
}

// Player p의 정보를 갱신해주기
void Update(Player p){
    int num;
    tie(num, ignore, ignore, ignore, ignore, ignore) = p;

    // Player의 위치를 찾아 값을 갱신해주기
    for(int i=0; i<m; i++){
        int num_i;
        tie(num_i, ignore, ignore, ignore, ignore, ignore) = players[i];

        if(num_i == num){
            players[i] = p;
            break;
        }
    }
}

// 플레이어 p를 pos 위치로 이동시켜주기
void Move(Player p, pair<int, int> pos){     // idx번 플레이어를 움직이기
    int num, x, y, d, s, a;
    tie(num, x, y, d, s, a) = p;

    int nx, ny;
    tie(nx, ny) = pos;

    // 가장 좋은 총으로 갱신해주기
    gun[nx][ny].push_back(a);
    sort(gun[nx][ny].begin(), gun[nx][ny].end(), greater<int>());
    a = gun[nx][ny][0];
    gun[nx][ny].erase(gun[nx][ny].begin());

    p = make_tuple(num, nx, ny, d, s, a);
    Update(p);
}

// 진 사람의 움직임을 진행하기
void LoserMove(Player p){
    int num, x, y, d, s, a;
    tie(num, x, y, d, s, a) = p;

    // 먼저 현재 위치에 총을 내려놓게 됨
    gun[x][y].push_back(a);
    // 빈 공간을 찾아 이동하게 된다
    // 현재 방향에서 시작하여 90'씩 시계방향으로 회전하다가 비어있는 최초의 곳으로 이동하기
    for(int i=0; i<4; i++){
        int ndir = (d+i) % 4;
        int nx = x+dx[ndir], ny = y+dy[ndir];
        if(InRange(nx, ny) && FindPlayer(make_pair(nx,ny)) == EMPTY){
            p = make_tuple(num, x, y, ndir, s, 0);
            Move(p, make_pair(nx,ny));
            break;
        }
    }
}

// p1과 p2가 pos에서 만나 결투를 진행하기
void Duel(Player p1, Player p2, pair<int, int> pos){
    int num1, d1, s1, a1;
    tie(num1, ignore, ignore, d1, s1, a1) = p1;

    int num2, d2, s2, a2;
    tie(num2, ignore, ignore, d2, s2, a2) = p2;

    // (초기 능력치 + 총의 공격력, 초기 능력치) 순으로 우선순위를 매겨 비교하기

    // p1이 이긴 경우
    if(make_pair(s1+a1, s1) > make_pair(s2+a2, s2)){
        // p1은 포인트를 얻게 됨
        points[num1] += (s1+a1) - (s2+a2);
        // p2는 진 사람의 움직임을 진행하기
        LoserMove(p2);
        // 이후 p1은 이긴 사람의 움직임을 진행
        Move(p1, pos);
    }
    // p2가 이긴 경우
    else{
        points[num2] += (s2+a2) - (s1+a1);
        LoserMove(p1);
        Move(p2, pos);
    }
}

void Simulate(){
    // 첫 번째 플레이어부터 순서대로 진행하기
    for(int i=0; i<m; i++){
        int num, x, y, d, s, a;
        tie(num, x, y, d, s, a) = players[i];


        // Step 1-1. 현재 플레이어가 움직일 그 다음 위치와 방향을 구하기
        int nx, ny, ndir;
        tie(nx, ny, ndir) = GetNext(x, y, d);

        // 해당 위치에 있는 전 플레이어 정보를 얻어오기
        Player next_player = FindPlayer(make_pair(nx, ny));

        // 현재 플레이어의 위치와 방향을 보정해주기
        Player curr_player = make_tuple(num, nx, ny, ndir, s, a);
        Update(curr_player);

        // Stpe 2. 해당 위치로 이동해보기
        // Step 2-1. 해당 위치에 플레이어가 없다면 그대로 움직이기
        if(next_player == EMPTY)
            Move(curr_player, make_pair(nx, ny));
        // Step 2-2. 해당 위치에 플레이어가 있다면 결투를 진행하기
        else
            Duel(curr_player, next_player, make_pair(nx,ny));
    }
}


void Output(){      // 정답을 출력하는 함수
    // 각 플레이어가 획득한 포인트를 출력하기
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