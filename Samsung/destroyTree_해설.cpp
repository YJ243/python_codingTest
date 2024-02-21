/*
 * 2024.02.19
 * 나무 박멸
 * 해설 풀이
 * 성장, 번식, 제초제 처리의 3가지 과정을 조화롭게 관리하는 시뮬레이션
 * 처리해야 할 연도 수(M)만큼 이 과정을 반복하여 나무를 박멸하니 O(M * N^2)
*/

#include <iostream>

#define MAX_N 20
#define DIR_NUM 4

using namespace std;

int n, m, k, c;
int tree[MAX_N+1][MAX_N+1];
int add_tree[MAX_N+1][MAX_N+1];
int herb[MAX_N+1][MAX_N+1];

int ans;

bool IsOutRange(int x, int y) {
    return !(1 <= x && x <= n && 1 <= y && y <= n);
}

// 입력을 받는 등 초기 작업을 진행
void Init(){
    cin >> n >> m >> k >> c;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
    		cin >> tree[i][j];
}

// 1단계: 인접한 네 개의 칸 중 나무가 있는 칸의 수만큼 나무가 성장
void StepOne(){
    int dx[DIR_NUM] = {-1,0,1,0};
    int dy[DIR_NUM] = {0,-1,0,1};

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            if(tree[i][j] <= 0) continue;

            // 나무가 있는 칸의 수(cnt)만큼 나무가 성장한다.
            int cnt = 0;
            for(int dir = 0; dir < 4; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(IsOutRange(nx, ny)) continue;
                if(tree[nx][ny] > 0) cnt++;
            }
            tree[i][j] += cnt;
        }
}

// 2단계: 기존에 있었던 나무들은 아무것도 없는 칸에 번식을 진행
void StepTwo(){
    int dx[DIR_NUM] = {-1,  0, 1, 0};
    int dy[DIR_NUM] = { 0, -1, 0, 1};

    // 모든 나무에서 동시에 일어나는 것을 구현하기 위해 하나의 배열을 더 이용한다.
    // add_tree를 초기화해준다.
    for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) 
            add_tree[i][j] = 0;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            if(tree[i][j] <= 0) continue;

            // 해당 나무와 인접한 칸 중 아무도 없는 칸의 개수를 찾기
            for(int dir = 0; dir < 4; dir++) {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(IsOutRange(nx, ny)) continue;
                if(herb[nx][ny]) continue;
                if(tree[nx][ny] == 0) cnt++;
            }

            // 인접한 나무 중 아무도 없는 칸은 cnt로 나눠준 만큼 번식한다.
            for(int dir = 0; dir < 4; dir++) {
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(IsOutRange(nx, ny)) continue;
                if(herb[nx][ny]) continue;
                if(tree[nx][ny] == 0) add_tree[nx][ny] += tree[i][j] / cnt;
            }
        }

    // add_tree를 더해 번식을 동시에 진행시킨다.
    for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) tree[i][j] += add_tree[i][j];
}

// 3단계: 가장 많이 박멸되는 칸에 제초제를 뿌리기
void StepTree(){
    int dx[DIR_NUM] = {-1,  1, 1, -1};
    int dy[DIR_NUM] = {-1, -1, 1,  1};

    int max_del = 0;
    int max_x = 1;
    int max_y = 1;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            // 모든 칸에 대해 제초제를 뿌려본다. 각 칸에서 제초제를 뿌릴 시 박멸되는 나무와 그루 수를 계산하고,
            // 이 값이 최대가 되는 지점을 찾기
            if(tree[i][j] <= 0) continue;
            int cnt = tree[i][j];
            for(int dir = 0; dir < 4; dir++){
                int nx = i, ny = j;
                for(int x=1; x <= k; x++){
                    nx = nx+dx[dir];
                    ny = ny+dy[dir];
                    if(IsOutRange(nx, ny)) break;
                    if(tree[nx][ny] <= 0) break;
                    cnt += tree[nx][ny];
                }
            }
            if(max_del < cnt){
                max_del = cnt;
                max_x = i;
                max_y = j;
            }
        }
    ans += max_del;

    // 찾은 칸에 제초제를 뿌리기
    if(tree[max_x][max_y] > 0){
        tree[max_x][max_y] = 0;
        herb[max_x][max_y] = c;
        for(int dir = 0; dir < 4; dir++){
            int nx = max_x;
            int ny = max_y;
            for(int x = 1; x <= k; x++){
                nx = nx+dx[dir];
                ny = ny+dy[dir];
                if(IsOutRange(nx,ny)) break;
                if(tree[nx][ny] < 0) break;
                if(tree[nx][ny] == 0){
                    herb[nx][ny] = c;
                    break;
                }
                tree[nx][ny] = 0;
                herb[nx][ny] = c;
            }
        }
    }
}

// 제초제의 기간을 1년 감소시킨다.
void DeleteHerb(){
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            if(herb[i][j] > 0)
                herb[i][j] -= 1;
}

int main(){
    // 입력을 받는 등 초기 작업을 하기
    Init();

    for(int i=1; i<=m; i++){
        // 1단계: 인접한 네 개의 칸 중 나무가 있는 칸의 수만큼 나무가 성장
        StepOne();

        // 2단계: 기존에 있었떤 나무들은 아무것도 없는 칸에 번식을 진행
        StepTwo();

        // 제초제의 기간을 1년 감소시킨다.
        DeleteHerb();

        // 3단계: 가장 많이 박멸되는 칸에 제초제를 뿌리기
        StepThree();
    }
    cout << ans;
    return 0;
}
