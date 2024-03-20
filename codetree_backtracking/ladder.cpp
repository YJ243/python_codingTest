/*
 * 2024.03.20
 * 사다리 타기
*/
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_N 11
#define MAX_M 15

using namespace std;
int n, m;

vector<pair<int, int> > lines;
vector<int> selected;
int result[MAX_N];
int ans;

bool IsSame(){
    int curr[n];
    for(int i=0; i<n; i++){
        curr[i] = i;
    }
    for(int i=0; i<(int)selected.size(); i++){
        int num = lines[selected[i]].second;
        int val = curr[num];
        curr[num] = curr[num+1];
        curr[num+1] = val;
    }


    for(int i=0; i<n; i++){
        if(curr[i] != result[i])
            return false;
    }
    return true;
}

void Choose(int idx){
    if(idx == m){
        if(IsSame()){
            ans = min(ans, (int)selected.size());
        }
        return;
    }

    selected.push_back(idx);
    Choose(idx+1);
    selected.pop_back();

    Choose(idx+1);
}

int main() {
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        lines.push_back(make_pair(b-1,a-1));    // 위에서부터 b번째 위치에 a ~ a+1번째 세로줄 연결
    }

    // Step 1. lines를 b 기준으로 정렬하기
    sort(lines.begin(), lines.end());

    // Step 2. 결과 저장하기
    for(int i=0; i<n; i++)
        result[i] = i;
    for(int i=0; i<m; i++){
        int num = lines[i].second;
        int val = result[num];
        result[num] = result[num+1];
        result[num+1] = val;
    }

    // step 3. 가로줄 선택하기
    ans = m;
    Choose(0);
    cout << ans;
    return 0;
}