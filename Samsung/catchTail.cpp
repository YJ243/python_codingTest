/*
 * 2024.02.18
 * 내 풀이
 * 5시간 걸려서 품... 계속 중간에 실수때문에 디버깅하느라 시간이 길어짐
 * 처음부터 설계를 잘해야 한다!!!!!!!!!!!!!
 * 실수 1: 공을 받은 팀만 머리와 꼬리가 바뀌는데, 나는 처음에 다 바뀐다고 함 -> 문제를 제대로 읽기!!! 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#define MAX_N 20
#define MAX_M 5

using namespace std;
int n, m, k;                                    // n: 격자 크기, m: 팀 개수, k: 라운드 수
int grid[MAX_N][MAX_N];                         // 격자 정보
int visited[MAX_N][MAX_N];                      // 방문 확인 배열
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};   // 방향 정보
int team_number = -1;                           // 팀의 번호 (0부터 시작)
int total_score;                                // 정답, 전체 점수 합

int team[MAX_N][MAX_N];                         // 격자 내에서 각 팀의 번호 저장
pair<int, int> team_head[MAX_N];                // 각 팀의 머리 좌표
pair<int, int> team_tail[MAX_M];                // 각 팀의 꼬리 좌표
int loc_dist;                                   // 현재 보고 있는 팀의 머리에서 얼마나 떨어져 있는지

void Input(){                   // 입력값을 받는 함수
    cin >> n >> m >> k;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
}

bool InRange(int x, int y){     // (x,y)가 범위 안에 있는지 확인하는 함수 
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){       // (x,y)가 범위 안에 있고, 아직 방문하지 않았으며, 경로가 맞는 경우 갈 수 있음
    return InRange(x, y) && !visited[x][y] && grid[x][y] != 0; 
}

void dfs(int x, int y){         // 초기 경로를 만들기 위한 탐색 함수
    for(int d=0; d<4; d++){
        // (x,y)와 연결되어 있는 팀 확인
        int nx = x+dirs[d][0], ny = y+dirs[d][1];
        if(CanGo(nx, ny)){              // 현재 보고 있는 팀의 경로에 있다면
            if(grid[nx][ny] == 3)       // 꼬리는 따로 저장 
                team_tail[team_number] = make_pair(nx, ny);
            visited[nx][ny] = true;     // 방문 처리
            team[nx][ny] = team_number; // team 번호 저장
            dfs(nx, ny);                // (nx, ny)를 시작으로 탐색 진행 
        }
    }
}

void MakeTeamNumberGrid(){      // 맨 처음에 어떤 팀으로 이루어졌는지 나타내는 team 격자 초기화하기
    for(int i=0; i<n; i++){     // 팀의 경로가 아닌 부분은 -1
        for(int j=0; j<n; j++){
            team[i][j] = -1;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 1 && !visited[i][j]){  // 머리를 찾았다면
                team_number++;                      // 팀 넘버 1 증가시킴
                // 1-1. 방문하지 않은 머리 찾기
                team_head[team_number] = make_pair(i,j);    // 머리 저장
                visited[i][j] = true;                       // 방문 표시
                team[i][j] = team_number;                   // 경로에 팀 번호 표시
                // 1-2. 연결되어 있는 꼬리 찾기 위해 탐색 진행
                dfs(i,j);
            }
        }
    }
}

void Initialize_visited(){      // 방문 배열을 초기화하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            visited[i][j] = false;  
        }
    }
}

void MoveTeam(){                // m 개의 팀을 하나씩 보면서 움직이는 함수
    for(int i=0; i<m; i++){
        int hX = team_head[i].first, hY = team_head[i].second;
        int tX = team_tail[i].first, tY = team_tail[i].second;

        // 2-1. 먼저 꼬리 이동시키기
        for(int d=0; d<4; d++){
            int nx = tX+dirs[d][0], ny = tY+dirs[d][1];
            // 꼬리와 맞닿아 있는 몸통으로 꼬리 이동
            if(InRange(nx, ny) && grid[nx][ny] == 2 && team[nx][ny] == i){
                // 범위 안에 있고, 같은 팀의 몸통이라면
                grid[nx][ny] = 3;                   // 그 다음 위치를 꼬리로
                grid[tX][tY] = 4;                   // 원래 꼬리 위치를 이동선으로
                team_tail[i] = make_pair(nx,ny);    // 꼬리 위치 업데이트
                break; 
            }
        }

        // 2-2. 그 다음 머리 이동시키기
        for(int d=0; d<4; d++){
            int nx = hX+dirs[d][0], ny = hY+dirs[d][1];
            if(InRange(nx, ny) && grid[nx][ny] == 4 && team[nx][ny] == i){
                // 범위 안에 있고, 같은 팀의 이동 선상이라면
                grid[nx][ny] = 1;                   // 그 다음 위치를 머리로
                grid[hX][hY] = 2;                   // 원래 위치를 몸통으로
                team_head[i] = make_pair(nx,ny);    // 머리 위치 업데이트하기
                break;
            }
        }
    }
}

bool IsPerson(int x){       // 해당 위치에 사람이 있는지 확인 
    return x == 3 || x == 2 || x == 1;
}

void Swich_head_and_tail(int team_num){     // team_num의 머리와 꼬리 바꾸기 
    int hX = team_head[team_num].first, hY = team_head[team_num].second;
    int tX = team_tail[team_num].first, tY = team_tail[team_num].second;
    grid[hX][hY] = 3;   // 머리를 꼬리로
    team_head[team_num] = make_pair(tX, tY);
    grid[tX][tY] = 1;   // 꼬리를 머리로
    team_tail[team_num] = make_pair(hX, hY);
    
}

queue<tuple<int, int, int> > q;     // (x,y), d: (x,y) 현재 보고 있는 좌표가 머리로부터 d만큼 떨어져 있음 

void find_dist(int toX, int toY){   // 공을 맞은 (toX, toY)까지 탐색 진행
    while(!q.empty()){
        int x, y, dist;
        tie(x, y, dist) = q.front();
        q.pop();

        if(x == toX && y == toY){   // 찾았다면 loc_dist에 순서 넣고 리턴
            loc_dist = dist;
            return;
        }
        for(int d=0; d<4; d++){
            int nx = x+dirs[d][0], ny = y+dirs[d][1];
            if(InRange(nx, ny) && !visited[nx][ny] && (grid[nx][ny] != 0 && grid[nx][ny] != 4) && team[x][y] == team[nx][ny]){
                visited[nx][ny] = true;
                q.push(make_tuple(nx, ny, dist+1));
            }
        }
    }
}

void UpdateScore(int x, int y){     // 공과 최초로 만난 (x,y) 위치의 사람이 들어간 팀의 점수를 업데이트하기
    loc_dist = 1;       // 머리부터 해당 (x,y)까지 몇번째인지 1로 초기화
    // 머리에서 (x,y) 위치의 사람까지 몇번 가야하는지 탐색하기
    Initialize_visited();           // 방문 배열 초기화
    while(!q.empty())   q.pop();    // 큐 비우기

    // (x,y)가 속해있는 그룹의 머리를 찾아서 bfs탐색 수행
    // 1. 현재 위치가 속해있는 그룹 번호
    int curr_group_num = team[x][y];
    // 2. 현재 그룹의 머리 좌표 
    int hX = team_head[curr_group_num].first;
    int hY = team_head[curr_group_num].second;
    visited[hX][hY] = true;     // 머리 방문 처리
    for(int d=0; d<4; d++){
        int nx = hX+dirs[d][0], ny = hY+dirs[d][1];
        if(InRange(nx, ny) && !visited[nx][ny] && grid[nx][ny] == 2 && team[nx][ny] == team[x][y]){
            // 3. 머리와 붙어있는 2가 있는 곳을 시작으로 탐색
            visited[nx][ny] = true;         // 첫 몸통 방문 처리
            q.push(make_tuple(nx, ny, 2));  // 큐에 넣기
            find_dist(x, y);                // 경로 탐색
            break; 
        }
    }

    total_score += loc_dist * loc_dist;     // 점수 업데이트

    // 머리와 꼬리 바꾸기
    Swich_head_and_tail(team[x][y]);        // 공을 맞은 그룹의 머리와 꼬리 바꾸기

}

void ThrowBall(int group_num, int idx){     // grou_num번째 묶음의 idx번째 줄에서 공을 던지는 함수
    if(group_num == 0){
        // 위에서부터 idx번
        for(int j=0; j<n; j++){
            if(IsPerson(grid[idx][j])){
                UpdateScore(idx, j);
                break;
            }
        }
    }
    else if(group_num == 1){
        for(int i=n-1; i>=0; i--){
            if(IsPerson(grid[i][idx])){
                UpdateScore(i, idx);
                break;
            }
        }
    }
    else if(group_num == 2){
        for(int j=n-1; j>=0; j--){
            if(IsPerson(grid[n-1-idx][j])){
                UpdateScore(n-1-idx, j);
                break;
            }
        }
    }
    else{   // group_num == 3
        for(int i=0; i<n;i++){
            if(IsPerson(grid[i][n-1-idx])){
                UpdateScore(i, n-1-idx);
                break;
            }
        }
    }
}


void Simulate(int round){        // 시뮬레이션을 진행하는 함수
    // Step 0. 탐색 전 방문 배열 초기화
    Initialize_visited();

    // 1. 각 팀 한 칸씩 이동하기
    MoveTeam();

    // 2. 공이 던져지는 선에 최초로 만나는 사람 점수 추가하기
    int group_num = (round / n)%4;      // 방향 선택
    int start_idx = round % n;          // 해당 방향의 몇 번째 줄인지 선택 
    ThrowBall(group_num, start_idx);    // round에 따라 공 던지기
}


int main() {
    // 입력 받기:
    Input();    
    // 초기 경로를 위해 연결되어 있는 팀의 머리와 꼬리 찾기
    MakeTeamNumberGrid();

    // k번의 턴에 대해 시뮬레이션 진행
    for(int cur_turn=0; cur_turn < k; cur_turn++){
        Simulate(cur_turn);
    }

    // 출력:
    cout << total_score;
    return 0;
}