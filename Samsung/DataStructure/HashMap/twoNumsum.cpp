/*
2023.10.06
- 서로 다른 위치에 있는 두 개의 수를 뽑아 더했을 때 
- k가 되는 가짓수를 구하는 프로그램을 작성해보세요.
*/

#include <iostream>
#include <unordered_map>

using namespace std;

#define MAX_N 100000

// 변수 선언
int n, k;
int arr[MAX_N];
unordered_map<long long, int> count;

int main(){
    // 입력:
    cin >> n >> k;
    for(int i=0; i<n; i++)
        cin >> arr[i];

    int ans = 0;

    // 배열을 앞에서부터 순회하면서 쌍을 만들어 줌
    for(int i=0; i<n; i++){
        long long diff = (long long)k - arr[i];

        // 가능한 모든 쌍의 수를 세어줌
        ans += count[diff];
        /*
            count에 diff를 key로 하는 원소가 존재하지 않으면
            해당 키와 기본값을 가지는 원소가 자동으로 추가 (ex. count[diff] = 0)
            
            만약 arr배열에 = {4,6,5,3,7}이라면
            step1. count[5] = 0, ans = 0, count[4] = 1
            step2. count[3] = 0, ans = 0, count[6] = 1
            step3. ans += count[4], count[5] = 1
            step4. ans += count[6], count[3] = 1
            step5. count[2] = 0, count[7] = 1 

        */

        // 현재 숫자의 개수를 하나 증가
        count[arr[i]]++;

    }
    cout << ans << '\n';
}