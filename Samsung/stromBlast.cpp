/*
 * 2024.03.29
 * 시공의 돌풍
 * 내 풀이
*/

#include <iostream>
#include <vector>
#define MAX_NM 50

using namespace std;

int n, m, t;
int grid[MAX_NM][MAX_NM];
int spread[MAX_NM][MAX_NM];
vector<pair<int, int> > vaccum;
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
void Input(){
    cin >> n >> m >> t;     // n, m: 방의 크기, t: 시간
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> grid[i][j];
            if(grid[i][j] == -1)
                vaccum.push_back(make_pair(i, j));
        }
    }
}

void Initialize_Spread(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            spread[i][j] = 0;
        }
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanGo(int x, int y){
    return InRange(x, y) && grid[x][y] != -1;
}
void SpreadDust(){
    // 1. 먼저 확산될 먼지 양 초기화하기
    Initialize_Spread();

    // 2. 격자를 하나씩 보면서 먼지의 +-양 구하기
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int dust_cnt = grid[i][j];
            int can_go_cnt = 0;
            for(int d=0; d<4; d++){
                int nx = i + dirs[d][0], ny = j + dirs[d][1];
                if(CanGo(nx, ny)){
                    can_go_cnt++;
                    spread[nx][ny] += dust_cnt/5;
                }
            }
            spread[i][j] -= (dust_cnt/5) * can_go_cnt;
        }
    }

    // 3. 모든 먼지가 확산을 끝난 다음 해당 칸에 반영해주기
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            grid[i][j] += spread[i][j];
        }
    }

}

void CleanDust(){
    for(int i=0; i<2; i++){
        // 먼저 첫번째 방향 밀어주기
        int vx = vaccum[i].first, vy = vaccum[i].second;
        int tmp = grid[vx][m-1];
        for(int j=m-1; j > 1; j--){
            grid[vx][j] = grid[vx][j-1];
        }
        grid[vx][1] = 0;

        // 두번째 방향 밀어주기
        int tmp2;
        if(i == 0){
            tmp2 = grid[0][m-1];      // 맨 위의 값 저장하기
            for(int x=0; x < vx-1; x++){
                grid[x][m-1] = grid[x+1][m-1];
            }
            grid[vx-1][m-1] = tmp;
        }
        else{
            tmp2 = grid[n-1][m-1];
            for(int x=n-1; x > vx+1; x--){
                grid[x][m-1] = grid[x-1][m-1];
            }
            grid[vx+1][m-1] = tmp;
        }

        // 세 번째 방향 밀어주기
        if(i == 0){
            tmp = grid[0][0];            
            for(int j=0; j<m-2; j++){
                grid[0][j] = grid[0][j+1];
            }
            grid[0][m-2] = tmp2;
        }
        else{
            tmp = grid[n-1][0];
            for(int j=0; j<m-2; j++){
                grid[n-1][j] = grid[n-1][j+1];
            }
            grid[n-1][m-2] = tmp2;
        }

        // 네 번째 방향 밀어주기
        if(i == 0){
            for(int x=vx-1; x > 1; x--)
                grid[x][0] = grid[x-1][0];
            grid[1][0] = tmp;
        }
        else{
            for(int x=vx+1; x <n-2; x++)
                grid[x][0] = grid[x+1][0];
            grid[n-2][0] = tmp;
        }

    }

}

void Simulate(){
    // 1. 먼저 먼지 확산하기
    SpreadDust();

    // 2. 시공의 돌풍 청소하기
    CleanDust();
}

void Output(){
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j] >=0)
                ans += grid[i][j];
        }
    }
    cout << ans;
}

int main() {
    // 입력 받기:
    Input();

    while(t--){
        Simulate();
    }    
    // 출력 하기:
    Output();
    return 0;
}