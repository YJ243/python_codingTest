/*
 * 2024.03.06
 * 이상한 원판
 * 내 풀이
 * 실수 1: 인접한 영역을 지우는 부분 설명을 잘못 읽어서, n과 m 둘다 % 연산을 했었음.
 *         m만 했어야 함!!
*/

#include <iostream>
#define MAX_NM 50

using namespace std;
int n, m, q;
int x, d, k;                    // x: 원판 종류, d: 방향, k: 회전하는 칸 수
int grid[MAX_NM+1][MAX_NM];   // 0: 지워진 곳, 양수: 적힌 숫자
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
bool IsErased;
void Input(){   // 입력값을 받는 함수
    cin >> n >> m >> q;             // n: 원판의 개수, m: 원판 내의 숫자 개수, q: 회전 횟수
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            cin >> grid[i][j];      // 원판에 적힌 수 입력받기 
        }
    }
}

void Rotate(int num){       // num번 원판의 번호 회전시키는 함수
    int temp[MAX_NM+1];     // num번째 원판 회전했을 때의 결과 배열
    int rotate_d = (d == 0) ? 1 : -1;   // 시계방향이면 1, 반시계방향이면 -1
    for(int j=0; j<m; j++){
        int nJ = (j + rotate_d * k + m) % m;    // 넘어가는 경우 처리하기
        temp[nJ] = grid[num][j];
    }
    for(int j=0; j<m; j++){
        grid[num][j] = temp[j]; 
    }

}

bool InRange(int x, int y){
    return 1 <= x && x <= n && 0 <= y && y < m;
}

void EraseSameNumber(){
    bool SameNumber[MAX_NM+1][MAX_NM];
    for(int i=1; i<=n; i++)
        for(int j=0; j<m; j++)
            SameNumber[i][j] = false;
    
    for(int i=1; i <= n; i++){
        for(int j=0; j<m; j++){
            for(int d=0; d<4; d++){
                int nx = i + dirs[d][0];
                int ny = (j + dirs[d][1]+m) % m;
                if(!InRange(nx, ny)) continue;
                if(grid[i][j] == grid[nx][ny] && grid[i][j] != 0){     // 만약 같은 숫자가 존재한다면
                    IsErased = true;                // 해당 턴에서 지워지는 숫자 있다고 표시
                    SameNumber[i][j] = true;          // 기준 숫자 같다고 표시
                    SameNumber[nx][ny] = true;        // 주변 숫자 같다고 표시
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            if(SameNumber[i][j]){
                grid[i][j] = 0;
            }
        }
    }
}

void Normalize(){                       // 정규화시키는 함수
    int cnt = 0, numSum = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] != 0){
                cnt++;
                numSum += grid[i][j];
            }
        }
    }
    int std_val = numSum / cnt;
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] == 0) continue;
            if(grid[i][j] > std_val)
                grid[i][j] -= 1;
            else if(grid[i][j] < std_val)
                grid[i][j] += 1;
        }
    }
}

void Simulate(){
    // Step 1. 원판의 번호가 x의 배수인 경우 회전시켜주기
    for(int i=x; i <= n; i += x){
        // d방향으로 k칸 회전시키기
        Rotate(i);
    }

    // Step 2. 전체 원판을 보면서 인접한 곳에 같은 수가 있는지 확인하기
    // 2-1. 있다면 지워주기
    IsErased = false;
    EraseSameNumber();

    // 2-2. 없다면 정규화 시켜주기
    if(!IsErased)
        Normalize();
}

void Output(){
    int result = 0;
    for(int i=1; i<=n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] != 0)
                result += grid[i][j];
        }
    }
    cout << result;
}

int main() {
    // 입력받기
    Input();    
    // 총 q번에 대해 시뮬레이션 진행하기
    while(q--){
        cin >> x >> d >> k;
        Simulate();
    }
    // 출력하기
    Output();
    return 0;
}