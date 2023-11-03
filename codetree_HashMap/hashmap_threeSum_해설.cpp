/*
 * 2023.11.03
 * 해설코드
 * 배열에서 두 원소를 골라 후보로 삼았을 때 target_sum을 만들 수 있는지 여부는?
 * 'target_sum - 두 원소의 합'에 해당하는 원소가 있는지 확인
 * 매번 모든 배열을 순회하며 해당 원소가 있는지 확인하면? => O(N)
 * 그렇지만 HashMap에 모든 배열의 원소 정보(개수)를 담아두면 그 후로는 O(1) 시간 만에 확인
*/

#include <iostream>
#include <unordered_map>

using namespace std;

# define MAX_N 1000

// 변수 선언
int n, k;
int arr[MAX_N];
unordered_map<int ,int> freq;

int main(){
    // 입력:
    cin >> n >> k;

    int ans = 0;

    // 각 숫자가 몇 번씩 나왔는지 hashmap에 기록해주기
    for(int i=0; i<n; i++){
        cin >> arr[i];
        freq[arr[i]]++;
    }

    // 배열을 앞에서부터 순회하며 쌍을 만들어주기
    for(int i=0; i<n; i++){
        // 이미 순회한 적이 있는 숫자는 빼버림으로서
        // 같은 조합이 여러 번 세어지는 것을 방지
        freq[arr[i]]--;

        for(int j=0; j<i; j++){
            // 전처리를 해주었기 때문에 이미 순회한 적이 있는 값은 hashmap에 없음
            // 이와 같은 방식으로 같은 조합이 중복되어 세어지는 것을 방지할 수 있음
            if(freq.count(k-arr[i]-arr[j])>0)
                ans += freq[k-arr[i]-arr[j]];
        }
    }
    cout << ans;
}