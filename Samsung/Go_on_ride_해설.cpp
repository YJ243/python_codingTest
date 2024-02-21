/*
 * 2024.02.21
 * 놀이기구 탑승
 * 해설 풀이
 * 완전탐색을 진행하면 각 학생이 어느 위치로 이동해야 하는지 계산할 수 있음
 * 그 후 (좋아하는 친구 수, 빈칸 수, -행 번호, -열 번호) 순으로 가장 값이 큰 곳으로 이동하면 됨
 * 복잡한 우선순위에 대한 처리는 tuple을 이용하면 비교적 간단하게 구현이 가능하다.
 * n^2명의 학생에 대해 n^2의 크기의 격자의 완전탐색을 진행해야 하므로 총 시간복잡도:O(N^4)
 * 친구인지 확인하기 위해 이중 배열로 선언
 * tuple로 비교!
*/

#include <iostream>
#include <cmath>
#include <tuple>

#define MAX_N 20
#define MAX_NUM 400
#define DIR_NUM 4
#define EMPTY 0

using namespace std;

// 칸의 상태
typedef tuple<int, int, int, int> Cell;

int n;

int target_num[MAX_NUM + 1];
bool friends[MAX_NUM+1][MAX_NUM+1];

// 놀이 기구 탑승 번호
int rides[MAX_N+1][MAX_N+1];

int dx[DIR_NUM] = {-1, 1, 0, 0};
int dy[DIR_NUM] = {0, 0, -1, 1};

bool InRange(int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

// num2가 num1이 좋아하는 친구인지 판단합니다.
bool IsFriend(int num1, int num2) {
    return friends[num1][num2];
}

// 우선순위에 따라 쉽게 계산하기 위해
// (좋아하는 친구 수, 빈 칸의 수, -행 번호, -열 번호)
// 순서대로 값을 넣어준다.
Cell GetCurrCell(int num, int x, int y){
    int friend_cnt = 0, blank_cnt = 0;
    for(int i=0; i<DIR_NUM; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(!InRange(nx, ny))
            continue;
        if(ridex[nx][ny] == EMPTY)
            blank_cnt++;
        else if(IsFriend(num, rides[nx][ny]))
            friend_cnt++;
    }
    return make_tuple(friend_cnt, blank_cnt, -x, -y);
}

void Move(int num){
    // Step 1. 가장 우선순위가 높은 칸을 선택한다.
    Cell best_cell = make_tuple(0,0,-(n+1),-(n+1));
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(rides[i][j] == EMPTY){
                Cell curr = GetCurrCell(num, i, j);

                if(best_cell < curr)
                    best_cell = curr;
            }
    // Step 2. 해당 위치에 탑승한다.
    int x, y;
    tie(ignore, ignore, x, y) = best_cell;
    rides[-x][-y] = num;
}

// (x,y) 위치에 있는 학생의 점수를 계산한다.
int GetScore(int x, int y){
    int cnt = 0;
    for(int i=0; i<DIR_NUM; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(InRange(nx ,ny) && IsFriend(rides[x][y], rides[nx][ny]))
            cnt++;
    }
    return (int)pow(10, cnt-1);
}

// 총 점수를 계산한다.
int GetTotalScore(){
    int score = 0;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            score += GetScore(i,j);
    return score;
}

int main(){
    cin >> n;

    for(int i=1; i<=n*n; i++){
        cin >> target_num[i];

        for(int j=1; j<=4; j++){
            int friend_num;
            cin >> friend_num;

            // 현재 번호에 친구 번호를 표시해주기
            friends[target_num[i]][friend_num] = true;
        }
    }

    // 순서대로 학생들을 놀이기구에 탑승시킨다.
    for(int i=1; i<=n*n; i++)
        Move(target_num[i]);
    
    // 총 점수를 계산한다.
    int ans = GetTotalScore();
    cout << ans;

}