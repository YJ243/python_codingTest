/*
 * 2023.11.14
 * 내 풀이
*/

#include <iostream>
#define MAX_N 50
using namespace std;
int N, M;
char a[MAX_N][MAX_N];
int dirs[8][2] = {{1,-1},{1,0},{1,1},{-1,-1},{-1,0},{-1,1},{0,-1},{0,1}};

bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < M;
}

int main() {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> a[i][j];
        }
    }
    int ans = 0;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(a[i][j] != 'L') continue; // 시작칸이 'L'이 아니라면 무시

            for(int d=0; d<8; d++){     // 가로, 세로, 대각선으로 인접한 8칸에 대해 완탐 진행
                int nx = i, ny = j;
                int e_cnt = 0;
                for(int k=0; k<2; k++){
                    nx = nx+dirs[d][0], ny = ny+dirs[d][1];
                    if(!InRange(nx,ny)) break;
                    if(a[nx][ny] == 'E') e_cnt++;
                }
                if(e_cnt == 2) ans++;
            }
        }
    }
    cout << ans;
    return 0;
}