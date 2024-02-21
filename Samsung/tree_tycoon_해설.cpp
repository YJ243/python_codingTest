/*
 * 2024.02.21
 * 내 풀이
*/

#include <iostream>
#include <tuple>

#define MAX_N 15
#define DIR_NUM 8

using namespace std;

int n, m;
int height[MAX_N][MAX_N];

bool fertilizer[MAX_N][MAX_N];
bool next_fert[MAX_N][MAX_N];

// 문제에서 주어진 순서대로 → ↗ ↑ ↖ ← ↙ ↓ ↘
int dx[DIR_NUM] = {0, -1, -1, -1,  0,  1, 1, 1};
int dy[DIR_NUM] = {1,  1,  0, -1, -1, -1, 0, 1};

void InitFertilizer() {
    for(int i = n - 2; i < n; i++)
        for(int j = 0; j < 2; j++)
            fertilizer[i][j] = true;
}

pair<int, int> NextPos(int x, int y, int d, int p){
    int nx = (x + dx[d]*p + n*p) % n;
    int ny = (y + dy[d]*p + n*p) % n;

    return make_pair(nx, ny);
}

void Move(int d, int p){
    // Step 1. 그 다음 fert 위치를 저장할 next_fert를 초기화한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_fert[i][j] = false;

    // Step 2. 각 영양제를 이동시킨다.
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            if(fertilizer[i][j]){
                int nx, ny;
                tie(nx, ny) = NextPos(i, j, d, p);
                next_fert[nx][ny] = true;
            }
        }
    
    // Stpe 3. next_fert 값을 fert로 옮겨주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            fertilizer[i][j] = next_fert[i][j];
}

void Grow(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(fertilizer[i][j])
                height[i][j]++;
}

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int GetDiagCnt(int x, int y){
    int cnt = 0;
    for(int i = 1; i < DIR_NUM; i += 2) {
        int nx = x + dx[i], ny = y + dy[i];
        if(InRange(nx, ny) && height[nx][ny] >= 1)
            cnt++;
    }

    return cnt;
}

void DiagonalGrow(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(fertilizer[i][j]){
                int cnt = GetDiagCnt(i,j);
                height[i][j] += cnt;
            }
}

void DetermineFert(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            // 기존 특수 영양제는 없애주고
            if(fertilizer[i][j])
                fertilizer[i][j] = false;
            // 새로운 특수 영양제는 추가해주기
            else if(height[i][j] >= 2){
                fertilizer[i][j] = true;
                height[i][j] -= 2;
            }
        }
}

void Simulate(int d, int p){
    // Step 1. 특수 영양제를 이동시킨다.
    Move(d, p);

    // Step 2. 특수 영양제 위치에 있던 리브로스가 성장한다.
    Grow();

    // Step 3. 대각선 방향의 높이가 1 이상인 리브로스 만큼 더 성장한다
    DiagonalGrow();

    // Step 4. 새로운 특수 영양제를 추가하고, 기존 영양제를 없애준다.
    DetermineFert();
}

int GetScore(){
    int sum = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            sum += height[i][j];
    return sum;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> height[i][j];
    
    InitFertilizer();

    // m번에 걸쳐 시뮬레이션을 진행한다.
    while(m--){
        int d, p;
        cin >> d >> p;

        Simulate(d-1, p);
    }

    int ans = GetScore();
    cout << ans;

    return 0;
}