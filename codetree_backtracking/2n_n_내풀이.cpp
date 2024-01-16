/*
 * 2024.1.14
 * 시간초과가 나온 풀이
 * 2nCn으로 풀어서 통과할 줄 알았는데..?
 * 내 풀이가 맞았음.. arr에서 MAX_N*2를 안해서 틀렸던 것임!!!!
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>

#define MAX_N 10
using namespace std;
int n;
int m;
int arr[MAX_N*2];
int total;

vector<int> selected;
int ans = INT_MAX;


void ChooseHalf(int idx, int curSum){
    if((int)selected.size() >= n){
        ans = min(ans, abs(total-curSum-curSum));
        return;
    }
    int curr = curSum;
    for(int i=idx; i<m; i++){
        selected.push_back(arr[i]);
        curr += arr[i];
        ChooseHalf(i+1, curr);
        selected.pop_back();
        curr -= arr[i];
        if(selected.size() == 0) return;
    }
}
int main() {
    cin >> n;
    m = 2*n;
    for(int i=0; i<m; i++){
        cin >> arr[i];
        total += arr[i];
    }

    ChooseHalf(0,0);  // 2n개 중 총 n개 원소를 고르는 함수(0번째 원소를 선택하러 감)
    cout << ans;

    return 0;
}