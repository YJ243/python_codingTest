/*
 * 2024.1.19
 * 해설 풀이
 * 시뮬레이션 + Memory Optimization
*/
#include <iostream>
#define MAX_NUM 100

using namespace std;
int n, m, end_of_array, end_of_temp;
int numbers[MAX_N];
int temp[MAX_NUM];



// 주어진 시작점에 대하여
// 부분 수열의 끝 위치를 반환
int GetEndIdxOfExplosion(int start_idx, int curr_num){
    int end_idx = start_idx + 1;
    while(end_idx < end_of_array){
        if(numbers[end_idx] == curr_num)
            end_idx++;
        else
            break;
    }
    return end_idx-1;
}

// 입력 배열에서 지우고자 하는 부분 수열을 삭제하기
void CutArray(int start_idx, int end_idx){
    int cur_len = end_idx - start_idx + 1;
    for(int i=end_idx+1; i < end_of_array; i++)
        numbers[i-cut_len] = numbers[i];
    end_of_array -= cur_len;
}
int main() {
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> numbers[i];    
    end_of_array = n;

    bool did_explode;
    int curr_idx;
    do{
        did_explode = false;
        curr_idx = 0;

        while(curr_idx < end_of_array){
            int end_idx = GetEndIdxOfExplosion(curr_idx, numbers[curr_idx]);

            if(end_idx - curr_idx+1 >= m){
                // 연속한 숫자의 개수가 m개 이상이면 폭탄이 터질 수 있는 경우 해당 부분 수열을 잘라낸 이후
                // 폭탄이 터졌음을 기록
                CutArray(curr_idx, end_idx);
                did_explode = true;
            }
            else{
                // 주어진 시작 원소에 대하여 폭탄이 터질 수 없는 경우
                // 다음 원소에 대하여 탐색하기
                curr_idx++;
            }
        }
    }
    while(did_explode);     // 더 이상 폭탄이 터질 수 없을 떄까지 반복

    cout << end_of_array << '\n';
    for(int i=0; i<end_of_array; i+)
        cout << numbers[i] << '\n';

    return 0;
}