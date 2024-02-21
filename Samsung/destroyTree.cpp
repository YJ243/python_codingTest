/*
 * 2024.02.19
 * 나무 박멸
 * 한 번에 맞은 문제
*/

#include <iostream>
#include <climits>

#define MAX_N 20
using namespace std;

int n, m, k, c;         // n: 격자 크기, m: 박멸 년수, k: 대각선으로 퍼지는 개수, c: 제초제 남아있는 년수 
int grid[MAX_N][MAX_N]; // 격자, 빈칸:0, 벽: -1, 양수: 나무 그루 수
int temp[MAX_N][MAX_N]; // 나무를 한 번에 성장하기 위해 저장할 배열
int herbicide[MAX_N][MAX_N];    // 0: 제초제X, 양수: 해당 년까지 제초제가 남아 있음

int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};           // 상하좌우
int direction[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};    // 대각선
int ans;

void Input(){
    cin >> n >> m >> k >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
}

void Initialize_Temp(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            temp[i][j] = grid[i][j];
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool IsTree(int x, int y){   // 범위 안에 있고, 나무 그루가 있다면
    return InRange(x, y) && grid[x][y] > 0; 
}

void Grow_Tree(int x, int y){  // (x,y)에 있는 나무 번식 진행
    int adjacent_tree = 0;

    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(IsTree(nx, ny))
            adjacent_tree++;
    }
    grid[x][y] += adjacent_tree;

}

void Copy_Temp_to_Grid(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = temp[i][j];
}

bool CanPropagatable(int x, int y, int cur_year){   // 번식할 수 있는지 확인하는 함수
    // 범위 안에 있고, 빈 칸이면서, 제초제가 남아 있지 않은 경우
    return InRange(x, y) && grid[x][y] == 0 && herbicide[x][y] < cur_year;
}

void Propagate_Tree(int x, int y, int cur_year){      // (i,j)에 있는 트리 번식하기
    // 1. 번식이 가능한 칸의 개수 탐색
    int plus_tree = 0, cnt = 0;
    for(int d=0; d<4; d++){
        int nx = x+dirs[d][0], ny = y+dirs[d][1];
        if(CanPropagatable(nx, ny, cur_year)){
            // 번식할 수 있다면
            cnt++;            
        }
    }

    // 2. 번식이 가능한 칸에 번식하기
    for(int d=0; d<4; d++){
        int nx = x+dirs[d][0], ny = y+dirs[d][1];
        if(CanPropagatable(nx, ny, cur_year)){
            temp[nx][ny] += grid[x][y] / cnt;
        }
    }
}

pair<int, int> Find_Herbicide_Target(){
    int minX = MAX_N, minY = MAX_N, maxTree = 0;
    int cur_deleted_tree = 0;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cur_deleted_tree = 0;
            if(grid[i][j] > 0){     // 나무가 있다면
                cur_deleted_tree = grid[i][j];
                for(int d=0; d<4; d++){
                    // 해당 위치에서 네 방향 확인
                    bool IsStopped = false;
                    for(int p=1; p<=k; p++){
                        if(IsStopped)
                            continue;
                        // k만큼 퍼져나감
                        int nx = i+direction[d][0]*p, ny = j+direction[d][1]*p;
                        // 범위를 벗어나거나 벽이 있거나, 나무가 전혀 없다면
                        if(!InRange(nx, ny)) continue;  
                        if(grid[nx][ny] == 0 || grid[nx][ny] == -1){
                            IsStopped = true;
                            continue;
                        }
                        cur_deleted_tree += grid[nx][ny];
                    }
                }
            }
            if(cur_deleted_tree > maxTree){
                minX = i, minY = j, maxTree = cur_deleted_tree;
            }
        }
    }
    ans += maxTree;
    return make_pair(minX, minY);
}

void Do_Spray(int x, int y, int cur_year){    // (x,y)칸에 제초제 처리하기
    // -1인 벽이면 그 칸을 0으로 만들지는 않음
    herbicide[x][y] = cur_year+c;
    if(grid[x][y] == -1) return;
    grid[x][y] = 0;
}

void Spray_Herbicide(pair<int, int> tgt, int cur_year){       // tgt를 중심으로 대각선 방향으로 k칸 만큼 제초제 뿌리기
    // 먼저 제초제가 뿌려지는 칸에 나무 그루 0으로 만들기
    int x = tgt.first, y = tgt.second;
    Do_Spray(x,y, cur_year);
    for(int d=0; d<4; d++){
        // 해당 위치에서 네 방향 확인
        bool IsStopped = false;
        for(int p=1; p<=k; p++){
            if(IsStopped)
                continue;
            // k만큼 퍼져나감
            int nx = x+direction[d][0]*p, ny = y+direction[d][1]*p;
            if(!InRange(nx, ny)) continue;      // 범위 벗어나면 넘어가기
            if(grid[nx][ny] == 0 || grid[nx][ny] == -1){    // 벽이나 나무가 아예 없는 칸을 만나면
                IsStopped = true;       // 이후로는 중단하고
            }
            Do_Spray(nx,ny, cur_year);            // 제초제는 모든 칸에 뿌리기
        }
    }
}

void Simulate(int cur_year){
    // Step 1. 각 나무가 인접한 나무 수만큼 성장하기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0){     // 만약 나무가 있다면
                // 번식 진행
                Grow_Tree(i,j);
            }
        }
    }
    
    // Step 2. 인접한 4개 칸에 번식하기
    // 2-1. 먼저 temp 배열 초기화
    Initialize_Temp();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0){     // 나무가 있다면
                // 번식 진행
                Propagate_Tree(i,j, cur_year);
            }
        }
    }
    Copy_Temp_to_Grid();

    // Step 3. 제초제를 뿌렸을 때 가장 많이 나무가 박멸되는 칸 구하기
    pair<int, int> tgt = Find_Herbicide_Target();
    
    // Step 4. 해당 칸에 제초제 뿌리기
    Spray_Herbicide(tgt, cur_year);
}

int main() {
    // 입력 받기
    Input();

    // m년 동안 박멸 진행
    for(int i=1; i<=m; i++){
        Simulate(i);
    }

    // 출력하기
    cout << ans;    // 총 박멸한 나무의 그루 수
    return 0;
}