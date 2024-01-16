/*
 * 2시간 넘게 잡고 풀었지만... 답이 틀림
 * backtracking으로 풀었는데 어디서 고쳐야될 지 모르겠음
*/

#include <iostream>
#include <vector>

#define MAX_N 20
#define MAX_M 10

using namespace std;
int n, m;
int grid[MAX_N][MAX_N];
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
bool visited[MAX_N][MAX_N];
vector<int> locations;
int goldCnt;
int curGoldCnt;
int maxDist;
int ans;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int Calculate(int x, int y){
    int curr = 0, curX = x, curY = y;
    for(int i=0; i<(int)locations.size(); i++){
        int nx = curX+dirs[locations[i]][0], ny = curY+dirs[locations[i]][1];
        if(InRange(nx,ny) && !visited[nx][ny]){
            if(grid[nx][ny])
                curr += grid[nx][ny];
            visited[nx][ny] = true;
            curX = nx, curY = ny;

        }
    }
    return curr;
}

void Move(int x, int y, int dist){
    if(dist >= maxDist){
        curGoldCnt += Calculate(x,y);
        return;
    }

    for(int i=0; i<4; i++){
        locations.push_back(i);
        Move(x,y,dist+1);
        locations.pop_back();
    }
}

void FindMaxGold(int x, int y){     // (x,y)에서 갈 수 있는 최대까지 움직이며 금을 최대한 많이 찾는 함수
    for(int k=0; (k*k)+(k+1)*(k+1) <= goldCnt*m; k++){
        // k는 움직이는 거리, 총 비용이 가장 많은 금을 채굴하고도 더 남기 전까지만 찾기
        maxDist = k;
        curGoldCnt = grid[x][y];
        locations.clear();
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                visited[i][j] = false;
        visited[x][y] = true;
        Move(x,y,0);
        ans = max(ans, curGoldCnt);
    }
}

int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j])  goldCnt++;
        }
    }

    // 채굴할 수 있는 금의 개수 탐색
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // (i,j)에서 갈 수 있는 최대까지 가기
            FindMaxGold(i,j);
        }
    }
    cout << ans;

    return 0;
}