/*
 * 2024.1.17
 * 내 풀이
*/

#include <iostream>

#define MAX_N 100
#define MAX_M 100
#define MAX_Q 100
using namespace std;

int n, m, q;
int grid[MAX_N][MAX_M];     // 초기 건물 상태 
int row[MAX_Q];             // 바람에 영향을 받는 행 번호
char dirs[MAX_Q];           // 바람이 불어오는 방향

void DoWind(int r, char d){ // r행을 d 방향으로 미는 함수
    if(d == 'L'){   // 오른쪽으로 밀어야 한다면
        int temp = grid[r][m-1];
        for(int i=m-1; i>=1; i--)
            grid[r][i] = grid[r][i-1];
        grid[r][0] = temp;
    }
    
    else{           // 왼쪽으로 밀어야 한다면
        int temp = grid[r][0];
        for(int i=0; i<m-1; i++)
            grid[r][i] = grid[r][i+1];
        grid[r][m-1] = temp;
    }
}

bool IsMovable(int s, int e){   // 옮겨서 바람을 불 수 있는지 확인하는 함수
    // 범위 벗어난 행이면 더이상 이동 불가
    if(e < 0 || e >= n) return false;

    // 모든 열을 보면서 같은 열에 같은 숫자가 적힌 것이 하나라도 있다면 이동 가능
    for(int i=0; i<m; i++){
        if(grid[s][i] == grid[e][i])
            return true;
    }
    // 같은 숫자를 가진 열이 하나라도 없다면 이동 불가
    return false;
}

void CheckUpward(int r, char d){    // r행을 d 방향으로 바람 분 이후 위쪽 행을 확인하는 함수
    int curR = r-1, beforeR = r;
    char curD = ' ', beforeD = d;

    // 이동 가능할 때까지
    while(IsMovable(beforeR, curR)){
        if(beforeD == 'L') curD = 'R';
        else        curD = 'L';
        
        DoWind(curR, curD);
        beforeR = curR;
        curR--;
        beforeD = curD;
    }

}

void CheckDownward(int r, char d){  // r행을 d 방향으로 바람 분 이후 아래쪽 행을 확인하는 함수
    int curR = r+1, beforeR = r;
    char curD = ' ', beforeD = d;
    // 이동 가능할 때까지
    while(IsMovable(beforeR, curR)){
        if(beforeD == 'L') curD = 'R';
        else        curD = 'L';
        
        DoWind(curR, curD);
        beforeR = curR;
        curR++;
        beforeD = curD;
    }
}

void Simulation(){
    for(int i=0; i<q; i++){
        int curR = row[i];
        char curD = dirs[i];
        // Step 1. curR행을 curD 방향으로 밀기
        DoWind(curR, curD);

        // Step 2. curR행 위쪽으로 확인
        CheckUpward(curR, curD);
        // Step 3. curR행 아래쪽으로 확인
        CheckDownward(curR, curD);
    }
}

int main() {
    // 입력:
    cin >> n >> m >> q;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> grid[i][j];
    
    for(int i=0; i<q; i++){
        cin >> row[i] >> dirs[i];
        row[i]--;
    }

    // 바람 부는 시뮬레이션 시작
    Simulation();

    // 출력:
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cout << grid[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}