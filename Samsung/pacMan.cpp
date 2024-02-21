/*
 * 2024.02.20
 * 팩맨
*/

#include <iostream>
#include <tuple>
#include <vector>

#define MAX_N 4
using namespace std;

int m, t;       // m: 몬스터 마리 수, t: 진행되는 턴 수
pair<int, int> pacMan;  // 팩맨의 위치
vector<int> monster[MAX_N][MAX_N];      // 몬스터의 방향을 해당 위치에 저장
vector<int> temp[MAX_N][MAX_N];         // 몬스터가 이동하는 중간 정보를 저장
vector<int> egg[MAX_N][MAX_N];          // 부화될 알의 방향을 해당 위치에 저장
vector<int> dead[MAX_N][MAX_N];         // 시체가 유지되는 시간을 해당 위치에 저장
// 방향은 위를 시작으로 반시계방향으로 돌아가면서 8개 방향을 저장
int dirs[8][2] = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
int direction[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};   // 상, 좌, 하, 우 우선순위
vector<int> selected_direction;         // 팩맨이 이동할 위치 찾아갈 때 쓰는 배열
vector<int> final_direction;            // 팩맨이 이동할 최종 위치
int MaxMonster;

void Input(){       // 입력을 받는 함수
    cin >> m >> t;                  // 몬스터 마리수와 턴의 수
    int r, c, d;               
    cin >> r >> c;                  // 팩맨 위치 
    pacMan = make_pair(r-1, c-1);
    for(int i=0; i<m; i++){         // 몬스터의 위치와 방향 정보 저장
        cin >> r >> c >> d;
        monster[r-1][c-1].push_back(d-1); 
    }
}

void Output(){      // 살아남은 몬스터를 출력하는 함수
    int ans = 0;
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            ans += monster[i][j].size();
        }
    }
    cout << ans << '\n';
}

void TryCopyMonster(){      // 몬스터 복제를 시도하는 함수, 알 생성하기
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            egg[i][j] = monster[i][j];
        }
    }
}

void Initialize_temp(){
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            temp[i][j].clear();
        }
    }
}

bool InRange(int x, int y){     // (x,y)가 범위 안에 있는지 확인하는 함수 
    return 0 <= x && x < MAX_N && 0 <= y && y < MAX_N;
}

bool CanGo(int x, int y){   // 몬스터가 (x,y)로 이동할 수 있는지 확인하는 함수
    // 범위 안에 있고, 몬스터 시체가 없으며, 팩맨이 없는 경우 이동 가능
    return InRange(x, y) && dead[x][y].size() == 0 && pacMan != make_pair(x, y);
}

void MoveMonster(int x, int y){        // (x,y)에 있는 몬스터 이동
    for(int k=0; k < (int)monster[x][y].size(); k++){
        // (x,y)에 있는 몬스터를 차례로 보면서 이동하기
        int d = monster[x][y][k];   // 현재 보고 있는 몬스터의 이동 방향
        int nx = -1, ny = -1;
        for(int dir = 0; dir < 8; dir++){
            int new_d = (d + dir) % 8;
            if(CanGo(x + dirs[new_d][0], y + dirs[new_d][1])){    // 만약 다음 위치로 이동 가능하다면
                nx = x + dirs[new_d][0], ny = y + dirs[new_d][1]; // 다음 위치 업데이트
                d = new_d;
                break;
            }
        }
        if(nx == -1 && ny == -1){
            // 만약 여덟방향을 다 돌았는데도 불구하고, 모두 움직일 수 없다면 해당 위치에 두기
            temp[x][y].push_back(d);
        }
        else{
            // 만약 움직일 수 있다면 해당 위치에 이동시키기
            temp[nx][ny].push_back(d);  // (nx, ny)위치에 d방향을 가진 몬스터 집어넣기
        }
    }
}

void CheckRoute(){                  // 해당 루트가 갈 수 있는지 확인하고, 최대 몬스터를 얻을 수 있다면 업데이트
    int curr = 0;
    int x = pacMan.first, y = pacMan.second;
    bool visited[MAX_N][MAX_N] = {false,};
    visited[x][y] = true;
    for(int k=0; k<3; k++){
        int nx = x + direction[selected_direction[k]][0];
        int ny = y + direction[selected_direction[k]][1];
        if(!InRange(nx, ny))    // 이동하는 과정에 격자 바깥을 나가는 경우 고려하지 않음
            return;
        if(!visited[nx][ny]){
            visited[nx][ny] = true;
            curr += temp[nx][ny].size();   // 다음 위치에 있는 몬스터 개수 추가
        }
        x = nx, y = ny;         // 위치 업데이트
    }
    if(MaxMonster < curr){
        // 만약 현재 먹은 몬스터가 제일 많다면 위치 업데이트
        final_direction = selected_direction;
        MaxMonster = curr;
    }
}

void Initialize_before_PacManMove(){            // 팩맨 이동 전 변수 초기화하는 함수 
    selected_direction.clear();
    final_direction.clear();
    MaxMonster = -1;
}

void FindDirectionforPacMan(int idx){           // 팩맨이 이동할 idx번째 방향을 찾는 함수
    if((int)selected_direction.size() == 3){
        CheckRoute();
        return;
    }
    for(int i=0; i<4; i++){
        selected_direction.push_back(i);
        FindDirectionforPacMan(idx+1);
        selected_direction.pop_back();
    }
}

void UpdatePacMan(int turn){    // turn 방향으로 팩맨이 이동하면서 시체 만들기
    int x = pacMan.first, y = pacMan.second;
    for(int k=0; k<3; k++){
        int nx = x + direction[final_direction[k]][0];
        int ny = y + direction[final_direction[k]][1];
        if(temp[nx][ny].size() > 0){
            // 만약 몬스터가 있다면
            for(int l=0; l<(int)temp[nx][ny].size(); l++){
                dead[nx][ny].push_back(turn+2); // 시체는 소멸되기까지 현재 턴부터 2턴 필요
            }
            temp[nx][ny].clear();       // 현재 위치에 있는 몬스터 없애기
        }
        x = nx, y = ny;         // 위치 업데이트
    }
    pacMan = make_pair(x, y);
}

void MovePacMan(int turn){      // 팩맨을 총 3칸 이동시키는 함수, 몬스터를 가장 많이 먹을 수 있는 방향으로 이동시키기
    // Step 1. 먼저 팩맨이 이동할 방향 정하기
    Initialize_before_PacManMove();
    FindDirectionforPacMan(0);
    // Step 2. 해당 방향으로 이동하며 시체 남기기
    UpdatePacMan(turn);

}

void DestroyDead(int turn){         // 시체를 사멸하는 함수 
    vector<int> temp_dead[MAX_N][MAX_N];
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            temp_dead[i][j].clear();
            if(dead[i][j].size() > 0){     // 만약 사체가 있고
                for(int k=0; k<(int)dead[i][j].size(); k++){
                    if(dead[i][j][k] > turn){  // 아직 소멸되지 않는 사체라면
                        temp_dead[i][j].push_back(dead[i][j][k]);
                    }
                }
            }
        }
    }
    // 다시 temp_dead를 dead로 복사
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            dead[i][j] = temp_dead[i][j];
        }
    }
}

void DoCopyMonster(){       // 몬스터 복제 완성하는 함수
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            if(egg[i][j].size() > 0){
                // 만약 알이 있다면
                for(int k=0; k < (int)egg[i][j].size(); k++){
                    monster[i][j].push_back(egg[i][j][k]);      // 해당 방향을 가진 몬스터 넣기
                }
            }
            egg[i][j].clear();      // 그리고 알 비우기
        }
    }
}

void Simulate(int turn){
    // Step 1. 몬스터 복제 시도
    TryCopyMonster();
    // Step 2. 몬스터 이동
    Initialize_temp();      // temp 초기화
    for(int i=0; i<MAX_N; i++)
        for(int j=0; j<MAX_N; j++)
            if(monster[i][j].size() > 0)
                MoveMonster(i,j);          // (i,j)에 있는 몬스터 이동하기
            
    // Step 3. 팩맨 이동하면서 시체 만들기
    // 3-1. 팩맨 이동
    MovePacMan(turn);
    // 3-2. 소멸되고 난 이후에 temp에서 monster로 복제
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            monster[i][j] = temp[i][j];
        }
    }
    // Step 4. 몬스터 사체 소멸
    DestroyDead(turn);

    // Step 5. 몬스터 복제 완성
    DoCopyMonster();
}

int main() {
    // 입력:
    Input();

    for(int turn=1; turn <= t; turn++){
        // t개의 턴에 대해서 시뮬레이션 진행
        Simulate(turn);
    }
    // 출력:
    Output();
    return 0;
}