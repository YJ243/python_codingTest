/*
 * 2023.11.11
 * 내 풀이
 * cur_d와 x/y 좌표 변경 순서를 바꾸어 적어서 답이 잘못 나옴

#include <iostream>
#define MAX_N 1000
using namespace std;
int N, K;
char a[MAX_N][MAX_N];
int x,y;
int cur_d;
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}; // 위,오,아,왼
bool InRange(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < N;
}

int do_laser(){
    int cnt=0;
    while(InRange(x,y)){
        if(a[x][y] == '\\'){
            if(cur_d % 2 == 0){
                x += dirs[cur_d+1][0];
                y += dirs[cur_d+1][1];
            }
            else{
                x += dirs[cur_d-1][0];
                y += dirs[cur_d-1][1];
            }
            cur_d = 3-cur_d;
        }
        else{
            x += dirs[3-cur_d][0];
            y += dirs[3-cur_d][1];
            if(cur_d % 2 == 0){
                cur_d++;
            }
            else{
                cur_d--;
            }
        }

        cnt++;
    }

    return cnt;
}
int main() {
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> a[i][j];
        }
    }
    cin >> K;
    if(0 < K && K <= N){
        x = 0;
        y = K-1;
        cur_d = 0;
    }
    else if(N<K && K <= 2*N){
        x = K-N-1;
        y = N-1;
        cur_d = 1;
    }
    else if(2*N < K && K <= 3*N){
        x = N-1;
        y = 3*N-K;
        cur_d=2;
    }
    else{
        x = 4*N-K;
        y = 0;
        cur_d=3;
    }
    
    cout<< do_laser();
    
    return 0;
}
*/