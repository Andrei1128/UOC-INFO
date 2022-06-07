#include <iostream>
#include <stack>
#include <vector>
#include <ctime>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
using namespace std;

/*     9.Joc de carti cu implementare STL
        Timp prezentare: 10 minute
        Descriere: Realizarea unei aplicatii in care se va rezolva problema utilizand o stiva in implementarea STL.
*/

stack<struct carte>pachetCarti;
stack<struct carte>restCarti;
vector<stack<struct carte>>_7stive;
vector<stack<struct carte>>_4stive;

HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

struct carte{
    int numar;
    char forma;
    int show;
};
char creezForma(int x){
    if(x==1) return 'R';
    if(x==2) return 'N';
    if(x==3) return 'T';
    if(x==4) return 'C';
    return x;
}
void creezPachet(){
    struct carte c;
    int m,n;
    for(m=1;m<=13;m++)
        for(n=1;n<=4;n++){
                c.numar=m;
                c.forma=creezForma(n);
                c.show=1;
                pachetCarti.push(c);
            }
}
void schimb(stack<struct carte>&stack1,stack<struct carte>&stack2){
    while(!stack1.empty()){
            stack2.push(stack1.top());
            stack1.pop();
        }
}
void culoare(struct carte a){
    if(a.forma=='R'||a.forma=='C')
        SetConsoleTextAttribute(color, 4);
    if(a.forma=='T'||a.forma=='N')
        SetConsoleTextAttribute(color, 1);
}
void afisezNumar(struct carte a){
    if(a.numar==1)
        wcout<<" A";
    else if(a.numar==11)
        wcout<<" J";
    else if(a.numar==12)
        wcout<<" Q";
    else if(a.numar==13)
        wcout<<" K";
    else wcout<<" "<<a.numar;
}
void unicode(char c)
{
    if(c=='R') wcout<<L"\u2665";
    else if(c=='N') wcout<<L"\u2660";
    else if(c=='T') wcout<<L"\u2663";
    else if(c=='C') wcout<<L"\u2666";
}
void afisez(){
    stack<struct carte>aux;
    stack<struct carte>deAfisat;
    int i;
    system("CLS");
    wcout<<endl;
    SetConsoleTextAttribute(color, 8);
    wcout<<"   0 >";
    SetConsoleTextAttribute(color, 7);
    if(pachetCarti.size()>2) wcout<<"  /// ";
    else if(pachetCarti.size()==2) wcout<<"  // ";
    else if(pachetCarti.size()==1) wcout<<"  / ";
    else wcout<<"  - ";
    if(!restCarti.empty()){
        afisezNumar(restCarti.top());
        culoare(restCarti.top());
        unicode(restCarti.top().forma);
    }
    else wcout<<" -";
    wcout<<"\t\t\t";
    for(i=0;i<4;i++){
        if(!_4stive[i].empty()){
            SetConsoleTextAttribute(color, 8);
            wcout<<i+8<<" >";
            SetConsoleTextAttribute(color, 7);
            afisezNumar(_4stive[i].top());
            culoare(_4stive[i].top());
            unicode(_4stive[i].top().forma);
            wcout<<"   ";
        }
        else {
            SetConsoleTextAttribute(color, 8);
            wcout<<i+8<<" >";
             SetConsoleTextAttribute(color, 7);
            wcout<<" -   ";
        }
    }
    wcout<<endl<<endl;
    for(i=0;i<7;i++){
        if(!_7stive[i].empty())
            _7stive[i].top().show=1;
        aux=_7stive[i];
        schimb(aux,deAfisat);
        SetConsoleTextAttribute(color, 8);
        wcout<<"   "<<i+1<<"  ";
        SetConsoleTextAttribute(color, 7);
        while(!deAfisat.empty()){
            if(deAfisat.top().show==1){
            afisezNumar(deAfisat.top());
            culoare(deAfisat.top());
            unicode(deAfisat.top().forma);
            wcout<<' ';
            SetConsoleTextAttribute(color, 7);
            }
            else wcout<<" / ";
            deAfisat.pop();
        }
        wcout<<endl;
    }
}
void creezStivaDe7siDe4(){
    int i;
    stack<struct carte>stk;
    for(i=0;i<7;i++)
        _7stive.push_back(stk);
    for(i=0;i<4;i++)
        _4stive.push_back(stk);
}
void amestecPachet(){
    int i;
    while(!pachetCarti.empty()){
        i=(rand()%100)%7;
        _7stive[i].push(pachetCarti.top());
        pachetCarti.pop();
    }
    for(i=0;i<7;i++)
        while(!_7stive[i].empty()){
            pachetCarti.push(_7stive[i].top());
            _7stive[i].pop();
        }
}
void impartCartileInStive(){
    for(int i=0;i<7;i++)
        for(int y=0;y<i+1;y++){
            _7stive[i].push(pachetCarti.top());
            pachetCarti.pop();
            _7stive[i].top().show=0;
        }
}
void verificare0(stack<struct carte>&stiva1,stack<struct carte>&stiva2){
    int ok=0;
    if(!stiva1.empty()&&!stiva2.empty())
        if(stiva1.top().numar+1==stiva2.top().numar)
            if((stiva1.top().forma=='R'||stiva1.top().forma=='C')&&(stiva2.top().forma=='N'||stiva2.top().forma=='T')) ok=1;
            else if((stiva1.top().forma=='N'||stiva1.top().forma=='T')&&(stiva2.top().forma=='R'||stiva2.top().forma=='C')) ok=1;
    if(ok==1){
        stiva2.push(stiva1.top());
        stiva1.pop();
    }
   else if(stiva2.empty()){
        if(stiva1.top().numar==13){
            stiva2.push(stiva1.top());
            stiva1.pop();
        }
    }
}
void verificare1(stack<struct carte>&stiva1,stack<struct carte>&stiva2){
    int ok=0;
    if(!stiva1.empty())
        if(stiva1.top().numar==1&&stiva2.empty()) ok=1;
        else if(!stiva2.empty()&&stiva1.top().numar-1==stiva2.top().numar)
            if(stiva1.top().forma==stiva2.top().forma) ok=1;
    if(ok==1){
        stiva2.push(stiva1.top());
        stiva1.pop();
    }
}
void verificare2(int nr,stack<struct carte>&stiva1,stack<struct carte>&stiva2){
    int auxnr=nr,ok,k=0;
    stack<struct carte>aux=stiva1;
    struct carte c;
    while(auxnr>0){
        ok=0;
        if(auxnr!=1){
                c=aux.top();
                aux.pop();
                    if(aux.top().numar==c.numar+1)
                        if((aux.top().forma=='R'||aux.top().forma=='C')&&(c.forma=='N'||c.forma=='T')) ok=1;
                        else if((aux.top().forma=='N'||aux.top().forma=='T')&&(c.forma=='R'||c.forma=='C')) ok=1;
                if(ok==0) return;
                auxnr--;
        }
        else{
                if(stiva2.empty()&&aux.top().numar==13) {
                    auxnr--;
                }
                else {
                if(aux.top().numar+1==stiva2.top().numar)
                    if((aux.top().forma=='R'||aux.top().forma=='C')&&(stiva2.top().forma=='N'||stiva2.top().forma=='T')) ok=1;
                    else if((aux.top().forma=='N'||aux.top().forma=='T')&&(stiva2.top().forma=='R'||stiva2.top().forma=='C')) ok=1;
                if(ok==0) return;
                auxnr--;
            }
        }
    }
    while(!aux.empty())
        aux.pop();
    auxnr=nr;
    while(auxnr>0){
        aux.push(stiva1.top());
        stiva1.pop();
        auxnr--;
    }
    while(nr>0){
        stiva2.push(aux.top());
        aux.pop();
        nr--;
    }
}
void mutare(int r1,int nr,int r2){
    if(r1==0){
        if(nr==1){
                if(r2==0){
                    if(!pachetCarti.empty()){
                        restCarti.push(pachetCarti.top());
                        pachetCarti.pop();
                    }
                    else{
                        schimb(restCarti,pachetCarti);
                    }
                }
                else if(r2>=1&&r2<=7){
                    verificare0(restCarti,_7stive[r2-1]);
                }
                else if(r2>=8&&r2<=11){
                    verificare1(restCarti,_4stive[r2-8]);
                }
        }
    } else if(r1>=1&&r1<=7){
        if(nr==1){
            if(r2>=1&&r2<=7){
                verificare0(_7stive[r1-1],_7stive[r2-1]);
            }
            else if(r2>=8&&r2<=11){
                verificare1(_7stive[r1-1],_4stive[r2-8]);
            }
        }
        else if(nr>1&&nr<=_7stive[r1-1].size()){
            if(r2>=1&&r2<=7){
                verificare2(nr,_7stive[r1-1],_7stive[r2-1]);
            }
        }
    }
}
void stergStive(){
    while(!pachetCarti.empty())
        pachetCarti.pop();
    while(!restCarti.empty())
        restCarti.pop();
    _4stive.clear();
    _7stive.clear();
}
void finish(){
        system("CLS");
        wcout<<"\n\n\t\t\t        Ai castigat!\n\n\t\tApasa orice tasta pentru a incepe un joc nou.\n\n\t\t       ";
        system("PAUSE");
}
void info(){
    wcout<<" __________________________________________\n\n";
    wcout<<"  R1 -> Randul din care mutam.\n  Nr -> Numarul de carti pe care il mutam.\n  R2 -> Randul in care mutam.\n\n";
    wcout<<"  -1 0 0 -> Pentru a inchide.\n  -2 0 0 -> Pentru a incepe un joc nou.\n\n";
}
int val(){
    string x;
    int y;
    cin >> x;
     try{
        y = stoi(x);
  }
   catch (const std::invalid_argument & e){
        return -3;
  }
    return y;
}
int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    int r1,nr,r2;
    eticheta1:
    creezPachet();
    creezStivaDe7siDe4();
    srand((unsigned) time(0));
    for (int i=0;i<(rand()%5)+5;i++)
            amestecPachet();
    impartCartileInStive();
    r1=0;
    while(r1!=-1){
    afisez();
    info();
    wcout<<" R1: "; r1 = val();
    wcout<<" Nr: "; nr = val();
    wcout<<" R2: "; r2 = val();
    mutare(r1,nr,r2);
    if(_4stive[0].size()==13&&_4stive[1].size()==13&&_4stive[2].size()==13&&_4stive[3].size()==13){
            finish();
            r1=-2;
        }
    if(r1==-2){
            stergStive();
            goto eticheta1;
        }
    }
    return 0;
}
