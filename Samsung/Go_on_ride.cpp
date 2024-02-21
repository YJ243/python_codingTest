/*
 * 2024.02.21
 * 놀이기구 탑승
 * 내 풀이
 * 실수1: n*n인데 n개만 선언하도록 해서 runtime 오류가 나왔음
 * 실수2: 처음에 숫자를 넣고, 이후에 비어있는 곳에만 넣도록 안해서 초반에 계속 틀렸었음
*/

#include <iostream>
#include <vector>

#define MAX_N 20

using namespace std;

int n;
int grid[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
vector<int> turn;
vector<int> like[MAX_N*MAX_N+1];
int max_friend, max_vacant;

int score[5] = {0, 1, 10, 100, 1000};
int total_score;

void Input(){
    cin >> n;
    for(int i=0; i<n*n; i++){
        int n0, n1, n2, n3, n4;
        cin >> n0 >> n1 >> n2 >> n3 >> n4;
        
        turn.push_back(n0);
        like[n0].push_back(n1);
        like[n0].push_back(n2);
        like[n0].push_back(n3);
        like[n0].push_back(n4);
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

pair<int, int> FindLoc(int curr){       // curr번 사람이 들어갈 가장 우선순위가 높은 위치를 반환하는 함수
    int curr_friend = 0, curr_vacant = 0;
    int nX, nY;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 현재 칸에서 인접한 네 방향을 보면서 좋아하는 친구와 비어있는 칸의 수 찾기
            if(grid[i][j]) continue;            // 숫자가 적혀있다면 패스
            curr_friend = 0, curr_vacant = 0;
            for(int d=0; d<4; d++){
                int nx = i + dirs[d][0], ny = j + dirs[d][1];
                if(InRange(nx, ny)){
                    // 비어있는 칸의 수 증가
                    if(grid[nx][ny] == 0)   curr_vacant++;
                    for(int k=0; k<4; k++){
                        // 좋아하는 친구가 있다면 증가
                        if(grid[nx][ny] == like[curr][k])
                            curr_friend++;
                    }
                }
            }

            if(curr_friend > max_friend || (curr_friend == max_friend && (max_vacant < curr_vacant))){
                max_friend = curr_friend;
                max_vacant = curr_vacant;
                nX = i, nY = j;
            }
        }
    }
    return make_pair(nX, nY);
}

void Simulate(){    // 입력으로 주어진 순서대로 가장 우선순위가 높은 칸으로 탑승시키는 함수
    for(int i=0; i<(int)turn.size(); i++){
        int curr = turn[i];
        //cout << "현재 보고있는 숫자: " <<curr << ' ';
        max_friend = -1, max_vacant = -1;
        // 1 다음 위치 찾기
        pair<int, int> Next = FindLoc(curr);
        //cout << Next.first << ' ' << Next.second << '\n';
        // 2. 그 위치에 번호 넣기
        grid[Next.first][Next.second] = curr;
    }

}   

void UpdateScore(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int curr = grid[i][j];
            int cnt = 0;
            for(int d=0; d<4; d++){
                int nx = i + dirs[d][0], ny = j + dirs[d][1];
                if(InRange(nx, ny)){
                    for(int k=0; k<4; k++){
                        // 좋아하는 친구가 있다면 증가
                        if(grid[nx][ny] == like[curr][k])
                            cnt++;
                    }
                }
            }
            total_score += score[cnt];
        }
    }
}

int main() {
    // 입력:
    Input();
    
    // 시뮬레이션 진행
    Simulate();
    // 점수 업데이트 하기
    UpdateScore();
    // 출력:
    cout << total_score;
    return 0;
}