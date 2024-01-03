/*
 * 2023.12.22
 * 처음에 i와 j가 나오는 횟수를 각각 카운팅하지 않고 ||으로 처리해서 틀림
*/
#include <iostream>
#include <algorithm>

using namespace std;

int numbers[3][3];
int ans;
int main(){
    for(int i=0; i<3; i++){
        int num;
        cin >> num;
        numbers[i][0] = num / 100;
        numbers[i][1] = (num / 10) % 10;
        numbers[i][2] = num % 10;
    }

    for(int i=1; i<=9; i++){
        for(int j=i+1; j<=9; j++){
            // 짝지어진 숫자는 i와 j

            // 가로 줄
            bool flag = false;
            for(int k=0; k<3; k++){
                int iCnt = 0, jCnt = 0;
                for(int l=0; l<3; l++){
                    if(numbers[k][l] == i)  iCnt++;
                    else if(numbers[k][l] == j) jCnt++; 
                }
                if((iCnt + jCnt == 3) &&(iCnt*jCnt != 0)){
                    flag = true;
                    break;
                }
            }
            if(flag){
                ans++;
                continue;
            }
            // 세로 줄
            flag = false;
            for(int k=0; k<3; k++){
                int iCnt = 0, jCnt = 0;
                for(int l=0; l<3; l++){
                    if(numbers[l][k] == i)  iCnt++;
                    else if(numbers[l][k] == j) jCnt++; 
                }
                if((iCnt + jCnt == 3) &&(iCnt*jCnt != 0)){
                    flag = true;
                    break;
                }
            }
            if(flag){
                ans++;
                continue;
            }

            // 우하 대각선
            int iCnt = 0, jCnt = 0;
            if(numbers[0][2] == i)  iCnt++;
            else if(numbers[0][2] == j) jCnt++;

            if(numbers[1][1] == i)  iCnt++;
            else if(numbers[1][1] == j) jCnt++;

            if(numbers[2][0] == i)  iCnt++;
            else if(numbers[2][0] == j) jCnt++;
            
            if((iCnt + jCnt == 3) &&(iCnt*jCnt != 0)){
                ans++;
                continue;
            }
            // 좌하 대각선
            iCnt = 0, jCnt = 0;
            if(numbers[0][0] == i)  iCnt++;
            else if(numbers[0][0] == j) jCnt++;

            if(numbers[1][1] == i)  iCnt++;
            else if(numbers[1][1] == j) jCnt++;

            if(numbers[2][2] == i)  iCnt++;
            else if(numbers[2][2] == j) jCnt++;
            
            if((iCnt + jCnt == 3) &&(iCnt*jCnt != 0)){
                ans++;
                continue;
            }
        }
    }
    cout << ans;
    return 0;
}