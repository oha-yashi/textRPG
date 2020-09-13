#include "textrpg.h"

void mdTableReplace(string &str, stringstream &ss){
  replace(str.begin(), str.end(), '|', ' ');
  ss << str;
}

template<class F> void mdPush(stringstream &ss, F &&f){ss << "| " << f << " |" << endl;}
template<class F, class ...S> void mdPush(stringstream &ss, F &&f, S &&...s){ss << "| " << f << " "; mdPush(ss, forward<S>(s)...);}
template<class ...P> string mdString(P &...p){
  stringstream ss; mdPush(ss, p...); return ss.str();
}
string mdLine(int n){
  string str("|");
  rep(i,n)str += " -- |";
  return str;
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
  Weapon(): type(0), name("Null"), dHP(0), dATK(0), dDEF(0), dSPD(0) , special_effect(0,0) {};
  Weapon(string n): type(0), name(n), dHP(0), dATK(0), dDEF(0), dSPD(0) , special_effect(0,0) {};
  //全値設定用コンストラクタ
  Weapon(int _type, string _name, int dhp, int datk, int ddef, int dspd, pair<int,int> se):
  type(_type), name(_name), dHP(dhp), dATK(datk), dDEF(ddef), dSPD(dspd),special_effect(se){};

  void info(){
    printf("%-6s \"%-s\"\tdHP:%d dATK:%d dDEF:%d dSPD:%d ",
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
  string name; int LVL, EXP, GLD, STG, PROG;
  int HP, MAX_HP, ATK, DEF, SPD;
  int head, body, weapon, shield, leg, spe;

  void info(){
    printf("player \"%s\" LVL:%d @%dF_%d%% ", name.c_str(), LVL, STG, PROG);
    printf("EXP:%d GLD:%d\n", EXP, GLD);
    printf("HP:%d/%d ATK:%d DEF:%d SPD:%d\n", HP, MAX_HP, ATK, DEF, SPD);
    printf("WEAPONS\n");
    printf("vvvvvvvvvv\n");
    printf("1: "); get_weapon(head).info();
    printf("2: "); get_weapon(body).info();
    printf("3: "); get_weapon(weapon).info();
    printf("4: "); get_weapon(shield).info();
    printf("5: "); get_weapon(leg).info();
    printf("6: "); get_weapon(spe).info();
    printf("^^^^^^^^^^\n");

    string com;
    while(1){
      printf("info$ ");
      getline(cin, com);

      if(COMMAND_HELP(com)){
        openHelp("info.txt");
      }else
      /*
      if(com.substr(0,2) == "wd"){
        try{
          switch(stoi(com.substr(2))){
            case 1: get_weapon(head).info(); break;
            case 2: get_weapon(body).info(); break;
            case 3: get_weapon(weapon).info(); break;
            case 4: get_weapon(shield).info(); break;
            case 5: get_weapon(leg).info(); break;
            case 6: get_weapon(spe).info(); break;
            default: throw -1;
          }
        }
        catch(...){
          printf("no such item\n");
        }
      }else
      //*/
      if(COMMAND_EXIT(com)){
        break;
      }
    }
  }

  bool get_data(){
    ifstream fp(P_FILE);
    if(fp){
      string s; stringstream ss;
      
      //データ
      rep(i,4)getline(fp, s); //読み飛ばし3行 + 読み込み1行
      mdTableReplace(s, ss);
      ss >> name >> LVL >> EXP >> GLD >> STG >> PROG;

      rep(i,5)getline(fp, s); mdTableReplace(s, ss);
      ss >> HP >> MAX_HP >> ATK >> DEF >> SPD;

      rep(i,5)getline(fp, s); mdTableReplace(s, ss);
      ss >> head >> body >> weapon >> shield >> leg >> spe;

      return true;
    }else{
      return false;
    }
  }

  void save_data(){
    ofstream fp(P_FILE);
    if(fp){
      fp << "## 基本データ\n";
      fp << "| name | LVL | EXP | GLD | STG | PROG |\n";
      fp << mdLine(6);
      fp << mdString(name, LVL, EXP, GLD, STG, PROG);

      fp << "\n## 戦闘データ\n";
      fp << "| HP  | MAX_HP | ATK | DEF | SPD |\n";
      fp << mdLine(5);
      fp << mdString(HP, MAX_HP, ATK, DEF, SPD);

      fp << "\n## 武器データ\n";
      fp << "| head | body | weapon | shield | leg | spe |\n";
      fp << mdLine(6);
      fp << mdString(head, body, weapon, shield, leg, spe);

      printf("success to save!\n");
    }else{
      printf("fale to save!\n");
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
    if(COMMAND_HELP(com)){
      openHelp("menu.txt");
    }else 
    if(com == "info"){
      me.info();
    }else
    if(com == "save"){
      me.save_data();
    }else
    if(COMMAND_EXIT(com)){
      break;
    }
  }

}