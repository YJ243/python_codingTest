/*
 * 2024.04.03
 * 포탑부수기
*/
#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>

#define NM 10

using namespace std;

int N, M, K;                // 격자 크기, 턴수
int power[NM][NM];          // 포탑 공격력
int attack_time[NM][NM];    // 포탑 공격 시간
bool IsRelated[NM][NM];     // 이번 턴에 공격과 관련이 되었는지

pair<int, int> attacker;    // 공격자 좌표
pair<int, int> target;      // 공격 대사 좌표

queue<pair<int, int> > q;   // 탐색을 위한 큐
pair<int, int> from[NM][NM];    // from[i][j]: (i,j)는 어디에서 왔는가?
bool visited[NM][NM];       // 방문 확인
int dirs[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{-1,-1},{-1,1},{1,-1},{1,1}};    // 우하좌상 우선순위 + 대각선

void Input(){
    cin >> N >> M >> K;     // 격자 크기, 턴수
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> power[i][j];     // 격자 정보 넣기
        }
    }
}

bool IsFinish(){
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(power[i][j] > 0)
                cnt++;
        }
    }
    if(cnt == 1){
        return true;
    }
    else
        return false;
}

void FindAttacker(){        // 공격자를 찾는 함수
    // 공격자의 공격력, 공격 시간, 좌표
    int minPower = INT_MAX, maxTime = -1, maxI = -1, maxJ = -1;     
    for(int sum = N+M-2; sum >= 0; sum--){
        for(int j = M-1; j >= 0; j--){
            int i = sum-j;
            if(i < 0 || i >= N) continue;
            if(power[i][j] == 0) continue;
            if(make_pair(minPower, -maxTime) > make_pair(power[i][j], -attack_time[i][j])){
                minPower = power[i][j], maxTime = attack_time[i][j], maxI = i, maxJ = j;
            }
        }
    }
    
    attacker = make_pair(maxI, maxJ);
}

void FindTarget(){          // 공격 대상을 찾는 함수
    // 공격대상의 공격력, 공격 시간, 좌표
    int maxPower = INT_MIN, minTime = INT_MAX, minI = INT_MAX, minJ = INT_MAX;     
    for(int sum = 0; sum < N+M-1; sum++){
        for(int j = 0; j < M; j++){
            int i = sum-j;
            if(i < 0 || i >= N) continue;
            if(power[i][j] == 0) continue;
            if(make_pair(maxPower, -minTime) < make_pair(power[i][j], -attack_time[i][j])){
                maxPower = power[i][j], minTime = attack_time[i][j], minI = i, minJ = j;
            }
        }
    }
    target = make_pair(minI, minJ);
}

void Initialize_before_search(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            visited[i][j] = false;      // 방문 여부 false
            IsRelated[i][j] = false;    // 현재 턴에 공격 관련 false
        }
    }
    IsRelated[attacker.first][attacker.second] = true;  // 공격자 공격과 관련있다 표시
}

bool CanGo(int x, int y){       // (x, y)로 이동할 수 있는지 확인하는 함수
    return !visited[x][y] && power[x][y] > 0;
}

void bfs(){
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        int cx = curr.first, cy = curr.second;
        for(int d=0; d<4; d++){
            int nx = (cx + dirs[d][0]+N)%N, ny = (cy + dirs[d][1]+M)%M;
            if(CanGo(nx, ny)){
                visited[nx][ny] = true;
                q.push(make_pair(nx, ny));
                from[nx][ny] = make_pair(cx, cy);
            }
        }
    }
}

void PowerAttack(int x, int y, int p){      // (x,y)에 p만큼 공격하기
    power[x][y] = max(power[x][y] - p , 0); // 공격력이 0보다 작아지면 0으로 만들기
    IsRelated[x][y] = true;
}

void DoLaser(){     // 실제로 공격자에서 공격대상으로 레이저 공격하기
    int aX = attacker.first, aY = attacker.second;      // 공격자 좌표
    int tX = target.first, tY = target.second;          // 공격 대상 좌표

    while(tX != aX || tY != aY){
        int p = power[aX][aY] / 2;          // 공격력 절반
        if(make_pair(tX, tY) == target)     // 만약 공격대상이면 공격자의 공격력만큼 피해 입히기
            p = power[aX][aY];
        PowerAttack(tX, tY, p);             // (tX, tY)에 p만큼 공격하기
        pair<int, int> next = from[tX][tY]; 
        tX = next.first, tY = next.second;  // 다음 좌표
    } 
}

bool tryLaser(){    // 공격자에서 공격대상까지 최단거리로 레이저 공격 시도하기
    // 1. 탐색 전 초기화하기
    Initialize_before_search();
    // 2. 공격자에서 공격 대상까지 최단거리 찾기
    int aX = attacker.first, aY = attacker.second;      // 공격자 좌표
    int tX = target.first, tY = target.second;          // 공격 대상 좌표
    visited[aX][aY] = true;         // 공격자 방문 표시
    q.push(make_pair(aX, aY));      // 공격자 좌표 큐에 넣기
    bfs();                          // 탐색 진행
    if(!visited[tX][tY])            // 만약 공격 대상까지 도달하지 못한다면 
        return false;               // laser 공격 할 수 없다고 표시하기
    
    // 3. 실제 레이저 공격하기
    DoLaser();
    return true;
}

void DoBomb(){
    int tX = target.first, tY = target.second;
    int p = power[attacker.first][attacker.second]/2;
    for(int d=0; d<8; d++){
        int nx = (tX + dirs[d][0] + N) % N, ny = (tY + dirs[d][1]+M)%M;
        if(power[nx][ny] != 0 && make_pair(nx, ny) != attacker){
            // 만약 공격할 수 있는 곳이라면
            
            PowerAttack(nx, ny, p);
        }
    }
    // 마지막 공격 대상도 공격하기
    PowerAttack(tX, tY, power[attacker.first][attacker.second]);
}

void Repair(){      // 부서지지 않은 포탑 중 공격과 무관했던 포탑 공격력 1씩 올리기
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(power[i][j] == 0) continue;      // 부서진 포탑이면 넘어가기
            if(IsRelated[i][j]) continue;       // 해당 턴에 공격과 관련있으면 넘어가기
            power[i][j]++;
        }
    }
}

void Simulate(int turn){
    // Step 1. 공격자 선정
    FindAttacker();
    // Step 2. 공격 대상 선정
    FindTarget();
    // 공격자 핸디캡 적용하기
    power[attacker.first][attacker.second] += N+M;
    
    // Step 3. 공격하기
    attack_time[attacker.first][attacker.second] = turn;    // 공격한 시점 표시하기
    if(!tryLaser()){    // 만약 레이저 공격이 안된다면
        DoBomb();       // 포탄 공격하기
    }

    // Step 4. 포탑 정비하기
    Repair();
    
}

int main() {
    // 입력 받기:    
    Input();
    for(int i=1; i<=K; i++){     // K번의 턴 동안 공격 진행하기
        if(IsFinish())      // 만약 부서지지 않은 포탑이 1개가 된다면
            break;          // 그 즉시 중지하기
        Simulate(i);         // 시뮬레이션 진행
    }
    FindTarget();
    cout << power[target.first][target.second];
    return 0;
}