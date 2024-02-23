/*
 * 24.02.23
 * 청소는 즐거워
 * 내 풀이
 * 맨 처음에 비율을 나타내는 격자도 회전하는지 모르고 풀어서 디버깅할 때 다시 짜느라 시간이 더 걸렸음
*/

#include <iostream>
#define MAX_N 499
using namespace std;

int n;                      // 격자 크기
int grid[MAX_N][MAX_N];     // 격자
double gridR[5][5];
int dirs[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};   // 좌, 하, 우, 상
int r, c;                   // 빗자루의 현재 위치
int OutDust;                // 격자 밖으로 떨어져 나간 먼지 양
int curD;                   // 현재 빗자루가 움직이는 방향
int curL=1;                 // 현재 빗자루가 움직이는 방향으로 이동해야 할 횟수
int totalSpread;

void Init(){
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];

    gridR[0][2] = gridR[4][2] = 0.02;

    gridR[1][1] = gridR[3][1] = 0.1;
    gridR[1][2] = gridR[3][2] = 0.07;
    gridR[1][3] = gridR[3][3] = 0.01;

    gridR[2][0] = 0.05;
    gridR[2][1] = 100.0;


}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Spread_Dust(int x, int y, int originDust, double ratio){
    int curSpreadCnt = originDust * ratio;
    //cout << curSpreadCnt<<"만큼 퍼져나감" << '\n';
    totalSpread += curSpreadCnt;            // 현재 퍼져나간 먼지 수 증가시키기
    if(!InRange(x, y)){
        // 만약 격자 밖으로 나갔다면
        OutDust += curSpreadCnt;            // 빠져나간 먼지수에 추가
    }
    else{
        // 격자 안에 있다면
        grid[x][y] += curSpreadCnt;         // 격자에 표시
    }
}

void MoveBloom(int x, int y){   // (x,y) 위치로 빗자루를 이동시키기
    int curDustCnt = grid[x][y];    // 현재 먼지
    //cout << x << ' ' << y << "위치로 이동:" << curDustCnt <<'\n';
    totalSpread = 0;            // 전체 퍼져나간 먼지
    int aX, aY;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(gridR[i][j] == 0) continue;
            if(gridR[i][j] == 100.0){
                aX = i, aY = j;
            }
            // 만약 퍼센트라면
            int dx = i-2, dy = j-2;
            // 빗자루 옆에 확인하기
            Spread_Dust(x+dx, y+dy, curDustCnt, gridR[i][j]);
        }
    }
    
    // a% 먼지 처리해주기
    int aDust = curDustCnt - totalSpread;
    if(!InRange(x+(aX-2), y+(aY-2))){
        OutDust += aDust;
    }
    else{
        grid[x+(aX-2)][y+(aY-2)] += aDust;
    }

    grid[x][y] = 0;       // 먼지 없애기

}

void RotateRatioGrid(){     // 반시계방향으로 ratio 배열을 회전하기
    double tempR[5][5];

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            tempR[4-j][i] = gridR[i][j];
        }
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            gridR[i][j] = tempR[i][j];
        }
    }
}

void Simulate(){
    bool IsFinish = false;
    r = n/2, c = n/2;
    // Step 1. 빗자루 한 칸 이동
    while(true){
        // 1-1. 먼저 curL만큼 curD 방향으로 이동하기
        for(int l=1; l <= curL; l++){
            int nr = r + dirs[curD][0], nc = c + dirs[curD][1];
            if(!InRange(nr, nc)){   // 만약 다음 위치가 격자를 벗어난다면 이제 끝났다는 얘기
                IsFinish = true;
                break;
            }
            MoveBloom(nr, nc);
            
            r = nr, c = nc;

        }
        if(IsFinish)
            break;

        // 이제 방향을 바꾸어 주어야 함
        curD = (curD + 1) % 4;
        RotateRatioGrid();
        if(curD % 2 == 0) curL++;       // 만약 좌우로 움직이는 방향에 왔다면 길이 증가

    }
}

int main() {
    // 수행을 위한 입력 및 초기화 진행:
    Init();    
    // 시뮬레이션 진행
    Simulate();
    // 출력하기:
    
    cout << OutDust;
    return 0;
}