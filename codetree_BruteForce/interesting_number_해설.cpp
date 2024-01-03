/*
 * 2023.12.18
 * x부터 y 사이의 각 숫자들에 대해 전부 알아보는 완전탐색
 * 배열의 인덱스에 같은 숫자의 등장 횟수를 기록했을 때
 * 전체 자릿수-1번 등장한 숫자가 있다면, 그 수는 한 자리를 제외하고 나머지가 같은 숫자로 이루어져 있음
 * 흥미로운 숫자의 판별을 나와 다르게 함, 나는 1개인 숫자, 1개보다 큰 숫자가 각각 딱 하나씩만 있어야 한다고 생각
*/

#include <iostream>
#include <algorithm>

using namespace std;

int x, y;

int main(){
    // 입력
    cin >> x >> y;

    int ans = 0;

    // 각 숫자에 대해 승미로운 숫자인지 아닌지 여부를 판단
    for(int i=x; i<=y; i++){
        // digit 배열을 만들어 각 자리 숫자의 개수를 저장
        // all_digits에는 총 자릿수의 개수를 저장
        int num = i;
        int digit[10] = {};
        int all_digits = 0;
        while(num){
            digit[num%10]++;
            all_digits++;
            num /= 10;
        }

        // interesting: i가 흥미로운 숫자라면 true, 아니면 false
        bool interesting = false;

        // 흥미로운 숫자가 되기 위해서는
        // 숫자 하나만 all_digits - 1회 등장해야 함
        for(int j=0; j<10; j++)
            if(digit[j] == all_digits -1)
                interesting = true;
        if(interesting)
            ans++;
             
    }
}