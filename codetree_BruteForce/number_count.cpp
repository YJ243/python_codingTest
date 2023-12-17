/*
 * 2023.12.13
 * 처음에는 주어진 n개의 숫자를 차례대로 보면서 개수를 세려고 함 -> 못품
 * 각 자리수에서 삼중 포문을 돌면서 count 값이 맞는지 확인하는 방식으로 가야 했음
 * 그런데 문제 조건에서 각 자리수가 서로 다르다는 조건을 못봐서 더 틀렸었음 
*/

#include <iostream>
#include <unordered_set>

using namespace std;
int n;
int arr[10];
pair<int, int> count[10];
int ans;

int main(){
    // 입력:
    cin >> n;

    for(int i=0; i<n; i++)
        cin >> arr[i] >> count[i].first >> count[i].second;

    // 각 자리마다 1부터 9까지 늘려나가면서 확인하기
    for(int i=1; i<=9; i++){
        for(int j=1; j<=9; j++){
            for(int k=1; k<=9; k++){
                // 하나라도 같은 숫자가 있으면 안됨
                if(i == j || j == k || k == i) continue;
                bool countable = true;
                for(int idx=0; idx<n; idx++){
                    // 각 n개의 숫자마다 사용할 자료구조
                    pair<int, int> cur_cnt = {0,0}; // first_cnt, second_cnt
                    unordered_set<int> numbers;
                    numbers.insert(i);
                    numbers.insert(j);
                    numbers.insert(k);

                    // a,b,c는 100, 10, 1의 자리수
                    int a = arr[idx]/100, c = arr[idx]%10;
                    int b = ((arr[idx]-c)/10)%10;
                    // 각 자리수별로 같은지 확인
                    if(a == i) cur_cnt.first++;
                    if(b == j) cur_cnt.first++;
                    if(c == k) cur_cnt.first++;

                    // a,b,c,가 들어있으면서, 똑같은 자리에는 없는지 확인
                    if(numbers.find(a) != numbers.end() && a != i)  cur_cnt.second++;
                    if(numbers.find(b) != numbers.end() && b != j)  cur_cnt.second++;
                    if(numbers.find(c) != numbers.end() && c != k)  cur_cnt.second++;

                    if((cur_cnt.first != count[idx].first) || (cur_cnt.second != count[idx].second)){
                        // 둘 중 하나라도 다르다면
                        countable = false;
                        break;
                    }
                    
                }
                if(countable)   ans++;
            }
        }

    }
    cout << ans;
    return 0;
}