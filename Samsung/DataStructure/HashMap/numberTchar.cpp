/*
2023.10.06
*/

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#define MAX_N 100000

// 변수 선언
int n, m;
string words[MAX_N+1];
unordered_map<string, int> string_to_num;

int main(){
    // 입력:
    cin >> n >> m;

    // 각 숫자에 대응되는 문자를 array에,
    // 각 문자에 대응되는 숫자를 hashmap에 기록
    for(int i=1; i<=n; i++){
        cin >> words[i];
        string_to_num[words[i]] = i;
    }
    while(m--){
        string key;
        cin >> key;

        // 입력된 값이 숫자일 때에는 array에 저장한 문자를 출력
        if('0' <= key[0] && key[0] <= '9')
            cout << words[stoi(key)] << '\n';
        
        // 입력된 값이 문자일 때에는 hashmap에 기록된 대응되는 숫자 출력
        else
        {
            cout << string_to_num[key] << '\n';
        }
    }
    return 0;
}