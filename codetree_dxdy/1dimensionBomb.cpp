/*
 * 2024.1.19
 * 내 풀이
*/
#include <iostream>
#define MAX_N 100
#define MAX_M 100

using namespace std;
int n, m;
int arr[MAX_N];
int lastIdx;

void doBomb(int s, int e){      // s부터 e까지의 폭탄 번호 0으로 만들
    for(int i=s; i<=e; i++)
        arr[i] = 0;
}

void Bomb(){
    lastIdx = n-1;

    while(true){
        if(lastIdx+1 < m) break;        // 만약 m개보다 작은 숫자가 남았다면 break;

        bool IsBombed = false;
        int startIdx = 0, curCnt = 1;
        // Step 1. 먼저 m개 이상 연속으로 같은 숫자가 적힌 폭탄 0으로 만들기
        int curNum = arr[startIdx];

        for(int i=1; i<=lastIdx; i++){
            // 만약 같지 않은 숫자가 나온다면
            if(arr[i] != curNum){
                if(curCnt >= m){            // 그전까지 m개이상의 폭탄이 나왔다면
                    IsBombed = true;
                    doBomb(startIdx, i-1);  // start인덱스부터 그전까지 0으로 만들기
                }
                curCnt = 1;                 // 다시 개수 1로 만들기
                startIdx = i;               // 시작 인덱스를 현재로
                curNum = arr[startIdx];     // 확인하려는 값을 현재 값으로
            }
            // 같은게 나왔다면
            else{
                curCnt++;                   // 같은 폭탄 개수 증가시키기
            }

        }

        // 마지막 인덱스도 확인하기
        if(curCnt >= m){
            IsBombed = true;
            doBomb(startIdx, lastIdx);    // start인덱스부터 현재까지 0으로 만들기
        }

        if(!IsBombed) break;        // 만약 폭탄이 터지지 않았다면 break

        // Step 2. 중력 작용시키기
        int tmp[lastIdx+1];
        int tmpCurIdx = 0;
        for(int i=0; i<=lastIdx; i++){
            if(arr[i]){     // 만약 숫자가 있다면
                tmp[tmpCurIdx] = arr[i];
                tmpCurIdx++;
            }
        }

        // Step 3. 원래 배열로 옮기기
        for(int i=0; i<tmpCurIdx; i++){
            arr[i] = tmp[i];
        }
        // Step 4. 인덱스 업데이트
        lastIdx = tmpCurIdx-1;
    }
}

int main() {
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++)
        cin >> arr[i];    
    
    // 폭발시키기
    Bomb();
    /*
    if(m == 1){
        cout << 0;
        return 0;
    }
    */
    // 출력:
    cout << lastIdx+1 << '\n';
    for(int i=0; i<=lastIdx; i++)
        cout << arr[i] << '\n';
    return 0;
}