/*
 * 2024.1.18
 * 내 풀이
*/

#include <iostream>
#include <string>

#define MAX_N 10

using namespace std;


string RunLengthEncoding(string input){
    // 이 함수는 input 문자열을 Run-Length-Encoding 한 결과를 반환하기
    string encoded = "";

    // 입력의 첫번째 값을 읽고 초기화하기
    char curr_char = input[0];
    int num_char = 1;
    for(int i=1; i<(int)input.length(); i++){
        if(input[i] == curr_char)
            num_char++;
        else{
            // 지금까지 세어온 curr_char와 num_char를 기록
            encoded += curr_char;
            encoded += to_string(num_char);

            // curr_char와 num_char를 현재 값으로 초기화하기
            curr_char = input[i];
            num_char = 1;
        }
    }

    // 마지막 덩어리에 해당하는 curr_char와 num_char를 기록
    encoded += curr_char;
    encoded += to_string(num_char);
    return encoded;
}


int main() {
    string A
    cin >> A;

    int min_length = RunLengthEncoding(A).length(); // 초기값은 shift 안했을 때의 값
    int n = A.length();
    int num_shift = n-1;    // 0부터 length-1번 shift 하기

    while(num_shift--){
        // 문자열 A를 오른쪽으로 1번 shift하기
        // 오른족부터 채워넣어야 하며, 마지막 값은 temp에 저장된 값을 사용해야 됨을 유의
        char temp = A[n-1];
        for(int i=n-1; i >= 1; i--)
            A[i] = A[i-1];
        A[0] = temp;

        int length = RunLengthEncoding(A).length();
        if(min_length > length)
            min_length = length;
    }

    // 출력
    cout << min_length;
    return 0;

}