#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;
    cin >> s;
    int answer = 0;
    for(int i=0; i<s.size(); i++){
        int cur = s[i] - '0';
        if(s[i] -'0' == 0 || s[i] - '0' == 1){
            answer = answer + (s[i]-'0');// 현재 수가 0이면 앞의 수와 더하기
        }
        else{
            if(answer == 0 || answer == 1){
                answer += (s[i]-'0');
            }
            else{
                answer *= (s[i]-'0');
            }
        }
    }
        cout << answer << ' ';
}