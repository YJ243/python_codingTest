#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n,0);
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int index = 0;
    int group_person = 0;
    

    int result = 0; // 총 그룹 수
    int cnt = 0; // 현재 그룹에 들어간 모험가 수
    for(int i=0; i<n; i++){ // 공포도가 낮은 것부터 하나씩 확인
        int cur = a[i];
        person++; // 현재 그룹에 해당 모험가 포함
        // 만약 현재 그룹에 들어간 수가
        // 현재 공포도인 cur보다 크거나 같으면 그룹으로 설정 가능
        if(person >= cur){// 현재 그룹에 포함된 모험가의 수가 현재 공포도 이상
            answer++; // 그룹 결성
            person = 0; // 현재 그룹에 포함된 모험가 수 초기화
        }
    }
    
    cout << answer << '\n';
}