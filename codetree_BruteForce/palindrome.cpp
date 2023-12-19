/*
 * 2023.12.19
 * x부터 y까지 팰린드롬인지 판단하는 완전탐색 진행
 * vector에 한자리수 씩 담아놓고 처음과 마지막, 그 다음과 마지막 전, ... 이렇게 같은지 확인함
 *
*/

#include <iostream>
#include <vector>
#define MAX_X 7
using namespace std;
int x, y;
int ans;
int main() {
    // 입력
    cin >> x >> y;
    
    // 각 정수에 대해 팰린드롬 수인지 아닌지 여부를 판단하기
    for(int i=x; i<=y; i++){
        int number = i;
        vector<int> digit;

        // 뒤에서부터 한자리씩 넣기
        while(number){
            digit.push_back(number%10);
            number /= 10;
        }
        bool isfal = true;
        int s = (int)digit.size();
        
        // 팰린드롬 수가 되기 위해서는, 거꾸로 읽어도 똑같은 수여야 함
        for(int j=0; j<s; j++){
            if(digit[j] != digit[s-1-j]){
                isfal = false;
                break;
            }
        }
        if(isfal)   ans++;
    }    
    cout << ans << '\n';
    return 0;
}