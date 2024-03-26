/*
 * 2024.03.22
 * 내 풀이
*/

#include <iostream>
#include <vector>

using namespace std;
int k, n;       // k이하의 숫자, n번 반복
vector<int> numbers;

void Print(){
    for(int i=0; i<(int)numbers.size(); i++){
        cout << numbers[i] << ' ';
    }
    cout << '\n';
}

void Choose(int idx){   // idx번 숫자 고르기
    if(idx == n){
        Print();
        return;
    }

    for(int i=1; i<=k; i++){
        if(idx <= 1 || (numbers.back() != i || numbers[(int)numbers.size()-2] != i)){
            numbers.push_back(i);
            Choose(idx+1);
            numbers.pop_back();
        }
        
    }
}

int main() {
    cin >> k >> n;
    Choose(0);      // 0번째 숫자 고르기
    return 0;
}