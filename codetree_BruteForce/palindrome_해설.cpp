/*
 * 2023.12.19
 * x부터 y까지 팰린드롬인지 판단하는 완전탐색 진행
 * vector에 한자리수 씩 담아놓고 처음과 마지막, 그 다음과 마지막 전, ... 이렇게 같은지 확인함
 *
*/

#include <iostream>
#include <algorithm>

using namespace std;

int x, y;
int main(){
    // 입력
    cin >> x >> y;

    int ans = 0;

    // 각 정수에 대해 팰린드롬 수인지 아닌지 여부를 판단
    for(int i=x; i<=y; i++){
        // 정수 형태를 문자열 배열로 바꿈
        string str = to_string(i);
        bool is_palindrome = true;

        // 펠린드롬 수가 되기 위해서는
        // 거꾸로 읽어도 똑같은 수여야 함
        string str_reverse = "";
        for(int j= (int)str.length()-1; j >=0; j--)
            str_reverse += str[j];
        
        if(str != str_reverse)
            is_palindrome = false;
        
        if(is_palindrome)
            ans++;
    }

    cout << ans;
    return 0;
}