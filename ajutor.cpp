#include <iostream>
using namespace std;

void ultimaOara(int indice){
    static int reti;
    cerr <<reti << " reti\n";
    cerr <<indice << " indice\n\n";
    reti=indice;
}
void ultimaOara2(int indice){
    static int reti;
    cerr <<reti << " reti\n";
    cerr <<indice << " indice\n\n";
    reti=indice;
}
int main(){
    for(int i=1;i<=3;i++)
        for(int j=25; j<=27;j++){
            ultimaOara(i);
            ultimaOara2(j);
            cerr << "\nAAAAAAAAAAAAAAAAAAAAAAAA\n";
        }
    return 0;
}