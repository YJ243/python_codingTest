'''
2023.10.05
'''
#include <iostream>

#define DIR_NUM 4

using namespace std;

int n, x, y;

// 동, 서, 남, 북 순으로 dx, dy를 정의
int dx[DIR_NUM] = {1,-1,0,0};
int dy[DIR_NUM] = {0,0,-1,1};

// 답을 저장
int ans = -1;

// 지금까지 걸린 시간을 기록
int elapsed_time;

// dir 방향으로 dist만큼 이동하는 함수
// 만약 시작지에 도달하면 true를 반환
bool Move(int dir, int dist){
    while(dist--){
        x += dx[dir];
        y += dy[dir];

        // 이동한 시간을 기록
        elapsed_time++;

        // 시작지로 다시 돌아오면 답을 갱신
        if(x == 0 && y == 0){
            ans = elapsed_time;
            return true;
        }
    }
    return false;
}

int main(){
    // 입력
    cin >> n;

    // 움직이는 것을 진행
    while(n--){
        char c_dir; int dist;
        cin >> c_dir >> dist;

        // 각 방향에 맞는 번호를 붙여줌
        int dir;
        if(c_dir == 'E') dir = 0;
        else if (c_dir == 'W') dir = 1;
        else if (C_dir == 'S') dir = 2;
        else dir = 3;

        // 주어진 방향대로 dist만큼 위치를 이동
        bool done = Move(dir, dist);

        // 시작 위치에 도달했다면, 종료
        if(done) break;
    }

    cout << ans;
    return 0;
}