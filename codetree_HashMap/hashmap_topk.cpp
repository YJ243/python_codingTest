/*
 * 2023.12.03
 * unordered_map에서 vector로 변환하고, 
 * vector의 원소 pair<int,int>에서 앞원소/뒷원소를 기준으로 정렬하는 방식 
 * 내 풀이
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#define MAX_N 100000

using namespace std;

int n, k; // 입력받을 n개 숫자, 출력할 k개 
int arr[MAX_N];
unordered_map<int, int> freq;

bool compare(const pair<int, int> &a, const pair<int, int> &b){
    if(a.second == b.second){       // 빈도수가 같다면
        return a.first > b.first;   // 숫자가 더 큰게 앞으로 가도록 정렬
    }
    return a.second > b.second;     // 빈도수가 큰 순으로 정렬
}

int main(){
    cin >> n >> k;

    for(int i=0; i<n; i++){
        cin >> arr[i];
        freq[arr[i]]++;     // 빈도수 저장
    }

    vector<pair<int, int> > vec(freq.begin(), freq.end()); // 빈도수 hashmap을 vector로 변경

    sort(vec.begin(), vec.end(), compare);  // 빈도수 -> 숫자 순으로 내림차순 정렬

    for(int i=0; i<k; i++){
        cout << vec[i].first << ' ';
    }
}