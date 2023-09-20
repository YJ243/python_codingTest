#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_DIGIT 20

using namespace std;

int n;
int digits[MAX_DIGIT];
int cnt;

int main(){
    // 입력
    cin >> n;

    // 이진수로 변환
    while(true){
        if(n < 2){
            digits[cnt++] = n;
            break;
        }

        digits[cnt++] = n % 2;
        n /= 2;
    }

    // 만들어진 digits 배열을 뒤집어 출력
    for(int i=cnt-1; i >=0; i--)
        cout << digits[i];

    return 0;
    
}