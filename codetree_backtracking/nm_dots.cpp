/*
 * 24.03.23
 * 내 풀이
*/

#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#define MAX_MN 20
using namespace std;
int n, m;
vector<pair<int, int> > dots;
vector<pair<int, int> > selected;
int ans = INT_MAX;

int Calc(){
    int max_dist = -1;
    for(int i=0; i<(int)selected.size(); i++){
        for(int j=i+1; j <(int)selected.size(); j++){
            int x1 = selected[i].first, y1 = selected[i].second;
            int x2 = selected[j].first, y2 = selected[j].second;
            max_dist = max(max_dist, (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
        }
    }
    return max_dist;
}

void Choose(int idx, int cnt){       // idx번째 점을 선택하러 가는 함수
    if(cnt == m){
        ans = min(ans, Calc());
        return;
    }
    if(idx == n){
        return;
    }

    Choose(idx+1, cnt);

    selected.push_back(dots[idx]);
    Choose(idx+1, cnt+1);
    selected.pop_back();
}

int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++){
        int x, y;
        cin >> x >> y;
        dots.push_back(make_pair(x, y));
    }
    Choose(0, 0);   // 0번째 고르러 가는 함수, 현재까지 0개 고름
    cout << ans;
    return 0;
}