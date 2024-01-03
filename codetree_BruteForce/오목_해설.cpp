/*
 * 2023.12.10
 * 해설
 * 모든 칸을 순서대로 탐색하면서, 특정 칸에서 가로/세로/대각선으로 인접한 8개 칸 보기
 * dx, dy로 바둑돌 종류 확인, 격자 크기 벗어나지 않는 것 주의
 * 하나의 칸에 대해서 한 방향에 대해 같은 종류 수가 존재한다면 그 방향으로 계속 탐색 진행
 * 주어진 격자의 크기를 벗어나거나, 원래 칸과 다른 수가 존재한다면 탐색 중단
*/


#include <iostream>
#include <algorithm>

#define DIR_NUM 8

using namespace std;

int arr[19][19];

int dx[DIR_NUM] = {1,1,1,-1,-1,-1,0,0};
int dy[DIR_NUM] = {-1,0,1,-1,0,1,-1,1};

int InRange(int x, int y){
    return 0 <= x && x < 19 && 0 <= y && y < 19;
}

int main(){
    // 입력
    for(int i=0; i<19; i++)
        for(int j=0; j<19; j++)
            cin >> arr[i][j];
    
    // 모든 좌표에서 다 확인해보기
    for(int i=0; i<19; i++)
        // 격자를 벗어나지 않을 범위로만 잡기
        for(int j=0; j<19; j++){
            if(arr[i][j] == 0) continue;

            for(int k=0; k<DIR_NUM; k++){
                int curt = 1;
                int curx = i, cury = j;
                while(true){
                    int nx = curx + dx[k];
                    int ny = cury + dy[k];
                    if(InRange(nx,ny) == false) break;
                    if(arr[nx][ny] != arr[i][j]) break;

                    curt++;
                    curx = nx; cury = ny;
                }
                if(curt == 5){
                    cout << arr[i][j] << '\n';
                    cout << i + 2*dx[k]+1 << ' ' << j + 2*dy[k]+1;
                    return 0;
                }
            }
        }
    cout << 0;
    return 0;
}