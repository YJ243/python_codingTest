/*
 * 24.03.22
 * 해설 풀이
 * 오름차순으로 순서쌍이 만들어지게 하기 위해 마지막으로 선택한 숫자를
 * 재귀함수의 last_num이라는 인자로 설정하여 해결
*/
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> combination;

// 방문한 원소들을 출력해줍니다.
void PrintCombination() {
    for(int i = 0; i < combination.size(); i++)
        cout << combination[i] << " ";
    cout << endl;
}

// 지금까지 뽑은 개수와 마지막으로 뽑힌 숫자를 추적하여
// 그 다음에 뽑힐 수 있는 원소의 후보를 정한다.
void FindCombination(int cnt, int last_num){
    // m개를 모두 뽑은 경우 답을 출력해준다.
    if(cnt == m){
        PrintCombination();
        return;
    }

    // 뽑을 수 있는 원소의 후보들을 탐색한다.
    for(int i=last_num+1; i <= n; i++){
        combination.push_back(i);
        FindCombination(cnt+1, i);
        combination.pop_back();
    }
}

int main() {
    cin >> n >> m;

    // 가능한 범위를 순회하며 해당 숫자가 조합의 첫번째 숫자일 떼를 탐색
    for(int i = 1; i <= n; i++){
        combination.push_back(i);
        FindCombination(1, i);
        combination.pop_back();
    }
    return 0;
}