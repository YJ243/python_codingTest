/*
 * 2024.2.6
 * 실수 1: pair<int, int> location[MAX_N*MAX_N+1] 여기에서 MAX_N*MAX_N이 아니라 MAX_N이라고 했음
 * 실수 2: grid[fromX][fromY].erase(grid[fromX][fromY].begin() + startIdx, grid[fromX][fromY].end());
 *         여기서 바로 insert하고 erase를 해서 location 업데이트가 되지 않았었음
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 20
#define MAX_M 100

using namespace std;
int n, m;
vector<int> grid[MAX_N][MAX_N];     // 숫자들이 저장되어 있는 격자판
pair<int, int> location[MAX_N*MAX_N+1];   // location[i]: i번 숫자의 위치
int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};    // 인접한 8개 방향

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int GetNextMaxValue(int x, int y){      // (x,y)위치에서의 가장 숫자를 반환
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
        // 인접한 8개 방향 확인
        int nx = x+dirs[d][0], ny = y+dirs[d][1];
        if(InRange(nx,ny) && grid[nx][ny].size() > 0){
            // 범위 안에 있고, 숫자가 하나 이상 있다면
            //그 칸에 있는 숫자들 중 현재 maxV보다 큰 숫자가 있는지 확인
            int next_v = GetNextMaxValue(nx,ny);
            maxV = max(maxV, next_v);
        }
    }

    return maxV;
}

void MoveTarget(int tgt, int maxV){     // tgt을 maxV 칸으로 옮기기
    // 0. 어디로 갈지 위치 저장
    int fromX = location[tgt].first, fromY = location[tgt].second;
    int toX = location[maxV].first, toY = location[maxV].second;

    // 1. tgt가 들어있는 칸에서 tgt부터 끝까지 숫자를 모두 옮기기
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

void Move(int tgt){     // tgt를 움직이는 함수
    // 1. tgt 주변 여덟방향에 대해서 제일 큰 숫자를 찾기
    int maxNumber = findMaxValue(tgt);
    // 1-1. 만약 인접한 여덟 방향에 아무 숫자도 없다면 움직이지 않음 
    if(maxNumber == 0) return;

    // 2-2. 제일 큰 숫자가 있는 칸으로 이동하기
    MoveTarget(tgt, maxNumber);

    return;
}

int main() {
    // 변수 선언 및 입력:
    cin >> n >> m;      // n: 격자 크기, m: 움직임 횟수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num;
            cin >> num;
            grid[i][j].push_back(num);
            location[num] = make_pair(i,j);
        }
    }
    // 움직일 m개의 숫자 입력받기
    for(int i=0; i<m; i++){
        int curr;
        cin >> curr;
        Move(curr);  
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