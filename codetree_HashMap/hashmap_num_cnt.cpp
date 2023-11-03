/*
 * 2023.11.03
*/

#include <iostream>
#include <unordered_map>

#define MAX_N 100000
using namespace std;

// 변수 선언
int n, m;
int arr[MAX_N];
unordered_map<int, int> m_cnt;  // key:특정 숫자, value: 해당 숫자가 수열에 몇 개 있는가?

int main(){
    // 입력:
    cin >> n >> m;

    for(int i=0; i<n; i++){
        cin >> arr[i];
        // 각 숫자가 몇 번씩 나왔는지 hashmap에 기록해줌
        if(m_cnt.find(arr[i]) == m_cnt.end()){
            // 처음 나온 숫자라면 1을 적어주기
            m_cnt[arr[i]] = 1;
        }
        else{
            // 이미 나와있던 숫자라면 1을 더해주기
            m_cnt[arr[i]]++;
        }
    }
    // m개의 질의에 대해 몇 번씩 나왔는지를 출력
    for(int i=0; i<m; i++){
        int k;
        cin >> k;
        cout << m_cnt[k]<<' ';
    }
}