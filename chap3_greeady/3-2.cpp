#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    // N, M, K를 공백으로 구분하여 입력받기
    int N, M, K;
    cin >> N >> M >> K;
    double answer=0;
    vector<int> a(N,0);

    // N 개의 수를 공백을 기준으로 구분하여 입력받기
    for(int i=0; i<N; i++){
        cin >> a[i];
    }

    // 입력받은 수 내림차순 정
    sort(a.rbegin(), a.rend());
    int first = a[0]; // 가장 큰 수
    int second = a[1]; // 두번째로 큰 수

    // 더해지는 횟수 계산
    int first_count = (M/(K+1))*K + (M%(K+1));
    int second_count = (M/(K+1));
    // second_count = M-first_count;
    
    
    answer = first*first_count + second*second_count;

    // 최종 답안 출력
    cout<<answer << '\n';
}