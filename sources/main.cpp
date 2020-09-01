#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <random>
#include <cstdlib>
#include <stdexcept>

using namespace std;

#define P_FILE "data/player.md"
#define M_FILE "data/monster.md"
#define B_FILE "data/boss.md"
#define W_FILE "data/weapon.md"

#define rep(i,n) for(int i=0; i<(int)n; i++)

void mdTableReplace(string &str, stringstream &ss){
  replace(str.begin(), str.end(), '|', ' ');
  ss << str;
}

void openHelp(string filename){
  ifstream fp("helps/"+filename);
  if(fp){
    string s;
    while(fp >> s)printf("%s\t", s.c_str());
    printf("\n");
  }
}

struct Player{
  string name;
  int HP, MAX_HP, ATK, DEF, SPD, EXP, GLD, SPE, LVL, STG, 
  head, body, weapon, shield, leg, spe;
  deque<int> monster_que;

  void print(){
    printf("player %s LVL:%d @%dF HP:%d/%d\n", name.c_str(), LVL, STG, HP, MAX_HP);
    printf("ATK:%d DEF:%d SPD:%d%% EXP:%d GLD:%d\n", ATK, DEF, SPD, EXP, GLD);
    if(monster_que.size() > 0){
      printf("Monster Queue : ");
      for(int x: monster_que)printf("%d ", x);
      printf("\n");
    }
  }

  bool get_data(){
    ifstream fp(P_FILE);
    if(fp){
      string s; stringstream ss;
      rep(i,3)getline(fp, s); //読み飛ばし
      getline(fp, s); mdTableReplace(s, ss);
      ss >> name
      >> HP >> MAX_HP >> ATK >> DEF >> SPD >> EXP >> GLD >> SPE >> LVL >> STG
      >> head >> body >> weapon >> shield >> leg >> spe;
      rep(i,2)getline(fp, s); //読み飛ばし
      //getline(fp, s); mdTableReplace(s, ss);
      int x;
      while(fp>>x)monster_que.push_back(x);
      return true;
    }else{
      return false;
    }
  }
};

void menu(Player &me){
  string com;
  
  while(1){
    printf("%s @%dF$ ", me.name.c_str(), me.STG);
    getline(cin, com);
    if(com == "help"){
      openHelp("menu.txt");
    }else 
    if(com == "test"){
      me.print();
    }else 
    if(com == "exit"){
      break;
    }
  }
}

int main(){
  Player me;
  if(!me.get_data()){
    printf("P_FILE OPEN ERROR!\n");
    return -1;
  }
  menu(me);
}