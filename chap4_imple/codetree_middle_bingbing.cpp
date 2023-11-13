/*
 * 2023.11.12
 * 마지막에 1,2,3,4,4가 된다는 것을 놓침
 * 내 풀이
*/
#include <iostream>
#define MAX_N 100

using namespace std;

int n, x, y;                                    // n: 격자 크기, (x, y): 초기 좌표
int c_cnt = 1, r_cnt = 1;                       // c_cnt: 오/왼 방향으로 채울 개수, r_cnt: 위/아래 방향으로 채울 개수
int dirs[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};   // 우, 상, 좌, 하 방향
int cur_d;                                      // 현재 방향 인덱스
int arr[MAX_N][MAX_N];                          // 채울 격자
int val = 1;                                    // 격자에 채워지는 값

void write_num(int cnt){    // cnt 개수 만큼 값을 채움
    for(int i=0; i<cnt; i++){
        x = x+dirs[cur_d][0], y = y+dirs[cur_d][1];     // cur_d 방향으로 cnt만큼 값을 채움
        if(val+1 > n*n) return;     // 만약 숫자를 모두 채웠다면 리턴
        arr[x][y] = ++Val;
    }
}

int main(){
    cin >> n;
    x = n/2, y = n/2;
    arr[x][y] = val;    // 가운데에 숫자 1 채우기
    while(true){
        if(cur_d % 2 == 0){     // 우/좌 방향이라면
            write_num(c_cnt);   // c_cnt만큼 숫자 채우기
            c_cnt++;            // 채워야 할 개수 증가
        }
        else{                   // 상/하 방향이라면
            write_num(r_cnt);   // r_cnt만큼 숫자 채우기
            r_cnt++;            // 채워야 할 개수 증가 
        }
        cur_d = (cur_d+1) % 4;
    }

    // 출력
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << arr[i][j] << ' ';
        }
        cout<<'\n';
    }
    return 0;
}