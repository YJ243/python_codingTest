#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string s;
    cin >> s;
    string alpabet;
    int sum = 0;
    for(int i=0; i<s.size(); i++){
        if(isalpha(s[i])){
        //if(s[i]-'A'>=0){
            alpabet += s[i];
        }
        else{
            int cur = s[i] - '0';

            sum = sum + cur;

        }
    }
    for(int i=0; i<alpabet.size()-1; i++){
        for(int j=i+1; j<alpabet.size(); j++){
            if(alpabet[i]-'A' > alpabet[j]-'A'){
                char tmp = alpabet[i];
                alpabet[i] = alpabet[j];
                alpabet[j] = tmp;
            }
        }
    }

    cout << alpabet<<sum<<'\n';

}