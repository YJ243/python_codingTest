#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
string str;
vector<char> result;
int value = 0;
int main(){
    cin >> str;

    // 문자를 하나씩 확인하며
    for(int i=0; i<str.size(); i++){
        // 알파벳인 경우 결과 리스트에 삽입
        if(isalpha(str[i])){
            result.push_back(str[i]);
        }
        else{
            // 숫자는 따로 더하기
            value += str[i] - '0';
        }
    }

    // 알파벳 오름차순 정렬
    sort(result.begin(), result.end());
    // 알파벳을 차례대로 출력
    for(int i=0; i<result.size(); i++){
        cout << result[i];
    }
    if(!value) cout << value<<'\n';

}