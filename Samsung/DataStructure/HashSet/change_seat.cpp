/*
 * 2023.12.08
 * 자리를 바꿀 때마다 arr 배열 업데이트, unordered_set에 앉게되는 번호들 넣기
*/

#include <iostream>
#include <unordered_set>
#include <tuple>

using namespace std;

#define MAX_N 100000

int arr[MAX_N + 1];                 // arr[i]: i번 자리에 앉아 있는 사람의 번호
unordered_set<int> seats[MAX_N+1];    // seats[i]: i번호표 사람이 앉게되는 자리들의 번호
tuple<int,int> change[MAX_N];       // 입력으로 주어지는 바꿔야 할 자리 쌍
int n, k;

int main(){
    cin >> n >> k;

    // 처음 자리 삽입
    for(int i=1; i<=n; i++){
        seats[i].insert(i);         // seats[i]: i번호표 사람이 앉는 자리
        arr[i] = i;                 // arr[i]: i번 자리에 앉아 있는 사람
    }

    for(int i=0; i<k; i++){
        int a, b;
        cin >> a >> b;
        change[i] = make_tuple(a,b);    // 바꿔야 할 자리 입력 받기
    }

    for(int i=0; i<3; i++){         // 총 3K번
        for(int j=0; j<k; j++){
            int a, b;
            tie(a, b) = change[j];

            int seat_a, seat_b;
            seat_a = arr[a];        // a자리에 앉아 있는 사람의 번호
            seat_b = arr[b];        // b자리에 앉아 있는 사람의 번호

            seats[seat_a].insert(b); // a자리에 앉은 사람이 옮길 자리는 b번 인덱스 자리
            seats[seat_b].insert(a); // b자리에 앉은 사람이 옮길 자리는 a번 인덱스 자리

            arr[a] = seat_b;        // a자리에 b자리 앉아 있던 사람 옮겨주기
            arr[b] = seat_a;        // b자리에 a자리 앉아 있던 사람 옮겨주기
        }
    }

    // 각 사람마다 앉은 자리 개수 출력
    for(int i=1; i<=n; i++)
        cout << seats[i].size() << '\n';
    return 0;
}