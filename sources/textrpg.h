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

#define COMMAND_HELP(x) (x)=="help" || (x)=="H"
#define COMMAND_EXIT(x) (x)=="exit" || (x)=="E"