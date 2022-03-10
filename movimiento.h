#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
class moviminto{
    private:
        char cuenta[20];
        int dni;
        int cbu;
        char tipoMov[20];
        Fecha fecha_transaccion;
        float Importe;
    public:
        void setCBU(int c){cbu=c;}
        void setDNI(int d){dni=d;}
        void setImporte(float i){Importe=i;}
        void setTIPOMOV(const char *m){strcpy(tipoMov,m);}
        void setCuenta(const char *c){strcpy(cuenta,c);}
        bool grabarEnDisco();
        bool leerDisco(int pos);
        int getDNI(){return dni;}
        int getCBU(){return cbu;}
        float getIMPORTE(){return Importe;}
        const char *getTIPOMOC(){return tipoMov;}
        const char *getCuenta(){return cuenta;}
        void cargarfecha(){fecha_transaccion.Cargar();}
        void mostrarfecha(){fecha_transaccion.Mostrar();}

};

bool moviminto::grabarEnDisco(){
    FILE *p;
    p=fopen("Movimiento.dat","ab");
    if(p==NULL) return false;
    bool grabo=fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return grabo;
}

bool moviminto::leerDisco(int pos){
    FILE *p;
    p=fopen("Movimiento.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos*sizeof *this,0);
    bool lee=fread(this, sizeof *this, 1, p);
    fclose(p);
    return lee;
}

#endif // MOVIMIENTO_H_INCLUDED
