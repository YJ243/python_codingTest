/*
 * 2023.12.05
 * A수열과 B수열을 모두 돌면서 해당 쌍으로 PQ안에 넣으면 시간초과가 나온다는 것은 알았음
 * 그런데 어떻게 시간초과가 안나도록 PQ를 활용해야 하는지 몰라서 토론 확인
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#define MAX_N 100000

using namespace std;

int n, m, k;
priority_queue<tuple<long long, int, int, int> > pq;    // 합, A수열 원소, B수열 원소, B수열 인덱스
int arr1[MAX_N];    // A수열
int arr2[MAX_N];    // B수열

long long ans;      // 정답 (A+B)

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++)
        cin >> arr1[i];
    // A수열 오름차순 정렬
    sort(arr1, arr1+n);
    for(int i=0; i<m; i++)
        cin >> arr2[i];
    sort(arr2, arr2+m);
    
    for(int i=0; i<n; i++){
        // 일단 수열 (A의 최솟값, B와의 조합) 넣기
        // 합을 넣어야 그 합이 작은 순으로 정렬됨
        // 그리고 pop한 조합에서의 다음 인덱스를 알기 위해 다음 인덱스도 넣기
        pq.push(make_tuple(-arr1[i]-arr2[0], -arr1[i], -arr2[0], 0));   // 합, A원소, B원소, B원소의 인덱스
    }

    // k번째 조합을 찾기
    while(k--){
        int x,y,idx;
        tie(ans, x, y, idx) = pq.top();     // 합, A원소, B원소, B원소의 인덱스
        pq.pop();

        pq.push(make_tuple(x-arr2[idx+1], x, -arr2[idx+1], idx+1));        
    }
    cout << -ans << '\n';
    return 0;
}