/*
 * 2024.1.21
 * 해설 풀이
 * 시간복잡도는 한 격자당 많아야 최대 1번씩 올 수 있으므로, 격자의 크기에 해당하는 O(N^2)
*/

#include <iostream>
#include <vector>

#define DIR_NUM 4
#define MAX_N 100

using namespace std;

// 전역 변수 선언:
int n;

int curr_x, curr_y;     // 현재 위치를 의미
int a[MAX_N+1][MAX_N+1];

// 방문하게 되는 숫자들을 담을 곳
vector<int> visited_nums;

// 범위가 격자 안에 들어가는지 확인
bool InRange(int x, int y){
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

// 범위가 격자 안이고, 해당 위치의 값이 더 큰지 확인
bool CanGo(int x, int y, int curr_num){
    return InRange(x,y) && a[x][y] > curr_num;
}

// 조건에 맞춰 움직여보기
// 움직였다면 true를 반환하고
// 만약 움직일 수 잇는 곳이 없었다면 false를 반환
bool Simulate(){
    // 코딩의 간결함을 위해 문제 조건에 맞게 상하좌우 순서로 방향 정의
    int dx[DIR_NUM] = {-1,1,0,0};
    int dy[DIR_NUM] = {0,0,-1,1};

    // 각각의 방향에 대해 나아갈 수 있는 곳이 있는지 확인 
    for(int i=0; i<DIR_NUM; i++){
        int next_x = curr_x + dx[i];
        int next_y = curr_y + dy[i];

        // 갈 수 있는 곳이라면 이동하고 true를 반환
        if(CanGo(next_x, next_y, a[curr_x][curr_y])){
            curr_x = next_x;
            curr_y = next_y;
            return true;
        }
    }
    // 움직일 수 있는 곳이 없었다는 의미로 false 값 반환
    return false;
}

int main(){
    // 입력:
    cin >> n >> curr_x >> curr_y;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> a[i][j];
    // 초기 위치에 적혀있는 값을 답에 넣어주기
    visited_nums.push_back(a[curr_x][curr_y]);
    
    while(true){
        // 조건에 맞춰 움직여보기
        bool greater_number_exist = Simulate();

        // 인접한 곳에 더 큰 숫자가 없다면 종료하기
        if(!greater_number_exist)
            break;
        // 움직이고 난 후의 위치를 답에 넣어주기
        visited_nums.push_back(a[curr_x][curr_y]);
    }

    // 출력:
    for(int i=0; i<(int) visited_nums.size(); i++)
        cout << visited_nums[i] << ' ';

    return 0;
}