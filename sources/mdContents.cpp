/**
 * markdownから目次を作成
 * 出来が悪い
 * */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
using namespace std;

int main(){
  printf("filename ***.md -> ");
  char filename[50];
  scanf("%s", filename);
  string path = string(filename) + ".md";

  ifstream fp(path);
  if(!fp){
    printf("%s open error!\n", path.c_str());
    return -1;
  }

  vector<pair<int, string>> titleList;

  string line;
  while(fp >> line){
    if(line == "#"){
      getline(fp, line);
      titleList.push_back(make_pair(0, line));
    }else
    if(line == "##"){
      getline(fp, line);
      titleList.push_back(make_pair(1, line));
    }else
    if(line == "###"){
      getline(fp, line);
      titleList.push_back(make_pair(2, line));
    }else
    if(line == "####"){
      getline(fp, line);
      titleList.push_back(make_pair(3, line));
    }else
    if(line == "#####"){
      getline(fp, line);
      titleList.push_back(make_pair(4, line));
    }else{
      ;//none
    }
  }

  //書き出し
  printf("\n\n");
  for(auto [n, str]: titleList){
    for(int i=0; i<n; i++)printf("    ");//4 spaces
    printf("- [%s](#%s)\n", str.c_str(), str.c_str());
  }
  printf("\n");
}