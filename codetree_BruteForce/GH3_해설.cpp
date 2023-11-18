/*
 * 2023.11.18
 * G, H를 저장하지 않고 바로 1, 2를 저장해서 이후에 더하도록
 * 주어진 인덱스의 최대값까지가 아니라 MAX_NUM까지 보도록!!
 * https://www.codetree.ai/missions/5/problems/G-or-H-3?&utm_source=clipboard&utm_medium=text
*/

#include <iostream>
#include <algorithm>

#define MAX_NUM 10000

using namespace std;

int n, k;
int arr[MAX_NUM + 1];

int main(){
    // 입력
    cin >> n >> k;
    for(int i=0; i<n; i++){
        int x, char c;
        cin >> x >> c;
        if(c == 'G')
            arr[x] = 1;
        else
        {
            arr[x] = 2;
        }
    }
    // 모든 구간의 시작점을 잡기
    int max_sum = 0;
    for(int i=0; i<=MAX_NUM-k; i++){
        // 해당 구간 내 원소의 합을 구하기
        int sum = 0;
        for(int j=i; j<=i+k; j++)
            sum += arr[j];
        // 최댓값을 구하기
        max_sum = max(max_sum, sum);
    }
    cout << max_sum;
    return 0;
}