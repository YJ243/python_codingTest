/*
 * 2024.03.22
 * 내 풀이
*/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_MN 20

using namespace std;

int n, m;
int arr[MAX_MN];
vector<int> selected;
int ans;
int Calc(){
    int curr = selected[0];
    for(int i=1; i<(int)selected.size(); i++){
        curr ^= selected[i];
    }
    return curr;
}

void Choose(int idx, int cnt){
    if(cnt == m){
        ans = max(ans, Calc());
        return;
    }

    for(int i=idx; i < n; i++){
        selected.push_back(arr[i]);
        Choose(i+1, cnt+1);
        selected.pop_back();
    }
}
int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> arr[i];

    Choose(0,0);      // 0번째 숫자를 고르러 가는 함수, 현재까지 0개 뽑음
    cout << ans;
    return 0;
}