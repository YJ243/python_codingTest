/*
 * 2024.03.22
 * �� Ǯ�� 
*/

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_N 10
using namespace std;

int n, m, c;
int grid[MAX_N][MAX_N];
int value[MAX_N][MAX_N];
int cur_max;
vector<int> selected;

void FindCurMax(){
    int curr = 0, curr_value = 0;
    for(int i=0; i<(int)selected.size(); i++){
        curr_value += selected[i]*selected[i];
        curr += selected[i];
    }
    if(curr <= c)
        cur_max = max(curr_value, cur_max);
}

void Choose(int x, int y, int idx){
    if(idx == m){
        FindCurMax();
        return;
    }

    selected.push_back(grid[x][y]);
    Choose(x, y+1, idx+1);
    selected.pop_back();

    Choose(x, y+1, idx+1);
}

void FindMaxValue(int x, int y){    // (x, y)���� m������ ������ ����� ���� �ִ� ��ġ
    // �������� ���ؾ� ��
    cur_max = 0;            // ���� �ִ� 0���� �ʱ�ȭ
    selected.clear();       // �迭 �ʱ�ȭ
    Choose(x, y, 0);        // (x,y)���� �����ؼ� 0��° ���ڸ� ���� �Լ�

    value[x][y] = cur_max;  // value�� ���� �ִ� �ֱ�
}

bool Possible(int x1, int y1, int x2, int y2){
    // ���� �� ���� �ٸ��� ����
    if(x1 != x2)
        return true;
    // ���� �� ���� ������ ��ġ�� �ʴ´ٸ� ����
    if(y1+m <= y2 || y2+m <= y1)
        return true;
    return false;
}

int main() {
    // �Է� �ޱ�:
    cin >> n >> m >> c;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    // ���� �� ĭ���� �������� �� ���� �� �ִ� �ִ� ��ġ ���ϱ�
    for(int i=0; i<n; i++){
        for(int j=0; j<=n-m; j++){
            FindMaxValue(i,j);
        }
    }
    int ans = 0;
    // ���� ����Ž�� �����ϱ�
    for(int i=0; i<n; i++){
        for(int j=0; j<=n-m; j++){
            for(int k=0; k<n; k++){
                for(int l=0; l<=n-m; l++){
                    if(Possible(i,j,k,l)){
                        ans = max(ans, value[i][j] + value[k][l]);
                    }
                }
            }
        }
    }
    cout << ans;
    return 0;
}