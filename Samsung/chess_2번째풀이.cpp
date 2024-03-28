/*
 * 2024.03.27
 * 해설 보고 내 풀이 고침
*/
#include <iostream>
#include <algorithm>
#include <tuple>

#define MAX_N 4
#define MAX_DIR 8
#define NOT_EXIST make_pair(-1, -1)

using namespace std;

int n = MAX_N;
pair<int, int> grid[MAX_N][MAX_N];
int sx, sy;     // 술래(seeker)의 위치
int sd;         // 술래의 방향
int dirs[MAX_DIR][2] = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
int ans;
int curr;
void Input(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num, dir;
            cin >> num >> dir;
            grid[i][j] = make_pair(num, dir-1);
        }
    }

}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool IsFinish(int x, int y, int d){        // 술래가 이동할 수 있는 곳에 도둑말이 더이상 존재하지 않는지 확인하기
    bool IsExist = false;
    for(int i=1; i<=n; i++){
        int nx = x + dirs[d][0]*i, ny = y + dirs[d][1]*i;
        if(InRange(nx, ny) && grid[nx][ny] != NOT_EXIST){
            IsExist = true;
        }
    }
    return !IsExist;
}

void CatchTheif(int x, int y){
    //int priorX = sx, priorY = sy, priorD = sd;
    //int priorS = curr;
    curr += grid[x][y].first;       // 점수 증가
    sd = grid[x][y].second;         // 술래 방향 바꿔주기
    sx = x, sy = y;                 // 술래 위치 바꿔주기
    grid[x][y] = NOT_EXIST;         // 해당 칸에 아무도 존재하지 않는다고 표시
    //return make_tuple(priorX, priorY, priorD, priorS);
}

void MoveThief(){
    for(int num=1; num<=16; num++){                     // 1번부터 16번까지 번호를 차례대로 보기
        bool IsMoved = false, cannotMovable = false;    // 해당 번호를 가진 도둑이 움직였는지, 움직일 수 없는지 확인하기
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                int curN = grid[i][j].first, curD = grid[i][j].second;      // 현재 보고 있는 칸의 번호와 방향
                if(curN == num){                                            // 만약 번호가 같다면
                    // 이제 (i,j)에 있는 도둑 옮기기
                    int nx = i + dirs[curD][0], ny = j + dirs[curD][1];     // 다음에 이동할 위치
                    int startX = nx, startY = ny;                           // 위를 처음 이동할 위치 좌표로 받아놓기
                    if(!InRange(nx, ny) || (nx == sx && ny == sy)){         // 만약 범위를 벗어나거나 술래가 있다면
                        for(int d=1; d<=8; d++){                            //  이동할 수 있을 때까지 45도 반시계 방향으로 회전하기
                            nx = i + dirs[(curD+d)%MAX_DIR][0], ny = j + dirs[(curD+d)%MAX_DIR][1];
                            if(InRange(nx,ny) && (nx != sx || ny != sy)){   // 이동 가능한 곳을 찾았다면 방향 저장하고 나가기
                                curD = (curD + d) % MAX_DIR;
                                break;
                            }
                        }
                        if(nx == startX && ny == startY){       // 만약 다시 처음으로 돌아왔다면 이동불가능하다는 의미
                            cannotMovable = true;
                            break;       // 이동할 수 없다면 움직이지 않기
                        }
                    }
                    // 이제 (i,j)에서 (nx,ny)로 바꾸기
                    int movingNum = grid[nx][ny].first, movingDir = grid[nx][ny].second;
                    grid[nx][ny] = make_pair(num, curD);
                    grid[i][j] = make_pair(movingNum, movingDir);
                    IsMoved = true;
                }
                if(IsMoved || cannotMovable)
                    break;
            }
            if(IsMoved || cannotMovable)
                break;
        }
    }
}

void ChooseNext(int x, int y, int d, int score){
    if(IsFinish(x, y, d)){
        // 만약 끝났다면 점수 업데이트하기
        ans = max(ans, score);
        return;
    }

    for(int i=1; i<=n; i++){
        //cout << cnt << "번째: " << '\n';
        int nx = x + dirs[d][0]*i, ny = y + dirs[d][1]*i;
        // 만약 술래가 이동할 곳이 범위 안이고, 도둑이 존재한다면
        if(!InRange(nx, ny) || grid[nx][ny] == NOT_EXIST)
            continue;

        pair<int, int> tmp[MAX_N][MAX_N];

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                tmp[i][j] = grid[i][j];

        int extra_score, next_dir;
        tie(extra_score, next_dir) = grid[nx][ny];
        CatchTheif(nx, ny);
  
        // 2. 도둑 이동하기
        MoveThief();
        // 3. 술래가 이동할 다음 위치 찾기
        ChooseNext(nx, ny, next_dir, score + extra_score);
        // 4. 도둑 움직이기 이전으로 되돌리기

        // catchTheif도 되돌리기
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                grid[i][j] = tmp[i][j];
    }
}

int main() {
    // 입력 받기:
    Input();    

    // 시뮬레이션 시작
    // 먼저 (0,0)에 있는 도둑을 잡고 시작
    int init_score, init_dir;
    tie(init_score, init_dir) = grid[0][0];

    CatchTheif(0,0);        
    MoveThief();

    ChooseNext(0, 0, init_dir, init_score);      // 술래가 (0,0)에서 1번째 이동할 곳을 정하러 가기

    cout << ans;
    return 0;
}