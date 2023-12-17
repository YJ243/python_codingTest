/*
 * 2023.12.14
 * 함수 모듈화하기
*/
#include <iostream>
#include <climits>
#include <cstdlib>
#include <algorithm>

#define MAX_N 5

using namespace std;
int n = MAX_N;
int arr[MAX_N];
int total_sum;

int Diff(int i, int j, int k){
    // i가 한 팀, (j, k)가 둘이서 한 팀, 나머지 두 명이 둘이서 한 팀일 경우의 능력 차이를 리턴하기
    int return_value = INT_MAX;

    // 세 번째 팀원의 합은 전체에서 첫 번째와 두 번째 팀원의 합을 빼주면 됨
    int sum1 = arr[i];
    int sum2 = arr[j] + arr[k];
    int sum3 = total_sum - arr[i]-arr[j]-arr[k];

    // 하나라도 합이 같은 팀이 있으면 불가능한 경우
    if(sum1 == sum2 || sum2 == sum3 || sum3 == sum1)
        return return_value;

    // 세 팀의 능력 중 최대에서 세 팀의 능력 중 최소를 빼기
    return max(max(sum1, sum2), sum3) - min(min(sum1, sum2),sum3);
}

int main(){
    // 입력
    for(int i=0; i<n; i++)
        cin >> arr[i];
    
    for(int i=0; i<n; i++)
        total_sum += arr[i];

    // 첫 번째 팀원 i와 두 번째 팀원 j, k를 골라줌
    int min_diff = INT_MAX;
    for(int i = 0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
                if(i != j && j != k && i != k)  // 모든 인덱스가 다를 때
                    min_diff = min(min_diff, Diff(i,j,k));

    // 만들 수 없는 경우에는 초기값인 INT_MAX가 그대로 남아 있음
    // 이 때 -1을 출력
    if(min_diff == INT_MAX)
        cout << -1;
    else
    {
        cout << min_diff;
    }
    return 0;
}