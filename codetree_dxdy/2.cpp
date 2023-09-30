#include <iostream>
#include <string>

#define DIR_NUM 4

using namespace std;

string dirs;
int x = 0, y = 0;
int curr_dir = 3;

// 동, 남, 서, 북 순으로 dx, dy 정의 
int dx[DIR_NUM] = {1,0,-1,0};
int dy[DIR_NUM] = {0,-1,0,1};

int main(){
    // 입력
    cin >> dirs;

    // 움직이기
    for(int i=0; i< (int)dirs.size(); i++){
        char c_dir = dirs[i];

        // 반시계 방향 90도 회전
        if(c_dir == 'L')
            curr_dir = (curr_dir + 3)%4;
        else if(c_dir == 'R')
            curr_dir = (curr_dir+1)%4;
        else{
            x += dx[curr_dir];
            y += dy[curr_dir];

        }
    }
    cout << x << " " << y;
    return 0;
}