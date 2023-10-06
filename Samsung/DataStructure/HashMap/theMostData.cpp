'''
2023.10.06
HashMap / 가장 많은 데이터
'''

#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

#define MAX_N 100000

using namespace std;

// 변수 선언
int n;
string words[MAX_N];
unordered_map<string, int> freq;

int ans; // 가장 많이 나온 횟수를 기록

int main(){
    // 입력:
    cin >> n;

    for(int i=0; i<n; i++)
        cin >> words[i];
    // 각 문자열이 몇 번씩 나왔는지 hashmap에 기록

    for(int i=0; i<n; i++){
        if(freq.find(words[i]) == freq.end()){
            freq[words[i]] = 1;
        }
        // 이미 나와있던 문자열이라면 1을 더해줌
        else 
            freq[words[i]]++;

        // 최댓값을 갱신
        ans = max(ans, freq[wrods[i]]);
    }

    cout << ans;
    return 0;
}