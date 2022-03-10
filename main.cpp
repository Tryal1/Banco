#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>

using namespace std;
#include "definicion.h"
#include "function.h"
#include "class.h"
#include "cuentas.h"
#include "menus.h"
#include "movimiento.h"


int main(){
    int opc=0;
    while(opc!=4){
        system("cls");
        cout<<(char)201;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)187;
        cout<<endl;
        cout<<(char)186;
        cout<<"1. Crear Cuenta de usuario                 ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"2. Ingresar a la cuenta                    "; cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"3. Informacion sobre cuentas               ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"4. Salir                                   ";cout<<(char)186<<endl;
        cout<<(char)200;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)188;
        cout<<endl;
        cin>>opc;
        system("cls");

        switch(opc){
            case 1:
                cargarusuario();
                break;
            case 2:
                ACcuentas();
                break;
            case 3:
                info();
                break;
            case 4:
                return 0;
                break;

        }
    }
    return 0;
}
