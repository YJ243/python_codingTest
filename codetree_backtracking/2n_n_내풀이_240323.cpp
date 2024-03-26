/*
 * 2024.3.23
 * 내 풀이
 * 빠르고 깔끔하게 풀어낸 것 같다.
*/
#include <iostream>
#include <climits>
#include <cmath>

#define MAX_N 10

using namespace std;

int n;
int arr[MAX_N*2];
int sum;
int ans = INT_MAX;
void Choose(int idx, int cnt, int cur_sum){
    if(cnt == n){
        ans = min(ans, abs(sum-cur_sum*2));
        return;
    }
    if(idx == 2*n)
        return;
    Choose(idx+1, cnt, cur_sum);            // idx번째 선택 안하는 경우
    Choose(idx+1, cnt+1, cur_sum+arr[idx]); // idx번째 선택 하는 경우
}

int main() {
    cin >> n;
    for(int i=0; i<n*2; i++){
        cin >> arr[i];
        sum += arr[i];
    }
    Choose(0, 0, 0);      // 처음 그룹의 첫 번째 숫자 고르러 가기, 총 0개, 원소합0
    cout << ans;
    return 0;
}