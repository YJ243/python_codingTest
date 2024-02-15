/*
 * 2024.02.12
 * 내 풀이
*/
#include <iostream>
#include <algorithm>

#define MAX_N 10
#define DIR_NUM 4
using namespace std;

int n, m, k;                // n: 격자 크기, m: 참가자 수, k: 게임 시간
int grid[MAX_N][MAX_N];     // 현재 미로, 0:빈칸, -1 ~ -9: 벽 내구도, -10: 출구, 양수: 참가자 수
int tmp[MAX_N][MAX_N];      // 참가자를 한 번에 이동하기 위해 중간 정보를 저장
int dirs[DIR_NUM][2] = {{-1,0},{1,0},{0,-1},{0,1}};   // 상하 -> 좌우 우선순위
int total_dist;

void Input(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            grid[i][j] = -grid[i][j];   // 내구도를 음수로 저장
        }
    }
    while(m--){
        int x, y;
        cin >> x >> y;
        grid[x-1][y-1]++;   // 참가자 수 증가
    }
    int x, y;
    cin >> x >> y;
    grid[x-1][y-1] = -10;   // 출구 좌표 저장
}

pair<int ,int> GetExit(){   // 출구 좌표를 반환하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == -10){
                return make_pair(i,j);
            }
        }
    }
}



bool InRange(int x, int y){     // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
} 

bool CanGo(int x, int y){       // (x,y)로 이동이 가능한지 확인하는 함수
    // 범위 안에 있고, 해당 칸에 참가자가 있거나 출구인 경우, 즉 벽이 아닌 경우 이동 가능
    return InRange(x,y) && (grid[x][y] >= 0 || grid[x][y] == -10);
}

void Move(int x, int y){        // (x,y)에 있는 참가자(들) 이동하는 함수
    // 출구 위치 불러오기
    int exit_x = GetExit().first, exit_y = GetExit().second;
    //cout << exit_x << ' ' <<exit_y << '\n';
    // 이제 현재 위치 기준 4방향 확인하기
    // 현재 머물러 있는 칸보다 출구까지 최단거리가 가까운 곳으로 가기
    int minD = abs(exit_x-x) + abs(exit_y-y), minX=0, minY=0;
    for(int d=0; d<4; d++){
        int nx = x+dirs[d][0], ny = y+dirs[d][1];
        if(CanGo(nx,ny)){       // 만약 다음 위치로 이동이 가능하다면
            int curD = abs(exit_x-nx) + abs(exit_y-ny);     // 그 다음 위치로부터 출구까지 거리 계산
            if(minD > curD){    // 만약 현재 위치보다 출구까지 더 가깝다면
                minD = curD, minX = nx, minY = ny;          // 좌표 업데이
            }
        }
    }
    if(minD == abs(exit_x-x) + abs(exit_y-y)){  // 만약 움직일 수 없는 상황이라면 움직이지 않기
        tmp[x][y] += grid[x][y];            // 현재 참가자 위치 그대로 두기
    }
    else{   // 만약 움직일 수 있다면
        total_dist += grid[x][y];    // 이동 거리 업데이트
        if(grid[minX][minY] != -10)         // 움직일 곳이 출구가 아닐 때만 참가자 옮기기
            tmp[minX][minY] += grid[x][y];          // 참가자 옮기기
    }
}

int GetMinLength(){     // 참가자와 출구를 포함하는 가장 작은 정사각형의 한 변의 길이를 구하는 함수
    int exit_x = GetExit().first, exit_y = GetExit().second;    // 출구 좌표
    int minL = MAX_N;       // 가장 작은 정사각형의 한 변의 길이
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0){     // 참가자가 있는 칸을 만났다면
                int curX = abs(exit_x-i), curY = abs(exit_y-j);     // 현재 참가자~출구의 가로/세로 길이 구하기
                if(minL > max(curX, curY)){     // 만약 더 작은 정사각형을 만들 수 있다면
                    minL = max(curX, curY);
                }
            }
        }
    }
    return minL;
}

bool CanMakeSquare(int x, int y, int len){      // 좌상단(r,c)에서 길이가 len인 정사각형을 만들 수 있다면
    int exit_x = GetExit().first, exit_y = GetExit().second;    // 출구 좌표
    bool IsPerson = false, IsExit = false;
    for(int i=x; i<=x+len; i++){
        for(int j=y; j<=y+len; j++){
            if(grid[i][j] > 0)
                IsPerson = true;
            if(grid[i][j] == -10)
                IsExit = true;
        }
    }
    if(IsPerson && IsExit)
        return true;
    else
        return false;
}

void Rotate(int x, int y, int len){         // 좌상단(r,c)에서 시작하는 길이가 len인 정사각형 회전하기
    //cout << x << ' ' << y << "좌상단" << '\n';
    int subTmp[len+1][len+1];       // 회전을 위해 옮길 조그만 정사각형
    int subRotate[len+1][len+1];    // 회전된 결과를 저장할 중간 정사각형
    // step1. 일단 옮겨야 할 부분 도려내기
    for(int i=x; i<=x+len; i++){
        for(int j=y; j<=y+len; j++){
            subTmp[i-x][j-y] = grid[i][j];
        }
    }

    // step2. 그 도려낸 부분 회전
    for(int i=0; i<=len; i++){
        for(int j=0; j<=len; j++){
            if(subTmp[i][j] >= -9 && subTmp[i][j] <= -1){
                // 만약 벽이라면 내구도 1 감소
                subTmp[i][j]++;
            }
            subRotate[j][len-i] = subTmp[i][j];
            
        }

    }
    // step3. 회전한 정사각형 다시 원래대로 옮겨놓기
    for(int i=x; i<=x+len; i++){
        for(int j=y; j<=y+len; j++){
            //cout << subRotate[i-x][j-y] << ' ';
            grid[i][j] = subRotate[i-x][j-y];
        }
        //cout << '\n';
    }
    //cout << "****************" << '\n';
    /*
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    */
}

void Initialize_tmp(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            tmp[i][j] = 0;
        }
    }
}
void Simulation(){
    // 0. tmp 배열 초기화
    Initialize_tmp();
    // 1. 참가자들 하나씩 보면서 이동해주기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 0) continue;   // 만약 0이면 일단 넘어가기
            else if(grid[i][j] <= -1 && grid[i][j] >= -10)
                tmp[i][j] = grid[i][j];     // 벽이나 출구이면 복사하기
            else if(grid[i][j] > 0){        // 만약 참가자가 있다면 이동하기
                Move(i,j);              
            }
        }
    }

    // 2. temp를 다시 grid로 옮기기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = tmp[i][j];
        }
    }
    /*
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    // 3. 미로 회전하기
    // 3-1. 한 명 이상의 참가자와 출구를 포함하는 가장 작은 정사각형 길이 구하기
    int minL = GetMinLength();       // 가장 작은 정사각형의 한 변의 길이

    // 3-2. minL의 길이를 가지는 가장 작은 정사각형 잡기, (r->c가 작은 순으로)
    bool IsRotated = false;
    for(int i=0; i<=n-1-minL; i++){
        for(int j=0; j<=n-1-minL; j++){
            if(CanMakeSquare(i,j,minL)){
                Rotate(i,j,minL);       // 해당 부분 정사각형 회전하기
                IsRotated = true;
                break;
            }
        }
        if(IsRotated)
            break;
    }

}

bool IsFinish(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0){
                // 참가자가 남아있다면
                return false;
            }
        }
    }
    return true;
}

void Output(){
    // 모든 참가자들의 이동 거리 합
    cout << total_dist << '\n';
    // 출구 좌표 출력
    int exit_x = GetExit().first, exit_y = GetExit().second;
    cout << exit_x+1 << ' ' << exit_y+1 << '\n';

}

int main() {
    // 입력:
    Input();

    // 시뮬레이션 진행:
    while(k--){     // k초 동안
        if(IsFinish()){
            break;
        }
        Simulation();
        //cout << "total: " << total_dist << '\n';
    }

    // 출력:
    Output();
    return 0;
}