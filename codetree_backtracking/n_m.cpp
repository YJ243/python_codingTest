/*
 * 24.03.22
 * 내 풀이
 * 조합을 이전 수보다 큰 수들을 고르는 과정으로 생각
*/
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> nums;

void Print(){
    for(int i=0; i<(int)nums.size(); i++){
        cout << nums[i] << ' ';
    }
    cout << '\n';
}
void Choose(int idx){
    if((int)nums.size() == m){
        Print();
        return;
    }

    for(int i=idx; i <= n; i++){
        nums.push_back(i);
        Choose(i+1);
        nums.pop_back();
    }
}

int main() {
    cin >> n >> m;
    Choose(1);  // 0번째 숫자를 고르기    
    return 0;
}