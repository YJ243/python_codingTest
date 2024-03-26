/*
 * 2024.03.25
 * 4시간을 잡았지만 못풀었다... 역시 3주동안 문제를 안 풀었더니 다시 원래대로 돌아갔다........................
*/
#include <iostream>
#include <vector>
#include <tuple>
#define MAX_N 12
#define MAX_K 10
using namespace std;
int n, k;
int color_grid[MAX_N][MAX_N];                       // color_grid[i][j]가 0: 흰색, 1: 빨강, 2: 파랑
vector<int> knight_grid[MAX_N][MAX_N];              // knight_grid[i][j]는 해당 칸에 있는 말의 번호
tuple<int, int, int> knight_loc[MAX_K];             // knight_loc[i]는 i번 말의 위치와 방향
int dirs[4][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};    // 0: 우, 1: 좌, 2: 상, 3: 하
int turn;                                           // 현재 턴

void Input(){               // 입력을 받는 함수
    cin >> n >> k;                                  // n: 윷놀이 판의 크기, k: 말의 개수
    for(int i=0; i<n; i++)                          // 색깔 입력받기
        for(int j=0; j<n; j++)
            cin >> color_grid[i][j];
    for(int i=0; i<k; i++){                         // k개의 말의 위치와 방향 입력받기
        int x, y, d;
        cin >> x >> y >> d;
        knight_grid[x-1][y-1].push_back(i);         // 해당 말의 번호 집어넣기
        knight_loc[i] = make_tuple(x-1,y-1,d-1);    // 0: 우, 1: 좌, 2: 상, 3: 하
    }
}

bool IsFinish(){            // 종료 조건을 확인하는 함수
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(knight_grid[i][j].size() >= 4)   // 말이 4개 이상 겹쳐지는 경우가 생기면 게임 종료
                return true;
        }
    return false;
}

bool InRange(int x, int y){ // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;  
}

bool Simulate(){    // 말을 움직이며 시뮬레이션하기, 만약 중간에 말이 4개 이상 겹쳐지면 더이상 진행 못한다는 의미로 false 반환 
    // step 1. 0번부터 k-1번 말을 차례대로 보면서 이동시키기
    for(int i=0; i<k; i++){
        if(IsFinish() || turn > 1000)
            return false;
        int x, y, d;
        tie(x, y, d) = knight_loc[i];                   // 현재 i번 말의 위치와 방향
        int nx = x + dirs[d][0], ny = y + dirs[d][1];   // i번 말이 그 다음으로 이동할 위치
        // Step 1-1. 파랑이나 격자 벗어나는 경우 
        if(!InRange(nx, ny) || color_grid[nx][ny] == 2){        // 만약 범위 안에 없거나 파란색이라면
            // 1) 이동하지 않고 방향 전환 
            if(d == 0 || d == 2) d += 1;
            else                 d -= 1;
            nx = x + dirs[d][0], ny = y + dirs[d][1];

            // 2) 만약 방향 전환하여 간 곳이 또 파란색이라면
            if(color_grid[nx][ny] == 2){
                // 방향 전환 후 이동하지 않고 가만히 있는다.
                knight_loc[i] = make_tuple(x, y, d);
            }
            // 3) 만약 방향 전환하여 갈 곳이 파란색이 아니면
            else{
                // 3-1) 먼저 해당 말의 방향 위치, 방향 업데이트
                int cur_idx = 0;
                knight_loc[i] = make_tuple(nx, ny, d);
                // 3-2) 해당 칸의 말을 위에서부터 옆 칸으로 옮기기
                for(int j=0; j<(int)knight_grid[x][y].size(); j++){
                    if(knight_grid[x][y][j] == i){
                        cur_idx = j;            
                        for(int k=cur_idx; k <(int)knight_grid[x][y].size(); k++){
                            // knight_grid와 knight_loc모두 바꿔주어야 한다.
                            int knight_num = knight_grid[x][y][k];
                            int knight_dir = 0;
                            knight_grid[nx][ny].push_back(knight_num);                      // 이동하려는 칸으로 번호 옮겨주기
                            tie(ignore, ignore, knight_dir) = knight_loc[knight_num];
                            knight_loc[knight_num] = make_tuple(nx, ny, knight_dir);        // 말의 정보 업데이트
                        }
                        knight_grid[x][y].erase(knight_grid[x][y].begin()+cur_idx, knight_grid[x][y].end());
                        continue;
                    }
                }
            }
        }
        
        // Step 1-2. 흰색이면 해당 칸으로 이동
        else if(color_grid[nx][ny] == 0){
            int cur_idx = 0;
            knight_loc[i] = make_tuple(nx, ny, d);
            for(int j=0; j<(int)knight_grid[x][y].size(); j++){
                if(knight_grid[x][y][j] == i){
                    cur_idx = j;
                    for(int k=cur_idx; k<(int)knight_grid[x][y].size(); k++){
                        // knight_grid와 knight_loc모두 바꿔주어야 한다.
                        int knight_num = knight_grid[x][y][k];
                        int knight_dir = 0;
                        knight_grid[nx][ny].push_back(knight_num);                      // 이동하려는 칸으로 번호 옮겨주기
                        tie(ignore, ignore, knight_dir) = knight_loc[knight_num];
                        knight_loc[knight_num] = make_tuple(nx, ny, knight_dir);        // 말의 정보 업데이트
                    }
                    knight_grid[x][y].erase(knight_grid[x][y].begin()+cur_idx, knight_grid[x][y].end());
                    continue;
                }
            }
        }
        // Step 1-3. 빨간색이면 순서를 뒤집어서 이동
        else{
            vector<int> tmp;
            for(int j=(int)knight_grid[x][y].size()-1; j >= 0; j--)
                tmp.push_back(knight_grid[x][y][j]);
            knight_grid[x][y] = tmp;
            int cur_idx = 0;
            knight_loc[i] = make_tuple(nx, ny, d);
            for(int j=0; j<(int)knight_grid[x][y].size(); j++){
                if(knight_grid[x][y][j] == i){
                    cur_idx = j;
                    for(int k=cur_idx; k<(int)knight_grid[x][y].size(); k++){
                        // knight_grid와 knight_loc모두 바꿔주어야 한다.
                        int knight_num = knight_grid[x][y][k];
                        int knight_dir = 0;
                        knight_grid[nx][ny].push_back(knight_num);                      // 이동하려는 칸으로 번호 옮겨주기
                        tie(ignore, ignore, knight_dir) = knight_loc[knight_num];
                        knight_loc[knight_num] = make_tuple(nx, ny, knight_dir);        // 말의 정보 업데이트
                    }
                    knight_grid[x][y].erase(knight_grid[x][y].begin()+cur_idx, knight_grid[x][y].end());
                    continue;
                }
            }
        }
    }
    return true;
}

int main() {
    // 입력받기:
    Input();   
    // 시뮬레이션 시작
    while(true){   
        turn++;
        if(IsFinish() || turn > 1000)
            break;
        if(!Simulate()){
            break;
        }

        
    }
    if(turn > 1000)
        turn = -1;
    cout << turn;
    return 0;
}