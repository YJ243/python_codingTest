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
vector<int> grid[MAX_N][MAX_N];     // ���ڵ��� ����Ǿ� �ִ� ������


pair<int, int> location[MAX_N*MAX_N+1];   // location[i]: i�� ������ ��ġ
int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};    // ������ 8�� ����

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

// �� ���� ��ġ�� ã�� ��ȯ�մϴ�.
pair<int, int> NextPos(pair<int, int> pos) {
    int dx[DIR_NUM] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[DIR_NUM] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    int x, y;
    tie(x, y) = pos;
    
    // ������ 8���� ĭ �� ���� ���� ū ��ġ�� ã�� ��ȯ�մϴ�.
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
    
    // Step1. (x, y) ��ġ�� �ִ� ���ڵ� ��
    // move_num ���� �ִ� ���ڵ��� ���� �� ��ġ�� �Ű��ݴϴ�.
    bool to_move = false;
    for(int i = 0; i < (int) grid[x][y].size(); i++) {
        if(grid[x][y][i] == move_num)
            to_move = true;
        
        if(to_move)
            grid[nx][ny].push_back(grid[x][y][i]);
    }
    
    // Step2. (x, y) ��ġ�� �ִ� ���ڵ� ��
    // ������ ���ڵ��� ���� ����ݴϴ�.
    while(grid[x][y].back() != move_num)
        grid[x][y].pop_back();
    grid[x][y].pop_back();
}

void Simulate(int move_num) {
    // �� �������� ���ư����� ��ġ�� ����
    // �ش� ��ġ�� ���ڵ��� �Ű��ݴϴ�.
    pair<int, int> pos = GetPos(move_num);
    pair<int, int> next_pos = NextPos(pos);
    if(next_pos != OUT_OF_GRID)
        Move(pos, next_pos, move_num);
}


int main() {
    // ���� ���� �� �Է�:
    cin >> n >> m;      // n: ���� ũ��, m: ������ Ƚ��
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num;
            cin >> num;
            grid[i][j].push_back(num);
        }
    }
    // ������ m���� ���� �Է¹ޱ�
    while(m--) {
		int move_num;
		cin >> move_num;
        Simulate(move_num);
	}

    // �� ��ġ�� �����ִ� ���ڸ� ����ϱ�
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // ���� �ش� ��ġ�� �ƹ� ���ڵ� ���ٸ�
            if(grid[i][j].size() == 0){
                cout << "None" << '\n';
            }
            // ���� ���ڰ� �ִٸ� 
            else{
                for(int idx = grid[i][j].size()-1; idx >= 0; idx--)
                    cout << grid[i][j][idx] << ' ';
                cout << '\n';
            }
        }
    }
      
    
    return 0;
}