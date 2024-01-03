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

/* 2023.12.11*/

#include <iostream>
using namespace std;

#define MAX_NM 50

int n, m;
char arr[MAX_NM][MAX_NM];

int dirs[8][2] = {{1,-1},{1,0},{1,1},{-1,-1},{-1,0},{-1,1},{0,-1},{0,1}};       // 가로, 세로, 대각선 8개 방향
int ans;

bool InRange(int nx, int ny){
    return 0 <= nx && nx < n && 0 <= ny && ny < m;
}

int main() {
    cin >> n >> m;    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> arr[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            // arr[i][j]가 첫 시작
            if(arr[i][j] == 'L'){
                for(int d=0; d<8; d++){
                    int cnt = 1;
                    int x=i, y=j;
                    while(true){
                        if(cnt == 3) break;
                        int nx = x+dirs[d][0], ny = y+dirs[d][1];
                        if(!InRange(nx,ny) || arr[nx][ny] != 'E')   break;
                        x = nx, y = ny;
                        cnt++;
                    }
                    if(cnt==3) ans++;
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}