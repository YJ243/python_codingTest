/*
 * 2024.03.25
 * 중간중간에 빼먹은 조건들이 많았다. 문제를 좀더 많이 읽고 코드를 작성하자.
 * 파란색 or 범위 벗어날 때 방향 바꿔서 다시 다음 위치를 정함. 여기서 그 다음 위치도 범위를 벗어날 수 있다는 것을 빼먹음
 * 그리고 그 다음 위치가 흰색이 아니라 빨간색일 수도 있다는 것을 빼먹음!!!
 * i번째 말의 그 다음 방향을 반영해주는 코드도 빼먹음
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define MAX_N 12
#define MAX_K 10

using namespace std;
int n, k;
int color[MAX_N][MAX_N];
vector<pair<int, int> > grid[MAX_N][MAX_N];   // grid[i][j]: [i][j]에 있는 (말의 번호, 그 말의 방향)
int dirs[4][2] = {{0, 1},{0, -1},{-1, 0},{1,0}};    // 우, 좌, 상, 하

void Input(){       // 입력을 받는 함수
    cin >> n >> k;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> color[i][j];
    for(int i=0; i<k; i++){
        int x, y, d;
        cin >> x >> y >> d;
        grid[x-1][y-1].push_back(make_pair(i, d-1));
    }

}

bool IsFinish(){    // 게임이 종료되었는지 확인하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if((int)grid[i][j].size() >= 4)  // 만약 말이 4개 이상 겹쳐지는 경우가 생긴다면
                return true;            // 게임이 끝났다는 의미로 true 반환
        }
    }
    return false;       // 그렇지 않으면 아직 게임이 끝나지 않음
}

tuple<int, int, int> GetPiece(int num){     // num번째 말의 위치와 방향을 구해주는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int l=0; l<(int)grid[i][j].size(); l++){
                if(grid[i][j][l].first == num){
                    return make_tuple(i, j, grid[i][j][l].second);
                }
            }
        }
    }
}

bool InRange(int x, int y){                 // (x,y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y, vector<pair<int, int> > tmp, bool reversed){
    // 만약 뒤집어야 한다면 뒤집기
    if(reversed)
        reverse(tmp.begin(), tmp.end());
    grid[x][y].insert(grid[x][y].end(), tmp.begin(), tmp.end());
}

bool Simulate(){    // 0번 ~ k-1번의 말을 차례대로 이동시키는 함수, 만약 더이상 이동할 수 없다면 false 반환
    for(int i=0; i<k; i++){
        int x, y, d;
        bool needToReverse = false;
        tie(x, y, d) = GetPiece(i);    // i번 말의 위치와 방향을 가져오기
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        
        if(!InRange(nx, ny) || color[nx][ny] == 2){     // 다음 이동할 곳이 범위 밖이거나 파란색이라면
            d = (d % 2 == 0) ? d+1 : d-1;               // 방향 바꾸기
            nx = x + dirs[d][0], ny = y + dirs[d][1];   // 다시 위치 확인하기
            
            if(!InRange(nx, ny) || color[nx][ny] == 2)
                nx = x, ny = y;
            else if(color[nx][ny] == 1){    // 만약 이동할 곳이 빨간색이라면 
                needToReverse = true;       // 방향 전환해야 함
            }

        }
        else if(color[nx][ny] == 1){
            needToReverse = true;
        }

        vector<pair<int, int> > tmp; //= assign(grid[x][y].begin() + )
        int a;
        for(a=0; a<(int)grid[x][y].size(); a++){
            if(grid[x][y][a].first == i){
                tmp.assign(grid[x][y].begin() + a, grid[x][y].end());
                break;
            }
        }
        tmp[0] = make_pair(i, d);
        grid[x][y].erase(grid[x][y].begin() + a, grid[x][y].end());
        Move(nx, ny, tmp, needToReverse);

        
        if(IsFinish())
            return false;
    }    
    return true;
}

int main() {
    // 입력 받기:
    Input();    
    
    // 시뮬레이션
    int ans = -1;
    for(int turn = 1; turn <= 1000; turn++){
        if(!Simulate()){    // 게임이 종료됐다면
            ans = turn;     // 종료되는 순간의 턴의 번호
            break;
        }
    }
    cout << ans;
    return 0;
}