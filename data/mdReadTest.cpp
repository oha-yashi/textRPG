#include <iostream>
#include <fstream>

#include <sstream> //stringstream

using namespace std;

void mdReplace(string &str, stringstream &ss){
  replace(str.begin(), str.end(), '|', ' ');
  ss << str;
}

int main(){
  string n;int h,a,d,e;char c;
  stringstream ss;
  ifstream fp("test.md");
  getline(fp, n);getline(fp, n);
  
  while(getline(fp, n)){
    mdReplace(n, ss);
    ss >> n >> h >> a >> d >> e;
    cout << n << h << a << d << e << endl;
  }

  return 0;
}