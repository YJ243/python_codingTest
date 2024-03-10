/*
 * 2024.02.25
 * 내 풀이
*/

#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 50
#define MAX_S 1000

using namespace std;

typedef tuple<int, int, int> marble;        // 구슬의 질량, 속력, 방향 저장
int n, m, k;                                // n: 격자 크기, m: 원자 개수, k: 실험 시간

vector<marble> grid[MAX_N][MAX_N];
vector<marble> temp[MAX_N][MAX_N];

// 상부터 시계방향으로
int dirs[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

void Input(){
    cin >> n >> m >> k;
    while(m--){
        int x, y, m, s, d;      // (x,y) 위치, m질량, s속력, d방향
        cin >> x >> y >> m >> s >> d;
        grid[x-1][y-1].push_back(make_tuple(m, s, d));
    }
}

void Initialize_temp(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            temp[i][j].clear();
}

void Move(int x, int y){        // (x,y) 칸에 있는 구슬을 모두 옮기기
    for(int k=0; k<(int)grid[x][y].size(); k++){
        int m, s, d;
        tie(m, s, d) = grid[x][y][k];
        // s만큼 d방향으로 움직이기
        int nx = (x + dirs[d][0] + n*s)%n;
        int ny = (y + dirs[d][1] + n*s)%n;
        
        temp[nx][ny].push_back(make_tuple(m, s, d));
    }

}

void Compound_marble(int x, int y){     // temp 배열에서 (x,y) 자리에 있는 구슬 합성하기
    int total_m = 0, total_s = 0;       // 현재 칸에 있는 구슬의 총 질량과 속력 합
    int next_m = 0, next_s = 0;         // 현재 칸에 다음으로 쪼개질 원자의 질량과 속력
    bool isDir1 = false, isDir2 = false;    // Dir1은 상하좌우, Dir2는 대각선방향, 해당 방향이 존재하는지 확인

    for(int k=0; k < (int)temp[x][y].size(); k++){
        int m, s, d;
        tie(m, s, d) = temp[x][y][k];

        total_m += m; total_s += s;
        if(d % 2 == 0) isDir1 = true;
        else           isDir2 = true;
    }
    next_m = total_m/5;
    next_s = total_s/(int)temp[x][y].size();

    temp[x][y].clear();         // 일단 먼저 해당 칸 비워놓고
    if(next_m == 0) return;     // 만약 질량이 0이라면 사라지는 것이니 바로 리턴

    int start_d;
    if(isDir1 == true && isDir2 == true)   // 만약 상하좌우, 대각선 방향이 둘다 있다면 대각선 방향
        start_d = 1;
    else
        start_d = 0;

    for(int i=start_d; i<8; i += 2)
            temp[x][y].push_back(make_tuple(next_m, next_s, i));   
}

void Simulate(){
    // Step 0. 움직이기 전 temp 배열 초기화
    Initialize_temp();

    // Step 1. 모든 격자를 차례대로 보면서 구슬이 있다면 해당 속력, 방향대로 이동시키기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(grid[i][j].size() > 0)
                Move(i,j);
    // Step 2. 합성 진행해주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(temp[i][j].size() >= 2)
                Compound_marble(i,j);

    // Step 3. temp 배열을 다시 grid 배열로 옮겨주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            grid[i][j].clear();
            if((int)temp[i][j].size() > 0)
                grid[i][j] = temp[i][j];
        }
}

void Output(){
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if((int)grid[i][j].size() > 0){
                for(int k=0; k<(int)grid[i][j].size(); k++){
                    int m;
                    tie(m, ignore, ignore) = grid[i][j][k];
                    ans += m;
                }
            }
        }
    }
    cout << ans << '\n';
}

int main(){
    // 입력 받기
    Input();

    // k초 동안 시뮬레이션 진행
    while(k--){
        Simulate();
    }

    // 출력하기
    Output();
    return 0;
}