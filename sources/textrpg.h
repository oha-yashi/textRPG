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

#define CL_RS "\e[0m"  //reset
#define CL_BK "\e[30m" //black
#define CL_RD "\e[31m" //red
#define CL_GR "\e[32m" //green
#define CL_YL "\e[33m" //yellow
#define CL_BL "\e[34m" //blue
#define CL_MG "\e[35m" //magenta
#define CL_CY "\e[36m" //cyan
#define CL_WH "\e[37m" //white

#define rep(i,n) for(int i=0; i<(int)n; i++)

#define COMMAND_HELP(x) (x)=="help" || (x)=="H"
#define COMMAND_EXIT(x) (x)=="exit" || (x)=="E"