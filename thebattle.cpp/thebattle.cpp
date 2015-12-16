/* compile with g++ -std=c++11 -l curses -o thebattle thebattle.cpp on linux!!*/
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#ifdef __linux__
#include <term.h>
#endif

using namespace std;

struct weapon {
    int attackscore;
    string name;
};
  struct player{
    int strength;
    int agility;
    int defence;
    weapon wep;
    string name;
    int score;
};

class legend{
    private:
       void read();
       string STRING;
       string scores[5];
       const char *filename;
    public:
        void update(int sc, string pname);
        void display();
        legend();
       
    friend void check_file_exists(legend scores);
};

void cls();
void init(player *n, player *m);
int menu();
const char* play(player *n, player *m, legend *ptr);
string pcnames[4]={"Connan the barbarian","John Rambo","Chuck Norris","Bob squarepants"};
weapon knife, axe, stick, nothing;
weapon weparr[4]={knife, axe, stick, nothing};

void legend::read() {
    int i=0;
   
    ifstream infile;
    infile.open (filename);
   
    while(getline(infile,STRING)) {// To get you all the lines.
           scores[i]=STRING;
           i++;
    }
    infile.close();
}

void legend::update(int sc, string pname) {
    for (int i=0;i<5;i++) {
        size_t b = scores[i].find(" ");
        if (b!= string::npos) {
            if(stoi(scores[i].substr(b),nullptr,0) < sc) {
                int pos = i;
                for (int i = pos; i < (5-pos); i++) {
                    string temp = scores[i+1];
                    scores[i+1] = scores[i];
                }
                scores[pos] = pname;
                scores[pos] += " ";
                string ssc = to_string(sc);
                scores[pos] += ssc;
                //cout << scores[pos] << endl;
                cout << "NEW HIGH SCORE!!! You are number " << (pos+1) << endl;
               
                ofstream nscore;
                nscore.open(filename);
                for (int i=0; i <5;i++) {
                    nscore << scores[i] << endl;
                }
                nscore.close();
                break;
            }
        }
    }
}

void legend::display(){
    for (int i=0;i<5;i++) {
        cout << scores[i] << endl;
    }
}

legend::legend(){
    filename="scores.txt";
    read();
}

void check_file_exists(legend scores){

    ifstream ifile(scores.filename);
    if (ifile) {
        scores.read();
    }else {
        cout << "no score file exists!";
    }
    ifile.close();
}

int main(int argc, char *argv[]){
    legend highscores;
    check_file_exists(highscores);
 
     player hero, pc;
     int action;
     legend *lptr;
    
     lptr = &highscores;
     weparr[0].attackscore = 5;
     weparr[1].attackscore = 8;
     weparr[2].attackscore = 1;
     weparr[3].attackscore = 0;
     weparr[0].name = "kitchen knife";
     weparr[1].name = "kickass double axe";
     weparr[2].name = "a small stick";
     weparr[3].name = "bare hands";
   
    //check for username
    if (argc == 1){
        cout << "enter hero's name" << endl;
        cin >> hero.name;
    }else {
        hero.name = argv[1];
    }
  
    //clear screen
    cls();
  
    //init players
    init(&pc, &hero);


    //show main screen incl. menu
    cout << endl;
    cout << "    ¦¦¦        _¦    ¦_       _¦¦¦¦¦¦¦¦      ¯¦¦¦¦¦¦¦¦¦_     _¦¦¦¦¦¦¦¦     ¦¦¦         ¦¦¦      _¦          _¦¦¦¦¦¦¦¦ " << endl;
    cout << "¯¦¦¦¦¦¦¦¦¦_   ¦¦¦    ¦¦¦     ¦¦¦    ¦¦¦        ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦ ¯¦¦¦¦¦¦¦¦¦_ ¯¦¦¦¦¦¦¦¦¦_ ¦¦¦         ¦¦¦    ¦¦¦ " << endl;
    cout << "   ¯¦¦¦¯¯¦¦   ¦¦¦    ¦¦¦     ¦¦¦    ¦¯         ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦    ¯¦¦¦¯¯¦¦    ¯¦¦¦¯¯¦¦ ¦¦¦         ¦¦¦    ¦¯  " << endl;
    cout << "    ¦¦¦   ¯  _¦¦¦____¦¦¦__  _¦¦¦___           _¦¦¦___¦¦¯    ¦¦¦    ¦¦¦     ¦¦¦   ¯     ¦¦¦   ¯ ¦¦¦        _¦¦¦___     " << endl;
    cout << "    ¦¦¦     ¯¯¦¦¦¯¯¯¯¦¦¦¯  ¯¯¦¦¦¯¯¯          ¯¯¦¦¦¯¯¯¦¦_  ¯¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦         ¦¦¦     ¦¦¦       ¯¯¦¦¦¯¯¯     " << endl;
    cout << "    ¦¦¦       ¦¦¦    ¦¦¦     ¦¦¦    ¦_         ¦¦¦    ¦¦_   ¦¦¦    ¦¦¦     ¦¦¦         ¦¦¦     ¦¦¦         ¦¦¦    ¦_  " << endl;
    cout << "    ¦¦¦       ¦¦¦    ¦¦¦     ¦¦¦    ¦¦¦        ¦¦¦    ¦¦¦   ¦¦¦    ¦¦¦     ¦¦¦         ¦¦¦     ¦¦¦¦    _   ¦¦¦    ¦¦¦ " << endl;
    cout << "   _¦¦¦¦¯     ¦¦¦    ¦¯      ¦¦¦¦¦¦¦¦¦¦      _¦¦¦¦¦¦¦¦¦¯    ¦¦¦    ¦¯     _¦¦¦¦¯      _¦¦¦¦¯   ¦¦¦¦¦__¦¦   ¦¦¦¦¦¦¦¦¦¦ " << endl;
    cout << endl << "Welcome " << hero.name << endl;
    cout << "are you ready to DIE??" << endl << endl;
   
   
    action = menu();
     if (action == 1){
        play(&pc, &hero, lptr);
    }else if (action == 2){
        highscores.display();
    }else if (action == 3){
        return 0;
    }

}

void init(player *n, player *m){
     /* initialize random seed: */
    srand (time(NULL));

    n->name = pcnames[rand() % 3];
    n->strength = rand() % 10;
    n->agility = rand() % 10;
    n->defence = rand() % 10;
    n->wep = weparr[rand() % 3];

    srand (time(NULL));

    m->strength = rand() % 10;
    m->agility = rand() % 10;
    m->defence = rand() % 10;
    m->wep = weparr[rand() % 3];

}

int menu(){
    int option;
    cout << "GAME MENU" << endl;
    cout << "===============" << endl;
    cout << "1) PLAY"<< endl;
    cout << "2) LEGEND"<< endl;
    cout << "3) EXIT"<< endl;
    cout << "select an option" << endl;

    do {
        cin >> option;
        switch (option){
        case 1 :
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        default :
            cout << "select a valid option!" << endl;
        }
    }while (option != 3);
    cout << "you are a C-O-W-A-R-D" << endl;
    return 0;
}

const char* play(player *pc, player *hero,legend *lptr){
    int sump, sumh;
    sump= (pc->agility+pc->strength+pc->defence)*pc->wep.attackscore;
    sumh= (hero->agility+hero->strength+hero->defence)*hero->wep.attackscore;
    cout << "You are attacking with " << hero->wep.name << endl;
    sleep(2);
    cout << pc->name << " attacks with " << pc->wep.name << endl;
    sleep(2);
    cout << "Your score " << sumh <<endl;
    cout << pc->name << "'s score " << sump << endl;
    if (sump > sumh){
        cout << "LOOOOOOOOOSER HO-HO-HO!" << endl;
    }else if(sump==sumh){
        cout << "IT'S A TIE (boring...)" << endl;
    }else {
        cout << "YOU ARE THE WINNER!!!!!!(unexpectable!)" << endl;    
    }
    lptr->update(sumh,hero->name);

    return "the end";
}


#ifdef __linux__
void cls() {
  if (!cur_term) {
    int result;
    setupterm( NULL, STDOUT_FILENO, &result );
    if (result <= 0) return;
  }

  putp( tigetstr( "clear" ) );
}

#else
void cls() {
    cout << string( 100, '\n' );
}
#endif

