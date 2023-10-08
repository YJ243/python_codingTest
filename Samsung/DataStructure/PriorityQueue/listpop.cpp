/*
2023.10.07
우선순위 큐를 이용하면 우선순위가 가장 높은 값을 O(logN)으로 삽입,삭제 가능
*/

#include <iostream>
#include <queue>

using namespace std;

// 변수 선언
int n;
priority_queue<int> pq;

int main(){
    // 입력:
    cin >> n;

    for(int i=0; i<n; i++){
        int x;
        cin >> x;

        if(x != 0){
            // x가 자연수라면 priority queue에 x를 넣어주기
            pq.push(x);
        }
        else{
            // x가 0이라면
            // 최댓값을 찾아 출력한 뒤 제거
            if(pq.empty()){
                cout << 0 << '\n';
            }
            else{
                cout << pq.top() << '\n';
                pq.pop();
            }
        }
    
    }
    return 0;
}