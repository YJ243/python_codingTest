/*
 * 2023.12.22
 * 처음에는 문자열의 길이를 1, 2, ..., n/2+1까지 늘려가면서 하면 되는줄 알았으나, n까지 다 봤어야 틀리지 않음
 * 예제로: XABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABA (길이:80) 생각해보기
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int n;
string str;

int main(){
    // 입력
    cin >> n;

    cin >> str;

    int ans = 1;

    // 1씩 늘려가면서 어느 길이까지 2번 등장하는지 모두 시도해보기
    for(int i=1; i<n; i++){
        // 모든 길이가 i인 부분 문자열에 대해 쌍을 짖고
        // 둘이 완전히 똑같은지 확인하기

        // twice: i 길이가 2회 이상 등장하는 부분 문자열이 존재하면 true
        bool twice = false;

        for(int j=0; j<=n-1; j++){
            for(int k=j+1; k<=n-i; k++){
                // issame: j부터 i길이의 부분 문자열과
                // k부터 i길이의 부분 문자열이 완전히 같으면 true
                bool issame = true;
                for(int l=0; l<i; l++){ // i 길이까지 볼 것임
                    if(str[j+l] != str[k+l])
                        issame = false;
                }
                if(issame) twice = true;

            }
        }
        // 만약 i길이가 2회 이상 등장한다면 답은 그 다음 길이로 넣어두기
        if(twice)
            ans = i+1;
        else    // 만약 길이가 1번밖에 안나타난다면 바로 반복문 빠져나와서 출력하기
        {
            break;
        }
    }
    cout << ans;
    return 0;

}