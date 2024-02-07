/*
 * 2024.2.6
 * ����� ���� ���� �����ε� �ڲ� �Ǽ��� �Ѵ�.
 * �̷� ������ ���� Ǯ� ���� ��� �Ǽ��� �ϴ��� �� Ȯ������!
 * �Ǽ� 1: GetDirectionIdx���� �ε����� �߸� ������
 * �Ǽ� 2: GetDirectionIdx�� �Ⱥθ��� char������ �Ѱ������
 * �Ǽ� 3: ������ �ٲٴµ����� �ð��� ���� �ҿ���� �ʴµ�, ���� ����ó�� �����ؼ� �ð��� �ҿ�ȴٰ� ������ Ǯ����
 * �Ĳ��ϰ� �� �а�!!! ���� Ǭ ���� ��� ������ �� �־����� �ϳ��� Ȯ���ؼ� �Ǽ��� ���̱� 
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>

#define MAX_N 50

using namespace std;
int n, m, t, k;     // n: ���� ũ��, m: ���� ����, t: �ð�, k: ��Ƴ��� �� �ִ� �ִ� ���� ��

vector<tuple<int, int, int> > marble[MAX_N][MAX_N];         // ������ ����
vector<tuple<int, int, int> > next_marble[MAX_N][MAX_N];    // �߰� �̵��� ���� �迭
int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};    // ��<->��, ��<->�� (d+2)%4

int GetDirectionIdx(char d){    // �Է¹��� ���⿡ ���ؼ� �ε����� ��ȯ�ϴ� �Լ� 
    int ret;
    if(d == 'U') ret = 0;
    else if(d == 'R') ret = 1;
    else if(d == 'D') ret = 2;
    else ret = 3;

    return ret;
}

void Initialize_next(){     // �߰� ����� �����ϴ� �迭 �ʱ�ȭ
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            next_marble[i][j].clear();
        }
    }
}

bool InRange(int x, int y){     // (x,y)�� ���� �ȿ� �ִ��� Ȯ���ϴ� �Լ�
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y){    // (x,y)�� �ִ� ������ �ű��
    for(int i=0; i<(int)marble[x][y].size(); i++){  // (x,y)�� �ִ� ������ ��� ���鼭 
        int v, id, d;   // �ӵ�, ���� ��ȣ, �̵� ����
        tie(v, id, d) = marble[x][y][i];
        
        int curX=x, curY=y;     // ���� ĭ�� curX, curY��
        for(int move=0; move<v; move++){ // v �ӵ���ŭ �����̱�
            int nx = curX+dirs[d][0], ny = curY+dirs[d][1];
            if(InRange(nx,ny)){
                // ���� �ȿ� �ִٸ� ��ǥ ������Ʈ
                curX = nx, curY = ny;
            }
            else{
                // ���� �ȿ� ���ٸ� ����ٲٰ� ��ǥ ������Ʈ�ϱ�
                // ������ �ٲٴ� ������ �ð��� ���� �ҿ���� ����
                d = (d+2) % 4;
                curX += dirs[d][0]; curY += dirs[d][1];
            }
        }
        next_marble[curX][curY].push_back(make_tuple(v, id, d));
    }
}

void RemoveLowPriority(int x, int y){   // (x,y)�� �ִ� ���� �� k���� ���� �켱������ ���� �ֵ� �����ϱ�
    // 1. �ӵ�, �ε��� ������ �������� �����ϱ�
    sort(next_marble[x][y].begin(), next_marble[x][y].end(), greater<tuple<int, int, int> >());
    
    // 2. �켱������ ���� �ֵ� �̾Ƽ� �����ϱ�
    int cnt = (int)next_marble[x][y].size() - k;
    while(cnt--){
        next_marble[x][y].pop_back();
    }
}

void Simulate(){
    // 1. �̵��� �ϱ� �� next �迭 �ʱ�ȭ
    Initialize_next();

    // 2. ���� �̵�
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(marble[i][j].size() > 0){
                // ���� �ش� ĭ�� ������ �ִٸ�
                Move(i,j);  // �̵���Ű��
                marble[i][j].clear(); // ���� vector�� �ʱ�ȭ��Ű��
            }
        }
    }

    // 3. ��� �����̰� �� ��, ����� ���� Ž���ؼ� ���ֱ�
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(next_marble[i][j].size() > k){
                // k������ ���ٸ�
                RemoveLowPriority(i,j);
            }
        }
    }

    // 4. ���� �迭�� �ű��
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(next_marble[i][j].size() > 0)
                for(int l=0; l<(int)next_marble[i][j].size(); l++){
                    int v, id, d;
                    tie(v, id, d) = next_marble[i][j][l];
                    marble[i][j].push_back(make_tuple(v, id, d));
                }
        }
    }
}

int main() {
    // ���� ���� �� �Է�:
    cin >> n >> m >> t >> k;    // n: ���� ũ��, m: ���� ����, t: �ð�, k: �� ĭ�� ���� �� �ִ� ���� ����
    for(int i=0; i<m; i++){     // m���� ���� �Է¹ޱ�
        int r, c, v; char d;    // (r,c)���� d�������� �ӵ�v�� �̵� ��
        cin >> r >> c >> d >> v;
        // ���Ŀ� �ӵ�, ���� ��ȣ�� ū ������ �켱������ ���� �Ű����ϱ� ������ �Ʒ��� ���� ����
        marble[r-1][c-1].push_back(make_tuple(v, i+1, GetDirectionIdx(d)));   // ���� ��ġ�� (�ӵ�, ���� ��ȣ, �̵�����) ����
    }

    // t�ʿ� ���ؼ� �ùķ��̼� ����
    for(int time_val=1; time_val<=t; time_val++){
        Simulate();     // �ùķ��̼� ����
    }

    // �����ִ� ������ ���� ���ϱ�
    int ans = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // ���� �ش� ĭ�� ������ �ִٸ�
            if(marble[i][j].size() > 0)
                // �� �ȿ� �ִ� ���� ������ŭ ����
                ans += (int)marble[i][j].size();
        }
    }

    cout << ans << '\n';
    return 0;
}