#include <iostream>
#include <unordered_map>

using namespace std;

int main(){
    unordered_map<int, int> m;      // HashMap 선언
    m.insert({1,2});                // HashMap에 쌍 (K,V)추가
    m[2] = 3;                       // key=2, value=3
    m.erase(1);                     // key가 1인 쌍을 찾아서 제거
    if m.find(1) != m.end(){        //m.find(K)가 있다면 해당 iterator 반환, 없다면 m.end() 값을 반환
        // m.find(K) != m.end() : 값이 있음
        // m.find(K) == m.end() : 값이 없음
        continue;
    }
    cout << (m.find(1))->first << endl;     // key가 1인 원소의 key 조회
    cout << (m.find(1))->second << endl;    // key가 1인 원소의 value 조회
    cout << (*m.find(1)).first << endl;     // key가 1인 원소의 key 조회
    cout << (*m.find(1)).second << endl;    // key가 1인 원소의 value 조회

    cout << m[1] << endl;                   // key가 1인 원소의 value 조회
    
}