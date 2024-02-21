/*
 * 2024.02.21
 * �� Ǯ��
*/

#include <iostream>

#define MAX_N 15
using namespace std;

int n, m;       // n: ���� ũ��, m: ����μ��� Ű��� �� ���
int tree[MAX_N][MAX_N];
bool nutrient[MAX_N][MAX_N];
int dirs[8][2] = {{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}};

void Init(){
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> tree[i][j];
    for(int i=n-2; i<n; i++)
        for(int j=0; j<2; j++)
            nutrient[i][j] = true;
}

void MoveNutrient(int d, int p){    // ��� ������� d�������� p��ŭ �����̱�
    bool temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            temp[i][j] = false;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j]){
                // ���� ������� �ִٸ� �����̱�
                int nx = (i + dirs[d][0]*p + n * 10) % n;
                int ny = (j + dirs[d][1]*p + n * 10) % n;
                temp[nx][ny] = true;
            }
        }
    }
    // �ٽ� temp �迭�� ������� nutrient�� �ֱ�
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            nutrient[i][j] = temp[i][j];

}

void InputNutrient(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j]){
                tree[i][j]++;   // �ش� ���ڿ� �ִ� ���� �� ������Ű��
            }
        }
    }


}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    return InRange(x, y) && tree[x][y] >= 1;
}

void GrowTree(int x, int y){
    int dir_tree[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};
    int cnt = 0;
    for(int d=0; d<4; d++){
        int nx = x + dir_tree[d][0], ny = y + dir_tree[d][1];
        if(CanGo(nx, ny)){
            cnt++;
        }
    }
    tree[x][y] += cnt;      // ������ ���� ������ŭ ������Ű��
}

void GrowMoreTree(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j]){
                // �������� ���Ե� ������ ���̰� 2 �̻��� �밢������ ������ ���� ������ŭ �� ����
                GrowTree(i,j);
            }
        }
    }
}

void MakeNutrient(){
    bool temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            temp[i][j] = false;
    } 
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(tree[i][j] >= 2 && !nutrient[i][j]){
                tree[i][j] -= 2;
                temp[i][j] = true;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(nutrient[i][j])
                nutrient[i][j] = false;
            nutrient[i][j] = temp[i][j];
        }
    }
}

void Output(){
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ans += tree[i][j];
        }
    }
    cout << ans << '\n';
}

int main() {
    // �ʱ� ���α׷��� ���� �Է°� ���� ����
    Init();
    while(m--){
        int d, p;           // �̵� ����� �̵� ĭ�� �Է¹ޱ�
        cin >> d >> p;
        d--;
        MoveNutrient(d, p);
        InputNutrient();
        GrowMoreTree();
        MakeNutrient();
    }
    // ���:
    Output();    
    return 0;
}