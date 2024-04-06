/*
 * 2024.04.05
 * 내 풀이
*/

#include <iostream>
#include <vector>

#define MAX_N 29

using namespace std;
int n;
int grid[MAX_N][MAX_N];             // 예술성 격자
int tmp_grid[MAX_N][MAX_N];         // 회전을 위한 격자

int group_grid[MAX_N][MAX_N];   // 그룹 번호를 저장하는 격자
int cur_group_num;              // 현재 탐색을 진행하는 그룹 번호
int coor_score;                 // 조화로움 점수
int artist_score;               // 조화로움 점수의 합인 예술 점수
int adjacentCnt;                // 인접한 변의 수

int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};   // 방향

bool visited[MAX_N][MAX_N];                 // 방문 여부
int cur_cnt;                                // 현재 탐색하는 그룹 내 멤버 수
vector<int> cnt_in_group;                   // 각 그룹마다 칸의 수를 세주기
vector<pair<int, int> > start_in_group;     // 각 그룹의 처음 시작점

void Input(){
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }
}

void Initialize_before_search(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;
        }
    }
    cur_group_num = -1;              // 그룹 넘버 초기화하기
    cnt_in_group.clear();
    start_in_group.clear();
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int val){
    return InRange(x, y) && !visited[x][y] && grid[x][y] == val;
}

void dfs(int x, int y,int val){
    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(CanGo(nx, ny, val)){
            visited[nx][ny] = true;
            group_grid[nx][ny] = cur_group_num;
            cur_cnt++;
            dfs(nx, ny, val);
        }
    }
}

void SeparateGroups(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!visited[i][j]){     // 만약 새로운 그룹을 만났다면
                cur_group_num++;    // 그룹 번호 증가
                cur_cnt = 1;        // 그룹 내 원소 개수 1로 초기화
                visited[i][j] = true;   // 방문 표시
                group_grid[i][j] = cur_group_num;   // 그룹 격자에 현재 그룹 번호 표시
                dfs(i, j, grid[i][j]);              // 탐색 진행
                cnt_in_group.push_back(cur_cnt);
                start_in_group.push_back(make_pair(i, j));
            }
        }
    }
}

void dfs_for_adjacent(int x, int y, int nextNum){
    // (x,y)에서 확인하기
    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(InRange(nx, ny) && group_grid[nx][ny] == nextNum){
            adjacentCnt++;
        }
    }
    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(InRange(nx, ny) && !visited[nx][ny] && (group_grid[nx][ny] == group_grid[x][y])){
            visited[nx][ny] = true;
            dfs_for_adjacent(nx, ny, nextNum);
        }
    }
}

void FindAdjacentCnt(int i, int j){  // i번 그룹과 j번 그룹이 맞닿아있는 변의 수 구하기
    // 1. i번 그룹에서 j번 그룹으로 도달할 수 있는 개수 세기
    int ix = start_in_group[i].first, iy = start_in_group[i].second;
    for(int x=0; x<n; x++){     // 먼저 방문 배열 초기화하기
        for(int y=0; y<n; y++){
            visited[x][y] = false;
        }
    }
    adjacentCnt = 0;
    visited[ix][iy] = true;

    dfs_for_adjacent(ix, iy, j);    // (ix, iy)에서 시작하는 그룹이 j번 그룹에 도달할 수 있는 카운트 세기
}

void GetArtistScore(){
    // Step 1. 동일한 숫자가 상하좌우로 인접해있는 그룹 찾기
    Initialize_before_search();     // 탐색 전 초기화하기
    SeparateGroups();

    // Step 2. 조화로움 구하기
    for(int i=0; i<(int)cnt_in_group.size(); i++){
        for(int j=i+1; j<(int)cnt_in_group.size(); j++){
            // 그룹 a와 b의 조화로움 
            // = (그룹 a에 속한 칸의 수 + 그룹 b에 속한 칸의 수 ) 
            // x 그룹 a를 이루고 있는 숫자 값 x 그룹 b를 이루고 있는 숫자 값 
            // x 그룹 a와 그룹 b가 서로 맞닿아 있는 변의 수
            
            coor_score = (cnt_in_group[i] + cnt_in_group[j]) 
            * grid[start_in_group[i].first][start_in_group[i].second]
            * grid[start_in_group[j].first][start_in_group[j].second];
            
            FindAdjacentCnt(i, j);
            coor_score *= adjacentCnt;
            artist_score += coor_score;
        }
    }

}
void RotateCross(){
    tmp_grid[n/2][n/2] = grid[n/2][n/2];    // 가운데 부분 저장
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            tmp_grid[n-1-j][i] = grid[i][j];
        }
    }
}

void RotateSquare(){
    // 2-1. 1번영역
    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            tmp_grid[j][n/2-1-i] = grid[i][j];
        }
    }
    // 2-2. 2번 영역
    for(int i=n/2+1; i < n; i++){
        for(int j=0; j<n/2; j++){
            tmp_grid[j+n/2+1][n-1-i] = grid[i][j];
        }
    }
    // 2-3. 3번 영역
    for(int i=0; i<n/2; i++){
        for(int j=n/2+1; j < n; j++){
            tmp_grid[j-(n/2+1)][n-1-i] = grid[i][j];
        }
    }
    // 2-4. 4번 영역
    for(int i=n/2+1; i<n; i++){
        for(int j=n/2+1; j<n; j++){
            tmp_grid[j][n-(i-n/2)] = grid[i][j];
        }
    }

}
void RotateGrid(){

    // Step 1. 십자 모양 회전하기
    RotateCross();
    // Step 2. 4개 정사각형 회전하기
    RotateSquare();
    // Step 3. tmp에서 grid로 옮기기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = tmp_grid[i][j];
        }
    }

}

int main() {
    // 입력 받기:
    Input();

    // 초기 ~ 3회전 이후 예술점수 합 구하기
    GetArtistScore();
    int ans = 0;
    ans += artist_score;

    for(int i=0; i<3; i++){
        artist_score = 0;
        RotateGrid();
        GetArtistScore();
        ans += artist_score;
    }
    cout << ans;
    return 0;
}