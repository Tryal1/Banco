#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
void info(){
    int opc;
    while(opc!=4){
        system("cls");
        cout<<(char)201;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)187;
        cout<<endl;
        cout<<(char)186;
        cout<<"1. Listar Todos los Usuario                ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"2. Listar Todas las Cuentas                "; cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"3. Buscar Usuario y sus cuentas            ";cout<<(char)186<<endl;
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
                TodosLosUsuario();
                break;
            case 2:
                TodasLasCuentas();
                break;
            case 3:
                BuscarUsuarioConCuentas();
                break;
            default:
                break;

        }
    }

}

void movimientos(int dni, const char *val){
    Cuentas cu;
    int opc;
    int pos=0,cont=0;
    if(verifcuenta(dni) == true){
    while(cu.leerDisco(pos++)){
    if(strcmp(val,cu.getTipo())==0){
        cont = 1;
        MostrarCuenta(dni,val);
        while(opc!=5){
        system("cls");
        cout<<(char)201;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)187;
        cout<<endl;
        cout<<(char)186;
        cout<<"1. Depositar                               ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"2. Retirar                                 "; cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"3. Transferir                              ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"4. Eliminar                                "; cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"5. Salir                                   ";cout<<(char)186<<endl;
        cout<<(char)200;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)188;
        cout<<endl;
        cin>>opc;
        system("cls");

        switch(opc){
            case 1:
                deposito(dni,val);
                break;
            case 2:
                retirar(dni,val);
                break;
            case 3:
                transferencia(dni,val);
                break;
            case 4:
                eliminarCuenta(dni,val);
                opc = 5;
                break;
            default:
                break;

        }
    }
    }

    }
    }
    if(cont == 0)cout<<"No pose una "<<val<<endl; getch();
}

void cuenta(int dni){
    int opc;
        while(opc!=5){
        system("cls");
        cout<<(char)201;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)187;
        cout<<endl;
        cout<<(char)186;
        cout<<"1. Crear cuenta                            ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"2. Acceder a la Caja de ahorro             "; cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"3. Acceder a la Cuenta corriente           "; cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"4. Movimientos de la cuenta                ";cout<<(char)186<<endl;
        cout<<(char)186;
        cout<<"5. Salir                                   ";cout<<(char)186<<endl;
        cout<<(char)200;
        for(int i=1; i<=43; i++)cout<<(char)205;
        cout<<(char)188;
        cout<<endl;
        cin>>opc;
        system("cls");

        switch(opc){
            case 1:
                cargarcuenta(dni);
                break;
            case 2:
                 movimientos(dni,"Caja de Ahorro");
                break;
            case 3:
                movimientos(dni,"Cuenta corriente");
                break;
            case 4:
                mostrarMov(dni);
                break;
            default:
                break;

        }
    }
}
#endif // MENUS_H_INCLUDED
