#ifndef DEFINICION_H_INCLUDED
#define DEFINICION_H_INCLUDED
///Menus
void info();
void movimientos(int,const char *);
void cuenta();

///usuario
void cargarusuario();
void MostrarUsuario();
void buscarusuario(int, const char *);
void cambiarToken();

///cuenta
void cargarcuenta(int);
void ACcuentas();
void MostrarCuenta(int,const char *);
int cbualeatorio();

///Transacciones y acciones de cuenta
void deposito(int,const char *);
void retirar(int,const char *);
void transferencia(int,const char *);
void eliminarCuenta(int,const char *);

///verificaciones
bool verifcuenta(int);
bool verifTipoDeCuenta(const char *,int);
bool verifUsuario(int dni);
int validartoken();


///Movimientos
void cargarMov(int,int,int,float,const char *);
void mostrarMov(int);

///Info
void TodosLosUsuario();
void TodasLasCuentas();
void BuscarUsuarioConCuentas();
void buscar(const char *, const char *);
#endif // DEFINICION_H_INCLUDED
