/*
 * 2024.03.13
 * 처음에 2명의 도둑이 잡을 위치를 정할 때 brute force + 그 이후 최대 가치를 구할 때 backtracking
*/

#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 10

using namespace std;

int n, m, c;
int grid[MAX_N][MAX_N];
int total_value;
int value;
vector<int> selected;
vector<int> thiefArea;
bool IsPossible(int x1, int y1, int x2, int y2){
    if(x1 != x2)
        return true;
    else if(y1+m <= y2 || y2+m <= y1)
        return true;
    return false;

}

void FindMaxValue(int idx){
    int cur_sum = 0, cur_value = 0;
    for(int j=0; j<(int)selected.size(); j++){
        cur_sum += selected[j];
        cur_value += selected[j]*selected[j];
    }
    if((cur_sum <= c)){
        if(cur_value > value){
            //cout << "valeu큼" <<cur_value << "\n";
            //for(int j=0; j<(int)selected.size(); j++)
            //    cout << selected[j]  << ' ';
            //cout << '\n';
            value = cur_value;
        }
    }
    if(idx == m){
        return;
    }
    for(int i=idx; i < m; i++){
        selected.push_back(thiefArea[i]);
        FindMaxValue(i+1);
        selected.pop_back();
    }
}

void Cal(int x1, int y1, int x2, int y2){
    value = 0;
    thiefArea.clear();
    // (x1, y1) ~ (x1, y1+m-1)에서 backtracking으로 고르기
    for(int j=y1; j < y1+m; j++)
        thiefArea.push_back(grid[x1][j]);
    
    FindMaxValue(0);
    int theifValue1 = value;    // theif1이 고른 최대 가치 
    // (x2, y2) ~ (x2, y2+m-1)에서 backtracking으로 고르기
    thiefArea.clear();
    value = 0;
    for(int j=y2; j < y2+m; j++)
        thiefArea.push_back(grid[x2][j]);
    FindMaxValue(0);
    int theifValue2 = value;    // theif2가 고른 최대 가치
    if(theifValue1 + theifValue2 > total_value){

        total_value = theifValue1 + theifValue2;
    }
}

int main() {
    cin >> n >> m >> c;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }

    // step 1. 먼저 두 도둑이 m개 열을 선택하기
    for(int i=0; i<n; i++){
        for(int j=0; j<=n-m; j++){
            for(int k=0; k<n; k++){
                for(int l=0; l<=n-m; l++){
                    if(IsPossible(i,j,k,l)){
                        // step 2. 각각 선택한 곳에서 가치 구하기
                        Cal(i,j,k,l);
                    }
                }
            }
        }
    }
    cout << total_value;
    return 0;
}