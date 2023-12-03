/*
 * 2023.12.03
 * 내풀이
 * flag를 설정해서 나중에 출력하도록 함
*/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

string s;
unordered_map<char, int> freq;

int main(){
    // 입력:
    cin >> s;
    for(auto a: s){
        freq[a]++;
    }
    char answer;
    bool flag = false;
    for(auto a:s){
        if(freq[a] == 1 && !flag){
            // 만약 빈도수가 1이고 처음 나왔다면
            flag = true;
            answer = a;
        }
    }
    if(flag){
        cout << answer;
    }
    else{
        cout << "None";
    }
    return 0;
}