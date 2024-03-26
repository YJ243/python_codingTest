/*
 * 2024.03.26
 * 격자 숫자 놀이
 * 해설 풀이
 * 시간복잡도: 각각의 단계에서 이루어지는 연산들로 인해 코드 분석과 정렬에 O(NM(logN + logM)) 만큼의 시간이 소요됨
 * 최종적으로는 이 단계가 T초 반복되기 때문에 O(TNM(logN + logM))의 시간복잡도를 가진다.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

#define MAX_N 100
#define MAX_NUM 100

using namespace std;

int n = 3, m = 3;
int r, c, k;

int grid[2*MAX_N + 1][2*MAX_N + 1];

// row행에 대해 숫자 놀이를 진행한다.
int RowPlay(int row){
    // 각 숫자에 대해 빈도수를 구해준다.
    // 정렬 시 빈도수, 숫자 순으로 오름차순 정렬이 되도록
    // (빈도수, 숫자) 형태로 저장해준다.
    vector<pair<int, int> > pairs;
    for(int num=1; num <= MAX_NUM; num++){
        int frequency = 0;
        for(int col = 1; col <= m; col++)
            if(grid[row][col] == num)
                frequency++;
        if(frequency)
            pairs.push_back(make_pair(frequency, num));
    }

    // 숫자를 새로 적어줘야 하므로, 그 전에 기존 row행에 있던 숫자들을 전부 0으로 바꿔준다.
    for(int col = 1; col <= m; col++)
        grid[row][col] = 0;
    sort(pairs.begin(), pairs.end());

    // row행에 새로운 숫자를 차례대로 적어준다.
    for(int i=0; i<(int)pairs.size(); i++){
        int frequency, num;
        tie(frequency, num) = pairs[i];
        grid[row][i*2+1] = num;
        grid[row][i*2+2] = frequency;
    }
    return (int) pairs.size() * 2;
}

// col 열에 대해 숫자 놀이를 진행한다.
int ColPlay(int col){
    // 각 숫자에 대해 빈도수를 구해준다.
    // 정렬 시 빈도수, 숫자 순으로 오름차순 정렬이 되도록
    // (빈도수, 숫자) 형태로 저장해준다.
    vector<pair<int, int> > pairs;
    for(int num=1; num <= MAX_NUM; num++){
        int frequency = 0;
        for(int row = 1; row <= m; row++)
            if(grid[row][col] == num)
                frequency++;
        if(frequency)
            pairs.push_back(make_pair(frequency, num));
    }

    // 숫자를 새로 적어줘야 하므로, 그 전에 기존 col 열에 있던 숫자들을 전부 0으로 바꿔준다.
    for(int row = 1; row <= m; row++)
        grid[row][col] = 0;
    
    sort(pairs.begin(), pairs.end());

    // col 열에 새로운 숫자를 차례대로 적어준다.
    for(int i=0; i<(int)pairs.size(); i++){
        int frequency, num;
        tie(frequency, num) = pairs[i];
        grid[i*2+1][col] = num;
        grid[i*2+2][col] = frequency;
    }
    return (int)pairs.size() * 2;
}

void Simulate(){
    // 행의 개수가 열의 개수와 일치하거나 더 많다면
    // 행 단위로 진행 후, 최대로 긴 열의 크기를 구한다.
    if(n >= m){
        int max_col = 0;
        for(int row = 1; row <= n; row++)
            max_col = max(max_col, RowPlay(row));
        m = max_col;
    }
    // 열의 개수가 더 많다면
    // 열 단위로 진행 후, 최대로 긴 행의 크기를 구한다.
    else{
        int max_row = 0;
        for(int col = 1; col <= m; col++)
            max_row = max(max_row, ColPlay(col));
        n = max_row;
    }


}

int main(){
    cin >> r >> c >> k;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            cin >> grid[i][j];
    int ans = -1;

    // 최대 100초동안 시뮬레이션을 진행한다.
    for(int t=0; t <= 100; t++){
        if(grid[r][c] == k){
            ans = t;
            break;
        }
        Simulate();
    }
    cout << ans;
    return 0;
}