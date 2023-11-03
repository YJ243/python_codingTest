/*
 * 2023.11.3
 * https://www.codetree.ai/missions/8/problems/corresponding-numbers-and-characters?&utm_source=clipboard&utm_medium=text
 * 숫자->문자열, 문자열->숫자
*/

/*
 * 내 풀이
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>
using namespace std;

#define MAX_INT 100001
string arr[MAX_INT] = {};
int n, m;
unordered_map<string, int> map;
int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        cin >> arr[i];
        map[arr[i]] = i;
    }
    for(int i=0; i<m; i++){
        string s;
        cin >> s;
        // 만약 s가 문자열이라면
        if(!isdigit(s[0])){
            cout<<map[s]<<'\n';
        }
        // 만약 s가 숫자라면
        else{
            cout<<arr[stoi(s)]<<'\n';
        }
    }
    return 0;
}
*/

// 해설 풀이
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

#define MAX_N 100000

// 변수 선언
int n, m;
string words[MAX_N + 1];
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

        // 입력된 값이 숫자일 떄에는 array에 저장한 문자를 출력
        if('0' <= key[0] && key[0] <= '9')
            cout << words[stoi(key)] << endl;
        // 입력된 값이 문자일 때에는 hashmap에 기록된 대응되는 숫자를 출력
        else
        {
            cout << string_to_num[key]<<'\n';
        }
    }
    return 0;
}