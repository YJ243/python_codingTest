#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<char> a(n+1);
    
    for(int i=1; i<=n; i++)
        cin >> a[i];
    int row=1;
    int column=1;
    for(int i=1; i<=n; i++){
        switch (a[i])
        {
        case 'L':
            if(column==1){
                break;                
            }
            else{
                column--;
            }
            break;
        case 'R':
            if(column==n)
            {
                break;
            }
            else{
                column++;
            }
            break;
        case 'U':
            if(row == 1){
                cout << row<< '\n';
                break;
            }
            else{
                row--;
            }
            break;
        case 'D':
            if(row == n){
                break;
            }
            else{
                row++;
            }
            break;
        }
    }
    cout << row << ' ' << column << '\n';
}