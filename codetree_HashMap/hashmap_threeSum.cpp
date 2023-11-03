/*
 * 2023.11.03
 * 세 수의 합
 * https://www.codetree.ai/missions/8/problems/sum-of-three-num?&utm_source=clipboard&utm_medium=text
*/

// 내 풀이
#include <iostream>
#include <unordered_map>

#define INT_MAX 1000
using namespace std;

int n, k;           // n: 원소의 개수, k: 세 수의 합
int arr[INT_MAX];   // 원소들이 담겨질 배열

int main() {
    cin >> n >> k;          // 입력받기
    int result = 0;         // 서로 다른 조합의 개수
    for(int i=0; i<n; i++){ // 배열에 숫자 담기
        cin >> arr[i];
    }

    for(int i=0; i<n-2; i++){       // k-후보값 = 나머지 두 개의 합임, 해당 후보 값을 0번부터 끝에서 -3까지 보면서 확인
        int std = arr[i];           // 후보값을 std로
        int tmp_sum = k-std;        // tmp_sum은 나머지 두 숫자의 합
        // 이제 i+1부터 끝까지 두 수의 합이 tmp_sum이 되는지 확인하기
        unordered_map<int, int> m;  // 해당 후보값마다 hashmap을 새로 선언, 나머지 두 개 원소에 대한 개수를 담기
        for(int j=i+1; j<n; j++){   // 후보값 이후부터 끝까지 확인하면서
            result += m[tmp_sum-arr[j]];    // 서로 다른 조합의 개수는 tmp_sum-arr[j], 즉 나머지 두 원소 중 하나의 cnt만큼 증가
            m[arr[j]]++;                    // 현재 값의 개수 증가
        }
    }
    cout << result << '\n';
    return 0;
}