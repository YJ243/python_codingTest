/*
2023.10.06

*/

#include <iostream>
#include <unordered_map>

using namespace std;

#define MAX_N 1000

// 변수 선언
int n, k;
int arr[MAX_N];
unordered_map<int,int> freq;

int main(){
    // 입력:
    cin >> n >> k;

    int ans = 0;

    // 각 숫자가 몇 번씩 나왔는지를 hashmap에 기록
    for(int i=0; i<n; i++){
        cin >> arr[i];
        freq[arr[i]]++;
    }

    // 배열을 앞에서부터 순회하면서 쌍을 만들어 줌
    for(int i=0; i<n; i++){
        // 이미 순회한 적이 있는 숫자는 빼서
        // 같은 조합이 여러번 세어지는 것을 방지
        freq[arr[i]]--;

        for(int j=0; j<i; j++){
            // 전처리를 했기 때문에 이미 순회한 적이 있는 값은 hashmap에서 제외
            // 이와 같은 방식으로 같은 조합이 중복되어 세어지는 것을 방지
            if(freq.count(k-arr[i]-arr[j])>0)
                ans += freq[k-arr[i]-arr[j]];
        }
    }

    cout << ans;
    return 0;
}