/*
 * 2023.11.03
 * 계속 시간초과 나왔던 문제
 * https://www.codetree.ai/missions/8/problems/sum-of-two-num?&utm_source=clipboard&utm_medium=text

*/

/*
 * 내 풀이
#include <iostream>
#include <unordered_map>
#define MAX_N 100000
using namespace std;
int arr[MAX_N];
unordered_map<int,int> m;

int n,k;
int main() {
    cin >> n >> k;
    for(int i=0; i<n; i++)
        cin >> arr[i];
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            int sum = arr[i] + arr[j];
            if(m.find(sum) == m.end()){
                m[sum] = 1;
            }
            else{
                m[sum]++;
            }
        }
    }
    cout<<m[k]<<'\n';
    return 0;
}
*/

// 해설 풀이
// 배열에서 한 원소를 골라 후보로 삼았을 때 target_sum을 만들 수 있는지 여부
// 'target_sum-후보 값'에 해당하는 원소가 있는지 확인
// HashMap에 모든 배열의 원소 정보를 담아두면 이후로 O(1) 시간 만에 확인 가능

#include <iostream>
#include <unordered_map>

#define MAX_INT 100000
using namespace std;

int arr[MAX_INT];
unordered_map<long long, int> m;
int n, k;
int main(){
    int n, k
    cin >> n >> k;
    int ans = 0;
    for(int i=0; i<n; i++){
        cin >> arr[i];
        // 가능한 모든 쌍의 수를 세어주기
        ans += m[arr[i]-k];
        // 현재 숫자의 개수 하나 증가
        m[arr[i]]++;
    }
    cout << ans << '\n';
}