/*
 * 2024.03.26
 * 바이러스 백신
 * 내 풀이
 * 코드 작성 + 디버깅까지 30분 걸림
 * 실수 1: 벽을 제외한 지역에 백신이 공급되는데, 바이러스에만 백신이 공급된다고 풀음
 * 실수 2: 큐에다가 넣을 때 selected를 봐야 하는데 hospitals를 봤음..
*/

#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_N 50
#define MAX_M 10

using namespace std;
int n, m;
int grid[MAX_N][MAX_N];
int spreadSec[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
vector<pair<int, int> > hospitals;
vector<int> selected;

queue<pair<int, int> > q;
int dirs[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int ans = INT_MAX;

void Input(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 2){
                hospitals.push_back(make_pair(i, j));   // 만약 병원이면 좌표 집어넣기
            }
        }
}

void Initialize_before_spread(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            spreadSec[i][j] = 0;        // 바이러스가 사라지는 시간(백신이 퍼진 시간) 0으로 초기화
            visited[i][j] = false;      // 방문 배열 초기화
        }
    }

}

bool InRange(int x, int y){         // (x, y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){           // (x, y)로 이동할 수 있는지 확인하는 함수
    return InRange(x, y) && !visited[x][y] && grid[x][y] != 1; 
}

void bfs(){
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first, y = curr.second;
        for(int d=0; d<4; d++){
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            if(CanGo(nx, ny)){
                q.push(make_pair(nx, ny));
                visited[nx][ny] = true;
                spreadSec[nx][ny] = spreadSec[x][y] + 1;
            }
        }
    }
}

bool DestroyAllVirus(){         // 모든 바이러스가 사라졌는지 확인하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 0 && !visited[i][j])   // 만약 바이러스가 있는 칸인데 방문하지 않았다면, 아직 바이러스가 남아 있는 것.
                return false;
        }
    }
    return true;
}

int Calc(){
    int ret = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == 0)
                ret = max(ret, spreadSec[i][j]);
        }
    }
    return ret;
}
/*
void Print(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << spreadSec[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
*/
void SpreadVaccine(){
    // 1. 백신 시간과 방문 배열 초기화
    Initialize_before_spread();

    // 2. 큐에 집어넣기
    for(int i=0; i<(int)selected.size(); i++){
        int x = hospitals[selected[i]].first, y = hospitals[selected[i]].second;
        q.push(hospitals[selected[i]]);
        visited[x][y] = true;
    }
    // 3.  탐색 시작
    bfs();
    //Print();
    int total_sec = 0;
    // 4. 바이러스가 사라지는데 총 몇 초가 걸리는지 계산하기
    if(DestroyAllVirus()){
        total_sec = Calc();
    }
    else
        total_sec = INT_MAX;
    ans = min(ans, total_sec);
}

void ChooseHospital(int idx){
    if((int)selected.size() == m){
        SpreadVaccine();
        return;
    }

    for(int i=idx; i <(int)hospitals.size(); i++){
        selected.push_back(i);
        ChooseHospital(i+1);
        selected.pop_back();
    }
}

int main() {
    // 입력:
    Input(); 

    // m개의 병원 선택하기
    ChooseHospital(0);
    if(ans == INT_MAX)
        ans = -1;
    cout << ans;
    return 0;
}