/*
 * 2024.2.6
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define MAX_N 20
#define DIR_NUM 8
#define OUT_OF_GRID make_pair(-1,-1)


using namespace std;

int n, m;
vector<int> grid[MAX_N][MAX_N];     // 숫자들이 저장되어 있는 격자판


pair<int, int> location[MAX_N*MAX_N+1];   // location[i]: i번 숫자의 위치
int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};    // 인접한 8개 방향

pair<int, int> GetPos(int num) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < (int) grid[i][j].size(); k++)
                if(grid[i][j][k] == num)
                    return make_pair(i, j);
}

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 그 다음 위치를 찾아 반환합니다.
pair<int, int> NextPos(pair<int, int> pos) {
    int dx[DIR_NUM] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[DIR_NUM] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    int x, y;
    tie(x, y) = pos;
    
    // 인접한 8개의 칸 중 가장 값이 큰 위치를 찾아 반환합니다.
    int max_val = -1;
    pair<int, int> max_pos = OUT_OF_GRID;
    for(int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(InRange(nx, ny)) {
            for(int j = 0; j < (int) grid[nx][ny].size(); j++) {
                if(grid[nx][ny][j] > max_val) {
                    max_val = grid[nx][ny][j];
                    max_pos = make_pair(nx, ny);
                }
            }
        }
    }
    
    return max_pos;
}

void Move(pair<int, int> pos, pair<int, int> next_pos, int move_num) {
    int x, y;
    tie(x, y) = pos;
    
    int nx, ny;
    tie(nx, ny) = next_pos;
    
    // Step1. (x, y) 위치에 있던 숫자들 중
    // move_num 위에 있는 숫자들을 전부 옆 위치로 옮겨줍니다.
    bool to_move = false;
    for(int i = 0; i < (int) grid[x][y].size(); i++) {
        if(grid[x][y][i] == move_num)
            to_move = true;
        
        if(to_move)
            grid[nx][ny].push_back(grid[x][y][i]);
    }
    
    // Step2. (x, y) 위치에 있던 숫자들 중
    // 움직인 숫자들을 전부 비워줍니다.
    while(grid[x][y].back() != move_num)
        grid[x][y].pop_back();
    grid[x][y].pop_back();
}

void Simulate(int move_num) {
    // 그 다음으로 나아가야할 위치를 구해
    // 해당 위치로 숫자들을 옮겨줍니다.
    pair<int, int> pos = GetPos(move_num);
    pair<int, int> next_pos = NextPos(pos);
    if(next_pos != OUT_OF_GRID)
        Move(pos, next_pos, move_num);
}


int main() {
    // 변수 선언 및 입력:
    cin >> n >> m;      // n: 격자 크기, m: 움직임 횟수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num;
            cin >> num;
            grid[i][j].push_back(num);
        }
    }
    // 움직일 m개의 숫자 입력받기
    while(m--) {
		int move_num;
		cin >> move_num;
        Simulate(move_num);
	}

    // 각 위치에 적혀있는 숫자를 출력하기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 만약 해당 위치에 아무 숫자도 없다면
            if(grid[i][j].size() == 0){
                cout << "None" << '\n';
            }
            // 만약 숫자가 있다면 
            else{
                for(int idx = grid[i][j].size()-1; idx >= 0; idx--)
                    cout << grid[i][j][idx] << ' ';
                cout << '\n';
            }
        }
    }
      
    
    return 0;
}