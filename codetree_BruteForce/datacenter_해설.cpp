/*
 * 2023.12.18
 * 탐색 범위가 불명확한 경우에 대한 완전 탐색
*/
#include <iostream>
#include <cstdlib>

#define MAX_N 1000
#define MAX_T 1000
using namespace std;

int n, c, g, h;
int ta[MAX_N], tb[MAX_N];

// 특정 장비의 t온도에서의 작업량을 계산
int SingleEfficiency(int low, int high, int t){
    if(t < low)
        return c;
    else if(t <= high)
        return g;
    else
        return h;
}

// 온도 t에 대한 작업량을 계산
int Performance(int t){
    int total_efficiency = 0;

    // 장비별 작업량의 합을 계산
    for(int i=0; i<n; i++)
        total_efficiency += SingleEfficiency(ta[i], tb[i], t);
    return total_efficiency;
}
int main(){
    // 입력:
    cin >> n >> c >> g >> h;

    for(int i=0; i<n; i++)
        cin >> ta[i] >> tb[i];
    
    // 각 온도에 대해 작업량을 계산하여
    // 그 중 최댓값을 구해줌
    int max_out = 0;
    for(int t=0; t<=MAX_T; t++)
        max_out = max(max_out, Performance(t));
    cout << max_out;
    return 0;
}