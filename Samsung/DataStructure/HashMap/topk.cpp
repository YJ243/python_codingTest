/*
2023.10.06
top k 숫자
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100000

// 변수 선언
int n, k;
int arr[MAX_N];
unordered_map<int, int> freq;
vector<pair<int, int> > v;

int main(){
    // 입력:
    cin >> n >> k;

    // 각 숫자가 몇 번씩 나왔는지 hashmap에 기록
    for(int i=0; i<n; i++){
        cin >> arr[i];
        freq[arr[i]]++;
    }
    // hashmap을 순회하면서
    // 중복되지 않게 새 배열을 만들어 줌
    for(unordered_map<int, int>::iterator it = freq.begin(); it != freq.end(); it++){
        v.push_Back({it->second, it->first});
    }

    // 문제에서 요구한 정렬 기준에 맞추어 정렬
    sort(v.begin(), v.end())

    // 출력:
    for(int i=(int)v.size()-1; i>=(int)v.size()-k; i--)
        cout << v[i].second << ' ';
    return 0;
}