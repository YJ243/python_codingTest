#include <iostream>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    int answer = 0;
    while(true){
        int target = (n / k)*k;
        answer += n - target;

        n = target;

        if (n < k) break;
        answer += 1;
        n /= k;

    }
    answer += (n-1);
    cout << answer;
}