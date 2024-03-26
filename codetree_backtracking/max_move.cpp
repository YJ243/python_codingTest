/*
 * 2024.03.22
 * 내 풀이
 * 움직일 떄 *i안해줘서 틀림
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

#define MAX_N 4
using namespace std;

int n, ans;
int final_ans;
int grid[MAX_N][MAX_N];
int direction[MAX_N][MAX_N];
int dirs[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int r, c;
vector<pair<int, int> > selected;

bool InRange(int x, int y){         // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int val){  // (x,y)로 갈 수 있는지 확인하는 함수
    return InRange(x, y) && grid[x][y] > val;
}

bool IsFinish(){
    int cr = selected.back().first, cc = selected.back().second;
    int cur_dir = direction[cr][cc];
    int cnt = 0;
    for(int i=1; i<n; i++){
        int nr = cr + dirs[cur_dir][0]*i, nc = cc + dirs[cur_dir][1]*i;
        if(CanGo(nr, nc, grid[cr][cc])){
            cnt++;
        }
    }
    if(cnt > 0)
        return false;
    return true;
}

void Choose(int idx){
    final_ans = max(ans, final_ans);
    //cout << ans << '\n';
    if(IsFinish()){       // 종료조건을 언제 만들어야 하는가?
        return;
    }

    int cr = selected.back().first, cc = selected.back().second;
    int cur_dir = direction[cr][cc];
    for(int i=1; i<n; i++){
        int nr = cr + dirs[cur_dir][0]*i, nc = cc + dirs[cur_dir][1]*i;
        if(CanGo(nr, nc, grid[cr][cc])){
            
            ans++;  // 정답 증가
            selected.push_back(make_pair(nr, nc));
            Choose(idx+1);
            ans--;
            selected.pop_back();
        }
    }
}

int main() {
    // 입력 받기
    cin >> n;                       // 격자 크기
    for(int i=0; i<n; i++)          // 격자 내 숫자
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    for(int i=0; i<n; i++){         // 방향
        for(int j=0; j<n; j++){
            cin >> direction[i][j];
            direction[i][j]--;
        }
    }
    cin >> r >> c;
    selected.push_back(make_pair(r-1,c-1));
    Choose(0);  // 처음 위치 다음으로 0번째를 선택하러 가는 함수
    cout << final_ans;
    return 0;
}