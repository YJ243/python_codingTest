/*
 * 2023.03.08
 * 폭탄을 놓아야 할 위치의 수: M => 총 3^M개의 가능한 모든 순열을 만들기
 * 각 순열에 대해 초토화되는 영역은 dx, dy 활용
 * 시간복잡도 O(3^M*N^2): 3^M개의 폭탄, N^2개의 격자 탐색
 * 공간복잡도 O(N^2)
*/

#include <iosteream>
#include <algorithm>
#include <vector>
#include <tuple>

#define MAX_N 20
#define BOMB_TYPE_NUM 3

using namespace std;

int n;
int bomb_type[MAX_N][MAX_N];
bool bombed[MAX_N][MAX_N];

int ans;

vector<pair<int, int> > bomb_pos;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Bomb(int x, int y, int b_type){
    // 폭탄 종류마다 터질 위치를 미리 정의한다.
    pair<int, int> bomb_shapes[BOMB_TYPE_NUM+1][5] = {
        {},
        { {-2, 0}, {-1, 0}, {0, 0},  {1, 0}, {2, 0}},
        { {-1, 0},  {1, 0}, {0, 0}, {0, -1}, {0, 1}},
        {{-1, -1}, {-1, 1}, {0, 0}, {1, -1}, {1, 1}}
    };

    // 격자 내 칸에 대해서만 영역을 표시한다.
    for(int i=0; i<5; i++){
        int dx, dy;
        tie(dx, dy) = bomb_shapes[b_type][i];

        int nx = x + dx, ny = y + dy;
        if(InRange(nx, ny))
            bombed[nx][ny] = true;
    }
}

int Calc(){
    // Step 1. 폭탄이 터진 위치를 표시하는 배열을 초기화한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            bombed[i][j] = false;
    
    // Step 2. 각 폭탄의 타입에 따라
    // 초토화 되는 영역을 표시한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(bomb_type[i][j])
                Bomb(i, j, bomb_type[i][j]);

    // Step 3. 초토화된 영역의 수를 구한다.
    int cnt = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(bombed[i][j])
                cnt++;
    return cnt;
}

void FindMaxArea(int cnt){
    if(cnt == (int) bomb_pos.size()){   // 만약 총 폭탄을 놓아야 할 곳에 모두 놓았다면
        ans = max(ans, Calc());
        return;
    }
    for(int i=1; i<=3; i++){
        int x, y;
        tie(x, y) = bomb_pos[cnt];

        bomb_type[x][y] = i;
        FindMaxArea(cnt+1);
        bomb_type[x][y] = 0;
    }
}

int main(){
    cin >> n;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            int bomb_place;
            cin >> bomb_place;
            if(bomb_place)
                bomb_pos.push_back(make_pair(i,j));
        }
    FindMaxArea(0);

    cout << ans;
    return 0;
}