/*
 * 2024.03.22
 * 내 풀이 
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10
using namespace std;

int n, m, c;
int grid[MAX_N][MAX_N];
int value[MAX_N][MAX_N];
int cur_max;
vector<int> selected;

void FindCurMax(){
    int curr = 0, curr_value = 0;
    for(int i=0; i<(int)selected.size(); i++){
        curr_value += selected[i]*selected[i];
        curr += selected[i];
    }
    if(curr <= c)
        cur_max = max(curr_value, cur_max);
}

void Choose(int x, int y, int idx){
    if(idx == m){
        FindCurMax();
        return;
    }

    selected.push_back(grid[x][y]);
    Choose(x, y+1, idx+1);
    selected.pop_back();

    Choose(x, y+1, idx+1);
}

void FindMaxValue(int x, int y){    // (x, y)에서 m길이의 물건을 골랐을 때의 최대 가치
    // 조합으로 구해야 함
    cur_max = 0;            // 현재 최댓값 0으로 초기화
    selected.clear();       // 배열 초기화
    Choose(x, y, 0);        // (x,y)에서 시작해서 0번째 숫자를 고르는 함수

    value[x][y] = cur_max;  // value에 현재 최댓값 넣기
}

bool Possible(int x1, int y1, int x2, int y2){
    // 만약 두 줄이 다르면 가능
    if(x1 != x2)
        return true;
    // 만약 두 줄이 같은데 겹치지 않는다면 가능
    if(y1+m <= y2 || y2+m <= y1)
        return true;
    return false;
}

int main() {
    // 입력 받기:
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    // 먼저 각 칸에서 시작했을 때 얻을 수 있는 최대 가치 구하기
    for(int i=0; i<n; i++){
        for(int j=0; j<=n-m; j++){
            FindMaxValue(i,j);
        }
    }
    int ans = 0;
    // 이제 완전탐색 진행하기
    for(int i=0; i<n; i++){
        for(int j=0; j<=n-m; j++){
            for(int k=0; k<n; k++){
                for(int l=0; l<=n-m; l++){
                    if(Possible(i,j,k,l)){
                        ans = max(ans, value[i][j] + value[k][l]);
                    }
                }
            }
        }
    }
    cout << ans;
    return 0;
}