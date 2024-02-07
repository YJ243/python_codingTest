/*
 * 2024.2.6
 * �Ǽ� 1: pair<int, int> location[MAX_N*MAX_N+1] ���⿡�� MAX_N*MAX_N�� �ƴ϶� MAX_N�̶�� ����
 * �Ǽ� 2: grid[fromX][fromY].erase(grid[fromX][fromY].begin() + startIdx, grid[fromX][fromY].end());
 *         ���⼭ �ٷ� insert�ϰ� erase�� �ؼ� location ������Ʈ�� ���� �ʾҾ���
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 20
#define MAX_M 100

using namespace std;
int n, m;
vector<int> grid[MAX_N][MAX_N];     // ���ڵ��� ����Ǿ� �ִ� ������
pair<int, int> location[MAX_N*MAX_N+1];   // location[i]: i�� ������ ��ġ
int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};    // ������ 8�� ����

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int GetNextMaxValue(int x, int y){      // (x,y)��ġ������ ���� ���ڸ� ��ȯ
    int maxValue = 0;
    for(int i=0; i<(int)grid[x][y].size(); i++){
        if(grid[x][y][i] > maxValue){
            maxValue = grid[x][y][i];
        }
    }
    return maxValue;
}


int findMaxValue(int tgt){
    int x = location[tgt].first, y = location[tgt].second;
    int maxV=0;
    for(int d=0; d<8; d++){
        // ������ 8�� ���� Ȯ��
        int nx = x+dirs[d][0], ny = y+dirs[d][1];
        if(InRange(nx,ny) && grid[nx][ny].size() > 0){
            // ���� �ȿ� �ְ�, ���ڰ� �ϳ� �̻� �ִٸ�
            //�� ĭ�� �ִ� ���ڵ� �� ���� maxV���� ū ���ڰ� �ִ��� Ȯ��
            int next_v = GetNextMaxValue(nx,ny);
            maxV = max(maxV, next_v);
        }
    }

    return maxV;
}

void MoveTarget(int tgt, int maxV){     // tgt�� maxV ĭ���� �ű��
    // 0. ���� ���� ��ġ ����
    int fromX = location[tgt].first, fromY = location[tgt].second;
    int toX = location[maxV].first, toY = location[maxV].second;

    // 1. tgt�� ����ִ� ĭ���� tgt���� ������ ���ڸ� ��� �ű��
    int startIdx = 0;
    for(int i=0; i<(int)grid[fromX][fromY].size(); i++){
        if(grid[fromX][fromY][i] == tgt){
            startIdx = i;
            break;
        }
    }
    
    for(int i=startIdx; i < (int)grid[fromX][fromY].size(); i++){
        int curr = grid[fromX][fromY][i];
        location[curr] = make_pair(toX,toY);
        grid[toX][toY].push_back(curr);

    }
    grid[fromX][fromY].erase(grid[fromX][fromY].begin() + startIdx, grid[fromX][fromY].end());
}

void Move(int tgt){     // tgt�� �����̴� �Լ�
    // 1. tgt �ֺ� �������⿡ ���ؼ� ���� ū ���ڸ� ã��
    int maxNumber = findMaxValue(tgt);
    // 1-1. ���� ������ ���� ���⿡ �ƹ� ���ڵ� ���ٸ� �������� ���� 
    if(maxNumber == 0) return;

    // 2-2. ���� ū ���ڰ� �ִ� ĭ���� �̵��ϱ�
    MoveTarget(tgt, maxNumber);

    return;
}

int main() {
    // ���� ���� �� �Է�:
    cin >> n >> m;      // n: ���� ũ��, m: ������ Ƚ��
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num;
            cin >> num;
            grid[i][j].push_back(num);
            location[num] = make_pair(i,j);
        }
    }
    // ������ m���� ���� �Է¹ޱ�
    for(int i=0; i<m; i++){
        int curr;
        cin >> curr;
        Move(curr);  
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