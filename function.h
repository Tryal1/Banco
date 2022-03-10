#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include "class.h"
#include "cuentas.h"
#include "menus.h"
#include "movimiento.h"
///Usuario
void cargarusuario(){
    Usuario ob;
    int dni;
    char correcto;
    while(true){
        cout<<"Ingrese Su Dni: ";
        cin>>dni;
        cout<<endl;
        if(verifUsuario(dni)==true){
            cout<<"Ya hay una cuenta registrada a este DNI"<<endl;
            getch();
        }else if(verifUsuario(dni)==false){
            system("cls");
            ob.cargar(dni);
            system("cls");
            ob.mostrar();
            cout<<endl;
            cout<<"Las datos son correctos? s/n: ";
            cin>>correcto;
        }
        if(correcto=='s'||correcto=='S'){
            ob.grabarEnDisco();
            cout<<"Usuario creado con exito"<<endl;
            getch();
            break;
        }
    }

}

void MostrarUsuario(){
    Usuario ob;
    int tok,dni;
    int cont=0,pos=0;
    cout<<"Ingrese su DNI y token para ver su cuenta"<<endl;
    cout<<"DNI: ";
    cin>>dni;
    cout<<"TOKEN: ";
    cin>>tok;

    while(ob.leerDisco(pos++)){
    if(tok == ob.getTOKEN()&&dni==ob.getDNI()&&cont==0){
    ob.mostrar();
    getch();
    cont++;
    cout<<endl;
    }
    }
    if(cont==0){
        cout<<"DNI o Token invalido";
    }
}

void buscarusuario(int cbu, const char *alias){
    Usuario ob;
    Cuentas cu;
    int pos=0,poss=0,dni;
    while(cu.leerDisco(pos++)){
        if(cbu==cu.getCBU()||strcmp(alias,cu.getAlias())==0){
            dni=cu.getDNI();
        }
    }
    while(ob.leerDisco(poss++)){
        if(dni==ob.getDNI()){
            cout<<"Nombre: "<<ob.getnombre_usuario()<<endl;
            cout<<"DNI: "<<ob.getDNI()<<endl;
        }
    }
}

void cambiarToken(){
    Usuario ob;
    char nombre[20];

    FILE *p=fopen("Usuario.dat","r+b");
    if(p==NULL){
        cout<<"No se pudo leer"<<endl;
        return;
    }

    cout<<"Dijite su nombre: ";
    fflush(stdin);
    cin.getline(nombre,20,'\n');

    while(!feof(p)){
        fread(&ob,sizeof(ob),1,p);
        if(strcmp(nombre,ob.getNombre())==0){
            cout<<"Dijite su nuevo token: ";
            ob.setTOKEN(validartoken());

            int pos=ftell(p)-sizeof(ob);
            fseek(p,pos,SEEK_SET);
            fwrite(&ob,sizeof(ob),1,p);
            break;
        }
    }
    fclose(p);
}

///Cuent

void cargarcuenta(int dni){
    Cuentas cu;
    int tipo=0;
    char val[20];

    while(tipo!=3){
    system("cls");
    cout<<"1. Caja de ahorro, 2. Cuenta corriente, 3.Salir: ";
    cin>>tipo;
     if(tipo==1){
        strcpy(val,"Caja de Ahorro");
    }
    else if(tipo==2){
        strcpy(val,"Cuenta corriente");
    }
    else if(tipo==3){
        break;
    }
    if(verifTipoDeCuenta(val,dni)==true){
        cout<<"Usted ya tiene una "<<val<<endl;
        getch();
    }
     else{
        cu.setTipo(val);
        cu.setDni(dni);
        cu.cargar();
        cu.grabarEnDisco();
        system("cls");
        cout<<"Cuenta creada con exito";
        getch();
        break;
    }
    }
}

void MostrarCuenta(int dni, const char *valtipo){
    Cuentas cu;
    int pos=0;
    while(cu.leerDisco(pos++)){
    if(dni==cu.getDNI()&&strcmp(valtipo,cu.getTipo())==0){
    cu.mostrar();
    getch();
    cout<<endl;
    }
}
}

void ACcuentas(){
    Usuario ob;
    char cambio;
    int dni,cont=0;
    char usua[20];
    int tok;
    FILE *p=fopen("Usuario.dat","rb");
    if(p==NULL){
    cout<<"No se pudo leer"<<endl;
    return;
    }

    while(cont == 0){
    cout<<"Digite su Nombre de usuario y token para ingresar"<<endl;
    cout<<"Nombre de usuario: ";
    fflush(stdin);
    cin.getline(usua,20,'\n');
    cout<<"Token: ";
    cin>>tok;
    while(!feof(p)){
    fread(&ob, sizeof ob, 1, p);
    if(tok == ob.getTOKEN()&&strcmp(usua,ob.getnombre_usuario())==0){
    dni=ob.getDNI();
    cuenta(dni);
    cont = 1;
    }
    }
    if(cont==0){
        cout<<"El nombre de usuario o token es invalido"<<endl;
        cout<<"Desea cambiar su Token? s/n: ";
        cin>>cambio;
        if(cambio == 's'|| cambio == 'S'){
            cambiarToken();
        }
    }
    break;
    }

    fclose(p);
}

int cbualeatorio(){
    int dato;
    srand(time(NULL));
    dato=1+rand()%(32767);

    return dato;
}

///Transacciones y acciones de cuenta

void deposito(int dni, const char *valtipo){
    Cuentas cu;
    float val,importe;
    int tipo=1;
    FILE *p=fopen("Cuenta.dat","r+b");
    if(p==NULL){
        cout<<"No se pudo leer"<<endl;
        return;
    }
    while(!feof(p)){
            fread(&cu,sizeof(cu),1,p);
            if(dni==cu.getDNI()&&strcmp(valtipo,cu.getTipo())==0){
            cout<<"Valance en la cuenta actualmente: "<<cu.getSALDO();
            cout<<endl;
            cout<<"Cuanto quiere Depositar: ";
            cin>>val;
            if(cu.getSaldo_descubierto()<0){
                cout<<"Debe "<<cu.getSaldo_descubierto()*(-1)<<" Deposite lo que debe antes de proseguir: "<<endl;
                cin>>val;
                importe=val;
                while(true){
                if(val<=cu.getSaldo_descubierto()*(-1)){
                    val=cu.getSaldo_descubierto()+val;
                    cu.setSaldo_descubierto(val);
                    break;
                }
                else{cout<<"Monto exede"<<endl;}
                }

            }
            else{importe=val;val=cu.getSALDO()+val;cu.setSALDO(val);}
            cargarMov(dni,cu.getCBU(),tipo,importe,valtipo);
            cout<<"Nuevo valance: "<<cu.getSALDO();
            cout<<endl;
            getch();
            int pos=ftell(p)-sizeof(cu);
            fseek(p,pos,SEEK_SET);
            fwrite(&cu,sizeof(cu),1,p);
            break;
            }
    }
    fclose(p);
}

void retirar(int dni, const char *valtipo){
    Cuentas cu;
    float val,importe;
    char giro;
    int tipo=2;
    FILE *p=fopen("Cuenta.dat","r+b");
    if(p==NULL){
        cout<<"No se pudo leer"<<endl;
        return;
    }
     while(!feof(p)){
            fread(&cu,sizeof(cu),1,p);
            if(dni==cu.getDNI()&&strcmp(valtipo,cu.getTipo())==0){
            cout<<"Valance en la cuenta actualmente: "<<cu.getSALDO();
            cout<<endl;
            while(true){
            cout<<"Cuanto quiere retirar: ";
            cin>>val;
            if(val<=cu.getSALDO()){
                    importe=val;
                    val=cu.getSALDO()-val;
                    cu.setSALDO(val);
                    break;
                }else  cout<<"No pose suficientes fondos"<<endl;
            if(val>=cu.getSALDO()&&strcmp(valtipo,"Cuenta corriente")==0){
                    cout<<"Quiere girar al descubiero? s/n: ";
                    cin>>giro;
                    if(giro=='S'||giro=='s'){
                        cout<<"Cuanto quiere retirar: ";
                        cin>>val;
                        val=cu.getSaldo_descubierto()-val;
                        cu.setSaldo_descubierto(val);
                        break;
                    }else{break;}
                }
            }
            cargarMov(dni,cu.getCBU(),tipo,importe,valtipo);
            cout<<"Nuevo valance: "<<cu.getSALDO()<<endl;
            cout<<"Plata que debe: "<<cu.getSaldo_descubierto()*(-1)<<endl;
            cout<<endl;
            getch();
            int pos=ftell(p)-sizeof(cu);
            fseek(p,pos,SEEK_SET);
            fwrite(&cu,sizeof(cu),1,p);
            break;
            }
    }
    fclose(p);
}

void transferencia(int dni, const char *valtipo){
    Cuentas cu;
    Cuentas cu2;
    float val,val2;
    int cont=0,numero,cbu,tipo=3;
    char alias[20];
    FILE *p=fopen("Cuenta.dat","r+b");
    if(p==NULL){
        cout<<"No se pudo leer"<<endl;
        return;
    }
        FILE *p2=fopen("Cuenta.dat","r+b");
    if(p2==NULL){
        cout<<"No se pudo leer"<<endl;
        return;
    }
    while(!feof(p)){
            fread(&cu,sizeof(cu),1,p);
            if(dni==cu.getDNI()&&strcmp(valtipo,cu.getTipo())==0){
            cout<<"Valance en la cuenta actualmente: "<<cu.getSALDO();
            cout<<endl;
            cout<<"1.Alias o 2.Cbu al usuario que le quiera transferir: ";
            cin>>numero;
            if(numero==1){
                cout<<"Alias de la persona al que quiera depositar: ";
                fflush(stdin);
                cin.getline(alias,20,'\n');
                break;cout<<"cree una clave token de 4 cifras: ";
            }
            else if(numero==2){
                cout<<"Cbu de la persona al que quiera depositar: ";
                cin>>cbu;
                break;
            }
            }
    }
    while(!feof(p2)){
        fread(&cu2,sizeof(cu2),1,p2);
        if((cbu==cu2.getCBU()||strcmp(alias,cu2.getAlias())==0)&&strcmp(valtipo,cu2.getTipo())==0){
            buscarusuario(cbu,alias);
            cont = 1;
            cout<<"Cuanto desea transferir: ";
            cin>>val;

            val2 = cu.getSALDO()-val;
            cu.setSALDO(val2);
            cargarMov(dni,cu.getCBU(),tipo,val,valtipo);

            int pos=ftell(p)-sizeof(cu);
            fseek(p,pos,SEEK_SET);
            fwrite(&cu,sizeof(cu),1,p);

            val = cu2.getSALDO()+val;
            cu2.setSALDO(val);

            int pos2=ftell(p2)-sizeof(cu2);
            fseek(p2,pos2,SEEK_SET);
            fwrite(&cu2,sizeof(cu2),1,p2);
            break;
        }
    }
    if(cont == 0)cout<<"Usuario no encontrado"<<endl; getch();
    fclose(p);
    fclose(p2);
}

void eliminarCuenta(int dni, const char *valtipo){
    Cuentas cu;
    FILE *p=fopen("Cuenta.dat","r+b");
    if(p==NULL){cout<<"No se pudo leer"<<endl;return;}

    FILE *p2=fopen("auxiliar.dat","a+b");
    if(p2==NULL){cout<<"No se pudo leer"<<endl;return;}


    while(fread(&cu,sizeof(cu),1,p)){

            if(dni==cu.getDNI()&&strcmp(valtipo,cu.getTipo())==0){
                    //nada
            }else{
                fwrite(&cu,sizeof(cu),1,p2);
            }
    }
    cout<<"Cuenta eliminada con exito";
    getch();
    fclose(p);
    fclose(p2);
    remove("Cuenta.dat");
    rename("auxiliar.dat","Cuenta.dat");
}

///verificaciones

bool verifcuenta(int dni){
    Cuentas cu;
    int pos=0;
    while(cu.leerDisco(pos++)){
        if(dni==cu.getDNI()){
                return true;
        }

    }
    return false;
}

bool verifUsuario(int dni){
    Usuario ob;
    int pos=0;
    while(ob.leerDisco(pos++)){
        if(dni==ob.getDNI()){
                return true;
        }

    }
    return false;
}

bool verifTipoDeCuenta(const char *val,int dni){
    Cuentas cu;
    int pos=0;
    while(cu.leerDisco(pos++)){
        if(strcmp(val,cu.getTipo())==0&&cu.getDNI()==dni){
                return true;
        }
    }
    return false;
}

int validartoken(){
    int cla;
    while(true){
    cin>>cla;
    if(cla>999&&cla<10000){
        return cla;
    }
    else{
        cout<<"Clave invalida vuelva a  ingresar otra"<<endl;
    }
    }
}

///Movimientos

void cargarMov(int dni,int cbu,int tipo,float importe,const char *valtipo){
    moviminto mo;
    cout<<"Fecha de transaccion: "<<endl;
    mo.cargarfecha();
    mo.setCuenta(valtipo);
    mo.setDNI(dni);
    mo.setCBU(cbu);
    mo.setImporte(importe);
    if(tipo==1){
     mo.setTIPOMOV("Deposito");
    }
    else if(tipo==2){
     mo.setTIPOMOV("Retiro");
    }
    else if(tipo == 3){
        mo.setTIPOMOV("Transferencia");
    }
    mo.grabarEnDisco();
    cout<<"Movimiento";
    cout<<dni<<endl;
    cout<<cbu<<endl;
    cout<<importe<<endl;
    cout<<tipo<<endl;
    mo.mostrarfecha();
}

void mostrarMov(int dni){
    moviminto mo;
    int pos=0,cont=0;
    while(mo.leerDisco(pos++)){
    if(dni==mo.getDNI()){
    cout<<"Fecha: ";
    mo.mostrarfecha();
    cout<<endl;
    cout<<"Cuenta: "<<mo.getCuenta()<<endl;
    cout<<"Tipo de Importe: "<<mo.getTIPOMOC()<<endl;
    cout<<"Cbu: "<<mo.getCBU()<<endl;
    cout<<"Importe: $"<<mo.getIMPORTE()<<endl;
    cout<<endl;

    }
    }
    if(cont != 0){cout<<"No hay movimientos registrados todavia";}
    getch();
}

///Info

void TodosLosUsuario(){
    Usuario ob;
    int pos=0;
    while(ob.leerDisco(pos++)){
        ob.mostrar();
        cout<<endl;
        cout<<endl;
    }
    getch();
}

void TodasLasCuentas(){
    Cuentas cu;
    int con =0;
    int pos=0;
    while(cu.leerDisco(pos++)){
        cu.mostrar();
        cout<<endl;
        cout<<endl;
        con = 1;
    }
    if(con == 0){
        cout<<"No hay cuentas registradas";
        getch();
    }else getch();
}

void BuscarUsuarioConCuentas(){
    Usuario ob;
    Cuentas cu;
    char nombre[20];
    char apellido[20];
    int pos =0, pos2=0,dni,cont=0;

    cout<<"Nombre y apellido de la persona que esta buscando"<<endl;
    cout<<"Nombre: ";
    fflush(stdin);
    cin.getline(nombre,20,'\n');
    cout<<"Apellido: ";
    fflush(stdin);
    cin.getline(apellido,20,'\n');
    cout<<endl;

    while(ob.leerDisco(pos++)){
        if(strcmp(nombre,ob.getNombre())==0 && strcmp(apellido,ob.getApellido())==0){
            ob.mostrar();
            dni = ob.getDNI();
            cont = 1;
            cout<<endl;
            while(cu.leerDisco(pos2++)){
                if(dni==cu.getDNI()){
                    cout<<endl;
                    cu.mostrar();
                }
            }
                getch();
        }

    }
    if(cont == 0 ){
        cout<<"Este usuario no existe"<<endl;
        getch();
    }else if(cont == 1){
        cout<<"Este usuario no tiene ningun tipo de cuenta";
        getch();
    }


}

#endif // FUNCTION_H_INCLUDED
