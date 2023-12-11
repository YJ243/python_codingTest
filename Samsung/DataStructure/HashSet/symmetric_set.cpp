/*
 * 2023.12.09
 * 내 풀이
*/

#include <iostream>
#include <unordered_set>

using namespace std;

unordered_set<long long> a;     // 대칭차집합의 A부분
unordered_set<long long> b;     // 대칭차집합의 B부분
int cnt_a, cnt_b;               // A와 B의 전체 원소 개수

int main() {
    cin >> cnt_a >> cnt_b;
    for(int i=0; i<cnt_a; i++){
        int val;
        cin >> val;
        a.insert(val);    
    }

    for(int i=0; i<cnt_b; i++){
        int val;
        cin >> val;
        // B의 원소가 A에도 있다면
        if(a.find(val) != a.end()){
            a.erase(val);   // A에서 지우기
        }
        else{
            // a에 원소가 없다면
            b.insert(val);  // 그때 넣어주기
        }
    }
    cout << (int) a.size() + b.size();
    return 0;
}