/*
 * 2024.03.22
 * 시간초과가 나와서 결국 이전 풀이 참고함
 * 중간에 가능한 경우에만 재귀함수를 호출하도록 바꿔야 했음
 * 그리고 IsPossible에서 n/2가 아니라 (int)nums.size()/2로 했어야 함
*/
#include <iostream>
#include <vector>
#define MAX_N 80

using namespace std;
int n;
vector<int> a;
bool Possible;

bool Verify(){

    for(int cnt=1; cnt <= (int)a.size()/2; cnt++){
        for(int s=0; s<=(int)a.size()-cnt*2; s++){
            int same_cnt = 0;
            for(int k=0; k<cnt; k++){
                if(a[s+k] == a[s+k+cnt]) same_cnt++;
            }
            if(same_cnt==cnt) {
                return false;
            }
        }
    }
    Possible = true;
    return true;
}

void Choose(int num){
    if(num == n){
        for(int i=0; i<(int)a.size(); i++)
            cout << a[i];
        exit(0);
        return;
    }

    for(int i=4; i<=6; i++){
        a.push_back(i);
        if(Verify()){
            // 지금까지 만든 숫자가 불가능한 수열이 아닐 때에만 진행
            Choose(num+1);
        }
        a.pop_back();
    }
}

int main(){
    cin >> n;
    // 이제 0번째 숫자를 선택하기
    Choose(0);
    return 0;
}