#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility> //pair
#include <deque>
#include <random>
#include <stdexcept>

using namespace std;

#define MY_DEBUG

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

string weapon_type[7] = {"none", "head", "body", "weapon", "shield", "leg", "special"};
struct Weapon{
  int type; string name;
  int dHP, dATK, dDEF, dSPD;
  pair<int, int> special_effect;

  //デフォルトコンストラクタ
  Weapon(): type(0), name("Null"), dHP(0), 
  dATK(0), dDEF(0), dSPD(0) , special_effect(0,0) {};

  Weapon(string n): type(0), name(n), dHP(0), 
  dATK(0), dDEF(0), dSPD(0) , special_effect(0,0) {};
  //全値設定用コンストラクタ
  Weapon(int _type, string _name, int dhp, int datk, int ddef, int dspd, pair<int,int> se):
  type(_type), name(_name), dHP(dhp), dATK(datk), dDEF(ddef), dSPD(dspd),special_effect(se){};

  void info(){
    printf("%s \"%s\" dHP:%d dATK:%d dDEF:%d dSPD:%d ",
    weapon_type[type].c_str(), name.c_str(), dHP, dATK, dDEF, dSPD);
    printf("effect %d:%d%%\n", special_effect.first, special_effect.second);
  }

  void info_short(){
    printf("%s\t\"%s\"\n", weapon_type[type].c_str(), name.c_str());
  }
};

Weapon get_weapon(int n){
  Weapon rtn;
  
  ifstream ifs(W_FILE);
  if(ifs){
    int i = 0;
    int t,h,a,d,s,s1,s2;string nm;
    string line;stringstream ss;

    rep(i,2)getline(ifs,line);
    while(getline(ifs,line)){
      if(i==n){
        mdTableReplace(line,ss);
        ss>>t>>nm>>h>>a>>d>>s>>s1>>s2;
        rtn = {t,nm,h,a,d,s,pair(s1,s2)};
        //rtn.info();
        break;
      }
      i++;
    }
  }else{
    rtn = Weapon("error");
  }
  
  return rtn;
}

struct Player{
  string name;
  int HP, MAX_HP, ATK, DEF, SPD, EXP, GLD, LVL, STG, 
  head, body, weapon, shield, leg, spe;
  deque<int> monster_que;

  void info(){
    printf("player \"%s\" LVL:%d @%dF ", name.c_str(), LVL, STG);
    printf("EXP:%d GLD:%d\n", EXP, GLD);
    printf("HP:%d/%d ATK:%d DEF:%d SPD:%d%%\n", HP, MAX_HP, ATK, DEF, SPD);
    printf("WEAPONS\n");
    printf("vvvvvvvvvv\n");
    get_weapon(head).info_short();
    get_weapon(body).info_short();
    get_weapon(weapon).info_short();
    get_weapon(shield).info_short();
    get_weapon(leg).info_short();
    get_weapon(spe).info_short();
    printf("^^^^^^^^^^\n");

    #ifdef MY_DEBUG
    printf("Monster Queue : ");
    if(monster_que.size() > 0){
      for(int x: monster_que)printf("%d ", x);
      printf("\n");
    }else{
      printf("none\n");
    }
    #endif

    string com;
    while(1){
      printf("info$ ");
      getline(cin, com);

      if(com == "help"){
        openHelp("info.txt");
      }else
      if(com.substr(0,2) == "wd"){
        try{
          switch(stoi(com.substr(2))){
            case 0: get_weapon(head).info(); break;
            case 1: get_weapon(body).info(); break;
            case 2: get_weapon(weapon).info(); break;
            case 3: get_weapon(shield).info(); break;
            case 4: get_weapon(leg).info(); break;
            case 5: get_weapon(spe).info(); break;
            default: throw -1;
          }
        }
        catch(...){
          printf("no such item\n");
        }
      }else
      if(com == "exit"){
        break;
      }
    }
  }

  bool get_data(){
    ifstream fp(P_FILE);
    if(fp){
      string s; stringstream ss;
      
      //データ
      rep(i,3)getline(fp, s); //読み飛ばし
      getline(fp, s); mdTableReplace(s, ss);
      ss >> name
      >> HP >> MAX_HP >> ATK >> DEF >> SPD >> EXP >> GLD >> LVL >> STG
      >> head >> body >> weapon >> shield >> leg >> spe;

      //戦闘キュー
      rep(i,2)getline(fp, s); //読み飛ばし
      int x;
      while(fp>>x)monster_que.push_back(x);
      return true;
    }else{
      return false;
    }
  }

  bool save_data(){
    ofstream fp(P_FILE);
    if(fp){

      return true;
    }else{
      return false;
    }
  }
};

int main(){
  Player me;
  if(!me.get_data()){
    printf("P_FILE OPEN ERROR!\n");
    return -1;
  }
  
  //menu loop
  string com;
  while(1){
    printf("%s %dF$ ", me.name.c_str(), me.STG);
    getline(cin, com);
    if(com == "help"){
      openHelp("menu.txt");
    }else 
    if(com == "info"){
      me.info();
    }else 
    if(com == "exit"){
      break;
    }
  }

}