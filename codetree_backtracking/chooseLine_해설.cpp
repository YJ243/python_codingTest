/*
 * 2024.03.20
 * 해설 풀이
 * 모든 선분을 선택하는 조합을 만들어본 후, 그 중 선분끼리 전혀 겹치지 않는 경우들 중 최대 선분의 수를 구하면 된다
 * 두 선분이 겹치는지 여부는 한 점이 다른 선분에 속하는지 여부로 쉽게 판단 가능하다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int n;
pair<int, int> segments[MAX_N];

int ans;
vector<pair<int, int> > selected_segs;

bool Overlapped(pair<int, int> seg1, pair<int, int> seg2){
    int ax1, ax2;
    tie(ax1, ax2) = seg1;

    int bx1, bx2;
    tie(bx1, bx2) = seg2;

    // 두 선분이 겹치는지 여부는 산 점이 다른 선분에 포함되는 경우로 판단 가능하다
    return (ax1 <= bx1 && bx1 <= ax2) || (ax1 <= bx2 && bx2 <= ax2) ||
           (bx1 <= ax1 && ax1 <= bx2) || (bx1 <= ax2 && ax2 <= bx2);
}

bool Possible(){
    // 단 한쌍이라도 선분끼리 겹치면 안된다.
    for(int i=0; i<(int)selected_segs.size(); i++)
        for(int j=i+1; j < (int)selected_segs.size(); j++)
            if(Overlapped(selected_segs[i], selected_segs[j]))
                return false;
    return true;
}

void FindMaxSegments(int cnt){
    if(cnt == n){
        if(Possible())
            ans = max(ans, (int) selected_segs.size());
        return;
    }

    selected_segs.push_back(segments[cnt]);
    FindMaxSegments(cnt+1);
    selected_segs.pop_back();

    FindMaxSegments(cnt+1);
}

int main(){
    cin >> n;

    for(int i=0; i<n; i++){
        int x1, x2;
        cin >> x1 >> x2;
        segments[i] = make_pair(x1, x2);
    }

    FindMaxSegments(0);

    cout << ans;
    return 0;
}