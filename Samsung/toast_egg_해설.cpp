/*
 * 2024.03.29
 * 해설 풀이 
 * 계란의 이동이 발생하는 총 횟수 = R, 각 이동에 대해 모든 격자를 최대 1번씩 보게 되므로
 * 시간복잡도: O(R*N^2)
*/

#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <queue>

#define MAX_N 50
#define DIR_NUM 4

using namespace std;

int n, L, R;                    // 토스트 틀 크기, L이상 R이하의 차이
int egg[MAX_N][MAX_N];         // 토스트 계란 양

queue<pair<int, int> > bfs_q;
vector<pair<int, int> > egg_group;
bool visited[MAX_N][MAX_N];

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int curr_egg) {
    if(!InRange(x, y))
      return false;
      
    int egg_diff = abs(egg[x][y] - curr_egg);
    return !visited[x][y] 
        && L <= egg_diff && egg_diff <= R;
}

// visited 배열을 초기화 해줍니다.
void InitializeVisited() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            visited[i][j] = false;
}

void BFS(){
    int dx[DIR_NUM] = {0, 1, 0, -1};
    int dy[DIR_NUM] = {1, 0, -1, 0};

    // BFS 탐색을 수행한다.
    while(!bfs_q.empty()){
        pair<int, int> curr_pos = bfs_q.front();
        int curr_x, curr_y;
        tie(curr_x, curr_y) = curr_pos;
        bfs_q.pop();

        for(int i=0; i<DIR_NUM; i++){
            int new_x = curr_x + dx[i];
            int new_y = curr_y + dy[i];

            // L, R 사이인 경우에만 합쳐질 수 있다.
            if(CanGo(new_x, new_y, egg[curr_x][curr_y])){
                bfs_q.push(make_pair(new_x, new_y));
                egg_group.push_back(make_pair(new_x, new_y));
                visited[new_x][new_y] = true;
            }
        }
    }
}

// 계란들을 합친다.
void MergeEggs(){
    int sum_of_eggs = 0;
    for(int k=0; k<(int)egg_group.size(); k++){
        int x, y;
        tie(x, y) = egg_group[k];
        sum_of_eggs += egg[x][y];
    }

    for(int k=0; k<(int)egg_group.size(); k++){
        int x, y;
        tie(x, y) = egg_group[k];
        egg[x][y] = sum_of_eggs / (int)egg_group.size();
    }
}

// 조건에 맞게 계란의 양을 바꿔준다.
bool MoveEggs(){
    // BFS 탐색을 위한 초기화 작업을 수행한다.
    InitializeVisited();

    bool is_changed = false;

    // 아직 방문하지 못한 칸에 대해  
    // BFS 탐색을 통해 합쳐질 계란들을 찾아낸다.
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!visited[i][j]){
                // 합쳐질 계란 목록을 담을 곳을 초기화한다.
                egg_group.clear();

                bfs_q.push(make_pair(i, j));
                egg_group.push_back(make_pair(i, j));
                visited[i][j] = true;

                BFS();

                // 계란의 이동이 한 번이라도 일어났는지를 확인한다.
                if((int)egg_group.size() > 1)
                    is_changed = true;
                
                // (i,j)와 관련이 있는 계란들을 합친다.
                MergeEggs();
            }
        }
    }
}
int main(){
    cin >> n >> L >> R;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> egg[i][j];
    
    int move_cnt = 0;

    // 이동이 더 이상 필요 없을 떄까지 계란의 이동을 반복한다.
    while(true){
        bool is_changed = MoveEggs();
        if(!is_changed)
            break;
        move_cnt++;
    }
    cout << move_cnt;
    return 0;
}