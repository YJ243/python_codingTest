/*
 * 2023.11.11
 * 시간을 많이 썼지만 못풀었음
*/

#include <iostream>
#define MAX_N 20
using namespace std;

int n;
int maze[MAX_N][MAX_N];

int dirs[4][2] = {{-1,1},{-1,-1},{1,-1},{1,1}};
bool InRange(int x, int y){
    return (0 <= x && x < n && 0 <= y && y < n);
}

int GetSum(int x, int y){ // (x,y)에서 1,2,3,4방향에 있는 지점의 숫자들의 합을 구해주는 함수
    int max_cnt = -1;
    for(int first_n = 1; first_n <= MAX_N; first_n++){
        for(int second_n=1; second_n <= MAX_N; second_n++){
            // 매번 처음 시작점에서 탐색 시작
            int cur_x = x, cur_y = y, cur_d=0;
            
            // 1번 방향으로 first_n만큼 이동
            int nx = x + first_n*dirs[0][0], ny = y + first_n*dirs[0][1];
            if(!InRange(nx,ny)){
                // 만약 범위를 1번부터 범위를 벗어나면 다음 first_n으로 가야함
                break;
            }
            cur_x = nx, cur_y = ny;
            // 2번 방향으로 second_n만큼 이동
            nx = x + first_n*dirs[1][0], ny = y + first_n*dirs[1][1];
            if(!InRange(nx,ny)){
                // 만약 범위를 1번부터 범위를 벗어나면 다음 first_n으로 가야함
                break;
            }
            cur_x = nx, cur_y = ny;
            // 여기까지 왔다는 것은 1번, 2번방향 모두 범위 안에 들어왔다는 것 그럼 3,4번도 모두 가능
            // 이제 각 방향만큼 돌면서 합 구하기
            int cur_sum = maze[x][y];
            while(first_n--){
                x += dirs[0][0];
                y += dirs[0][1];
                cur_sum += maze[x][y];
            }
            while(second_n--){
                x += dirs[1][0];
                y += dirs[1][1];
                cur_sum += maze[x][y];
            }
            while(first_n--){
                x += dirs[2][0];
                y += dirs[2][1];
                cur_sum += maze[x][y];
            }
            while(second_n--){
                x += dirs[3][0];
                y += dirs[3][1];
                cur_sum += maze[x][y];
            }
            max_cnt = max(cur_sum, max_cnt);
        }
    }
    return max_cnt;
}
int main() {
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> maze[i][j];
    // Step 1. 모든 격자에 대해서 확인하는데, (2,1)부터 기울어진 직사각형을 만들 수 있음
    int max_sum = 0;
    for(int i=2; i<n; i++){
        for(int j=1; j<n-1; j++){
            // Step2. 1방향으로 나갈 시작점은 (i,j)
            // 백트래킹인가? 갈 수 있는 곳까지 가고 아니면 다시 빼기
            int first_cnt=0, second_cnt = 0;
            int cur_sum = GetSum(i,j);
            
            max_sum = max_sum < cur_sum ? cur_sum:max_sum;
        }
    }
    cout<<max_sum;
    return 0;
}