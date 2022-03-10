#ifndef CUENTAS_H_INCLUDED
#define CUENTAS_H_INCLUDED
class Cuentas{
    private:
        int dni;
        char tipo[20];
        Fecha fecha_apertura;
        int cbu;
        char alias[20];
        float saldo;
        float saldo_descubierto;
    public:
        void cargar();
        void mostrar();
        bool grabarEnDisco();
        bool leerDisco(int pos);
        void setCBU(int c){cbu=c;}
        void setDni(int d){dni=d;}
        void setSALDO(int d){saldo=d;}
        void setSaldo_descubierto(int sd){saldo_descubierto=sd;}
        void setTipo(const char *t){strcpy(tipo,t);}
        char *getTipo(){return tipo;}
        char *getAlias(){return alias;}
        int getSALDO(){return saldo;}
        int getSaldo_descubierto(){return saldo_descubierto;}
        int getDNI(){return dni;}
        int getCBU(){return cbu;}
};

void Cuentas::cargar(){
    fflush(stdin);
    cout<<"Fecha de apertura ";
    fecha_apertura.Cargar();
    setCBU(cbualeatorio());
    fflush(stdin);
    cout<<"Cree un Alias: ";
    cin.getline(alias,20,'\n');
    cout<<"Saldo inicial: ";
    cin>>saldo;
    saldo_descubierto=0;
}

void Cuentas::mostrar( ){
    cout<<"Tipo de cuenta: "<<tipo<<endl;
    cout<<"DNI: "<<dni<<endl;
    cout<<"Fecha de apertura: ";
    fecha_apertura.Mostrar();
    cout<<endl;
    cout<<"Alias: "<<alias<<endl;
    cout<<"CBU: "<<cbu<<endl;
    cout<<"Saldo: "<<saldo<<endl;
    if(strcmp(tipo, "Cuenta corriente")==0){
        cout<<"Saldo que debe: "<<saldo_descubierto*(-1)<<endl;
    }
}

bool Cuentas::grabarEnDisco(){
    FILE *p;
    p=fopen("Cuenta.dat","ab");
    if(p==NULL) return false;
    bool grabo=fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return grabo;
}

bool Cuentas::leerDisco(int pos){
    FILE *p;
    p=fopen("Cuenta.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos*sizeof *this,0);
    bool lee=fread(this, sizeof *this, 1, p);
    fclose(p);
    return lee;
}


#endif // CUENTAS_H_INCLUDED
