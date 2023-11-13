#include <iostream>
#include <unordered_map>

using namespace std;

int main(){
    unordered_map<int, int> m;  // 정수를 관리할 hashmap을 선언 => 빈 hashmap
    m.insert({5,6});
    m.insert({2,2});
    m[10] = 1;          // {10,1}

    if(m.find(2) != m.end()){   // key가 2인 쌍이 hashmap에 있다면
        cout << m[2] << '\n';   // key가 2인 value 값을 출력
    }
    m.erase(5);               // key가 5인 쌍을 제거
    if(m.find(5) == m.end()){ // key가 5인 쌍이 hashmap에 없다면
        cout << "not exists!" << '\n';
    }
    m[2] = 10;              // key가 2인 곳에 들어있는 value 값을 10으로 ㅂ녀경
    cout << m[2] << '\n';   // key가 2인 value값(10)을 출력

    unordered_map<string, int> m;   // key가 문자열
    m["banana"] = 6;
    m["helloworld"] = 2;
    m["apple"] = 5;

    cout << m["banana"] << '\n';    // key가 banana인 쌍의 value 출력(6)
    return 0;
}