/*
 * 2024.03.22
 * 해설 풀이
 * 특정 위치로부터 주어진 방향에 놓여있는 칸 중 어떤 칸으로 움직일 것인지를 선택하는 재귀함수
 * 현재 숫자보다 큰 칸으로만 움직이면 총 탐색 시간을 줄일 수 있음
 * 언제 움직임이 끝날 지 확실하게 정의하기가 어려운 문제이기 땜누에 함수가 호출될 때마다 항상 최댓값 갱신하기
*/

#include <iostream>
#include <algorithm>

#define MAX_N 4
#define DIR_NUM 8
using namespace std;

int n;
int num[MAX_N][MAX_N], move_dir[MAX_N][MAX_N];
int ans;

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y, int prev_num) {
    return InRange(x, y) && num[x][y] > prev_num;
}

void FindMax(int x, int y, int cnt){
    // 언제 끝날 지 모르기 때문에 항상 최댓값을 갱신해준다.
    ans = max(ans, cnt);

	int dx[DIR_NUM] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dy[DIR_NUM] = {0, 1, 1, 1, 0, -1, -1, -1};
	int d = move_dir[x][y] - 1;

    for(int i=0; i<n; i++){
        int nx = x + dx[d]*i, ny = y + dy[d]*i;
        if(CanGo(nx, ny, num[x][y]))
            FindMax(nx, ny, cnt+1);
    }
}

int main(){
    cin >> n;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> num[i][j];
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> move_dir[i][j];
    
    int r, c;
    cin >> r >> c;

    FindMax(r-1, c-1, 0);
    cout << ans;

    return 0;
}