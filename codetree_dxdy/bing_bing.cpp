#include <iostream>
#define MAX_N 100
using namespace std;
int n, m;
int x=0, y=-1; // 시작 전 좌표
int d, plus_cnt; // 현재 방향, 'A'에서 얼마를 더하는지
char arr[MAX_N][MAX_N]={'@',};

int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; // 우,하,좌,상
bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
    cin >> n >> m;
    int cnt = n*m;

    cout << (char)('A'+1)<<'\n';
    
    while(cnt--){
        int nx = x+dirs[d][0], ny = y+dirs[d][1]; // 확인할 다음 좌표
        if(!InRange(nx,ny) || arr[nx][ny] != '@'){
            d = (d+1) % 4; // 방향 1 증가
        }
        x = x+dirs[d][0], y = y+dirs[d][1];
        if(plus_cnt == 66)
            plus_cnt=0;
        arr[x][y] = (char)('A'+plus_cnt);
        cout<<arr[x][y] << ' ';
        plus_cnt++;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<arr[i][j] << ' ';
        }
        cout<<'\n';
    }
    return 0;
}