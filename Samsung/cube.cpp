/*
 * 2024.02.20
 * 정육면체 한 번 더 굴리기
 * 방향 -1 + 4에서 +4를 빼먹은 것 제외하고는 1시간 내에 푼 문제
*/

#include <iosteram>
#include <utility>
#include <tuple>
#include <queue>

#define MAX_N 20
#define FACE_NUM 6
#define DIR_NUM 4
#define OUT_OF_GRID make_pair(-1, -1)

using namespace std;

int n, m;

// 현재 위치와 방향을 기록한다. (시작은 오른쪽)
int x, y;
int move_dir;

// 방향은 오른쪽, 아래, 왼쪽, 위 순이다.
// 시계방향, 반시계방향 회전을 용이하게 하기 위한 순서로 정의한다.
int dx[DIR_NUM] = {0,1,0,-1};
int dy[DIR_NUM] = {1,0,-1,0};

int grid[MAX_N][MAX_N];

// bfs 진행을 위해 필요한 값들
queue<pair<int, int> > bfs_q;
bool visited[MAX_N][MAX_N];

// 주사위가 놓여있는 상태
int u = 1, f = 2, r = 3;    // up, front, right 

int ans;

// 격자 안에 있는지를 확인한다.
bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 동일한 숫자에 대해서만 이동이 가능
bool CanGo(int x, int y, int target_num) {
    return InRange(x, y) && !visited[x][y] && grid[x][y] == target_num;
}

int BFS(int x, int y, int target_num){
    // visited 값을 초기화한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = false;
    
    // 시작점을 표시한다.
    visited[x][y] = true;
    bfs_q.push(make_pair(x, y));

    int score = 0;

    // BFS 탐색을 수행한다.
    while(!bfs_q.empty()){
        pair<int, int> curr_pos = bfs_q.front();
        int curr_x, curr_y;
        tie(curr_x, curr_y) = curr_pos;
        bfs_q.pop();
        score += target_num;    // 점수에 target_num 더해주기

        for(int i=0; i < DIR_NUM; i++){
            int new_x = curr_x + dx[i];
            int new_y = curr_y + dy[i];

            if(CanGo(new_x, new_y, target_num)){
                bfs_q.push(make_pair(new_x, new_y));
                visited[new_x][new_y] = true;
            }
        }
    }
    return score;
}

// 현재 위치를 기준으로 했을 때의 점수를 계산한다.
int GetScore(){
    return BFS(x, y, grid[x][y]);
}

// 해당 방향으로 이동했을 때의 다음 위치를 구한다.
// 이동이 불가능할 경우 OUT_OF_GRID를 반환한다.
pair<int, int> NextPos(){
    int nx = x + dx[move_dir], ny = y + dy[move_dir];
    if(InRange(nx, ny))
        return make_pair(nx, ny);
    else
        reutnr OUT_OF_GRID;
}

void Simulate(){
    // 현재 방향으로 굴렸을 때의 격자 상의 위치를 구하기
    pair<int, int> next_pos = NextPos();

    // 격자를 벗어난다면, 방향을 반대로 튼 이후의 격자를 구하기
    if(next_pos == OUT_OF_GRID){
        move_dir = (move_dir < 2) ? (move_dir + 2) : (move_dir - 2);
        next_pos = NextPos();
    }
    
    // 위치를 이동한다.
    tie(x, y) = next_pos;

    // 점수를 더해준다.
    ans += GetScore();

    // 주사위가 놓여있는 상태를 조정한다.
    if(move_dir == 0)   // 오른쪽
        tie(u, f, r) = make_tuple(7-r, f, u);
    else if(move_dir == 1) // 아래쪽
        tie(u, f, r) = make_tuple(7 - f, u, r);
    else if(move_dir == 2) // 왼쪽
        tie(u, f, r) = make_tuple(r, f, 7 - u);
    else if(move_dir == 3) // 위쪽
        tie(u, f, r) = make_tuple(f, 7 - u, r);

    // 주사위의 바닥면에 적혀있는 숫자와, 격자 숫자를 비교한다.
    int bottom = 7 - u;
    // 주사위에 적힌 숫자가 더 크면 시계방향으로 90' 회전
    if(bottom > grid[x][y])
        move_dir = (move_dir + 1) % 4;
    // 주사위에 적힌 숫자가 더 작으면 반시계방향으로 90' 회전
    else if(bottom < grid[x][y])
        move_dir = (move_dir - 1 + 4) % 4;
}

int main(){
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    // 시뮬레이션 진행
    while(m--)
        Simulate();
    
    // 점수 출력
    cout << ans;
    return 0;
}