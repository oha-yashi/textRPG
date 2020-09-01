#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]){
  if(argc != 2){
    printf("give file name helps/***.txt!\n");
    printf("./helpSort ***\n");
    return -1;
  }

  std::string filename(argv[1]);

  std::ifstream ifs("helps/"+filename+".txt");
  if(!ifs){
    printf("file %s.txt open error!\n", argv[1]);
    return -1;
  }

  std::string s;
  std::vector<std::string> vs;
  while(ifs >> s){
    vs.push_back(s);
  }
  ifs.close();

  std::ofstream ofs("helps/"+filename+".txt");
  if(!ofs){
    printf("file %s.txt open error!\n", argv[1]);
    return -1;
  }

  printf("Befor Sort\n");
  for(auto h: vs)printf("%s ", h.c_str());
  printf("\n");
  std::sort(vs.begin(), vs.end());
  printf("After Sort\n");
  for(auto h: vs)printf("%s ", h.c_str());
  printf("\n");

  for(auto h: vs){
    ofs << h << " ";
  }
  ofs.close();

  return 0;
}