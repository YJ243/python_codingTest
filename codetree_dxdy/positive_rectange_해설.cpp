/*
 * 2024.1.16
 * 해설 풀이
 * 모든 좌표 (0,0) ~ (n-1,m-1) 까지 순회하면서 직사각형의 좌상단점 정하기
 * 그 점을 (i,j)라고 했을 때, 다시  (i,j)부터 (n-1,m-1)까지를 우하단 점으로 정하고,
 * 그렇게 정의해 만들어진 직사각형이 양수 직사각형인지 판단하고 크기 구하기
 * 시간복잡도: O((NM)^3)
*/

#include <iostream>
#include <algorithm>

#define MAX_NUM 20

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];

// (x1, y1), (x2, y2)를 두 꼭지점으로 하는
// 직사각형에 있는 값이 전부 양수인지 판단합니다.
bool PositiveRect(int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++)
        for(int j = y1; j <= y2; j++)
            if(grid[i][j] <= 0)
                return false;
    
    return true;
}

int main() {
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> grid[i][j];
	
	int ans = -1;
    
    // 직사각형의 양쪽 두 꼭지점 (i, j), (k, l)
    // 를 정하여
    // 해당 직사각형안에 있는 값이 전부 양수일 때만
    // 크기를 갱신합니다.
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for(int k = i; k < n; k++)
				for(int l = j; l < m; l++)
                    if(PositiveRect(i, j, k, l))
						ans = max(ans, 
                                  (k - i + 1) * (l - j + 1));
	cout << ans;
	
	return 0;
}