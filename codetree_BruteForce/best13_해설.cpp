/*
 * 2023.11.14
 * �ؼ� Ǯ��
*/

#include <iostream>
#include <algorithm>
#include <cstdlib>

#define MAX_N 20

using namespace std;

int n;
int arr[MAX_N][MAX_N];

int main(){
    // �Է�
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> arr[i][j];

    // Step 1.
    // ù��° ���ڸ� ���� (i,j)
    int max_cnt = 0;
    for(int i=0; i<n; i++)
        // ���ڸ� ����� ���� �����θ� ����
        for(int j=0; j<n-2; j++){
            // �� ��° ���ڸ� ����(k,l)
            for(int k=0; k<n; k++){
                for(int l=0; l<n-2; l++){
                    // step2. �� ���ڰ� ��ġ�� ��쿡�� �������� ���� ����
                    if(i == k && abs(j-l) <= 2)
                        continue;

                    // Step3.  �� ���ڰ� ��ġ�� �ʴ� ��쿡 ���� ���� ���� ���� ����
                    int cnt1 = arr[i][j] + arr[i][j+1] + arr[i][j+2];
                    int cnt2 = arr[k][l] + arr[k][l+1] + arr[k][l+2];
                    max_cnt = max(max_cnt, cnt1+ cnt2);
                }
            }
        }
    cout << max_cnt;
    return 0;
}