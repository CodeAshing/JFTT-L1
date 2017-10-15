#include <iostream>
#include <regex>



using namespace std;


int min(int a, int b){
    if(a>b)
        return b;
    return a;
}
int find(char a, string b){
    for (int i = 0; i < b.size(); ++i) {
        if(a==b[i]){
            return i;
        }
    }
    return -1;
}
bool suffix(string a, int sa, string b, int sb,char x){
    if (sa+1>a.size()){
        sa=a.size()-1;
    }
    if (sb+1>b.size()){
        sb=b.size()-1;
    }
    if(a[sa]!=x){
        return false;
    }
    if(sb<0){
        return true;
    }
    sa--;
    for (int i = sb; i >= 0 ; --i) {
        if(sa<0){
            return true;
        }
        if(a[sa]!=b[i]){
            return false;
        }
        sa--;
    }
    return true;
}

void delta(int**d, const string &pattern,string alphabet){
    int m=pattern.size();
    int k;
    for (int q = 0; q <= m; ++q) {
        for (int j = 0; j < alphabet.size(); ++j) {
            k=min(m,q+1);
            while((!suffix(pattern,k-1,pattern,q-1,alphabet[j])) && k>0){
                k--;
            }
            d[q][j]=k;
        }
    }
}
void FAM(string T, int** d, int m, const string &alphabet){
    int n=T.size(),q=0,x;
    for (int i = 0; i < n; ++i) {
        x=find(T[i],alphabet);
        if(x==-1){
            cout<<"Wrong input"<<endl;
            break;
        }
        q=d[q][x];
        if(q==m){
            cout<<"Found: "<<i-m+1<<endl;
        }
    }

}

bool verifyAlphabet(string a){
    string b= std::move(a);
    sort(b.begin(),b.end());
    for (int i = 0; i < b.size()-1; ++i) {
        if(b[i]==b[i+1]){
            return false;
        }
    }
    return true;
}
bool verifyText(string a, string alphabet){
    string b= std::move(a);
    int j=0;
    sort(alphabet.begin(),alphabet.end());
    sort(b.begin(),b.end());
    for (char i : b) {
        if(i !=alphabet[j]){
            j++;
            while(true){
                if(i !=alphabet[j]){
                    if(j+1<alphabet.size()){
                        j++;
                    }else{
                        return false;
                    }
                }else{
                    break;
                }
            }
        }
    }
    return true;
}

int main() {
    string alphabet,input,pattern,a;
    regex re("[a-zA-Z0-9 ]+");
    while(true){
        cout << "Enter the alphabet:" << endl;
        cin >> alphabet;
        if(verifyAlphabet(alphabet)&&regex_match(alphabet,re)){
            break;
        }else{
            cout<<"Wrong alphabet!"<<endl;
        }
    }
    while(true){
        cout << "Enter the input:" << endl;
        cin>>input;
        if(verifyText(input,alphabet)){
            break;
        }else{
            cout<<"Wrong input!"<<endl;
        }
    }
    while(true){
        cout << "Enter the pattern:" << endl;
        cin>>pattern;
        if(verifyText(pattern,alphabet)){
            break;
        }else{
            cout<<"Wrong pattern!"<<endl;
        }
    }
    auto ** d=new int*[pattern.size()+1];
    for (int i = 0; i < pattern.size()+1; ++i) {
        d[i]=new int[alphabet.size()];
    }
    delta(d,pattern,alphabet);
    FAM(input,d,pattern.size(),alphabet);
    for (int i = 0; i <pattern.size() ; ++i) {
        delete [] d [i];
    }
    delete [] d;
    return 0;
}