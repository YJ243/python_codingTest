#include <iostream>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    int answer = 0;
    while ( n != 1){
        if(n % k == 0)
        {
            n /= k;
            answer++;
        }
        else
        {
            n -= 1;
            answer++;
        }
    }
    cout << answer;
}