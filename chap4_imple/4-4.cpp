#include <iostream>
#include <vector>

using namespace std;

int n, m, x, y, direction;
// 방문한 위치를 저장하기 위한 맵을 생성하여 0으로 초기화
int d[50][50] = {0};
// 전체 맵 정보
int arr[50][50] = {0};

// 북, 동, 남, 서 방향 정의
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};

// 왼쪽으로 회전
void turn_left(){
    direction--;
    if(direction == -1) direction = 3;
}

int main(){
    cin >> n >> m;
    cin >> x >> y >> direction;
    
    d[x][y]=1; // 현재 좌표 방문 처리

    // 전체 맵 정보를 입력 받기
    for(int i=0; i<n; i++){
        for(int j=0; j<m ;j++){
            cin >> arr[i][j];
        }
    }
    // 시뮬레이션 시작
    int cnt = 1;
    int turn_time = 0;
    while(true){
        turn_left();
        int nx = x + dx[direction];
        int ny = y + dy[direction];

        if(d[nx][ny] == 0 && arr[nx][ny] == 0){
            x = nx;
            y = ny;
            turn_time = 0;
            d[x][y] = 1;
            cnt++;
            continue;
        }
        else
        {
            turn_time++;
        }
        if(turn_time == 4){
            int nx = x - dx[direction];
            int ny = y - dy[direction];
            if(arr[nx][ny] == 0){
                x = nx;
                y = ny;
                turn_time = 0;
            }
            else
            {
                break;
            }
        }
    }
    cout << cnt << '\n';
}
