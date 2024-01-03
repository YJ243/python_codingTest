/*
 * 2023.12.22
 * 처음에는 문자열의 길이를 1, 2, ..., n/2+1까지 늘려가면서 하면 되는줄 알았으나, n까지 다 봤어야 틀리지 않음
 * 예제로: XABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABA (길이:80) 생각해보기
*/

#include <iostream>
#include <string>
#include <climits>
#include <vector>

using namespace std;

int n;
string s;
int ans = INT_MAX;
int main() {
    cin >> n;
    cin >> s;

    // i는 연속 부분 문자열의 개수임
    for(int i=1; i<=n; i++){
        // step 1. s에서 i개수만큼 앞에서부터 뽑아보기
        int i_max = 0;
        for(int j=0; j<n; j++){
            // cur: s에서 j번 인덱스부터 i 길이의 부분 문자열
            string cur = s.substr(j, i);
            int cnt = 0;
            for(int k=0; k<n-i+1; k++){
                // step 2. cur가 s에서 2개 이상이 나오는지 확인
                string tmp = s.substr(k,i);
                if(tmp == cur)  cnt++;      // cur이 s에 들어있다면 cnt 증가
            }

            i_max = max(i_max, cnt);        // s에 들어있는 부분 문자열의 개수 중 최대 개수가 i_max가 됨
        }
        if(i_max == 1){                     // 그런데 최대가 1이라면 2번 이상 등장하지 않는다는
            ans = min(ans, i);              // 답을 갱신하고 반복문 나가기
            break;           
        }
    }
    cout << ans;
    return 0;
}