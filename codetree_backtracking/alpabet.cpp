/*
 * 2024.02.23
 * 알파벳과 사칙연산
 * ans를 INT_MIN으로 두지 않아서 틀림
*/

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#define ALPABET_NUM 6
using namespace std;

string s;
vector<int> selected;
int numbers[ALPABET_NUM];
int ans = INT_MIN;

void Calc(){
    int curr = selected[s[0]-'a'];      // 초깃값 설정
    for(int i=2; i<s.length(); i += 2){
        if(s[i-1] == '+'){
            curr += selected[(s[i]-'a')];
        }
        else if(s[i-1] == '-'){
            curr -= selected[(s[i]-'a')];
        }
        else{       // *기호
            curr *= selected[(s[i]-'a')];
        }
    }
    ans = max(ans, curr);

}

void Choose(int cnt){   // cnt번째 알파벳에 들어갈 숫자를 고르는 함수
    if(selected.size() == ALPABET_NUM){
        Calc();
        return;
    }

    for(int i=1; i<=4; i++){
        selected.push_back(i);
        Choose(cnt+1);
        selected.pop_back();

    }
}

int main() {
    cin >> s;
    Choose(0);
    cout << ans << '\n';
    return 0;
}