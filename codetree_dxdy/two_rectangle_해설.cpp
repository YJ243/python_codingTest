/*
 * 24.01.16
 * 해설 풀이
 * 두 직사각형을 전부 잡아서 겹치지 않는 경우 중 최대 합 구하기
 * 두 직사각형이 겹쳐지는지에 대한 여부는 새로운 배열을 이용해 쉽게 계산
 * 격자에 각 직사각형 영역마다 1씩 증가시켜 숫자가 2 이상인 칸이 있는지 확인하여 구현
*/

#include <iostream>
#include <algorithm>
#include <climits>

#define MAX_NUM 5

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];
int board[MAX_NUM][MAX_NUM];

void ClearBoard(){
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            board[i][j] = 0;
}

void Draw(int x1, int y1, int x2, int y2){
    for(int i=x1; i<=x2; i++)
        for(int j=y1; j<=y2; y++)
            board[i][j]++;    
}

// (x1,y1), (x2,y2) 그리고 (x3,y3), (x4,y4)로 이루어져 있는
// 두 직사각형이 겹치는지 확인하는 함수
bool Overlapped(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
    ClearBoard();
    Draw(x1,y1,x2,y2);
    Draw(x3,y3,x4,y4);
    return CheckBoard();
}

int RectSum(int x1, int y1, int x2, int y2){
    int sum_of_nums = 0;
    for(int i=x1; i<=x2; i++)
        for(int j=y1; j<=y2; j++)
            sum_of_nums += grid[i][j];
    return sum_of_nums;
}

// 첫 번째 직사각형이 (x1, y1), (x2, y2)를 양쪽 꼭짓점으로 할 때
// 두 번째 직사각형을 겹치지 않게 잘 잡아 최대 합을 반환하는 함수
int FindMaxSum(int x1, int y1, int x2, int y2){
    int max_sum = INT_MIN;

    // (i,j), (k,l)을 양쪽 꼭짓점으로 하는
    // 두 번째 직사각형을 정하여 겹치지 않았을 때 중 최댓값을 찾아 반환
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=i; k<n; k++)
                for(int l=j; l<m; l++){
                    if(!Overlapped(x1,y1,x2,y2,i,j,k,l))
                        max_sum = max(max_sum, RectSum(x1,y1,x2,y2) + RectSum(i,j,k,l));
                }
    return max_sum;
}
// 두 직사각형을 잘 잡았을 때의 최대 합을 반환하는 함수
int FindMaxSum(){
    int max_sum = INT_MIN;

    // (i,j), (k,l)을 양쪽 꼭지점으로 하는 
    // 첫 번째 직사각형을 정하여
    // 그 중 최댓값을 찾아 반환
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            for(int k=i; k<n; k++)
                for(int l=j; l<m; l++)
                    max_sum = max(max_sum, FindMaxSum(i,j,k,l));
    return max_sum;
}

int main(){
    cin >> n >> m;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> grid[i][j];
	
	int ans = FindMaxSum();
	cout << ans;
	
	return 0;
}
