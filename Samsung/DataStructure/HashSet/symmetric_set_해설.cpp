/*
 * 2023.12.09
 * a원소 개수 + b원소 개수 - 겹치눈 원소 개수 * 2
*/

#include <iostream>
#include <unordered_set>

#define MAX_NUM 200000
using namespace std;
// 변수 선언
int n, m;
int A[MAX_NUM];
int B[MAX_NUM];
int ans;

unordered_set<int> s;

int main(){
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> A[i];
    for(int i=0; i<m; i++)
        cin >> B[i];

    ans = n+m;

    // 수열 A의 원소를 전부  HashSet에 넣어줌
    for(int i=0; i<n; i++)
        s.insert(A[i]);
    
    // 수열 B의 원소가 A에 들어있는지 확인
    for(int i=0; i<m; i++){
        // 만약 들어있다면 A와 B에 모두 있는 값임
        // 대칭 차집합의 원소가 아니므로 정답에서 지워주기
        if(s.find(B[i]) != s.end())
            ans -= 2;
    }
    // 대칭 차집합의 원소 개수 출력
    cout << ans;
    return 0;
}   