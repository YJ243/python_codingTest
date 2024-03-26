/*
 * 2024.03.25
 * 해설 풀이
 * 1. 현재 이동할 말이 있는 칸을 찾는다.
 * 2. 이동할 말과 그 위에 있는 모든 말들의 목록을 가져온다.
 * 3. 말이 이동할 다음 칸의 색상에 따라 알고리즘을 다르게 적용한다.
 * 3-1. 흰색이면 그대로 이동
 * 3-2. 빨간색인 경우 말의 순서를 뒤집고 이동
 * 3-3. 파란색 또는 격자 밖으로 이동하는 경우 방향을 반대로 하고 다시 이동 시도
 * 4. 말의 새로운 위치에 말을 쌓는다.
 * 5. 이동한 결과가 게임을 종료하는 조건을 만족하는지 확인한다.
 * 시간복잡도: 각 턴마다 모든 말을 확인하고 이동하는데 걸리는 시간 고려했을 때 매 턴 N^2*K만큼 연산 필요
 * O(T*N^2*K)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define MAX_N 12
#define DIR_NUM 4
#define WHITE 0
#define RED 1
#define BLUE 2

using namespace std;

int n, k;
int board[MAX_N][MAX_N];
vector<pair<int, int> > pieces_grid[MAX_N][MAX_N];

tuple<int, int, int> FindPiece(int target_num){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < (int) pieces_grid[i][j].size(); k++) {
                int piece_num, move_dir;
                tie(piece_num, move_dir) = pieces_grid[i][j][k];
                if(piece_num == target_num)
                    return make_tuple(i, j, move_dir);
            }
}

// 1턴 진행한다.
bool Simulate(){
    // 문제에서 주어진 순서인
    // 오른족, 왼쪽, 위, 아래 순으로 적어주기
    int dx[DIR_NUM] = {0,0,-1,1};
    int dy[DIR_NUM] = {1,-1,0,0};

    // 번호 순서대로 한 번씩 움직인다.
    for(int num=0; num < k; num++){
        int piece_x, piece_y, move_dir;
        tie(piece_x, piece_y, move_dir) = FindPiece(num);

        int next_x = piece_x + dx[move_dir];
        int next_y = piece_y + dy[move_dir];

        bool need_reverse = false;

        // 그 다음 위치가 격자를 벗어나거나 파란색 지점인 경우
        // 현재 위치에서 방향을 전환한 뒤 이동한다.
        if(!InRange(next_x, next_y) || board[next_x][next_y] == BLUE){
            move_dir = (move_dir % 2 == 0) ? (move_dir + 1) : (move_dir - 1);
            next_x = piece_x + dx[movd_dir];
            next_y = piece_y + dy[move_dir];
            // 방향 전환 후 그 다음 위치로 이동이 불가하거나 파란색 지점인 경우 그대로 멈춰있는다.
            if(!InRange(next_x, next_y) || board[next_x][next_y] == BLUE)
                next_x = piece_x, next_y = piece_y;
            // 만약 이동이 가능하다면, 빨간색 지점일 경우 뒤집어서 이동해야 한다.
            else if(board[next_x][next_y] == RED)
                need_reverse = true;
        }
        // 만약 가려는 곳이 빨간색 지점인 경우라면 순서를 뒤집어서 이동해야 한다.
        else if(board[next_x][next_y] == RED)
            need_reverse = true;
        
        // 현재 piece 포함 위에 있는 모든 말들을 빼온다.
        vector<pair<int, int> > pieces = PopPieces(piece_x, piece_y, num);

        // num번 말의 그 다음 방향을 반영해준다.
    }
}




int main(){
    cin >> n >> k;
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> board[i][j];
 
    for(int num = 0; num < k; num++) {
        int x, y, d;
        cin >> x >> y >> d;
        pieces_grid[x - 1][y - 1].push_back(make_pair(num, d - 1));
    }
    
    int ans = -1;
    
    // 최대 1000번 턴을 진행해봅니다.
    for(int t = 1; t <= 1000; t++) {
        bool is_done = Simulate();
        // 4개 이상이 겹쳐진 경우가 생긴다면
        // 턴을 종료합니다.
        if(is_done) {
            ans = t;
            break;
        }
    }

    cout << ans;
    return 0;
}