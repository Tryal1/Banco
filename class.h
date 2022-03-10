#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
class Fecha{
    private:
        int dia, mes, anio;
    public:
        void Cargar(){
            cout<<"Dia: ";
            cin>>dia;
            cout<<"Mes: ";
            cin>>mes;
            cout<<"Anio: ";
            cin>>anio;
            }

        void Mostrar(){
            cout<<dia<<"/"<<mes<<"/"<<anio;
            }
        int getDia(){return dia;}
        int getMes(){return mes;}
        int getAnio(){return anio;}
};
class Usuario{
    private:
        char nombre[20];
        char apellido[20];
        char nombre_usuario[20];
        int dni;
        Fecha fecha_nacimiento;
        char domicilio[20];
        char email[30];
        int token;
        bool estado;
    public:
        void setTOKEN(int t){token=t;}
        int getTOKEN(){return token;}
        int getDNI(){return dni;}
        char *getnombre_usuario(){return nombre_usuario;}
        char *getNombre(){return nombre;}
        char *getApellido(){return apellido;}
        void cargar(int);
        void mostrar();
        bool grabarEnDisco();
        bool leerDisco(int);
        Fecha getFecha_nacimiento(){return fecha_nacimiento;}
};
void Usuario::cargar(int DNI){
    fflush(stdin);
    cout<<"Nombre: ";
    cin.getline(nombre,20,'\n');
    cout<<"Apellido: ";
    cin.getline(apellido,20,'\n');
    cout<<"Nombre de usuario: ";
    cin.getline(nombre_usuario,20,'\n');
    dni=DNI;
    cout<<"Fecha de nacimiento ";
    fecha_nacimiento.Cargar();
    fflush(stdin);
    cout<<"Domicilio: ";
    cin.getline(domicilio,20,'\n');
    fflush(stdin);
    cout<<"Email: ";
    cin.getline(email,30,'\n');
    cout<<"cree una clave token de 4 cifras: ";
    setTOKEN(validartoken());
    estado = true;

}

void Usuario::mostrar(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Apellido: "<<apellido<<endl;
    cout<<"Nombre de usuario: "<<nombre_usuario<<endl;
    cout<<"DNI: "<<dni<<endl;
    cout<<"token: "<<token<<endl;
    cout<<"Domicilio: "<<domicilio<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Fecha de nacimiento: ";
    fecha_nacimiento.Mostrar();
}

bool Usuario::grabarEnDisco(){
    FILE *p;
    p=fopen("Usuario.dat","ab");
    if(p==NULL) return false;
    bool grabo=fwrite(this, sizeof *this, 1, p);
    fclose(p);
    return grabo;
}

bool Usuario::leerDisco(int pos){
    FILE *p;
    p=fopen("Usuario.dat","rb");
    if(p==NULL) return false;
    fseek(p, pos*sizeof *this,0);
    bool lee=fread(this, sizeof *this, 1, p);
    fclose(p);
    return lee;
}


#endif // CLASS_H_INCLUDED
