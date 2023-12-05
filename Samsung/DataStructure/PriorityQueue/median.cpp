/*
 * 2023.12.05
 * 처음에 PQ를 두 개 쓸 생각도 해보았는데, 각각 PQ모두 모든 배열 원소가 들어가 있도록 생각했었음
 * 그런데 그 두 개의 PQ를 가지고 어떻게 풀지 생각이 안났어서 아래와 같이 풀었음
 * 다 집어넣고 중앙값전까지 원소들 빼기 -> 중앙값 출력 -> 뺀 원소 다시 집어넣기 
 * 그런데 시간초과 나옴
*/

#include <iostream>
#include <queue>
#define MAX_M 100000
using namespace std;
int t, m;

int main() {
    cin >> t;
    while(t--){
        int arr[MAX_M];
        int tmp[MAX_M/2];
        priority_queue<int> pq;
        cin >> m;
        for(int i=0; i<m; i++){
            cin >> arr[i];
        }
        int cnt=0;
        for(int i=0; i<m; i++){
            cnt++;
            pq.push(arr[i]);
            if(i%2==0){
                for(int j=0; j<cnt/2; j++){
                    int val = pq.top();
                    tmp[j] = val;
                    pq.pop();
                }
                cout<< pq.top() << ' ';
                for(int j=0; j<cnt/2; j++){
                    pq.push(tmp[j]);
                }
            }
        }
        cout << '\n';
    }
    return 0;
}