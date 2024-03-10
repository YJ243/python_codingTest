/*
 * 2024.02.29
 * 내 풀이
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#define MAX_N 20

using namespace std;
int n, m;
int grid[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
queue<pair<int, int> > q;
tuple<int, int, int, int> MaxBomb;      // 크기, -빨간색, 행, -열
int cur_cnt;
int red_cnt;
int total_score;
void Input(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
}

void Initialize(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = false;

}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int val){
    return InRange(x, y) && !visited[x][y] && (grid[x][y] == val || grid[x][y] == 0);
}

tuple<int, int, int, int> bfs(int val){
    pair<int, int> std_point = make_pair(-1, MAX_N);
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first, y = curr.second;
        //cout << x << ' ' << y << '\n';
        if(grid[x][y] > 0){         // 기준점인지 확인하기=> 이 부분을 여기가 아니라 네가지 방향을 보면서 탐색할 때 하느라, 처음일 경우를 빠뜨림
            if(x > std_point.first || ( x == std_point.first && y < std_point.second))
                std_point = make_pair(x, y);
        }
        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            if(CanGo(nx, ny, val)){
                visited[nx][ny] = true;
                cur_cnt++;
                if(grid[nx][ny] == 0)       // 빨간색이라면 빨간색 개수 증가
                    red_cnt++;
                q.push(make_pair(nx, ny));
            }
        }
    }
    //cout << '\n';
    return make_tuple(cur_cnt, -red_cnt, std_point.first, -std_point.second);
}

void FindMaxSizeBomb(){
    MaxBomb = make_tuple(-1, (MAX_N*MAX_N), -1, (MAX_N*MAX_N));     // MaxBomb초기화 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0 && !visited[i][j]){
                Initialize();       // 빨간색 폭탄에 대한 깔끔한 처리를 위해 각 칸마다 BFS 진행해야 하며, 진행전 visited 모든 칸 초기화
                cur_cnt = 1;
                red_cnt = 0;
                visited[i][j] = true;
                q.push(make_pair(i,j));
                tuple<int, int, int, int> cur = bfs(grid[i][j]);
                if(cur > MaxBomb)
                    MaxBomb = cur;
            }
        }
    }
    int curCnt, redCnt, r, c;
    tie(curCnt, redCnt, r, c) = MaxBomb;
    
}

void DeleteBomb(){
    Initialize();
    int cnt,r, c;
    tie(cnt, ignore, r, c) = MaxBomb;
    c = -c;

    visited[r][c] = true;
    q.push(make_pair(r,c));
    bfs(grid[r][c]);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
        if(visited[i][j])
            grid[i][j] = -2;
        }
    }
    total_score += cnt*cnt;
}


void DoGravity(){
    // 비어있는 곳에 대해서 폭탄 떨어뜨리기
    int temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp[i][j] = -2;
        }
    }
    
    for(int j=0; j<n; j++){
        // 각 열단위로 보기
        vector<int> after;
        int nextIdx = n-1;
        for(int i=n-1; i >= 0; i--){
            if(grid[i][j] == -2)
                continue;
            else if(grid[i][j] >= 0)
                after.push_back(grid[i][j]);
            else if(grid[i][j] == -1){
                int start_idx=i;
                int s = (int)after.size(), l = n-1-i;
                for(int k=s; k < l; k++)
                    after.push_back(-2);

                after.push_back(grid[i][j]);
            }
        }
        for(int k=0; k<(int)after.size(); k++)
            temp[nextIdx--][j] = after[k];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = temp[i][j];
        }
    }
    
}

void RotateCounterClockwise(){
    int temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp[n-1-j][i] = grid[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = temp[i][j];
        }
    }
}

bool Simulate(){
    // 0. 초기화하기
    Initialize();

    // 1. 크기가 가장 큰 폭탄 묶음 찾기
    FindMaxSizeBomb();
    
    int cur_total;
    tie(cur_total, ignore, ignore, ignore) = MaxBomb;
    if(cur_total <= 1)
        return true;
    // 2. 선택한 묶음 내 폭탄 제거하기
    DeleteBomb();
    
    // 3. 중력 작용시키기
    DoGravity();
    
    // 4. 반시계방향으로 90도 회전시키기
    RotateCounterClockwise();

    // 5. 중력 작용시키기
    DoGravity();

    return false;       // 아직 끝나지 않음
}

int main() {
    // 입력받기:
    Input();

    // 시뮬레이션 진행
    while(true){
        bool IsFinish = Simulate();
        if(IsFinish)
            break;
        //cout << total_score<<'\n';
    }

    cout << total_score;
    return 0;
}