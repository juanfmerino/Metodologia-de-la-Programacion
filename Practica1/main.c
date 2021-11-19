#include<stdio.h>
#include<locale.h>

#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

#define MAXPELIS 200
#define MAXSOCIOS 50
#define ANO 5
#define TRUE 1
#define FALSE 0
//**********************************************************************************************************************
//Juan de Frutos Merino
// Ainhoa Merino Gomez
// Grupo                                       Fecha:26/04/2020
//****************************************************************************************************

typedef struct
{
    int dia;
    int mes;
    int ano;
} tRegFecha;

typedef struct
{
    char calle[30];
    int numero;
    char localidad[20];
    char codigo_postal[5];
    char ciudad[20];

} tRegDomicilio;

typedef struct{
    char Dni[10];
    char nombre[20];
    char apellido1[10];
    char apellido2[10];
    char telefono[10];
    int peliculas;
    tRegFecha FechaNac;
    tRegFecha FechaBaja;
    tRegFecha FechaAlta;
    tRegDomicilio Domicilio;
}tRegSocio;

typedef struct{
    char codigo[5];
    char titulo[40];
    char director[40];
    char ano[5];
    char DniCliente[10];
    tRegFecha FechaEntrega;
    bool prestada;
}tRegPeli;


int MenuPrincipal();
void MensajeDespedida();
void pausa();
void MensajeBienvenida();

//SUBPROGRAMAS SOCIOS
void GestionSocios(int ContSocios,tRegSocio tablaSocio[],tRegPeli tablaPelis[],int ContBaja);
void AltaSocio(int *ContSocios,tRegSocio tablaSocio[],int *ContBaja);
void BajaSocio(int *ContSocios,tRegSocio tablaSocio[],int *ContBaja);
void ModSocio(int ContSocios,tRegSocio tablaSocio[]);
void ImportarSocio(int *ContSocios,tRegSocio tablaSocio[]);
void ListadoSocio(int ContSocios,tRegSocio tablaSocio[],tRegPeli tablaPelis[],int ContBaja);
void ListadoGeneral(int ContSocios,tRegSocio tablaSocio[]);
void ListadoNuevosSocios(int ContSocios,tRegSocio tablaSocio[],int ContBaja);
void ListadoSociosConPelis(int ContSocios,tRegSocio tablaSocio[],tRegPeli tablaPelis[]);
void InformeBajas(int ContSocios,tRegSocio tablaSocio[], int ContBaja);
//SUBPROGARMAS FICHEROS SOCIOS
void LeerSocios(tRegSocio tablaSocio[],int *ContSocios);
void GuardarSocios(tRegSocio tablaSocio[],int ContSocios);
void LeerHcoSoc(tRegSocio tablaSocio[],int *ContSocios,int *ContBaja);
void GuardarHcoSoc(tRegSocio tablaSocio[],int ContSocios,int ContBaja);
void LeerNuevoSocio(tRegSocio tablaSocio[],int ContSocio, int ContBaja);
void GuardarNuevoSocio(tRegSocio tablaSocio[],int ContSocio, int ContBaja);
//SUBPROGRAMAS PELICULAS
void GestionPelis(tRegPeli tablaPelis[], int ContPelis, int ContPelisPrestadas,tRegSocio tablaSocio[],int ContSocios,int Alquiler[5][12], int contador2);
void ImportarPeliculas(tRegPeli tablaPelis[], int *ContPelis);
void MostrarPeliculas(tRegPeli tablaPelis[], int ContPelis);
void SubmenuListadoPeliculas(tRegPeli tablaPelis[],int ContPelis, int ContPelisPrestadas,tRegSocio tablaSocio[],int ContSocios,int Alquiler[5][12], int contador2);
void ListadoGeneralPeliculas(tRegPeli tablaPelis[], int ContPelis, int ContPelisPrestadas);
void ListadoPeliculasnoPrestadas(tRegPeli tablaPelis[], int ContPelis, int ContPelisPrestadas);
void ListadoPeliculasPrestadas(tRegPeli tablaPelis[], int ContPelis, int *ContPelisPrestadas);
void ListadoPeliculasPorTitulo(tRegPeli tablaPelis[], int ContPelis);
void Listadopeliculasa(tRegPeli tablaPelis[], int ContPelis);
void devolucionPeliculas(tRegPeli tablaPelis[], int ContPelis, int *ContPelisPrestadas,tRegSocio tablaSocio[], int ContSocios);
void PrestamoPeliculas(tRegPeli tablaPelis[], int ContPelis,int *ContPelisPrestadas,tRegSocio tablaSocio[],int ContSocios,int Alquiler[5][12]);
void InformePrestamos(tRegPeli tablaPelis[], int ContPelis, int ContPelisPrestadas,int Alquiler[5][12], int contador2);
//SUBPROGRAMAS MATRIZ PRESTAMOS
void Inicializar(tRegPeli tablapelis[], int ContPelis);
void InicializarMatriz(int Alquiler[5][12]);
void ActualizarMatriz(tRegPeli tablaPelis[], int ContPelis, int Alquiler[5][12],int contador2);
//SUBPROGRAMAS FICHEROS PELICULAS
void LeerPeliculas(tRegPeli tablaPelis[], int *ContPelis);
void GuardarPeliculas(int ContPelis,tRegPeli tablaPelis[]);
void LeerMatriz(int Alquiler[5][12]);
void GuardarMatriz(int Alquiler[5][12]);







int main()
{
    tRegSocio tablaSocio[MAXSOCIOS];
    tRegPeli tablaPelis[MAXPELIS];


    int opcion;
    int i;
    char respuesta;
    int ContPelis=0;
    int ContSocios=0;
    int ContBaja=0;
    int ContPelisPrestadas=0;
    int Alquiler [5][12];
    int contador2=0;

    setlocale(LC_CTYPE, "Spanish");

    MensajeBienvenida();


    //Cargar Datos Peliculas y Socios
    LeerSocios(tablaSocio,&ContSocios);
    LeerHcoSoc(tablaSocio,&ContSocios,&ContBaja);
    LeerNuevoSocio(tablaSocio,ContSocios,ContBaja);
    LeerPeliculas(tablaPelis, &ContPelis);

    LeerMatriz(Alquiler);

    if(ContPelisPrestadas==0){
        Inicializar(tablaPelis,ContPelis);
        InicializarMatriz(Alquiler);

        for(i=0;i<ContSocios;i++){
            tablaSocio[i].peliculas=0;
        }
        printf("Todo inicializado con exito");
        pausa();
    }




    do{
        opcion=MenuPrincipal();
        switch(opcion){
            case 1:GestionSocios(ContSocios,tablaSocio,tablaPelis,ContBaja);
                break;
            case 2:GestionPelis(tablaPelis,ContPelis, ContPelisPrestadas,tablaSocio,ContSocios,Alquiler,contador2);
                break;
            case 0:
                GuardarSocios(tablaSocio,ContSocios);
                GuardarHcoSoc(tablaSocio,ContSocios,ContBaja);
                GuardarNuevoSocio(tablaSocio,ContSocios,ContBaja);
                GuardarMatriz(Alquiler);

                GuardarPeliculas(ContPelis,tablaPelis);
                MensajeDespedida();
                break;

        }
    }while(opcion!=0);

    return 0;
}


//********************************************************//
//SUBPROGRAMA: MensajedeBienvenida
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS:
//OBJETIVO: El objetivo de este subprograma es mostrar
//por pantalla un mensaje de bienvenida al programa
//ADVERTENCIAS:
//********************************************************//
void MensajeBienvenida()
{
    printf("\t\t*************************************************\n");
    printf("\t\t*************************************************\n");
    printf("\t\t*************************************************\n");
    printf("\t\t\tBIENVENIDOS A LA APLICACION\n\n");
    printf("\t\t*************************************************\n");
    printf("\t\t*************************************************\n");
    printf("\t\t*************************************************\n");

    pausa();
}
//********************************************************//
//SUBPROGRAMA: MensajeDespedida
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS:
//OBJETIVO: El objetivo de este subprograma es mostrar
//por pantalla un mensaje de despedida
//ADVERTENCIAS:
//********************************************************//
void MensajeDespedida()
{
    pausa();
    printf("Gracias por utilizar la aplicacion\n\n");
}
//********************************************************//
//SUBPROGRAMA: MenuPrincipal
//TIPO:Función (Devuelve un valor )
//PRERREQUISITOS:
//OBJETIVO: El objetivo de este subprograma, es que el usuario
//eliga una opción la cual devolverá mediante un return al main()
//********************************************************//

int MenuPrincipal()
{

    int opcion;

    system("cls");
    printf("\t\tMENU PRINCIPAL\n\n");

    printf("\t\t1-Gestion de Socios\n");
    printf("\t\t2-Gestion de Peliculas\n");
    printf("\t\t0-Salir\n\n");


    fflush(stdin);
    printf("\t\tElija opcion:");
    scanf("%i",&opcion);

    printf("\n");
    pausa();

    return opcion;
}
//********************************************************//
//SUBPROGRAMA: Pausa
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS:
//OBJETIVO: El objetivo de este subprograma es mostrar
//por pantalla un mensaje de pausa
//ADVERTENCIAS:
//********************************************************//
void pausa()
{

    printf("\n\nPulse <Intro> para continuar...");
    fflush(stdin);
    getchar();
}
//********************************************************//
//SUBPROGRAMA: GestionSocios
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO: El objetivo de este subprograma es mostrar un menu de
// seis opciones , en la que el usuario deberá elegir una
//ADVERTENCIAS:
//********************************************************//

void GestionSocios(int ContSocios,tRegSocio tablaSocio[],tRegPeli tablaPelis[],int ContBaja){
    int opcion;

    system("cls");

    pausa();
    system("cls");

    do{

        printf("\tGESTION DE SOCIOS\n\n");

        printf("\t1-Alta\n");
        printf("\t2-Baja\n");
        printf("\t3-Modificacion\n");
        printf("\t4-Importar Socios\n");
        printf("\t5-Listado de Socios\n\n");

        printf("\t0-Volver al menu principal\n\n");

        printf("Elija la opcion que desee:");
        scanf("%i",&opcion);


        switch(opcion){
            case 1:
                AltaSocio(&ContSocios,tablaSocio,&ContBaja);
                break;
            case 2:
                BajaSocio(&ContSocios,tablaSocio,&ContBaja);
                break;
            case 3:
                ModSocio(ContSocios,tablaSocio);
                break;
            case 4:
                ImportarSocio(&ContSocios,tablaSocio);
                break;
            case 5:
                ListadoSocio(ContSocios,tablaSocio,tablaPelis,ContBaja);
                break;
            case 0:
                MenuPrincipal();
                break;
        }
    }while(opcion!=0);
}

//********************************************************//
//SUBPROGRAMA: GestionPelis
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar un menu de
// seis opciones , en la que el usuario deberá elegir una
//ADVERTENCIAS:
//********************************************************//

void GestionPelis(tRegPeli tablaPelis[], int ContPelis,int ContPelisPrestadas,tRegSocio tablaSocio[],int ContSocios,int Alquiler[5][12], int contador2){


   int opcion;

   system("cls");

    do{

    printf("\tGESTION DE PELICULAS\n\n");

    printf("\t1-Importar Peliculas\n");
    printf("\t2-Mostrar los datos de una Pelicula\n");
    printf("\t3-Prestamo\n");
    printf("\t4-Devolucion\n");
    printf("\t5-Listado de Peliculas\n\n");

    printf("\t0-Volver al menu principal: ");
    scanf("%i",&opcion);




        switch(opcion){
            case 1:
                ImportarPeliculas(tablaPelis, &ContPelis);
                break;
            case 2:
                MostrarPeliculas(tablaPelis, ContPelis);
                break;
            case 3:
                PrestamoPeliculas(tablaPelis,ContPelis,&ContPelisPrestadas,tablaSocio,ContSocios,Alquiler);
                break;
            case 4:
                devolucionPeliculas(tablaPelis,ContPelis,&ContPelisPrestadas, tablaSocio,ContSocios);
                break;
            case 5:
                SubmenuListadoPeliculas(tablaPelis,ContPelis,ContPelisPrestadas,tablaSocio,ContSocios,Alquiler,contador2);
                break;
            case 0:
                MenuPrincipal();
                break;
        }
    }while(opcion!=0);
}
//********************************************************//
//SUBPROGRAMA: AltaSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO: El objetivo de este subprograma es registrar en la aplicacion
// a un socio que el usuario introduzca por teclado
//ADVERTENCIAS:
//********************************************************//

void AltaSocio(int *ContSocios,tRegSocio tablaSocio[],int *ContBaja){

    system("cls");


    char respuesta,confirmacion;
    char dniaux[10];
    int contador;

    //LeerNuevoSocio(tablaSocio,&*ContSocios,ContBaja);


    if(*ContSocios>50){
        printf(" Lo sentimos no se pueden introducir mas socios\n\n");
        pausa();
        system("cls");
    }else{

        do{
            printf("\tBIENVENIDO AL ALTA DE SOCIO\n\n");
            pausa();
            system("cls");
            printf("\t\tINTRODUZCA LOS SIGUIENTES DATOS\n");
            do{
                do{

                    printf("\n\tIntroduzca el DNI(12345678x):");
                    fflush(stdin);
                    gets(dniaux);

                    if(strlen(dniaux)!=9)
                    {
                        printf("\n\nError.Formato del DNI incorrecto, Escriba otro\n\n");
                    }
                }while(strlen(dniaux)!=9);

                contador=-1;
                strupr(dniaux);

                    do
                    {
                        contador++;
                        if(strcmp(tablaSocio[contador].Dni,dniaux)==0)
                        {
                            printf("Atencion: Este dni ya esta registtado en la aplicacion");
                        }
                    }
                    while((strcmp(tablaSocio[contador].Dni,dniaux)!=0)&&(contador< *ContSocios));
            }while(strcmp(tablaSocio[contador].Dni,dniaux)==0);

            strcpy(tablaSocio[*ContSocios].Dni,dniaux);

            printf("\n\tIntroduzca el Nombre:");
            fflush(stdin);
            gets(tablaSocio[*ContSocios].nombre);

            printf("\n\tIntroduzca el Primer apellido:");
            fflush(stdin);
            gets(tablaSocio[*ContSocios].apellido1);

            printf("\n\tIntroduzca el Segundo apellido:");
            fflush(stdin);
            gets(tablaSocio[*ContSocios].apellido2);




            printf("\n\tDOMICILIO DEL PACIENTE\n");
            printf("\tIntroduce la calle donde vives:");
            fflush(stdin);
            gets(tablaSocio[*ContSocios].Domicilio.calle);

            printf("\n\tIntroduce el numero de la calle:");
            fflush(stdin);
            scanf("%i",&tablaSocio[*ContSocios].Domicilio.numero);

            printf("\n\tIntroduce la localidad:");
            fflush(stdin);
            gets(tablaSocio[*ContSocios].Domicilio.localidad);

            printf("\n\tIntroduce el codigo postal:");
            fflush(stdin);
            //scanf("%i",&tablaSocio[*ContSocios].Domicilio.codigo_postal);
            gets(tablaSocio[*ContSocios].Domicilio.codigo_postal);

            printf("\n\tIntroduce la ciudad:");
            fflush(stdin);
            gets(tablaSocio[*ContSocios].Domicilio.ciudad);



            printf("\n\tFECHA DE NACIMIENTO:\n");

            do
            {
                printf("\n\tIntroduce el dia(DD):");
                fflush(stdin);
                scanf("%i",&tablaSocio[*ContSocios].FechaNac.dia);
            }
            while((((tablaSocio[*ContSocios].FechaNac.dia)<0)||((tablaSocio[*ContSocios].FechaNac.dia)>31)));
            do
            {
                printf("\n\tIntroduce el Mes(MM):");
                fflush(stdin);
                scanf("%i",&tablaSocio[*ContSocios].FechaNac.mes);
            }
            while((((tablaSocio[*ContSocios].FechaNac.mes)<0)||((tablaSocio[*ContSocios].FechaNac.mes)>12)));

                printf("\n\tIntroduce el ano(AAAA):");
                fflush(stdin);
                scanf("%i",&tablaSocio[*ContSocios].FechaNac.ano);


            printf("\n\tIntroduce el telefono:");
            fflush(stdin);
            //scanf("%i",&tablaSocio[*ContSocios].telefono);
            gets(tablaSocio[*ContSocios].telefono);

            printf("\n\tFECHA DE ALTA DEL SOCIO:\n");

            do
            {
                printf("\n\tIntroduce el dia(DD):");
                fflush(stdin);
                scanf("%i",&tablaSocio[*ContSocios].FechaAlta.dia);
            }
            while((((tablaSocio[*ContSocios].FechaAlta.dia)<0)||((tablaSocio[*ContSocios].FechaAlta.dia)>31)));
            do
            {
                printf("\n\tIntroduce el Mes(MM):");
                fflush(stdin);
                scanf("%i",&tablaSocio[*ContSocios].FechaAlta.mes);
            }
            while((((tablaSocio[*ContSocios].FechaAlta.mes)<0)||((tablaSocio[*ContSocios].FechaAlta.mes)>12)));

                printf("\n\tIntroduce el ano(AAAA):");
                fflush(stdin);
                scanf("%i",&tablaSocio[*ContSocios].FechaAlta.ano);

            system("cls");


            printf("\tEstos son los datos del nuevo socio:\n\n");

            printf("\nEl nombre del nuevo socio es: %s %s %s\n", tablaSocio[*ContSocios].nombre,tablaSocio[*ContSocios].apellido1,tablaSocio[*ContSocios].apellido2);
            printf("El DNI del nuevo es: %s\n",tablaSocio[*ContSocios].Dni);
            printf("La fecha de nacimiento del nuevo socio es: %i-%i-%i\n",tablaSocio[*ContSocios].FechaNac.dia,tablaSocio[*ContSocios].FechaNac.mes,tablaSocio[*ContSocios].FechaNac.ano);
            printf("El telefono del nuevo socio es: %s\n",tablaSocio[*ContSocios].telefono);
            printf("El nuevo socio vive en %s con CP %s en la provincia de %s en la calle %s con numero %i",tablaSocio[*ContSocios].Domicilio.localidad,tablaSocio[*ContSocios].Domicilio.codigo_postal,tablaSocio[*ContSocios].Domicilio.ciudad,tablaSocio[*ContSocios].Domicilio.calle,tablaSocio[*ContSocios].Domicilio.numero);

           /* strcpy(tablaSocio[*ContSocios].Dni,tablaSocio[*ContNuevosSocios].Dni);
            strcpy(tablaSocio[*ContSocios].nombre,tablaSocio[*ContNuevosSocios].nombre);
            strcpy(tablaSocio[*ContSocios].apellido1,tablaSocio[*ContNuevosSocios].apellido1);
            strcpy(tablaSocio[*ContSocios].apellido2,tablaSocio[*ContNuevosSocios].apellido2);
            strcpy(tablaSocio[*ContSocios].telefono,tablaSocio[*ContNuevosSocios].telefono);
            strcpy(tablaSocio[*ContSocios].Domicilio.localidad,tablaSocio[*ContNuevosSocios].Domicilio.localidad);
            strcpy(tablaSocio[*ContSocios].Domicilio.codigo_postal,tablaSocio[*ContNuevosSocios].Domicilio.codigo_postal);
            strcpy(tablaSocio[*ContSocios].Domicilio.ciudad,tablaSocio[*ContNuevosSocios].Domicilio.ciudad);
            strcpy(tablaSocio[*ContSocios].Domicilio.calle,tablaSocio[*ContNuevosSocios].Domicilio.calle);
            tablaSocio[*ContSocios].FechaNac.dia=tablaSocio[*ContNuevosSocios].FechaNac.dia;
            tablaSocio[*ContSocios].FechaNac.mes=tablaSocio[*ContNuevosSocios].FechaNac.mes;
            tablaSocio[*ContSocios].FechaNac.ano=tablaSocio[*ContNuevosSocios].FechaNac.ano;
            tablaSocio[*ContSocios].Domicilio.numero=tablaSocio[*ContNuevosSocios].Domicilio.numero;
            pausa();*/

            printf("\n\n\t¿Datos correctos?(S/N)");
            fflush(stdin);
            scanf("%c",&confirmacion);
            confirmacion = toupper(confirmacion);

            if(confirmacion=='S'){
                *ContSocios=*ContSocios+1;
                //*ContNuevosSocios=*ContNuevosSocios+1;
                printf("El socio se ha dado de alta correctamente\n\n");

                //GuardarSocios(tablaSocio,ContSocios);
                //GuardarNuevoSocio(tablaSocio,ContSocios,ContBaja);
            }else{
                printf("\nLos datos eran incorrectos insertelos de nuevo");
                printf("\n Proceso de alta abortado");
            }


            printf("El numero de socios registrados es de %i\n\n",*ContSocios);

            pausa();
            system("cls");

            printf("\n\n\t¿Desea introducir mas socios?(S/N)");
            fflush(stdin);
            scanf("%c",&respuesta);
            respuesta = toupper(respuesta);


        }while(respuesta=='S');
    }



    printf("Saliendo del alta de Socios\n\n");
    pausa();
    system("cls");

}
//********************************************************//
//SUBPROGRAMA: BajaSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios , y el Contador de baja , el cual
// es una variable que almacena el numero de socios que se han dado
// de baja en la aplicación
//OBJETIVO: El objetivo de este subprograma es dar de baja
// a un socio el cual estaba previamente registrado en la aplicacion
//ADVERTENCIAS:
//********************************************************//

void BajaSocio(int *ContSocios,tRegSocio tablaSocio[],int *ContBaja){


    char dniaux[10];
    int contador,i;
    char respuesta, confirmacion;

    system("cls");

    printf("BIENVENIDO A LA BAJA DE SOCIOS\n\n");
    printf("El numero de socios registrados es de %i\n\n",*ContSocios);

    if(*ContSocios==0){
        printf("No hay Socios registrados aun\n\n");
        printf("No puedes dar de baja ningun Socio");
    }else{

        do{
            do{
                do{

                        printf("\nIntroduzca el dni de la persona:");
                        fflush(stdin);
                        gets(dniaux);

                        if(strlen(dniaux)!=9)
                        {
                            printf("\n\nError.Formato del DNI incorrecto, Escriba otro\n\n");
                        }
                    }while(strlen(dniaux)!=9);

                    contador=-1;
                    strupr(dniaux);

                        do
                        {
                            contador++;
                            if(strcmp(tablaSocio[contador].Dni,dniaux)!=0){

                                printf("Atencion: Este dni no esta registado en la aplicacion");
                            }

                        }while((strcmp(tablaSocio[contador].Dni,dniaux)!=0)&&(contador< *ContSocios));

                        printf("DNI de la persona encontrado\n\n");
            }while(strcmp(tablaSocio[contador].Dni,dniaux)!=0);

            pausa();
            system("cls");


            printf("Introduce la fecha de la baja\n\n");

            do{
                    printf("\n\tIntroduce el dia(DD):");
                    fflush(stdin);
                    scanf("%i",&tablaSocio[contador].FechaBaja.dia);
                }
                while((((tablaSocio[contador].FechaBaja.dia)<0)||((tablaSocio[contador].FechaBaja.dia)>31)));
                do
                {
                    printf("\n\tIntroduce el Mes(MM):");
                    fflush(stdin);
                    scanf("%i",&tablaSocio[contador].FechaBaja.mes);
                }
                while((((tablaSocio[contador].FechaBaja.mes)<0)||((tablaSocio[contador].FechaBaja.mes)>12)));

                    printf("\n\tIntroduce el ano(AAAA):");
                    fflush(stdin);
                    scanf("%i",&tablaSocio[contador].FechaBaja.ano);

            pausa();
            system("cls");

            printf("\tEstos son los datos del socio:\n\n");

            printf("\nEl nombre del nuevo socio es: %s %s %s\n", tablaSocio[contador].nombre,tablaSocio[contador].apellido1,tablaSocio[contador].apellido2);
            printf("El DNI del nuevo es: %s\n",tablaSocio[contador].Dni);
            printf("La fecha de nacimiento del nuevo socio es: %i-%i-%i\n",tablaSocio[contador].FechaNac.dia,tablaSocio[contador].FechaNac.mes,tablaSocio[contador].FechaNac.ano);
            printf("El telefono del nuevo socio es: %s\n",tablaSocio[contador].telefono);
            printf("El nuevo socio vive en %s con CP %s en la provincia de %s en la calle %s con numero %i\n\n\n\n",tablaSocio[contador].Domicilio.localidad,tablaSocio[contador].Domicilio.codigo_postal,tablaSocio[contador].Domicilio.ciudad,tablaSocio[contador].Domicilio.calle,tablaSocio[contador].Domicilio.numero);
            printf("El dia donde se confirma la baja es: %i-%i-%i\n",tablaSocio[contador].FechaBaja.dia,tablaSocio[contador].FechaBaja.mes,tablaSocio[contador].FechaBaja.ano);
             printf("El socio tiene: %i peliculas prestadas\n\n",tablaSocio[contador].peliculas);

/*
            printf("\nEl nombre del nuevo socio es: %s %s %s\n", tablaSocio[*ContSocios].nombre,tablaSocio[*ContSocios].apellido1,tablaSocio[*ContSocios].apellido2);
            printf("El DNI del nuevo es: %s\n",tablaSocio[*ContSocios].Dni);
            printf("La fecha de nacimiento del nuevo socio es: %i-%i-%i\n",tablaSocio[*ContSocios].FechaNac.dia,tablaSocio[*ContSocios].FechaNac.mes,tablaSocio[*ContSocios].FechaNac.ano);
            printf("El telefono del nuevo socio es: %s\n",tablaSocio[*ContSocios].telefono);
            printf("El nuevo socio vive en %s con CP %s en la provincia de %s en la calle %s con numero %i\n\n",tablaSocio[*ContSocios].Domicilio.localidad,tablaSocio[*ContSocios].Domicilio.codigo_postal,tablaSocio[*ContSocios].Domicilio.ciudad,tablaSocio[*ContSocios].Domicilio.calle,tablaSocio[*ContSocios].Domicilio.numero);
            printf("El dia donde se confirma la baja es: %i-%i-%i",tablaSocio[*ContSocios].FechaBaja.dia,tablaSocio[*ContSocios].FechaBaja.mes,tablaSocio[*ContSocios].FechaBaja.ano);
            printf("El socio tiene: %i peliculas prestadas\n\n",tablaSocio[*ContSocios].peliculas);
*/
            pausa();


            printf("\n\n\t¿Desea dar de baja este socio?(S/N)");
            fflush(stdin);
            scanf("%c",&confirmacion);
            confirmacion = toupper(confirmacion);

            if((confirmacion=='S')&&(tablaSocio[*ContSocios].peliculas==0)){
                *ContSocios=*ContSocios-1;
                *ContBaja=*ContBaja+1;
                printf("Socio Eliminado\n");

                /*for(i=contador;i<*ContSocios;i++){
                    tablaSocio[i]=tablaSocio[i+1];
                }*/
                printf("El numero de socios registrados es de %i\n\n",*ContSocios);


                 //GuardarHcoSoc(tablaSocio,ContSocios,ContBaja);
            } else
                printf("Proceso de baja abortado");

            printf("\n\n\t¿Desea dar de baja mas socios?(S/N)");
            fflush(stdin);
            scanf("%c",&respuesta);
            respuesta = toupper(respuesta);


        }while(respuesta=='S');
    }

    pausa();
    system("cls");

    printf("\n\nSaliendo de la BAJA DE SOCIOS\n\n");
    pausa();
    system("cls");


}
//********************************************************//
//SUBPROGRAMA: ModSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO: El objetivo de este subprograma es poder modificar
//alguno de los campos de el registro socio
//ADVERTENCIAS:
//********************************************************//

void ModSocio(int ContSocios,tRegSocio tablaSocio[]){

    char dniaux[10];
    int contador,opcion;
    char respuesta;

    system("cls");

    printf("BIENVENIDO A LA MODIFICACION DE SOCIOS\n\n");
    printf("El numero de socios registrados es de %i\n\n",ContSocios);

    if(ContSocios==0){
        printf("No hay Socios registrados aun\n\n");
        printf("No puedes modificar ningun Socio");
    }else{

            do{
                do{

                        printf("\nIntroduzca el dni de la persona:");
                        fflush(stdin);
                        gets(dniaux);

                        if(strlen(dniaux)!=9)
                        {
                            printf("\n\nError.Formato del DNI incorrecto, Escriba otro\n\n");
                        }
                    }while(strlen(dniaux)!=9);

                    contador=-1;
                    strupr(dniaux);

                        do
                        {
                            contador++;
                            if(strcmp(tablaSocio[contador].Dni,dniaux)!=0)
                            {
                                printf("Atencion: Este dni no esta registado en la aplicacion");
                            }
                        }while((strcmp(tablaSocio[contador].Dni,dniaux)!=0)&&(contador< ContSocios));

                        printf("DNI de la persona encontrado\n\n");
            }while(strcmp(tablaSocio[contador].Dni,dniaux)!=0);

            pausa();
            system("cls");
    do{
            for(contador=0;contador<ContSocios;contador++){

                if(strcmp(tablaSocio[contador].Dni,dniaux)==0){
                    printf("Bienvenido a la Modificacion de Datos\n\n");

                      do
                    {
                        printf("1-Modificar Nombre:\n");
                        printf("2-Modificar Primer apellido:\n");
                        printf("3-Modificar Segundo apellido:\n");
                        printf("4-Modificar Telefono:\n");
                        printf("5-Modificar Calle Domicilio:\n");
                        printf("6-Modificar Numero del Domicilio:\n");
                        printf("7-Modificar Localidad del Domicilio:\n");
                        printf("8-Modificar Codigo Postal:\n");
                        printf("9-Modificar Ciudad del Domicilio:\n");
                        printf("0-Salir\n\n");

                        printf("Elija la opcion: ");
                        scanf("%i",&opcion);
                        system("cls");


                        switch(opcion)
                        {
                        case 1:
                            printf("El nobmbre es:%s\n\n",tablaSocio[contador].nombre);
                            printf("Introduce el nuevo Nombre ");
                            fflush(stdin);
                            gets(tablaSocio[contador].nombre);
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            printf("\nIntroduce el Primer Apellido:");
                            fflush(stdin);
                            gets(tablaSocio[contador].apellido1);
                            system("pause");
                            system("cls");
                            break;
                        case 3:
                            printf("\nIntroduce el Segundo Apellido ");
                            fflush(stdin);
                            gets(tablaSocio[contador].apellido2);
                            system("pause");
                            system("cls");
                            break;
                        case 4:
                            printf("\nIntroduce el nuevo numero de telefono ");
                            fflush(stdin);
                           // scanf("%i",&tablaSocio[contador].telefono);
                            gets(tablaSocio[contador].telefono);
                            system("pause");
                            system("cls");
                            break;
                        case 5:
                            printf("\nIntroduce la nueva calle de tu domicilio:");
                            fflush(stdin);
                            gets(tablaSocio[contador].Domicilio.calle);
                            system("pause");
                            system("cls");
                            break;
                        case 6:
                            printf("\nIntroduce el nuevo numero de tu domicilio:");
                            fflush(stdin);
                            scanf("%i",&tablaSocio[contador].Domicilio.numero);
                            system("pause");
                            system("cls");
                            break;
                        case 7:
                            printf("\nIntroduce la nueva localidad de tu domicilio:");
                            fflush(stdin);
                            gets(tablaSocio[contador].Domicilio.localidad);
                            system("pause");
                            system("cls");
                            break;
                        case 8:
                            printf("\nIntroduce el nuevo codigo postal:");
                            fflush(stdin);
                            gets(tablaSocio[contador].Domicilio.codigo_postal);
                            //scanf("%s",&tablaSocio[contador].Domicilio.codigo_postal);
                            system("pause");
                            system("cls");
                            break;
                        case 9:
                            printf("\nIntroduce la nueva ciudad de tu domicilio:");
                            fflush(stdin);
                            gets(tablaSocio[contador].Domicilio.ciudad);
                            system("pause");
                            system("cls");
                            break;
                        case 0:
                            printf("Estas saliendo de la Modificacion de Datos\n\n");
                            system("pause");
                            system("cls");
                            break;
                        }

                    }while(opcion!=0);

                printf("El Socio se encuentra en la posicion %i\n\n",contador);


                printf("\tEstos son los nuevos datos del socio con DNI: %s:\n\n",tablaSocio[contador].Dni);

                printf("\nEl nombre del socio es: %s %s %s\n", tablaSocio[contador].nombre,tablaSocio[contador].apellido1,tablaSocio[contador].apellido2);
                printf("La fecha de nacimiento del nuevo socio es: %i-%i-%i\n",tablaSocio[contador].FechaNac.dia,tablaSocio[contador].FechaNac.mes,tablaSocio[contador].FechaNac.ano);
                printf("El telefono del socio es: %s\n",tablaSocio[contador].telefono);
                printf("El socio vive en %s con CP %s en la provincia de %s en la calle %s con numero %i\n",tablaSocio[contador].Domicilio.localidad,tablaSocio[contador].Domicilio.codigo_postal,tablaSocio[contador].Domicilio.ciudad,tablaSocio[contador].Domicilio.calle,tablaSocio[contador].Domicilio.numero);
                printf("El socio tiene: %i peliculas prestadas\n\n\n",tablaSocio[contador].peliculas);

                pausa();

                }
            }

            printf("\n\n\t¿Desea modificar mas socios?(S/N)");
            fflush(stdin);
            scanf("%c",&respuesta);
            respuesta = toupper(respuesta);

        }while(respuesta=='S');

        pausa();
        system("cls");

        printf("\n\nSaliendo de la MODIFICACION DE SOCIOS\n\n");
        pausa();
        system("cls");
    }
}
//********************************************************//
//SUBPROGRAMA: ImportarSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO: El objetivo de este subprograma es leer la información
//la cual esta almacenada en el fichero de texto Socios.txt ,
// después se copiará la información del fichero de texto
// al array de socios.
//ADVERTENCIAS:Si el fichero Socios.txt, no se puee abrir
// se mostrara un error por pantalla y se abortara el programa
//********************************************************//

void ImportarSocio(int *ContSocios,tRegSocio tablaSocio[]){

    tRegSocio tablauxiliarsocio[MAXSOCIOS];
    int i,j;
    char delimitadores[]="-";
    char limitador[]=" ";
    char limitador2[]="\n";
    char *token;
    char linea[200];

    system("cls");

    FILE *Ficheroauxiliar;

    Ficheroauxiliar= fopen("Socios.txt","r");

    if(Ficheroauxiliar==NULL){
        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        Ficheroauxiliar = fopen("Socios.txt","wb");

        printf("El fichero ya ha sido creado\n\n");

    }else{
        if(*ContSocios>=50){
            printf("Imposible registrar nuevos socios en la aplicacion\n\n");
        }else{

            for(i=0;!feof(Ficheroauxiliar);i++){
            //while((!feof(Ficheroauxiliar))&&(*ContSocios<MAXSOCIOS)){

                    //token=strtok(linea,limitador2);
                    fgets(tablauxiliarsocio[i].Dni,10,Ficheroauxiliar);

                    /*token=strtok(linea,limitador);
                    fgets(linea,200,Ficheroauxiliar);*/

                    //token=strtok(Ficheroauxiliar,limitador);
                    fgets(tablauxiliarsocio[i].nombre,20,Ficheroauxiliar);
                    //token=strtok(NULL,limitador);
                    fgets(tablauxiliarsocio[i].apellido1,10,Ficheroauxiliar);
                    //token=strtok(NULL,limitador);
                    fgets(tablauxiliarsocio[i].apellido2,10,Ficheroauxiliar);


                    /*token=strtok(NULL,delimitadores);
                    fscanf(Ficheroauxiliar,"%i",tablauxiliarsocio[i].FechaNac.dia);
                    //tablauxiliarsocio[i].FechaNac.dia=atoi(token);
                    token=strtok(NULL,delimitadores);
                    fscanf(Ficheroauxiliar,"%i",tablauxiliarsocio[i].FechaNac.mes);
                    //tablauxiliarsocio[i].FechaNac.mes=atoi(token);
                    token=strtok(NULL,limitador2);
                    fscanf(Ficheroauxiliar,"%i",tablauxiliarsocio[i].FechaAlta.ano);
                    //tablauxiliarsocio[i].FechaNac.ano=atoi(token);

                    token=strtok(NULL,delimitadores);
                    fgets(tablauxiliarsocio[i].Domicilio.calle,10,Ficheroauxiliar);
                    token=strtok(NULL,delimitadores);
                    fgets(tablauxiliarsocio[i].Domicilio.ciudad,10,Ficheroauxiliar);
                    token=strtok(NULL,delimitadores);
                    fgets(tablauxiliarsocio[i].Domicilio.codigo_postal,10,Ficheroauxiliar);
                    token=strtok(NULL,delimitadores);
                    fgets(tablauxiliarsocio[i].Domicilio.localidad,10,Ficheroauxiliar);
                    token=strtok(NULL,limitador2);
                    //tablauxiliarsocio[i].Domicilio.numero=atoi(token);
                    fscanf(Ficheroauxiliar,"%i",tablauxiliarsocio[i].Domicilio.numero);

                    token=strtok(NULL,limitador2);
                    fgets(tablauxiliarsocio[i].telefono,10,Ficheroauxiliar);*/


                    /*tablauxiliarsocio[i].FechaNac.dia=atoi(token);
                    tablauxiliarsocio[i].FechaNac.mes=atoi(token);
                    tablauxiliarsocio[i].FechaNac.ano=atoi(token);
                    tablauxiliarsocio[i].Domicilio.numero=atoi(token);*/

                    printf("Dni:%s\n",tablauxiliarsocio[i].Dni);
                    printf("Nombre:%s %s %s\n",tablauxiliarsocio[i].nombre,tablauxiliarsocio[i].apellido1,tablauxiliarsocio[i].apellido2);
                   /* printf("Fecha Nacimiento:%i-%i-%i\n",tablauxiliarsocio[i].FechaNac.dia,tablauxiliarsocio[i].FechaNac.mes,tablauxiliarsocio[i].FechaAlta.ano);
                    printf("Calle:%s\n",tablauxiliarsocio[i].Domicilio.calle);
                    printf("Ciudad:%s con CP: %s y localidad: %s numero %i\n",tablauxiliarsocio[i].Domicilio.ciudad,tablauxiliarsocio[i].Domicilio.codigo_postal,tablauxiliarsocio[i].Domicilio.localidad,tablauxiliarsocio[i].Domicilio.numero);
                    printf("Telefono:%s\n",tablauxiliarsocio[i].telefono);*/

                    pausa();

                    strupr(tablauxiliarsocio[i].Dni);

                    strcpy(tablauxiliarsocio[i].Dni,tablaSocio[*ContSocios].Dni);
                    strcpy(tablauxiliarsocio[i].nombre,tablaSocio[*ContSocios].nombre);
                    strcpy(tablauxiliarsocio[i].apellido1,tablaSocio[*ContSocios].apellido1);
                    strcpy(tablauxiliarsocio[i].apellido2,tablaSocio[*ContSocios].apellido2);

                    tablauxiliarsocio[i].FechaNac.dia=tablaSocio[*ContSocios].FechaNac.dia;
                    tablauxiliarsocio[i].FechaNac.mes=tablaSocio[*ContSocios].FechaNac.mes;
                    tablauxiliarsocio[i].FechaNac.ano=tablaSocio[*ContSocios].FechaNac.ano;

                    strcpy(tablauxiliarsocio[i].Domicilio.calle,tablaSocio[*ContSocios].Domicilio.calle);
                    strcpy(tablauxiliarsocio[i].Domicilio.ciudad,tablaSocio[*ContSocios].Domicilio.ciudad);
                    strcpy(tablauxiliarsocio[i].Domicilio.codigo_postal,tablaSocio[*ContSocios].Domicilio.codigo_postal);
                    strcpy(tablauxiliarsocio[i].Domicilio.localidad,tablaSocio[*ContSocios].Domicilio.localidad);
                    tablauxiliarsocio[i].Domicilio.numero=tablauxiliarsocio[i].Domicilio.numero;

                    strcpy(tablauxiliarsocio[i].telefono,tablaSocio[*ContSocios].telefono);


                    *ContSocios=*ContSocios+1;


                }
            fclose(Ficheroauxiliar);


            pausa();
            system("cls");

            printf("Se ha copiado el los datos al array de Socios\n");
            printf("Vector de Socios actualizadas\n");
            printf("El numero de Socios es de : %d\n",*ContSocios);
        }

    pausa();
    system("cls");

    }
}
//********************************************************//
//SUBPROGRAMA: ListadoSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO: El objetivo de este subprograma es mostrar un menu de
// cinco opciones , en la que el usuario deberá elegir una
//ADVERTENCIAS:
//********************************************************//

void ListadoSocio(int ContSocios,tRegSocio tablaSocio[],tRegPeli tablaPelis[],int ContBaja){

    int opcion;

    system("cls");

    do{
        printf("\tSUBMENU LISTADO DE SOCIOS\n\n");
        printf("1-Listado general\n");
        printf("2-Listado de nuevos socios registrados\n");
        printf("3-Listado de socios que tienen peliculas prestadas\n");
        printf("4-Informe de bajas de socios\n\n");
        printf("0-Volver al submenu Gestion de Socios\n\n");

        printf("Elija Opcion:");
        scanf("%i",&opcion);

        switch(opcion){
        case 1:ListadoGeneral(ContSocios,tablaSocio);
            break;
        case 2:ListadoNuevosSocios(ContSocios,tablaSocio,ContBaja);
            break;
        case 3:ListadoSociosConPelis(ContSocios,tablaSocio,tablaPelis);
            break;
        case 4:InformeBajas(ContSocios,tablaSocio,ContBaja);
            break;
        case 0: GestionSocios(ContSocios,tablaSocio,tablaPelis,ContBaja);
            break;
        }
    }while(opcion!=0);



}
//********************************************************//
//SUBPROGRAMA: ListadoGeneral
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma , es mostrar un listado de
//todos los socios con sus respectivas caracteristicas
//ADVERTENCIAS:
//********************************************************//

void ListadoGeneral(int ContSocios,tRegSocio tablaSocio[]){

    int i;
    system("cls");

    printf("Actualmente hay %i socio registrados\n\n",ContSocios);

    printf("\t\tLISTADO GENERAL DE SOCIOS\n\n");
    printf("DNI\tNombre y Apellidos\t\tF.Nacimiento\t Telefono\n");
    printf("___________________________________________________\n");

    for(i=0;i<ContSocios;i++){

        printf("%s\t%s %s %s\t\t%i/%i/%i\t%s\n",tablaSocio[i].Dni,tablaSocio[i].nombre,tablaSocio[i].apellido1,tablaSocio[i].apellido2,tablaSocio[i].FechaNac.dia,tablaSocio[i].FechaNac.mes,tablaSocio[i].FechaNac.ano,tablaSocio[i].telefono);
    }

    pausa();
    system("cls");

}
//********************************************************//
//SUBPROGRAMA: ListadoNuevosSocios
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma , es mostrar un listado de
// los socios que se han registrado en la aplicación
//ADVERTENCIAS:
//********************************************************//
void ListadoNuevosSocios(int ContSocios,tRegSocio tablaSocio[],int ContBaja){

    int i;
    int ContNuevo;
    system("cls");
    LeerNuevoSocio(tablaSocio,ContSocios,ContBaja);
    ContNuevo=ContSocios+ContBaja;


    pausa();
    system("cls");

    printf("\t\t LISTADO DE NUEVOS SOCIOS\n\n");
    printf("DNI\tNombre y Apellidos\t\t\tTelefono\t Fecha de Alta\n");
    printf("___________________________________________________\n");

    for(i=0;i<ContNuevo;i++){

        printf("%s\t%s %s %s\t\t\t%s\t%i-%i-%i\n",tablaSocio[i].Dni,tablaSocio[i].nombre,tablaSocio[i].apellido1,tablaSocio[i].apellido2,tablaSocio[i].telefono,tablaSocio[i].FechaAlta.dia,tablaSocio[i].FechaAlta.mes,tablaSocio[i].FechaAlta.ano);
    }


    pausa();
    system("cls");


}
//********************************************************//
//SUBPROGRAMA: ListadoSociosconPelis
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios , además de la tabla de peliculas , que
// corresponde al array de peliculas en las que como maximo se almacenaran
//200 peliculas
//OBJETIVO : El objetivo de este subprograma , será mostrar las peliculas
// que tienen en este momento los socios
//ADVERTENCIAS:
//********************************************************//

void ListadoSociosConPelis(int ContSocios,tRegSocio tablaSocio[],tRegPeli tablaPelis[]){


    int i;
    system("cls");

    printf("\t\t LISTADO DE SOCIOS CON PELICULAS PRESTADAS\n\n");

    printf("DNI\tNombre y Apellidos\t\tN. peliculas\t Titulo/s\n");
    printf("_____________________________________________________________________________\n");
    for(i=0;i<ContSocios;i++){
        if(tablaSocio[i].peliculas>=1){
            printf("%s\t%s %s %s \t\t%i\t%s\n",tablaSocio[i].Dni,tablaSocio[i].nombre,tablaSocio[i].apellido1,tablaSocio[i].apellido2,tablaSocio[i].peliculas,tablaPelis[i].titulo);
        }
    }
    pausa();
    system("cls");
}
//********************************************************//
//SUBPROGRAMA: InformeBajas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma es mostrar
// los socios los cuáles se han dado de baja en el subprogana
//ADVERTENCIAS: --
//********************************************************//

void InformeBajas(int ContSocios,tRegSocio tablaSocio[], int ContBaja){

   // LeerHcoSoc(tablaSocio,ContSocios,ContBaja); Cambiar forma

    int i, ano;
    int contador2018=0;
    int contador2019=0;
    int contador2020=0;
    int contador2021=0;
    int contador2022=0;


    system("pause");
    system("cls");


    printf("\t\tBienvenido a Informe Bajas\n\n ");
    fflush(stdin);
    printf("\t\tEl numero de bajas es de : %d\n\n",ContBaja);

    fflush(stdin);
    if(ContBaja==0){
        printf("No hay socios que se han dado de baja actualmente\n");
    }else{
            printf("INFORME BAJAS\n");
            printf("\tAño\t");
            printf("Numero de Bajas\n");
            printf("--------------------------------------------------------------\n");
        for(i=0;i<ContBaja;i++){
            if(tablaSocio[i].FechaBaja.ano==2018){
                contador2018++;
            }else{if(tablaSocio[i].FechaBaja.ano==2019){
                    contador2019++;
                }else{if(tablaSocio[i].FechaBaja.ano==2020){
                        contador2020++;
                    }else{if(tablaSocio[i].FechaBaja.ano==2021){
                            contador2021++;
                        }else{if(tablaSocio[i].FechaBaja.ano==2022){
                                contador2022++;
                            }
                        }
                    }
                }
            }
        }

        printf("\t2018\t%i\n",contador2018);
        printf("\t2019\t%i\n",contador2019);
        printf("\t2020\t%i\n",contador2020);
        printf("\t2021\t%i\n",contador2021);
        printf("\t2022\t%i\n",contador2022);
    }
        pausa();
        system("cls");


    }





//********************************************************//
//SUBPROGRAMA: LeerSocios
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este programa es actualizar la información
// es decir al principio del programa se copiará la información de
// el fichero pelis.dat al array tabla de socios.
//ADVERTENCIAS: Si el fichero Socios.dat , no se puede abrir
// se mostrara un mensaje de error y acontinuación se abortara el programa
//********************************************************//

void LeerSocios(tRegSocio tablaSocio[],int *ContSocios){

    FILE *fichLeerSocios;

    system("cls");


    fichLeerSocios = fopen("Socios.dat","rb");

    if(fichLeerSocios==NULL)
    {

        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        fichLeerSocios = fopen("Socios.dat","wb");

        printf("El fichero de Socios ya ha sido creado\n\n");


        printf("\n\t");
        system("pause");
    }
    else
    {
        fflush(stdin);

        if(fichLeerSocios==NULL)
                 {
                     printf("\n\nYa estamos en el final de fichero\n\n");
                 }

        else{
            fread(&tablaSocio[*ContSocios], sizeof(tRegSocio), 1, fichLeerSocios);
            while(!feof(fichLeerSocios)){
                *ContSocios= *ContSocios + 1;
                fread(&tablaSocio[*ContSocios], sizeof(tRegSocio), 1, fichLeerSocios);

            }
        }


        printf("\n\n\tVector de Socios actualizado\n");

        printf("El numero de Socios ya registrados es: %i",*ContSocios);
        getchar();


        printf("\n\t");
        system("pause");
    }

    fclose(fichLeerSocios);


}
//********************************************************//
//SUBPROGRAMA: GuardarSocios
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados,
// además de  la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma es escribir en el fichero
// Socios.dat todas las modificaciones que hayan sido realizado a lo largo
//del programa , para ello este subprograma volcará la información de el registro
// en el fichero socios.dat
//ADVERTENCIAS: Si el fichero Socios.dat , no se puede abrir
// se mostrara un mensaje de error y acontinuación se abortara el programa
//********************************************************//
void GuardarSocios(tRegSocio tablaSocio[],int ContSocios){

    int i;
    FILE *fichSociosGuardar;

    //printf("%i",*ContSocios);

    fichSociosGuardar=fopen("Socios.dat","wb");

    if(fichSociosGuardar==NULL)
    {

        printf("\n\tAtención, no se puede abrir el fichero... \n\n");
        exit(1);
    }

    else
    {
        fflush(stdin);
        for(i= 0 ;i < ContSocios; i++){
            fwrite(&tablaSocio[i] , sizeof(tRegSocio), 1, fichSociosGuardar);
        }

        printf("\n\n\tFichero guardado\n");
        printf("El numero de Socios ya registrados es: %i",ContSocios);
        getchar();
        pausa();

    }

    fclose(fichSociosGuardar);

}
//********************************************************//
//SUBPROGRAMA: LeerNuevoSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados , Contador
// bajas , esta variable almacena el numero de socios que se han dado
//de baja , y por último la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma es leer de el fichero
// los socios que hay almacenado en este fichero
//ADVERTENCIAS: Si el fichero LeerNuevoSocio , no se puede abrir
// se mostrara un mensaje de error y acontinuación se abortara el programa
//********************************************************//

void LeerNuevoSocio(tRegSocio tablaSocio[],int ContSocios,int ContBaja){

   char aux[120];
    FILE *Fich_nuevoSocio;
    int contador;

   /* contador= *ContSocios + *ContBaja;
    printf("El numero de bajas: %i\n",*ContBaja);
    printf("El numero de socios es de %i\n",*ContSocios);
    printf("El numero de Socios que hay en este fichero es: %i\n\n",contador);*/

    Fich_nuevoSocio=fopen("Nuevos Socios.TXT","r");


    if(Fich_nuevoSocio==NULL)
    {
        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        Fich_nuevoSocio = fopen("Nuevos Socios.TXT","wb");

        printf("El fichero ya ha sido creado\n\n");

    }else{
        fgets(aux,120,Fich_nuevoSocio);
       //while(!feof(Fich_nuevoSocio)){
        for(contador=0;!feof(Fich_nuevoSocio);contador++){
            strcpy(tablaSocio[contador].Dni,strtok(aux,"* "));
            strcpy(tablaSocio[contador].nombre,strtok(NULL," "));
            strcpy(tablaSocio[contador].apellido1,strtok(NULL," "));
            strcpy(tablaSocio[contador].apellido2,strtok(NULL," *"));
            strcpy(tablaSocio[contador].telefono,strtok(NULL," *"));
            tablaSocio[contador].FechaAlta.dia = atoi(strtok(NULL,"-"));
            tablaSocio[contador].FechaAlta.mes = atoi(strtok(NULL,"-"));
            tablaSocio[contador].FechaAlta.ano = atoi(strtok(NULL,"*"));
            fgets(aux,120,Fich_nuevoSocio);
        }

        printf("\n\n\tVector de Nuevos Socios actualizado\n");

        printf("El numero de Socios que hay en este fichero es: %i\n\n",contador);
    }

    fclose(Fich_nuevoSocio);
}
//********************************************************//
//SUBPROGRAMA: GuardarNuevoSocio
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados , Contador
// bajas , esta variable almacena el numero de socios que se han dado
//de baja , y por último la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma es guardar en el fichero
// de texto Nuevos Socios todos aquellos socios que hayan sido dados de
//alta en la aplicacion
//ADVERTENCIAS: Si el fichero GuardarNuevoSocio , no se puede abrir
// se mostrara un mensaje de error y acontinuación se abortara el programa
//********************************************************//
void GuardarNuevoSocio(tRegSocio tablaSocio[],int ContSocios,int ContBaja){

    int i,contador;

    contador= ContSocios + ContBaja;
    FILE *Fich_nuevoSocio;

    Fich_nuevoSocio=fopen("Nuevos Socios.TXT","w");


    if(Fich_nuevoSocio==NULL){
        printf("\t\tATENCION NO SE PUEDE ABRIR EL FCIHERO\n");
        exit(EXIT_FAILURE);
    }else{


       for(i=0;i<contador;i++){

                fprintf(Fich_nuevoSocio,"%s ",tablaSocio[i].Dni);
                fprintf(Fich_nuevoSocio,"%s ",tablaSocio[i].nombre);
                fprintf(Fich_nuevoSocio,"%s ",tablaSocio[i].apellido1);
                fprintf(Fich_nuevoSocio,"%s ",tablaSocio[i].apellido2);
                fprintf(Fich_nuevoSocio,"%s ",tablaSocio[i].telefono);
                fprintf(Fich_nuevoSocio,"%i-",tablaSocio[i].FechaAlta.dia);
                fprintf(Fich_nuevoSocio,"%i-",tablaSocio[i].FechaAlta.mes);
                fprintf(Fich_nuevoSocio,"%i\n",tablaSocio[i].FechaAlta.ano);

       }


        printf("\n\n\tVector de Nuevos Socios actualizado\n");

        printf("El numero de Socios ya registrados es: %i\n\n",contador); // NO Saca los Socios que realmente hay Error de paso de parametros
    }
    system("pause");
    fclose(Fich_nuevoSocio);
}
//SUBPROGRAMA: LeerHcoSoc
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados , Contador
// bajas , esta variable almacena el numero de socios que se han dado
//de baja , y por último la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma es leer la información
// que esta almacenada en el fichero correspondiente a los socios
// que se han dado de baja , y actualizar la tabla de socios
//ADVERTENCIAS: Si el fichero LeerSociosHistoricos , no se puede abrir
// se mostrara un mensaje de error y acontinuación se abortara el programa
//********************************************************//

void LeerHcoSoc(tRegSocio tablaSocio[],int *ContSocios,int *ContBaja){

    FILE *fichLeerHcoSoc;

    system("cls");


    fichLeerHcoSoc = fopen("HcoSoc.dat","rb");

    if(fichLeerHcoSoc==NULL)
    {

        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        fichLeerHcoSoc = fopen("HcoSoc.dat","wb");

        printf("El fichero de Baja de Socios ya ha sido creado\n\n");


        printf("\n\t");
        system("pause");
    }
    else
    {
        fflush(stdin);

        if(fichLeerHcoSoc==NULL)
                 {
                     printf("\n\nYa estamos en el final de fichero\n\n");
                 }

        else{
            fread(&tablaSocio[*ContBaja], sizeof(tRegSocio), 1, fichLeerHcoSoc);
            while(!feof(fichLeerHcoSoc)){
                    //*ContSocios=*ContSocios - 1;
                    *ContBaja= *ContBaja + 1;
                fread(&tablaSocio[*ContBaja], sizeof(tRegSocio), 1, fichLeerHcoSoc);

            }
        }


        printf("El numero de Socios ya borrados es: %i",*ContBaja);
        getchar();

        printf("\n\t");
        system("pause");
    }
    fclose(fichLeerHcoSoc);
}
//********************************************************//
//SUBPROGRAMA: GuardarHcoSoc
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Socios, esta es
// la variable que almacena el numero de socios registrados , Contador
// bajas , esta variable almacena el numero de socios que se han dado
//de baja , y por último la tabla de socios , que corresponde al array
// de como máximo 50 socios
//OBJETIVO :El objetivo de este subprograma es guardar en el fichero
//los socios que se dan de baja en la aplicación
//ADVERTENCIAS: Si el fichero GuardarSociosHistoricos , no se puede abrir
// se mostrara un mensaje de error y acontinuación se abortara el programa
//********************************************************//
void GuardarHcoSoc(tRegSocio tablaSocio[],int ContSocios,int ContBaja){

    int i;
    char dniaux;
    FILE *fichGuardarHcoSoc;

    fichGuardarHcoSoc=fopen("HcoSoc.dat","wb");

    if(fichGuardarHcoSoc==NULL)
    {

        printf("\n\tAtención, no se puede abrir el fichero... \n\n");
        exit(1);
    }

    else
    {
        fflush(stdin);
        for(i= 0 ;i < ContBaja; i++){
            fwrite(&tablaSocio[i] , sizeof(tRegSocio), 1, fichGuardarHcoSoc);
        }

        printf("\n\n\tFichero de Baja de Socios guardado\n");
        printf("El numero de Socios ya dados de baja es: %i",ContBaja);
        getchar();
        pausa();

    }

    fclose(fichGuardarHcoSoc);

}


//********************************************************//
//SUBPROGRAMA: MostrarPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar la información
// de una pelicula , para ello el usuario deberá introducir el código
// de dicha pelicula
//ADVERTENCIAS:
//********************************************************//
void MostrarPeliculas(tRegPeli tablaPelis[], int ContPelis){


    char codigoaux[5];
    int contador=0;
    char respuesta,confirmacion;

     system("cls");

    printf("-------------------------------------------------------------------------------------\n");
    printf("\n\t\tMOSTRAR PELICULA\n\n");
    printf("El numero de peliculas registrados es de %i\n\n",ContPelis);
    printf("---------------------------------------------------------------------------------------");

    if(ContPelis==0){
        printf("No hay peliculas registradas\n\n");
    }else{

        do{
            do{
                do{
                        printf("\n\nPara consultar la pelicula, debe introducir los siguientes datos:\n");
                        printf("\n");

                        printf("\nIntroduzca el codigo de la pelicula:");
                        fflush(stdin);
                        gets(codigoaux);

                        if(strlen(codigoaux)!=4)
                        {
                            printf("\t\t\nError, formato del codigo incorrecto. Introduzca el formato correcto(A123)\n");
                        }
                    }while(strlen(codigoaux)!=4);

                    contador=-1;
                    strupr(codigoaux);

                        do
                        {
                            contador++;
                            if(strcmp(tablaPelis[contador].codigo,codigoaux)!=0)
                            {
                                printf("Atencion ,este codigo esta registrado en la aplicacion\n\n");
                                system("cls");
                            }
                        }while((strcmp(tablaPelis[contador].codigo,codigoaux)!=0)&&(contador< ContPelis));


            }while(strcmp(tablaPelis[contador].codigo,codigoaux)!=0);

            printf("CODIGO ENCONTRADO\n\n\n\n");
            system("pause");
            system("cls");

            printf("\t\t\n\nDATOS PELICULA:\n");
            printf("\t\t\n\nCodigo : %s", tablaPelis[contador].codigo);
            printf("\t\t\n\nTitulo de la pelicula: %s",  tablaPelis[contador].titulo);
            printf("\t\t\n\n Director de la pelicula: %s", tablaPelis[contador].director);
            printf("\t\t\n\n Año de estreno de la pelicula : %s", tablaPelis[contador].ano);


            printf("\n\n\t¿Desea consultar mas peliculas?(S/N)");
            fflush(stdin);
            scanf("%c",&respuesta);
            respuesta = toupper(respuesta);


        }while(respuesta=='S');
    }

    system("pause");
    system("cls");



}
//********************************************************//
//SUBPROGRAMA:DevolucionPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO:
//ADVERTENCIAS:
//********************************************************//

void devolucionPeliculas(tRegPeli tablaPelis[], int ContPelis, int *ContPelisPrestadas, tRegSocio tablaSocio[], int ContSocios){

    char respuesta,confirmacion;
    int contador;
    char codigoaux[5];

    system("cls");

    printf("\t\tBienvenido a la Devolución de Peliculas...\n\n");
    printf("\t\tEl numero de peliculas es de : %d\n\n",ContPelis);
    printf("\t\tEl numero de peliculas prestadas es de : %d\n\n", *ContPelisPrestadas);
    pausa();
    system("cls");
    do{



            do{
                do{

                        printf("\nIntroduzca el código de la pelicula:");
                        fflush(stdin);
                        gets(codigoaux);

                        if(strlen(codigoaux)!=4)
                        {
                            printf("\n\nError.Formato del código incorrecto. Introduzca otro\n\n");
                        }
                    }while(strlen(codigoaux)!=4);

                    contador=-1;
                    strupr(codigoaux);

                        do
                        {
                            contador++;
                            if(strcmp(tablaPelis[contador].codigo,codigoaux)!=0)
                            {
                                printf("Atencion: Este codigo no esta registrado en la aplicación");
                            }
                        }while((strcmp(tablaPelis[contador].codigo,codigoaux)!=0)&&(contador< *ContPelisPrestadas));


            }while(strcmp(tablaPelis[contador].codigo,codigoaux)!=0);
            printf("Codigo de la pelicula encontrado \n\n");
            pausa();
            system("cls");

                printf("\t\tDATOS\n\n");
                printf("Codigo: %s\n\n",tablaPelis[contador].codigo);
                printf("¿Los datos son correctos?\n");
                fflush(stdin);
                scanf("%c",&confirmacion);
                if((confirmacion=='s')||(confirmacion=='S')){
                    tablaPelis[contador].prestada == FALSE;
                    *ContPelisPrestadas= *ContPelisPrestadas-1;

                    tablaSocio[contador].peliculas--;
                    strcpy(" ",tablaPelis[contador].DniCliente);

            }else{
                printf("\n\nProceso Abortado\n");
            }


            printf("¿Desea devolver mas peliculas?:");
            fflush(stdin);
            scanf("%c",&respuesta);

    printf("\nDEVOLUCION REALIZADA\n");
    printf("\nEl numero de peliculas prestadas es : %d",*ContPelisPrestadas);


    }while((respuesta=='S')||(respuesta=='s'));

    pausa();
    system("cls");


}



//********************************************************//
//SUBPROGRAMA: PrestamoPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO:
//ADVERTENCIAS:
//********************************************************//
void PrestamoPeliculas(tRegPeli tablaPelis[], int ContPelis,int *ContPelisPrestadas,tRegSocio tablaSocio[],int ContSocios,int Alquiler[5][12]){

    char respuesta,confirmacion;
    int contador=0;
    int contador2=0;
    char dniaux[10];
    char codigoaux[5];

    system("cls");

    printf("\t\tBienvenido al Prestamo de Peliculas\n\n");
    printf("\t\tEl numero de peliculas es de : %d\n\n",ContPelis);
    printf("\t\tEl numero de peliculas prestadas es de : %d\n\n", *ContPelisPrestadas);
    pausa();
    system("cls");
    ListadoPeliculasPrestadas(tablaPelis,ContPelis,ContPelisPrestadas);
    pausa();
    system("cls");
    printf("\t\tPRESTAMO PELICULAS\n");
do{
    do{
                do{

                        printf("\nIntroduzca el dni de la persona:");
                        fflush(stdin);
                        gets(dniaux);

                        if(strlen(dniaux)!=9)
                        {
                            printf("\n\nError.Formato del DNI incorrecto, Escriba otro\n\n");
                        }
                    }while(strlen(dniaux)!=9);

                    contador=-1;
                    strupr(dniaux);

                        do
                        {
                            contador++;
                            if(strcmp(tablaSocio[contador].Dni,dniaux)!=0)
                            {
                                printf("Atencion: Este dni no esta registado en la aplicacion");
                                system("cls");
                            }
                        }while((strcmp(tablaSocio[contador].Dni,dniaux)!=0)&&(contador< ContSocios));


            }while(strcmp(tablaSocio[contador].Dni,dniaux)!=0);
            printf("DNI de la persona encontrado\n\n");


            do{
                do{

                        printf("\nIntroduzca el código de la pelicula:");
                        fflush(stdin);
                        gets(codigoaux);

                        if(strlen(codigoaux)!=4)
                        {
                            printf("\n\nError.Formato del código incorrecto. Introduzca otro\n\n");
                        }
                    }while(strlen(codigoaux)!=4);

                    contador2=-1;
                    strupr(codigoaux);

                        do
                        {
                            contador2++;
                            if(strcmp(tablaPelis[contador2].codigo,codigoaux)!=0)
                            {
                                printf("Atencion: Este codigo no esta registrado en la aplicación");
                                system("cls");
                            }
                        }while((strcmp(tablaPelis[contador2].codigo,codigoaux)!=0)&&(contador2< ContPelis));


            }while(strcmp(tablaPelis[contador2].codigo,codigoaux)!=0);
            printf("Codigo de la pelicula encontrado \n\n");


            printf("\t\nFECHA DE PRESTAMO\n\n\n");
            printf("Introduce el dia :");
            scanf("%d",&tablaPelis[contador2].FechaEntrega.dia);
            printf("Introduce el mes:");
            scanf("%d",&tablaPelis[contador2].FechaEntrega.mes);
            printf("Introduce el año:");
            scanf("%d",&tablaPelis[contador2].FechaEntrega.ano);

                pausa();
                system("cls");


                printf("\tDATOS\n\n");
                printf("DNI del socio: %s\n\n",tablaSocio[contador].Dni);
                printf("Codigo pelicula: %s\n\n",tablaPelis[contador2].codigo);
                printf("¿Los datos son correctos?\n");
                fflush(stdin);
                scanf("%c",&confirmacion);
                if((confirmacion=='s')||(confirmacion=='S')){

                    tablaPelis[contador2].prestada= TRUE;
                    ActualizarMatriz(tablaPelis,ContPelis,Alquiler,contador2);

                    tablaSocio[contador].peliculas++;
                    *ContPelisPrestadas=*ContPelisPrestadas+1;
                     printf("El numero de peliculas prestadas es : %i\n\n",*ContPelisPrestadas);
                     strcpy(tablaPelis[contador2].DniCliente,tablaSocio[contador].Dni);

                }else{
                    printf("\tProceso Abortado\n");
                }



            printf("¿Desea prestar mas peliculas\n");
            fflush(stdin);
            scanf("%c",&respuesta);

    }while((respuesta=='S')||(respuesta=='s'));

    pausa();
    system("cls");
}



//********************************************************//
//SUBPROGRAMA: SubmenuListadoPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar un menu de
// cinco opciones , en la que el usuario deberá elegir una
//ADVERTENCIAS:
//********************************************************//
void SubmenuListadoPeliculas(tRegPeli tablaPelis[],int ContPelis, int ContPelisPrestadas,tRegSocio tablaSocio[],int ContSocios,int Alquiler[5][12],int contador2){
     int opcion;
    system("cls");

    printf("\t\t\nBienvenido al Submenu Listado de Peliculas:\n");
    system("pause");
    system("cls");


    do{
        printf("\t\t\t\nSUBMENU LISTADO DE PELICULAS\n");
        printf("\t\t1.Listado General\n");
        printf("\t\t2.Listado de peliculas no prestadas\n");
        printf("\t\t3.Listado peliculas prestadas\n");
        printf("\t\t4.Listado de peliculas por titulo\n");
        printf("\t\t5.Listado de peliculas por año\n");
        printf("\t\t6.Informe de prestamos\n");
        printf("\t\t0.Volver al submenu Gestion de peliculas\n");

        printf("Eliga una opcion:");
        scanf("%d",&opcion);

            switch(opcion){

            case 1: ListadoGeneralPeliculas(tablaPelis,ContPelis,ContPelisPrestadas);
                break;

            case 2: ListadoPeliculasnoPrestadas(tablaPelis,ContPelis,ContPelisPrestadas);
                break;

            case 3: ListadoPeliculasPrestadas(tablaPelis,ContPelis,&ContPelisPrestadas);
                break;

            case 4:ListadoPeliculasPorTitulo(tablaPelis,ContPelis);
                break;

            case 5:Listadopeliculasa(tablaPelis,ContPelis);
                break;

            case 6:InformePrestamos(tablaPelis,ContPelis,ContPelisPrestadas,Alquiler, contador2);
                break;

            case 0: GestionPelis(tablaPelis, ContPelis, ContPelisPrestadas,tablaSocio,ContSocios,Alquiler,contador2);
            default: printf("La opción que has elegido es incorrecta (0-5)\n");


            }
    }while(opcion!=0);
}



//********************************************************//
//SUBPROGRAMA: ListadoGeneralPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar un listado
//con todas lass peliculas que han sido registradas en la aplicacion
//con todas sus caracteristicas
//ADVERTENCIAS:
//***************************************************   *****//
void ListadoGeneralPeliculas(tRegPeli tablaPelis[], int ContPelis,int ContPelisPrestadas){

    int i;

    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\nLISTADO GENERAL PELICULAS\n");
    printf("----------------------------------------------------------------------------------------------------------------------");
    printf("\n");



    printf("Codigo\t");
    printf("Titulo\t\t\t\t");
    printf("Director\t\t");
    printf("Año estreno\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    for(i=0; i<ContPelis; i++){
        printf("%s\t", tablaPelis[i].codigo);
        printf("%s\t\t\t", tablaPelis[i].titulo);
        printf("%s\t\t\t", tablaPelis[i].director);
        printf("%s\n", tablaPelis[i].ano);


    }
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");
    printf("NUMERO TOTAL PELICULAS: %d\n",ContPelis);
    printf("----------------------------------------------------------------------------------------------------------------------------");
    printf("\n");

    system("pause");
    system("cls");

}
//********************************************************//
//SUBPROGRAMA: ListadoPeliculasnoPrestadas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar las peliculas
//las cuáles no han sido prestadasºººººº
//********************************************************//
void ListadoPeliculasnoPrestadas(tRegPeli tablaPelis[], int ContPelis, int ContPelisPrestadas){

    system("cls");

    int i, ContPelisnoPrestadas=0;
    ContPelisnoPrestadas= ContPelis-ContPelisPrestadas;



    printf("\t\t\tLISTADO PELICULAS NO PRESTADAS\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("\t\tEl numero de peliculas es de : %d\n\n",ContPelis);
    printf("-----------------------------------------------------------------------------------------\n");



    printf("Codigo\t");
    printf("Titulo\t\t\t\t");
    printf("Director\t");
    printf("Año estreno\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    for(i=0; i<ContPelis; i++){
        if(tablaPelis[i].prestada==FALSE){
            printf("%s\t", tablaPelis[i].codigo);
            printf("%s\t\t", tablaPelis[i].titulo);
            printf("%s\t\t\t", tablaPelis[i].director);
            printf("%s\n", tablaPelis[i].ano);
        }

    }

    pausa();
    system("cls");
    }
//********************************************************//
//SUBPROGRAMA: ListadoPeliculasprestadas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar lass peliculas
//que han sido prestadas
//ADVERTENCIAS:
//********************************************************//

void ListadoPeliculasPrestadas(tRegPeli tablaPelis[], int ContPelis, int *ContPelisPrestadas){
    int i;

    system("cls");


     printf("------------------------------------------------------------------------------------\n");
     printf("\t\t\nLISTADO PELICULAS PRESTADAS\n");
     printf("\t\t\nEl numero total de peliculas es de: %d\n\n",ContPelis);
     printf("\t\t\nEl numero total de peliculas prestadas es de : %d\n\n",*ContPelisPrestadas);
     printf("---------------------------------------------------------------------------------------\n");


    if(*ContPelisPrestadas==0){
        printf("No hay peliculas prestadas\n");
    }else{
        printf("Codigo\t");
        printf("Titulo\t\t\t");
        printf("Dni Cliente\n");

        for(i=0;i<ContPelis;i++){
            if(tablaPelis[i].prestada==TRUE){
                printf("%s\t",tablaPelis[i].codigo);
                printf("%s\t\t\t",tablaPelis[i].titulo);
               // printf("%s\n",tablaSocios[i].DniCliente);
            }
        }

    }

        printf("\n");
        pausa();
        system("cls");
}



//********************************************************//
//SUBPROGRAMA: ListadoPeliculasPorTitulo
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar las caracteristicas
//de una pelicula , la cual es buscada a través del titulo;
//el usuario deberá introducir un titulo , y a continuación se mostrara
//por pantalla todas las peliculas con ese titulo además de sus caracteristicas
//ADVERTENCIAS:
//********************************************************//
void ListadoPeliculasPorTitulo(tRegPeli tablaPelis[], int ContPelis){

    system("cls");


    char tituloaux[30],respuesta;
    int contador;

    printf("----------------------------------------------------------------------------------\n");
    printf("\t\t\t\nLISTADO PELICULAS POR TITULO \n\n\n");
    printf("El numero de peliculas registradas es: %d\n\n\n", ContPelis);
    printf("--------------------------------------------------------------------------------------");


    if(ContPelis==0){
        printf("\nLo sentimos, en este momento no ha peliculas registradas \n");
        system("pause");
        system("cls");
    }else{
            do{

                    printf("\nIntroduzca el titulo de la pelicula:");
                    fflush(stdin);
                    gets(tituloaux);

                    contador=-1;
                    strupr(tituloaux);
                    do{
                        contador++;
                        if(strcmp(tituloaux,tablaPelis[contador].titulo)==0){
                            printf("Titulo encontrado\n\n");
                            pausa();
                            system("cls");

                            printf("Datos de la pelicula:\n\n");
                            printf("Codigo pelicula: %s\n", tablaPelis[contador].codigo);
                            printf("Titulo pelicula: %s\n", tablaPelis[contador].titulo);
                            printf("Director pelicula: %s\n", tablaPelis[contador].director);
                            printf("Ano estreno pelicula: %s\n", tablaPelis[contador].ano);
                }
        }while(strcmp(tituloaux,tablaPelis[contador].titulo)!=0);

        printf("¿Desea consultar mas peliculas:");
        scanf("%c",&respuesta);

    }while((respuesta=='s')||(respuesta=='S'));


    printf("\n\nSaliendo de Listado de peliculas por titulo\n");
    pausa();
    system("cls");
}

}

//********************************************************//
//SUBPROGRAMA:ListadoPeliculasa
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es mostrar por pantalla
// las peliculas que tengan el mismo año de estreno , es decir
//el usuario introduce un año de estreno y a continuación se mostrara
//todas las peliculas con ese año de estreno y sus caracteristicas
//ADVERTENCIAS:
//********************************************************//
 void Listadopeliculasa(tRegPeli tablaPelis[], int ContPelis){

    system("pause");
    system("cls");
    printf("El numero de peliculas registradas es: %d\n\n\n", ContPelis);

    char anoaux[5], respuesta;
    int contador=-1;


    printf("\tLISTADO PELICULAS AÑO\n\n\n");

    if(ContPelis==0){
        printf("\nLo sentimos, en este momento no ha peliculas registradas \n");
        system("pause");
        system("cls");
    }else{
        do{



            printf("\nIntroduzca el año de estreno  de la pelicula:");
            fflush(stdin);
            gets(anoaux);

            for(contador=0;contador<ContPelis;contador++){
                if(strcmp(anoaux,tablaPelis[contador].ano)==0){

                    printf("Codigo  pelicula: %s\n", tablaPelis[contador].codigo);
                    printf("Titulo pelicula: %s\n", tablaPelis[contador].titulo);
                    printf("Director pelicula: %s\n", tablaPelis[contador].director);
                    printf("Año estreno  pelicula: %s\n", tablaPelis[contador].ano);
                    printf("----------------------------------------\n\n");
                }

                printf("¿Desea consultar mas peliculas:");
                fflush(stdin);
                scanf("%c",&respuesta);
                }
    }while((respuesta=='S')||(respuesta=='s'));

    }

    printf("\n\nSaliendo del Listado de peliculas por año\n");
    pausa();
    system("cls");
}


//********************************************************//
//SUBPROGRAMA: LeerPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma , es leer las peliculas
//las cuales estan almacenadas en el fichero .dat y pasarlas al
// array de peliculas
//ADVERTENCIAS: Si el fichero pelis.dat no se puede abrir
//se mostrara un mensaje de error por pantalla y se abortara
//el programa
//********************************************************//
void LeerPeliculas(tRegPeli tablapelis[], int *Contpelis){

    FILE *fichLeerPelis;

    system("cls");


    fichLeerPelis = fopen("Peliculas.dat","rb");

    if(fichLeerPelis==NULL)
    {

        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        fichLeerPelis = fopen("Peliculas.dat","wb");

        printf("El fichero de Peliculas ya ha sido creado\n\n");


        printf("\n\t");
        system("pause");
    }
    else
    {
        fflush(stdin);

        if(fichLeerPelis==NULL)
                 {
                     printf("\n\nYa estamos en el final de fichero\n\n");
                 }

        else{

            fread(&tablapelis[*Contpelis], sizeof(tRegPeli), 1, fichLeerPelis);
            while(!feof(fichLeerPelis)){
                *Contpelis= *Contpelis + 1;
                fread(&tablapelis[*Contpelis], sizeof(tRegPeli), 1, fichLeerPelis);

            }
        }


        printf("\n\n\tVector de Peliculas actualizado\n");

        printf("El numero de Peliculas ya registrados es: %i",*Contpelis);
        getchar();


        printf("\n\t");
        system("pause");
    }

    fclose(fichLeerPelis);


}



//********************************************************//
//SUBPROGRAMA: GuardarPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es cargar lass peliculas
//del array de peliculas al fichero pelis.dat
//ADVERTENCIAS:Si el fichero no se puede abrir se mandara
//un mensaje de error y se abortara el programa
//********************************************************//


void GuardarPeliculas(int Contpelis, tRegPeli tablapelis[]){

     int i;
    FILE *fichPelisGuardar;

    printf("%i",Contpelis);

    fichPelisGuardar=fopen("Peliculas.dat","wb");

    if(fichPelisGuardar==NULL)
    {

        printf("\n\tAtención, no se puede abrir el fichero... \n\n");
        exit(1);
    }

    else
    {
        fflush(stdin);
        for(i= 0 ;i < Contpelis; i++){
            fwrite(&tablapelis[i] , sizeof(tRegPeli), 1, fichPelisGuardar);
        }

        printf("\n\n\tFichero guardado\n");
        printf("El numero de Peliculas ya registrados es: %i",Contpelis);
        getchar();
        pausa();

    }

    fclose(fichPelisGuardar);



}


//********************************************************//
//SUBPROGRAMA: ImportarPeliculas
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO: El objetivo de este subprograma es leer los datos los
//cuáles proceden del fichero de texto pelis.txt y pasarla al array
//de peliculas
//ADVERTENCIAS:Si el fichero pelis.txt no se puede abrir , se mostrara
//un mensaje de error y se abortara el programa
//********************************************************//
void ImportarPeliculas(tRegPeli tablapelis[], int *Contpelis){


    system("cls");
    printf("-----------------------------------------------------------------------\n");
    printf("\t\t\nIMPORTAR PELICULAS\n");
    printf("El numero de peliculas es de : %d\n",*Contpelis);
    printf("------------------------------------------------------------------------");

    tRegPeli tablapelisauxiliar[MAXPELIS];
    int contador,i,j,longitud;
    char aux[40];

    FILE *ficheroimportar;

    ficheroimportar= fopen("Pelis.txt","r");

    if(ficheroimportar==NULL){
        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        exit(EXIT_FAILURE);

    }else{


                for(i=0;!feof(ficheroimportar);i++){
                    fgets(tablapelisauxiliar[i].codigo,5,ficheroimportar);

                    fgets(aux,40,ficheroimportar);

                    fgets(tablapelisauxiliar[i].titulo,41,ficheroimportar);
                    longitud= strlen(tablapelisauxiliar[i].titulo);
                    tablapelisauxiliar[i].titulo[longitud-1]='\0';

                    fgets(tablapelisauxiliar[i].director,41,ficheroimportar);
                    longitud= strlen(tablapelisauxiliar[i].director);
                    tablapelisauxiliar[i].director[longitud-1]='\0';

                    fgets(tablapelisauxiliar[i].ano,41,ficheroimportar);
                    longitud= strlen(tablapelisauxiliar[i].ano);
                    tablapelisauxiliar[i].ano[longitud-1]='\0';




                    strupr(tablapelisauxiliar[i].titulo);

                    strcpy(tablapelis[*Contpelis].codigo,tablapelisauxiliar[i].codigo);
                    strcpy(tablapelis[*Contpelis].titulo,tablapelisauxiliar[i].titulo);
                    strcpy(tablapelis[*Contpelis].director,tablapelisauxiliar[i].director);
                    strcpy(tablapelis[*Contpelis].ano,tablapelisauxiliar[i].ano);


                    *Contpelis=*Contpelis+1;


                }
            for(j=0;j<*Contpelis;j++){
             printf("Codigo:%s\n",tablapelis[j].codigo);
             printf("Titulo:%s\n",tablapelis[j].titulo);
             printf("Director:%s\n",tablapelis[j].director);
             printf("Año estreno:%s\n",tablapelis[j].ano);
            }


        fclose(ficheroimportar);


            pausa();
            system("cls");

            printf("Se ha copiado el los datos al array de peliculas\n");
            printf("Vector de peliculas actualizadas\n");
            printf("El numero de peliculas es de : %d\n",*Contpelis);



    }
    pausa();
    system("cls");



}




//********************************************************//
//SUBPROGRAMA:Inicializar
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas
//OBJETIVO:El objetivo de este subprograma es inicializar la el campo
//prestada del registro peliculas a FALSE , para que todas las peliculas
//antes de que se desarrolle la aplicación se considera que no estan
//prestdas
//********************************************************//
void Inicializar(tRegPeli tablapelis[], int ContPelis){

    int i,j;
    for(i=0;i<=ContPelis;i++){
        tablapelis[i].prestada=FALSE;

    }

}
//********************************************************//
//SUBPROGRAMA:Inicializar Matriz
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS:Pasamos como parametro la matriz alquilar
//Alquiler junto con el contador2 que se utiliza para recorrer dicha matriz
//OBJETIVO:El objetivo de este subprograma es inicializar la matriz a 0
//es decir ttodas las posiciones de la matriz a 0
//********************************************************//
void InicializarMatriz(int Alquiler[5][12]){

    int i,j;

    for(i=0;i<=4;i++){
        for(j=0;j<=11;j++){
            fflush(stdin);
            Alquiler[i][j]=0;

        }
    }
}
//********************************************************//
//SUBPROGRAMA:Actualizar Matriz
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas, ademas pasamos como parametro la matriz
//Alquiler junto con el contador2 que se utiliza para recorrer dicha matriz
//OBJETIVO:El objetivo de este subprograma es actualizar la matriz , cuando se
//realizan prestamos o devolucones
//********************************************************//

void ActualizarMatriz(tRegPeli tablaPelis[], int ContPelis, int Alquiler[5][12], int contador2){

    int mes=0;
    int ano=0;
    int i,j;

    mes=tablaPelis[contador2].FechaEntrega.mes;
    ano=tablaPelis[contador2].FechaEntrega.ano;

    printf("La peliculas se alquila el mes %i y el año %i",mes,ano);
    pausa();

    if(ano==2018)
        ano=0;
    if(ano==2019)
        ano=1;
    if(ano==2020)
        ano=2;
    if(ano==2021)
        ano=3;
    if(ano==2022)
        ano=4;


    Alquiler[ano][mes]++;
    system("cls");

    for(i=0;i<=4;i++){
        for(j=0;j<=11;j++){
            printf("El año %i en el mes %i:",i,j);
            printf("%i\n",Alquiler[i][j]);
            pausa();
        }
    }
}
//********************************************************//
//SUBPROGRAMA:LeerMatriz
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como paramtero la matriz alquilar
//OBJETIVO:El objetivo de este subprograma es leer la matriz
//en el fichero binario HcoPrest.dat
//ADVERTENCIAS:
//********************************************************//

void LeerMatriz(int Alquiler[5][12]){
    int i,j;
    FILE *fichero;

    pausa();
    system("cls");

    fichero= fopen("Alquiler.dat","rb");

    if(fichero== NULL){
        printf("\n\tAtención, no se puede abrir el fichero... \n\n");

        fichero = fopen("Alquiler.dat","wb");

        printf("El fichero prestamos matrices se ha creado\n\n");


        printf("\n\t");
        system("pause");
    }else{
        fread(Alquiler,sizeof(int),60,fichero);
            }


    fclose(fichero);

    printf("Se ha leido la matriz de alquiler correctamente\n");
    pausa();
    system("cls");

    }
//********************************************************//
//SUBPROGRAMA:GuardarMatriz
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como paramtero la matriz alquilar
//OBJETIVO:El objetivo de este subprograma es guardar la matriz
//en el fichero binario HcoPrest.dat
//ADVERTENCIAS:
//********************************************************//

void GuardarMatriz(int Alquiler[5][12]){

    system("cls");
    int i,j;

    FILE *fichero;

    pausa();
    system("cls");

    fichero= fopen("Alquiler.dat","wb");
    if(fichero==NULL){
        printf("\t\tNo se puede abrir el fichero\n");
        exit(EXIT_FAILURE);


    }else{

        fwrite(Alquiler,sizeof(int),60,fichero);
    }

    fclose(fichero);
    printf("Se ha guardado la matriz de alquiler correctamente\n");
    pausa();
    system("cls");
}
//********************************************************//
//SUBPROGRAMA:Informe Prestamos
//TIPO: Procedimiento (Funcion tipo void)
//PRERREQUISITOS: Pasamos como parametro el Contador de Peliculas, esta es
// la variable que almacena el numero de peliculas registradas,
// además de  la tabla de peliculas , que corresponde al array
// de como máximo 200 peliculas, ademas pasamos como parametro la matriz
//Alquiler junto con el contador2 que se utiliza para recorrer dicha matriz
//OBJETIVO:El objetivo de este subprograma es mostrar por pantalla los prestamos
//que se han realizado durante el desarrollo de la aplicacion
//ADVERTENCIAS:
//********************************************************//

void InformePrestamos(tRegPeli tablaPelis[], int ContPelis, int ContPelisPrestadas,int Alquiler[5][12], int contador2){
      int i,j,k;
    int contador=0;
    int contador2018=0;
    int contador2019=0;
    int contador2020=0;
    int contador2021=0;
    int contador2022=0;


    system("pause");
    system("cls");


    printf("\t\tBienvenido a Informe Prestamos\n\n ");
    fflush(stdin);


    fflush(stdin);
    if(ContPelisPrestadas==0){
        printf("No hay peliculas prestadas actualmente\n");
    }else{
            printf("INFORME PRESTAMOS\n");
            printf("\tAño\t");
            printf("Numero de prestamos\n");
            printf("--------------------------------------------------------------\n");

            for(i=0;i<ContPelisPrestadas;i++){
                if(tablaPelis[i].FechaEntrega.ano==2018){
                    contador2018++;
                }else if(tablaPelis[i].FechaEntrega.ano==2019){
                    contador2019++;
                }else if(tablaPelis[i].FechaEntrega.ano==2020){
                    contador2020++;
                }else if(tablaPelis[i].FechaEntrega.ano==2021){
                    contador2021++;
                }else if(tablaPelis[i].FechaEntrega.ano==2022){
                    contador2022++;
                }
            }



        }

        printf("\t2018\t%i\n",contador2018);
        printf("\t2019\t%i\n",contador2019);
        printf("\t2020\t%i\n",contador2020);
        printf("\t2021\t%i\n",contador2021);
        printf("\t2022\t%i\n",contador2022);

        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("Numero total prestamos: %d\n",ContPelisPrestadas);
        printf("---------------------------------------------------------------------------------------------------------\n");
        pausa();
        system("cls");

}








