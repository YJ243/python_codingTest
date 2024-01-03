/*
 * 2023.11.14
 * https://www.codetree.ai/missions/5/problems/find-hidden-words-2?&utm_source=clipboard&utm_medium=text 
 * 모든 칸에 대해서 해당 칸이 'L'이라면 해당 칸 주변의 가로, 세로, 대각선으로 인접한 8칸에 대해 환탐 진행 

*/

#include <iostream>
#include <algorithm>
#include <string>

#define MAX_N 100
#define DIR_NUM 8

int n, m;
string arr[MAX_N];

int dx[DIR_NUM] = {1,1,1,-1,-1,-1,0,0};
int dy[DIR_NUM] = {-1,0,1,-1,0,1,-1,1};

int InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main(){
    // 입력
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> arr[i];
    
    // 모든 좌표에서 다 확인해보기
    int cnt = 0;
    for(int i=0; i<n; i++){
        // 격자를 벗어나지 않을 범위로만 잡기
        for(int j=0; j<m; j++){
            if(arr[i][j] != 'L') continue;

            for(int k=0; k<DIR_NUM; k++){
                int curt = 1;
                int curx = i;
                int cury = j;

                while(true){
                    int nx = curx+dx[k];
                    int ny = cury+dy[k];
                    if(InRange(nx,ny)==false) break;
                    if(arr[nx][ny] != 'E') break;

                    curt++;
                    curx = nx;
                    cury = ny;
                }
                if(curt >= 3)
                    cnt++;

            }
        }
    }
    cout << cnt;
    return 0;
}