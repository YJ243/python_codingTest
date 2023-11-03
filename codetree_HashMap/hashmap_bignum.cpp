/*
 * 2023.11.03
 * unordered_map은 (k,v)형태로 데이터를 저장할 수 있고,
 * key의 범위는 정의하기 나름이고, 사용되는 메모리는 실제 unordered_map에 들어간 데이터 수에 비례
 * 숫자 범위와 무관하게 n개의 숫자에 대한 메모리만 사용
*/

#include <iostream>
#include <unordered_map>

#define MAX_N 6

using namespace std;

int arr[MAX_N];
unordered_map<int, int> num_to_index;

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        cin >> arr[i];
        num_to_index[arr[i]] = i+1;
    }
    int k;
    cin >> k;

    cout << num_to_index[k];
    return 0;
}