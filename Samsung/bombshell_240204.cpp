/*
 * 2024.02.04
 * 여전히 실수를 많이 함
 * 중간 중간 함수 만들고 출력하면서 맞게 나오는지 계속 확인하기
 * 실수 1: 다 고쳐놓고선 마지막에 우/하/좌/상 우선순위를 우/하/상/좌로 해서 틀림
 * 실수 2: 함수 원형으로 다써놓고 bool로 리턴하는 것은 return 값을 써줘야 하는데 안그래서 중간에 출력할 때 오류남
 * 실수 3: attacker를 고를 때 grid[i][j] == 0이면 continue하도록 해야하는데 빼먹어서 0인 얘기 atk가 됨
 * 실수 4: sum <=n+m-2인데 n+m+2로 씀 
 * 실수 5: 공격대상에 피해 입힐 떄 만약 음수가 된다면 0이 되도록 해야하는데, 이부분을 처리하지 않아서 음수가 되고도 터지지 않은 포탑으로 됨
 * 실수 6: 레이저 공격 시 경로 따라갈 때 while(nx != atk.first && ny != atk.second) 이렇게 해서 틀림, 둘다 달라야 한다고 해서
*/
#include <iostream>
#include <queue>
#include <tuple>

#define MAX_NM 10
#define MAX_K 5000

using namespace std;

int n, m, k;                        // n, m: 격자 크기, k: 턴 수
int grid[MAX_NM][MAX_NM];           // 포탑을 나타내는 격자 => 0: 부서진 포탑
int atk_time[MAX_NM][MAX_NM];       // 각 포탑의 공격 시간
bool isRelated[MAX_NM][MAX_NM];     // 이번 턴에 공격에 관련되어 있는지

pair<int, int> atk;                 // 공격자 좌표
pair<int, int> tgt;                 // 공격 대상 좌표

queue<pair<int, int> > q;           // bfs 탐색을 위한 큐
bool visited[MAX_NM][MAX_NM];       // 레이저 공격 시도 전 bfs 탐색을 위한 방문 체크 배열
pair<int, int> from[MAX_NM][MAX_NM];// 레이저 공격 시도 전 bfs 탐색을 진행하면서 어디에서 왔는지 기록
// 우/하/좌/상 우선순위, 나머지 4개는 포탄 공격을 위한 대각선 방향
int dirs[8][2] = {{0,1},{1,0},{0,-1},{-1,0},{-1,-1},{-1,1},{1,-1},{1,1}};


void Input(){           // 입력받는 함수
    cin >> n >> m >> k;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> grid[i][j];
}

bool IsFinish(){        // 부서지지 않은 포탑이 1개인지 확인
    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] != 0)
                cnt++;
        }
    }
    if(cnt == 1)
        return true;
    return false;
}

void Choose_attacker(){     // 공격자를 찾는 함수
    int minPower = MAX_K+1, minX = 0, minY = 0;         // 가장 약한 포탑
    for(int sum = n+m-2; sum >= 0; sum--){      // 행+열의 합이 큰 순으로 확인
        for(int j=m-1; j>=0; j--){              // 열 값이 큰 순으로 확인
            int i = sum-j;
            if(i < 0 || i >= n) continue;       // 범위 벗어나면 무시
            if(grid[i][j] == 0) continue;       // 이미 부서진 포탑이면 넘어가기
            if(minPower > grid[i][j]){          
                // 공격력이 현재 최소 공격력보다 낮다면 업데이트
                minX = i, minY = j, minPower = grid[i][j];
            }
            else if(minPower == grid[i][j] && atk_time[i][j] > atk_time[minX][minY]){
                // 최소 공격력과 같지만 공격 시간이 더 최근이라면
                minX = i, minY = j, minPower = grid[i][j];
            }
        }
    }
    atk = make_pair(minX, minY);        // 공격자 좌표 업데이트
}

void Choose_target(){       // 공격대상을 찾는 함수
    int maxPower = 0, maxX = 0, maxY = 0;       // 가장 강한 포탑
    for(int sum = 0; sum <= n+m-2; sum++){      // 행+열의 합이 작은 순으로 확인
        for(int j=0; j < m; j++){              // 열 값이 작은 순으로 확인
            int i = sum-j;
            if(i < 0 || i >= n) continue;       // 범위 벗어나면 무시
            if(grid[i][j] == 0) continue;       // 이미 부서진 포탑이면 넘어가기
            if(maxPower < grid[i][j]){          
                // 공격력이 현재 최대 공격력보다 크다면 업데이트
                maxX = i, maxY = j, maxPower = grid[i][j];
            }
            else if(maxPower == grid[i][j] && atk_time[i][j] < atk_time[maxX][maxY]){
                // 최대 공격력과 같지만 공격 시간이 더 예전이라면
                maxX = i, maxY = j, maxPower = grid[i][j];
            }
        }
    }
    tgt = make_pair(maxX, maxY);        // 공격 대상 좌표 업데이트
}

void Initialize_visited(){              // 방문 배열 초기화하는 함수 
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            visited[i][j] = false;
        }
    }
}

void bfs(){     // 레이저 공격을 위해 최단 경로 탐색을 진행
    while(!q.empty()){
        int x, y;
        tie(x, y) = q.front();
        q.pop();

        // 네가지 방향에 대해서 확인, 우/하/좌/상 우선순위
        for(int d=0; d<4; d++){
            int nx = (x + dirs[d][0] + n)%n, ny = (y + dirs[d][1] + m)%m;   // 가장자리에서 넘어가는 경우까지 처리
            if(!visited[nx][ny] && grid[nx][ny] != 0){
                // 방문하지 않고, 터지지 않은 포탄의 경우에만
                visited[nx][ny] = true;             // 방문 처리
                from[nx][ny] = make_pair(x,y);      // 어디에서 왔는지 표기 
                q.push(make_pair(nx,ny));           // 큐에다가 넣기
            }
        }
    }

}

void attack(int x, int y, int p){       // grid[x][y]에 p만큼의 공격을 입히기
    int cur_power = max(0, grid[x][y]-p);
    grid[x][y] = cur_power;
    isRelated[x][y] = true;
}

bool do_laser(){            // 레이저 공격 함수
    // 1. 먼저 atk에서 tgt까지 bfs 탐색
    Initialize_visited();
    visited[atk.first][atk.second] = true;  // 공격자 좌표 방문 표시
    q.push(atk);                            // 큐에다가 공격자 좌표 넣기(시작좌표)
    bfs();      // 탐색 수행

    // 2. 만약 공격 대상까지 도달할 수 없다면
    if(!visited[tgt.first][tgt.second])
        return false;
    // 3. 도달할 수 있다면 경로를 따라가면서 피해 입히기
    // 3-1. 공격 대상 먼저 공격
    isRelated[atk.first][atk.second] = true;    // 공격자가 이번 턴에 공격과 관련되어 있다고 표시
    int power = grid[atk.first][atk.second];    // 피해 입힐 공격력
    attack(tgt.first, tgt.second, power);       // 공격 대상 power만큼 공격 입히기
    // 3-2. 이제 따라가면서 공격 입히기
    int curX = tgt.first, curY = tgt.second;

    while(true){
        // 공격자에게 도달하기 전까지 수행
        int nx = from[curX][curY].first, ny = from[curX][curY].second;
        if(nx == atk.first && ny == atk.second) break;      // 만약 공격자에 도달했다면 반복문 나가기
        attack(nx, ny, power/2);        // 경로에 있는 포탑은 공격력의 절반만큼 피해 입히기
        curX= nx, curY = ny;            // 현재 좌표를 다음 좌표로
    }    

    return true;
}

void bombshell(){   // 포탄 공격 함수
    // 공격 대상 먼저 공격
    isRelated[atk.first][atk.second] = true;    // 공격자가 이번 턴에 공격과 관련되어 있다고 표시
    int power = grid[atk.first][atk.second];    // 피해 입힐 공격력
    attack(tgt.first, tgt.second, power);       // 공격 대상 power만큼 공격 입히기
    // 이제 공격 대상의 주변 8개 방향에 대해서 공격 입히기
    int x = tgt.first, y = tgt.second;
    for(int d=0; d<8; d++){
        int nx = (x + dirs[d][0] + n)%n, ny = (y + dirs[d][1] + m)%m;   // 가장자리에서 넘어가는 경우까지 처리
        if(grid[nx][ny] != 0){      // 부서지지 않은 포탑에 대해서
            if(nx == atk.first && ny == atk.second) continue;   // 만약 그 방향에 공격자가 있다면 무시
            attack(nx, ny, power/2);
        }
    }
}

void Simulation(){      // 시뮬레이션 수행
    // k번의 턴에 대해서
    for(int i=1; i<=k; i++){
        // 0. 이번 턴에 공격과 관련되어있는지 배열 초기화
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                isRelated[i][j] = false;
            }
        }

        // 1. 공격자 선정
        Choose_attacker();
        // 2. 공격 대상 선정
        Choose_target();
        // 3. 공격자에게 핸디캡 적용 / 공격자의 공격 시간 업데이트
        grid[atk.first][atk.second] += n+m;     // 공격 대상을 찾은 다음에 더해주기
        atk_time[atk.first][atk.second] = i;    // 공격자의 공격 시간 현재 턴으로 업데이트
        // 4. 공격
        // 4.1 레이저 공격 시도
        if(!do_laser())
            // 4.2 레이저가 안되면 포탄 공격
            bombshell();
        // 5. 포탑 정비
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!isRelated[i][j] && grid[i][j] != 0){
                    // 이번 턴에 공격과 무관하고 부서진 포탑이 아니라면
                    grid[i][j]++;       // 공격력 1씩 증가
                }
            }
        }
        // 6. 부서지지 않은 포탑이 1개가 된다면 중지
        if(IsFinish())
            break;
    }

}


int main(){
    // 변수 입력받기:
    Input();

    // 시뮬레이션 시작
    Simulation();

    // 가장 강한 포탑 공격력 출력:
    Choose_target();
    cout << grid[tgt.first][tgt.second];
    return 0;
}