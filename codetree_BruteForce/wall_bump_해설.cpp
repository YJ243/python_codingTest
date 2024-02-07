/*
 * 2024.2.4
 * 2차원 배열로 구슬 목록을 관리하여 Simulation
*/
#include <iostream>
#include <vector>

#define DIR_NUM 4
#define MAX_N 50
#define ASCII_NUM 128
#define BLANK -1
#define COLLIDE -2

using namespace std;

// 전역 변수 선언:
int t, n, m;

int curr_dir[MAX_N + 1][MAX_N + 1];
int next_dir[MAX_N + 1][MAX_N + 1];

int mapper[ASCII_NUM];

// 후에 구슬이 벽에 부딪혔을 때의 처리를 간단히 하기 위해
// dir 기준 0, 3이 대칭 1, 2가 대칭이 되도록 설정합니다.
int dx[DIR_NUM] = {-1, 0, 0, 1};
int dy[DIR_NUM] = {0, 1, -1, 0};

// 해당 위치가 격자 안에 들어와 있는지 확인합니다.
bool InRange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

// 해당 위치에 dir 방향을 갖는 구슬이 새롭게 추가되는 경우에 대한
// 처리를 합니다.
void UpdateNextDir(int x, int y, int dir) {
    // 빈 곳이었다면 해당 구슬을 넣어주고
    if(next_dir[x][y] == BLANK)
        next_dir[x][y] = dir;
    // 빈 곳이 아니었다면 이미 다른 구슬이 놓여져 있는 것이므로
    // 충돌 표시를 해줍니다.
    else
        next_dir[x][y] = COLLIDE;
}

void Move(int x, int y, int dir) {
    // 바로 앞에 벽이 있는지 판단합니다.
    int nx = x + dx[dir], ny = y + dy[dir];
    
    // Case 1 : 벽이 없는 경우에는 그대로 한 칸 전진합니다.
    // 따라서 그 다음 위치에 같은 방향을 갖는 구슬이 있게 됩니다.
    if(InRange(nx, ny))
        UpdateNextDir(nx, ny, dir);

    // Case 2 : 벽이 있는 경우에는 방향을 반대로 틀어줍니다.
    // 따라서 같은 위치에 반대 방향을 갖는 구슬이 있게 됩니다.
    else
        UpdateNextDir(x, y, 3 - dir);
}

// 구슬을 전부 한 번씩 움직여 봅니다.
void MoveAll() {
    // 그 다음 각 위치에서의 방향들을 전부 초기화해놓습니다.
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            next_dir[i][j] = BLANK;
    
    // (i, j) 위치에 구슬이 있는경우 
    // 움직임을 시도해보고, 그 결과를 전부 next_dir에 기록합니다.
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(curr_dir[i][j] != BLANK)
                Move(i, j, curr_dir[i][j]);

    // next_dir 값을 curr_dir에 복사합니다.
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            curr_dir[i][j] = next_dir[i][j];
}

// 충돌이 일어나는 구슬은 전부 지워줍니다.
void RemoveDuplicateMarbles() {
    // 충돌이 일어난 구슬들이 있는 위치만 빈 곳으로 설정하면 됩니다.
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(curr_dir[i][j] == COLLIDE)
                curr_dir[i][j] = BLANK;
}

// 조건에 맞춰 시뮬레이션을 진행합니다.
void Simulate() {
    // Step1
    // 구슬을 전부 한 번씩 움직여 봅니다.
    MoveAll();

    // Step2
    // 움직임 이후에 충돌이 일어나는 구슬들을 골라 목록에서 지워줍니다.
    RemoveDuplicateMarbles();
}

int main(){
    mapper['U'] = 0;
    mapper['R'] = 1;
    mapper['L'] = 2;
    mapper['D'] = 3;

    // 테스트 케이스 수 입력:
    cin >> t;

    while(t--) {
        // 입력:
        cin >> n >> m;

        // 새로운 테스트 케이스가 시작될때마다 기존에 사용하던 값들을 초기화해줍니다.
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                curr_dir[i][j] = BLANK;

        for(int i = 1; i <= m; i++) {
            int x, y; char d;
            cin >> x >> y >> d;
            curr_dir[x][y] = mapper[d];
        }

        // 2*n번 이후에는 충돌이 절대 일어날 수 없으므로
        // 시뮬레이션을 총 2*n번 진행합니다.
        for(int i = 1; i <= 2 * n; i++)
            Simulate();
        
        // 출력:
        int marble_cnt = 0;

        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(curr_dir[i][j] != BLANK)
                    marble_cnt++;

        cout << marble_cnt << endl;
    }
}