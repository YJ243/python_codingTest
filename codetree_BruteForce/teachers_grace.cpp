/*
 * 2023.12.18
 * 처음에는 가격을 1순위, 배송비를 2순위로 정렬하고 구함
 * 그 이후에는 배송비 1순위, 가격 2순위 추가
 * 마지막 답은 두개의 합을 1순위 2순위를 가격이 낮은 순으로 정렬해서 풀었음
*/
#include <iostream>
#include <algorithm>
#define MAX_N 1000

using namespace std;
int n, b;                       // n명의 학생에게 b만큼의 예산으로 선물 주기
pair<int, int> students[MAX_N]; // <학생이 원하는 선물 가격, 배송비>
int ans;                        // 선생님이 선물 가능한 학생의 최대 명수

int main(){
    // 입력
    cin >> n >> b;
    for(int i=0; i<n; i++)
        cin >> students[i].first >> students[i].second;
    
    for(int i=0; i<n; i++){
        // Step1. 먼저 pair를 복사하기
        pair<int, int> tmp[n];
        for(int j=0; j<n; j++){
            tmp[j].first = students[j].first;
            tmp[j].second = students[j].second;
        }

        // Step2. i번 학생의 선물을 반값으로 할인하기
        tmp[i].first /= 2;
        
        // Step3. 가격+배송비 합을 기준으로 오름차순 정렬, 만약 같다면 가격 기준으로 오름차순 정렬
        sort(tmp, tmp+n, [](const pair<int, int> &a, const pair<int, int> &b){
            if(a.first + a.second == b.first + b.second)
                return a.first < b.first;
            return a.first + a.second < b.first + b.second;
        });

        // Step4. 예산 범위 내에서 최대 명수 구하기
        
        int cost = 0, cnt = 0;
        for(int j=0; j<n; j++){
            if(cost + tmp[j].first + tmp[j].second > b)
                break;
            cost += tmp[j].first + tmp[j].second;
            cnt++;
        }

        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}