/*
 * 2023.11.09
 * 내 풀이

#include <iostream>
using namespace std;
int N;
int x, y;
int move_time;
int dirs[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; // 우,하,좌,상
int main() {
    cin >> N;
    int final_time=-1;
    for(int i=0; i<N; i++){
        char d;
        int l,cur_d;
        cin>>d >> l;
    
        if(d=='N')  cur_d=3;
        else if(d=='E') cur_d=0;
        else if(d=='W') cur_d=2;
        else cur_d=1;

        while(l--){
            move_time++;
            x += dirs[cur_d][0];
            y += dirs[cur_d][1];
            if(x==0 && y == 0) {
                final_time=move_time;
            }
        }
        if(final_time > 0) break;
    }

    cout<<final_time;
    return 0;
}
*/

// 해설 풀이
#include <iostream>
#define DIR_NUM 4

using namespace std;
int n, x, y;

// 남, 북, 서, 동 순으로 dx, dy를 정의
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

        // 시작지로 다시 돌아오면, 답을 갱신해 줌
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
        cin>>c_dir>>dist;

        // 각 방향에 맞는 번호를 붙여줌
        int dir;
        if(c_dir == 'E')
            dir=0;
        else if(c_dir == 'W')
            dir=1;
        else if(c_dir == 'S')
            dir=2;
        else
        {
            dir=3;

        }

        // 주어진 방향대로 dist 만큼 위치 이동
        bool done = Move(dir, dist);

        // 시작 위치에 도달했다면 종료,
        if(done)
            break;
    }
    cout<<ans;
    return 0;
}