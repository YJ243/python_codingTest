/*
 * 2024.02.16
 * 내 풀이
 * 실수를 너무 많이 한다. . .
 * G1, G2를 보는데, G2가 G3까지 카운트해버렸음, G1과 G3의 숫자가 같아서..
 * DFS를 그전에 한 번 돌리고, BFS 탐색을 진행하도록 했음
 * 그리고 숫자가 같은데 다른 그룹인 경우 바로 return하도록 해야 했음. 아니면 틀리게 카운트 됨.
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#define MAX_N 29

using namespace std;

int n;                          // 격자 크기
int grid[MAX_N][MAX_N];         // 현재 격자
int tmp[MAX_N][MAX_N];          // 회전을 위한 격자
int visited[MAX_N][MAX_N];      // 방문 확인을 위한 배열
queue<pair<int, int> > bfs_q;   // 붙어있는 변의 수를 확인하기 위한 큐
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};     // 상, 우, 하, 좌


vector<tuple<int, int, int, int> > groups;  // (그룹의 구성 숫자, 그룹 구성 칸수, 처음 시작점) 저장
int cur_num, cnt_in_group;                  // 탐색에 필요한 변수, 그룹 구성 숫자, 그룹 구성 칸수
int curr_harmony, adjacent_side;            // 현재 조합에 대한 조화로움 값, 현재 조합에서 붙어있는 변의 개수
vector<int> selected_groups;                // 조합에 선택된 그룹 번호 (구성 숫자, 백트래킹)
int total_beauty;               // 정답


void Input(){       // 입력값을 받는 함수
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
}

void Initialize_before_search(){    // 탐색 전 방문 배열을 초기화하는 함수
    // 방문 배열 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = false;
}

bool InRange(int x, int y){         // (x,y)가 격자 내에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int val){           // (x,y)로 갈 수 있는지 확인하는 함수
    // 범위 안에 있으면서, 방문하지 않았고, val과 같은 숫자면 이동 가능
    return InRange(x,y) && !visited[x][y] && grid[x][y] == val; 
}

void dfs(int x, int y){                     // (x,y)와 같은 숫자를 가진 칸을 탐색하는 함수 
    for(int d=0; d<4; d++){
        int nx = x+dirs[d][0], ny = y+dirs[d][1];   // (x,y)에서 다음으로 이동할 좌표
        if(CanGo(nx, ny, grid[x][y])){
            visited[nx][ny] = true;
            cnt_in_group++;         // 현재 그룹에 포함되는 값의 카운트 증가
            dfs(nx,ny);
        }
    }
}

void DivideGroup(){         // 동일한 숫자가 인접해있는 그룹을 찾아서 나누는 함수
    // 그룹 초기화
    groups.clear();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 만약 방문하지 않았떤 숫자라면
            if(!visited[i][j]){
                visited[i][j] = true;
                cur_num = grid[i][j];
                cnt_in_group = 1;   // 그룹 내 처음 숫자 만남, 1로 초기화하기
                dfs(i,j);           // 해당 격자를 시작으로 탐색 진행하기
                groups.push_back(make_tuple(cur_num, cnt_in_group, i, j));
            }
        }
    }
}

void bfs(int value){        // value 값이랑 붙어있는 숫자를 탐색
    while(!bfs_q.empty()){
        pair<int, int> curr = bfs_q.front();
        bfs_q.pop();
        for(int d=0; d<4; d++){
            int nx = curr.first + dirs[d][0], ny = curr.second + dirs[d][1];
            if(CanGo(nx,ny, grid[curr.first][curr.second])){    // 같은 그룹 내 격자
                visited[nx][ny] = true;
                bfs_q.push({nx,ny});
                for(int k=0; k<4; k++){     // 그 격자와 인접해있는 4방향을 확인하면서 다른 그룹의 숫자와 같다면 증가
                    int checkX = nx+dirs[k][0], checkY = ny+dirs[k][1];
                    //visited[checkX][checkY]는 그 이전에 dfs 탐색을 한 번 더 돌아서 체크하는 다른 그룹을 표시했었음
                    if(InRange(checkX, checkY) && grid[checkX][checkY] == value && visited[checkX][checkY]){
                        adjacent_side++;
                    }
                }
            }
        }
    }
}

void Get_harmony_score(){   // 조화로움 값을 찾고, 0이 아니면 예술 점수 업데이트하기
    int num1, cnt1, x1, y1;
    tie(num1, cnt1, x1, y1) = groups[selected_groups[0]];
    int num2, cnt2, x2, y2;
    tie(num2, cnt2, x2, y2) = groups[selected_groups[1]];
    if(num1 == num2) return;    // 만약 숫자가 같은데 다른 그룹이라면 붙어있는 변의 개수가 0이니 바로 리턴

    // (x1,y1)에서 탐색을 진행하는데,
    curr_harmony = 0, adjacent_side = 0;

    Initialize_before_search();             // 탐색 전 방문 배열 초기화

    // 그룹 두번째 dfs 탐색 먼저 해놓기, 그래야 나중에 인접한 변 개수를 찾을 수 있음 
    visited[x2][y2] = true;
    dfs(x2,y2); 

    // 그룹 첫번째 bfs 탐색
    visited[x1][y1] = true;
    bfs_q.push(make_pair(x1,y1));
    // 시작점 먼저 확인
    for(int k=0; k<4; k++){
        int checkX = x1+dirs[k][0], checkY = y1+dirs[k][1];
        if(InRange(checkX, checkY) && grid[checkX][checkY] == num2 && visited[checkX][checkY]){
            adjacent_side++;
        }
    }
    bfs(num2);
    curr_harmony = (cnt1 + cnt2) * num1 * num2 * adjacent_side;
    
    if(curr_harmony != 0)   // 0이 아닐 때만 업데이트
        total_beauty += curr_harmony;
    
}

void Choose(int num){       // num번째 그룹 번호 조합을 고르는 함수
    if(selected_groups.size() == 2){
        Get_harmony_score();
        return;
    }

    for(int i=num; i<(int)groups.size(); i++){
        selected_groups.push_back(i);
        Choose(i+1);
        selected_groups.pop_back();
    }
}

void EvaluateArtistic(){     // grid 격자의 예술성을 평가하는 함수 
    // 0. 초기화 진행하기
    Initialize_before_search();
    // 1. 격자내에서 동일한 숫자가 상하좌우로 인접해있는 그룹을 찾기
    DivideGroup();
    // 2. 그룹 쌍 간의 조화로움 값이 0보다 큰 조합을 찾아서 전부 더하기
    // 2-1. 그룹 조합을 선택하기
    Choose(0);      // 0번째 그룹 숫자 선택
}

void RotateCross(){
    // 1-1. 첫번째 부분
    for(int x=0; x<n/2; x++){
        tmp[n-1-n/2][x] = grid[x][n/2];
    }
    // 1-2. 두번째 부분
    for(int y=0; y<n/2; y++){
        tmp[n-1-y][n/2] = grid[n/2][y];
    }
    // 1-3. 세번째 부분
    for(int x=n/2+1; x<n; x++){
        tmp[n-1-n/2][x] = grid[x][n/2];
    }
    // 1-4. 네번째 부분
    for(int y=n/2+1; y<n; y++){
        tmp[n-1-y][n/2] = grid[n/2][y];
    }
}

void RotateOthers(){
    // 1-1. 첫번째 부분
    for(int x=0; x<n/2; x++){
        for(int y=0; y<n/2; y++){
            tmp[y][n/2-1-x] = grid[x][y];
            
        }
    }
    // 1-2. 두번째 부분
    for(int x=0; x<n/2; x++){
        for(int y=n/2+1; y<n; y++){
            tmp[y-(n/2+1)][n-1-x] = grid[x][y];
        }
    }

    // 1-3. 세번째 부분
    for(int x=n/2+1; x<n; x++){
        for(int y=n/2+1; y<n; y++){
            tmp[y][n-1+n/2+1-x] = grid[x][y];
        }
    }
    // 1-4. 네번째 부분
    for(int x=n/2+1; x<n; x++){
        for(int y=0; y<n/2; y++){
            tmp[n/2+1+y][n-1-x] = grid[x][y];
        }
    }

}

void Rotate(){
    tmp[n/2][n/2] = grid[n/2][n/2];
    // 1. 십자 외 부분 회전하기
    RotateOthers();
    // 2. 십자 모양 회전하기
    RotateCross();
    // 3. tmp에서 원래 배열로 옮겨놓기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = tmp[i][j];
        }
    }
    
}

int main() {
    // 입력받기
    Input();    
    // 1. 초기 예술성 평가하기
    EvaluateArtistic();
    for(int i=0; i<3; i++){
        Rotate();                           // 회전하기
        EvaluateArtistic(); // 예술 점수 구하기
    }

    // 출력
    cout << total_beauty;
    return 0;
}