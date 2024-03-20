/*
 * 2024.03.20
 * 내 풀이
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
vector<pair<int, int> > lines;
vector<int> selected;

int ans;

bool IsOverlapping(){
    for(int i=0; i<(int)selected.size(); i++){
        int x1 = lines[selected[i]].first , x2 = lines[selected[i]].second;
        for(int j=i+1; j<(int)selected.size(); j++){
            int x3 = lines[selected[j]].first, x4 = lines[selected[j]].second;
            if((x3 <= x1 && x1 <= x4) || (x1 <= x3 && x3 <= x2))
                return true;
        }
    }
    return false;
}

void Choose(int idx){
    if(!IsOverlapping()){       // 만약 겹치지 않는다면
        ans = max(ans, (int)selected.size());        
    }
    if(idx == n)
        return;
    
    for(int i=idx; i < n; i++){
        selected.push_back(i);
        Choose(i+1);
        selected.pop_back();
    }
}
int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        int x1, x2;
        cin >> x1 >> x2;
        lines.push_back(make_pair(x1, x2));
    }
    Choose(0);      // 0번째 선분을 고르는 함수
    cout << ans;
    return 0;
}