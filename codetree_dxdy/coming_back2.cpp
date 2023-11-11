/*
 * 2023.11.11
 * 내 풀이
#include <iostream>
#include <string>
using namespace std;

int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}; // 위,오,아,왼 방향
int x, y, cur_d;
int t;
int main() {
    string cmd;
    cin >> cmd;

    for(auto c : cmd){
        t++;
        if(c=='F'){ // F가 주어지면
            // 바라보고 있는 방향으로 한칸 이동
            x += dirs[cur_d][0];
            y += dirs[cur_d][1];
            if(x==0 && y == 0){     // (0,0)으로 돌아온다면
                break;
            }
        }
        else if(c=='R'){
            cur_d = (cur_d+1)%4;
        }
        else{
            cur_d = (cur_d+3)%4;
        }
    }

    if(t != 0 && (x ==0 && y == 0)){
        cout<<t;
    }
    else cout << -1;
    return 0;
}
*/

// 해설 풀이
#include <iostream>
#include <string>

#define DIR_NUM 4

string dirs;
int x,y;
int curr_dir = 3;

// 남, 서, 북, 동 순으로 dx, dy를 정의
int dx[DIR_NUM] = {1,0,-1,0};
int dy[DIR_NUM] = {0,-1,0,1};

int main(){
    // 입력
    cin >> dirs;

    // flag: 시작점으로 되돌아 왔는지 여부
    bool falg = false;

    // 움직이는 것을 진행
    for(int i=0; i<(int) dirs.size(); i++){
        char c_dir = dirs[i];

        // 반 시계방향 90' 회전
        if(c_dir == 'L')
            curr_dir = (curr_dir+3) %4;
        // 시계방향 90' 회전
        else if(c_dir == 'R')
            curr_Dir = (curr_dir+1)%4;
        // 직진
        else{
            x += dx[curr_dir];
            y += dy[curr_dir];
        }
        // 시작점으로 되돌아왔을 떄
        if(x == 0 && y == 0)
        {
            cout<<i+1;
            flag = true;
            break;
        }
    }

    // 시작점으로 되돌아오지 못했을 때
    if(flag == false)
        cout << -1;
    return 0;
}