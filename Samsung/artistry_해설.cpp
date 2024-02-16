/*
 * 2024.02.16
 * 해설 풀이
 * 시간 복잡도: 각 회전마다 DFS를 통해 그룹을 형성하는데 최대 O(N^2), 모든 인접 칸을 확인하여 예술 점수를 계산하는데도 O(N^2),
 *             이를 네 번 반복하므로, 전체 시간복잡도는 O(4*N^2) = O(N^2)
 * 이 풀이에서는 따로 group배열을 만들어, 각 칸에 그룹 번호를 적어주는 식으로 해결했음(탐색 과정을 줄였음)
*/

#include <iostream>

#define MAX_N 29
#define DIR_NUM 4

using namespace std;

// 변수 선언
int n;
int arr[MAX_N][MAX_N];
int next_arr[MAX_N][MAX_N];

// 그룹의 개수를 관리한다
int group_n;

// 각 칸에 그룹 번호를 적어주기
int group[MAX_N][MAX_N];
int group_cnt[MAX_N * MAX_N + 1]; // 각 그룹마다 칸의 수를 세준다.

bool visited[MAX_N][MAX_N];

int dx[DIR_NUM] = {1, -1, 0,  0};
int dy[DIR_NUM] = {0,  0, 1, -1};

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

// (x, y) 위치에서 DFS를 진행하기
void DFS(int x, int y){
    for(int i=0; i < DIR_NUM; i++){
        int nx = x+dx[i], ny = y+dy[i];
        // 인접한 칸 중 숫자가 동일하면서 방문한 적이 없는 칸으로만 이동 가능
        if(InRange(nx, ny) && !visited[nx][ny] && arr[nx][ny] == arr[x][y]){
            visited[nx][ny] = true;
            group[nx][ny] = group_n;
            group_cnt[group_n]++;
            DFS(nx, ny);
        }
    }
}

// 그룹을 만들어 주기
void MakeGroup(){
    group_n = 0;

    // visited 값을 초기화해주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            visited[i][j] = false;
    
    // DFS를 이용해서 그룹을 묶는 작업을 진행
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!visited[i][j]){
                group_n++;              // 총 그룹 개수 증가
                visited[i][j] = true;   // 방문 처리
                group[i][j] = group_n;  // 그룹 번호 적기
                group_cnt[group_n] = 1; // 해당 그룹의 카운트를 1로 초기화
                DFS(i,j);
            }
        }
    }
}

int GetArtScore(){
    int art_score = 0;

    // 특정 변을 사이에 두고
    // 두 칸의 그룹이 다른 경우라면
    // (그룹 a에 속한 칸의 수 + 그룹 b에 속한 칸의수) * a숫자값 * b숫자값 만큼 예술 점수가 더해진다.
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<DIR_NUM; k++){
                int nx = i+dx[k], ny = j+dy[k];
                if(InRange(nx, ny) && arr[i][j] != arr[nx][ny]){
                    int g1 = group[i][j], g2 = group[nx][ny];
                    int num1 = arr[i][j], num2 = arr[nx][ny];
                    int cnt1 = grou_cnt[g1], cnt2 = group_cnt[g2];

                    art_score += (cnt1 + cnt2) * num1 * num2;
                }
            }
        }
    }
    // 중복 계산을 제외시켜주기
    return art_score / 2;
}

void RotateSquare(int sx, int sy, int square_n){
    // 정사각형을 시계방향으로 90도 회전
    for(int x=sx; x < sx+square_n; x++)
        for(int y=sy; y < sy+square_n; y++){
            // Step 1. (sx, sy)를 (0,0) 으로 옮겨주는 변환을 진행
            int ox = x-sx, oy = y-sy;
            // Step 2. 변환된 상태에서는 회전 이후의 좌표가 (x,y) -> (y,square_n-x-1)이 됨
            int rx = oy, ry = square_n-ox-1;
            // Step 3. 다시 (sx, sy)를 더해주기
            next_arr[rx+sx][ry+sy] = arr[x][y];
        }
}

void Rotate(){
    // Step 1. next arr값을 초기화해주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_arr[i][j] = 0;

    // Step 2. 회전을 진행
    // Step 2-1. 십자 모양에 대한 반시계 회전을 진행
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            // Case 2-1. grid의 세로줄에 대해서는 (i,j) -> (j,i)가 됨
            if(j == n/2)
                next_arr[j][i] = arr[i][j];
            // Case 2-2. grid의 가로줄에 대해서는 (i,j) -> (n-j-1, i)가 됨
            else if(i == n/2)
                next_arr[n-j-1][i] = arr[i][j];
        }

    // Step 2-2. 4개의 정사각형에 대해 시계 방향 회전을 진행
    int square_n = n/2;
    RotateSquare(0,0,square_n);
    RotateSquare(0, square_n+1, square_n);
    RotateSquare(square_n+1, 0, square_n);
    RotateSquare(square_n+1, square_n+1, square_n);

    // Step 3. next_arr 값을 다시 옮겨줌
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            arr[i][j] = next_arr[i][j];
}

int GetScore(){
    // Step 1. 그룹을 형성
    MakeGroup();

    // Step 2. 예술 점수를 계산
    return GetArtScore();
}

int main(){
    // 입력:
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> arr[i][j];
    
    // 3회전까지의 예술 점수를 더해주기
    int ans = 0;
    for(int i=0; i<4; i++){
        // 현재 예술 점수를 더해주기
        ans += GetScore();

        // 회전을 진행
        Rotate();
    }

    cout << ans;
    return 0;
}