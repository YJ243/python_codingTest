/*
 * 2024.01.12
 * Backtracking + Cutting
 * 시간복잡도: O(3^N * N^2)
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

#define NUM_LEN 3

using namespace std;

int n;
vector<int> series;
int numbers[NUM_LEN] = {4,5,6};

// 시작과 끝 인덱스가 주어진 두 수열이 동일한지 여부를 판별
bool IsEqual(int start1, int end1, int start2, int end2){
    for(int i=0; i <= (end1-start1); i++){
        if(series[start1+i] != series[start2+i])
            return false;
    }
    return true;
}

// 가능한 수열인지 판별하기
bool IsPossibleSeries(){
    // 수열의 가장 앞부터 각 인덱스가 시작점일 때
    // 인접한 연속 부분 수열이 동일한 경우가 있는지 탐색
    for(int idx=0; idx < (int)series.size(); idx++){
        // 가능한 연속 부분 수열의 길이 범위를 탐색하기
        int len = 1;
        while(true){
            // 연속 부분 수열의 시작과 끝 인덱스를 설정
            int start1 = idx, end1 = idx+len-1;
            int start2 = end1+1, end2 = start2+len-1;

            // 두번째 연속 부분 수열의 끝 인덱스가 범위를 넘어가면 탐색 종료
            if(end2 >= (int)series.size()) break;

            // 인접한 연속 부분 수열이 같은지 화인
            if(IsEqual(start1, end1, start2, end2))
                return false;
            len++;
        }
    }
    return true;
}

// 특정 시점까지 cnt개의 숫자를 뽑았을 때 그 다음 어떤 숫자를 뽑을 지를 선택
void FindMinSeries(int cnt){
    // n개의 숫자가 선택됐을 때 불가능한 수열의 경우 탐색을 종료
    // 가능한 수열인 경우 이를 출력하고 프로그램 종료
    if(cnt == n){
        for(int i=0; i<series.size(); i++)
            cout << series[i];
        exit(0);
    }

    // 사용 가능한 각 숫자가 뽑혔을 때의 경우를 탐색
    for(int i=0; i<NUM_LEN; i++){
        series.push_back(num)
    }
}

int main(){
    cin >> n;

    FindMinSeries(0);   // 아직까지 뽑은 숫자가 없으니 0을 인자로 넘기기
    return 0;
}
