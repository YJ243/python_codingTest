/*
 * 2024.04.04
 * 포탑 부수기 게임에서 각 턴마다 가장 약한 포탑을 각성시켜 공격자로 만들고,
 * 강한 포탑을 공격하는 전략을 취한다.
 * 각 턴마다 최선의 공격을 수행함으로써 남은 포탑 중 가장 강한 포탑의 공격력을 결정
 *
 * Algorithm**
 * 초기 상태에서 모든 포탑의 상태를 읽어온 뒤, 주어진 턴 수만큼 게임을 진행
 * 각 턴에서는 현재 살아있는 포탑들의 목록을 만들어 선정 규칙에 따라 정렬한다.
 * 정렬된 목록에서 가장 앞에 있는 포탑이 각성하여 공격자로 선정되고,
 * 각성 효과로 추가 공격력을 얻는다.
 *
 * 이후 가장 강한 포탑에 대해 공격을 시도하고, 레이저 공격이 가능할 경우 최단 경로를 차장 피해를 입힌다.
 * 불가능한 경우 포탄 공격으로 피해를 준다.
 * 그 다음 공격으로 인해 파괴된 포탑을 제거도고, 공격에 참여하지 않은 포탑들은 정비 시간을 가져서 공격력 상승
 * 이 모든 과정을 남은 포탑이 1개가 될 때까지 또는 주어진 턴 수가 종료될 때까지 반복하고,
 * 최종적으로 살아남은 포탑들 중 가장 강력한 포탑의 공격력을 출력
 * 시간복잡도: 각 턴마다 포탑들을 정리하고 정렬하는 데 O(NMlog(NM)) 소요, 전체 공정을 K번 반복
 * 최종 시간복잡도: O(KNMlog(NM))
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

#define MAX_N 10

const int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};       // 우,하,좌,상 우선순위
const int dx2[9] = {0,0,0,-1,-1,-1,1,1,1}, dy2[9] = {0,-1,1,0,-1,1,0,-1,1};

int n, m, k;
int turn;

// 현재 포탑들이 가진 힘과 언제 각성했는지 기록해준다.
int board[MAX_N][MAX_N];
int rec[MAX_N][MAX_N];

// 빛의 공격을 할 때 방문 여부와 경로 방향을 기록해준다.
bool vis[MAX_N][MAX_N];
int back_x[MAX_N][MAX_N], back_y[MAX_N][MAX_N];

// 공격과 무관했는지 여부를 저장한다.
bool is_active[MAX_N][MAX_N];

// 구조체 turret을 정의해 관리한다.
struct Turret{
    int x, y, r, p;
};

// 살아있는 포탑들을 관리한다.
vector<Turret> live_turret;

// turret의 약함, 강함 우선순위에 맞게 정렬함수를 만들어준다.
bool cmp(Turret a, Turret b){
    if(a.p != b.p) return a.p < b.p;
    if(a.r != b.r) return a.r > b.r;
    if(a.x + a.y != b.x + b.y) return a.x + a.y > b.x + b.y;
    return a.y > b.y;
}

// 턴을 진행하기 전 필요한 전처리를 정리해준다.
void Init(){
    turn++;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++){
            vis[i][j] = false;
            is_active[i][j] = false;
        }
}

// 각성을 진행한다.
// 각서응ㄹ 하면 가장 약한 포탑이 n+m 만큼 강해진다.
void Awake(){
    // 우선순위에 맞게 현재 살아잇는 포탑들을 정렬해준다.
    sort(live_turret.begin(), live_turret.end(), cmp);

    // 가장 약한 포탑을 찾아 n+m 만큼 더해주고,
    // is_active와 live_turret 배열도 갱신해준다.

    Turret weak_turret = live_turret[0];
    int x = weak_turret.x;
    int y = weak_turret.y;

    board[x][y] += n+m;
    rec[x][y] = turn;
    weak_turret.p = board[x][y];
    weak_turret.r = rec[x][y];
    is_active[x][y] = true;

    live_turret[0] = weak_turret;
}

// 레이저 공격을 진행한다.
bool LaserAttack(){
    // 기존에 정렬된 가장 앞선 포탑이 각성한 포탑이다.
    Turret weak_turret = live_turret[0];
    int sx = weak_turret.x;
    int sy = weak_turret.y;
    int pow = weak_turret.p;

    // 기존에 정렬된 가장 뒤 포탑이
    // 각성한 포탑을 제외한 포탑 중 가장 강한 포탑이다.
    Turret strong_turret = live_turret[(int)live_turret.size()-1];
    int ex = strong_turret.x;
    int ey = strong_turret.y;

    // bfs를 통해 최단 경로를 관리해준다.
    queue<pair<int, int> > q;
    vis[sx][sy] = true;
    q.push(make_pair(sx, sy));

    // 가장 강한 포탑에게 도달 가능한지 여부를 can_attack에 관리해준다.
    bool can_attack = false;

    while(!q.empty()){
        int x, y;
        tie(x, y) = q.front(); q.pop();

        // 가장 강한 포탑에게 도달할 수 있다면 바로 멈춘다.
        if(x == ex && y == ey){
            can_attack = true;
            break;
        }
    
        // 각각 우, 하, 좌, 상 순서대로 방문하며 방문 가능한 포탑들을 찾고 queue에 저장해준다.
        for(int dir = 0; dir < 4; dir++){
            int nx = (x + dx[dir]+ n) % n;
            int ny = (y + dy[dir]+ m) % m;

            // 이미 방문한 포탑이라면 넘어간다.
            if(vis[nx][ny])
                continue;

            // 벽이라면 넘어간다.
            if(board[nx][ny] == 0)
                continue;

            vis[nx][ny] = true;
            back_x[nx][ny] = x;
            back_y[nx][ny] = y;
            q.push(make_pair(nx, ny));
        }
    }

    // 만약 도달 가능하다면 공격을 진행한다.
    if(can_attack){
        // 우선 가장 강한 포탑에게는 pow만큼의 공격을 진행한다.
        board[ex][ey] -= pow;
        if(board[ex][ey] < 0)
            board[ex][ey] = 0;
        is_active[ex][ey] = true;

        // 기존의 경로를 역추적하며
        // 경로 상에 있는 모든 포탑에게 pow/2만큼의 공격을 진행한다.
        int cx = back_x[ex][ey];
        int cy = back_y[ex][ey];

        while(!(cx == sx && cy == sy)){
            board[cx][cy] -= pow/2;
            if(board[cx][cy] < 0)
                board[cx][cy] = 0;
            is_active[cx][cy] = true;

            int next_cx = back_x[cx][cy];
            int next_cy = back_y[cx][cy];

            cx = next_cx;
            cy = next_cy;
        }
    }
    // 공격을 성공했는지 여부를 반환한다.
    return can_attack;
}

// 레이저 공격을 하지 못했다면 폭탄 공격을 진행한다.
void BombAttack(){
    // 기존에 정렬된 가장 앞선 포탑이 각성한 포탑이다.
    Turret weak_turret = live_turret[0];
    int sx = weak_turret.x;
    int sy = weak_turret.y;
    int pow = weak_turret.p;

    // 기존에 정렬된 가장 뒤 포탑이
    // 각성한 포탑을 제외한 포탑 중 가장 강한 포탑이다.
    Turret strong_turret = live_turret[(int)live_turret.size() - 1];
    int ex = strong_turret.x;
    int ey = strong_turret.y;

    // 가장 강한 포탑의 3*3 범위를 모두 탐색하며
    // 각각에 맞는 공격을 진행한다.
    for(int dir=0; dir < 9; dir++){
        int nx = (ex + dx2[dir]+n) % n;
        int ny = (ey + dy2[dir]+m) % m;

        // 각성한 포탑 자기 자신일 경우 넘어간다.
        if(nx == sx && ny == sy)
            continue;

        // 가장 강한 포탑일 경우 pow만큼의 공격을 진행한다.
        if(nx == ex && ny == ey){
            board[nx][ny] -= pow;
            if(board[nx][ny] < 0)
                board[nx][ny] = 0;
            is_active[nx][ny] = true;
        }
        // 그 외의 경우 pow/2 만큼의 공격을 진행한다.
        else{
            board[nx][ny] -= pow/2;
            if(board[nx][ny] < 0)
                board[nx][ny] = 0;
            is_active[nx][ny] = true;
        }
    }
}

// 공격에 관여하지 않은 모든 살아있는 포탑의 힘을 1 증가시킨다.
void Reserve(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(is_active[i][j])
                continue;
            if(board[i][j] == 0)
                continue;
            board[i][j]++;
        }
    }
}
int main(){
    // 입력:
    cin >> n >> m >> k;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> board[i][j];
        
    // k턴 동안 진행된다.
    while(k--){
        // 턴을 진행하기 전 살아있는 포탑을 정리한다.
        live_turret.clear();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(board[i][j]){
                    Turret new_turret;
                    new_turret.x = i;
                    new_turret.y = j;
                    new_turret.r = rec[i][j];
                    new_turret.p = board[i][j];

                    live_turret.push_back(new_turret);
                }
            }
        }
        // 살아있는 포탑이 1개 이하라면 바로 종료한다.
        if(live_turret.size() <= 1)
            break;

        // 턴을 진행하기 전 필요한 전처리를 정리해준다.
        Init();

        // 각성을 진행한다.
        Awake();

        // 레이저 공격을 진행한다.
        bool is_suc = LaserAttack();
        // 레이저 공격을 하지 못했다면 포탄 공격을 진행한다.
        if(!is_suc)
            BombAttack();

        // 공격에 관여하지 않은 모든 살아있는 포탑의 힘을 1 증가시킨다.
        Researve();
    }

    // 살아있는 포탑의 힘 중 가장 큰 값을 출력ㅎ나다.
    int ans = 0;
    for(int i=0; i<n; i++)
        for(itn j=0; j<m; j++)
            ans = max(ans, board[i][j]);
    cout << ans;
    return 0;
}