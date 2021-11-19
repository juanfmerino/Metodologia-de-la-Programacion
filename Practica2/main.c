#include <stdio.h>
#include <stdlib.h>

#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

//**********************************************************************************************************************
//Juan de Frutos Merino
// Ainhoa Merino Gomez
// Grupo                                       Fecha:26/04/2020
//****************************************************************************************************



void MensajeDespedida();
void pausa();
void MensajeBienvenida();
void PeticionDatos(char cadena1[30],char cadena2[30],char cadena3[30],int numeros1[5],int numeros2[5]);

void ContarApariciones(char cadena1[30],char cadena2[30],char cadena3[30]);
int  Contar(char cadenaselcc[30],char caracter,int i,int contador);

void CambiarCaracteres(char cadena1[30],char cadena2[30],char cadena3[30]);
void Cambiar(char cadenamod[30],int num,int t,int j,char caracternuevo[5],char caracterviejo[5]);

void ReducirCadena(char cadena1[30],char cadena2[30],char cadena3[30]);
void Reducir(char cadenaselcc[30],char cadenamod[30],int i);

void MostrarPosicionTotalImpares(int numeros1[5],int numeros2[5]);
void Impares(int numeroselc[5],int i,int *contImp,int *confirmacion,int t,int *posicion);

int main()
{
    int opcion;

    char cadena1[30];
    char cadena2[30];
    char cadena3[30];
    int numeros1[5];
    int numeros2[5];

    MensajeBienvenida();
    system("cls");
    do{

        printf("MENU RECURSIVIDAD\n\n");

        printf("1.-Peticion de datos\n");
        printf("2.-Contar Apariciones\n");
        printf("3.-Reemplazar Caracteres\n");
        printf("4.-Eliminar un caracter repetido\n");
        printf("5.-Mostrar posicion total impares\n\n");
        printf("0.-Salir\n\n");

        printf("Elija Opcion:");
        scanf("%i",&opcion);

        switch(opcion){
            case 1:PeticionDatos(cadena1,cadena2,cadena3,numeros1,numeros2);
                break;
            case 2:ContarApariciones(cadena1,cadena2,cadena3);
                break;
            case 3:CambiarCaracteres(cadena1,cadena2,cadena3);
                break;
            case 4:ReducirCadena(cadena1,cadena2,cadena3);
                break;
            case 5:MostrarPosicionTotalImpares(numeros1,numeros2);
                break;
            case 0:MensajeDespedida();
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


void PeticionDatos(char cadena1[30],char cadena2[30],char cadena3[30],int numeros1[5],int numeros2[5]){

    char cadenaux1[30];
    char cadenaux2[30];
    char cadenaux3[30];
    int numerosaux[10];
    int i,j,k,p;
    int t=0;
    int repetir;
    system("cls");

    printf("BIENVENIDO A LA PETICION DE DATOS\n\n\n");

    printf("\nIntroduce la cadena de caracteres 1:");
    fflush(stdin);
    gets(cadenaux1);

    printf("\n\nIntroduce la cadena de caracteres 2:");
    fflush(stdin);
    gets(cadenaux2);

    printf("\n\nIntroduce la cadena de caracteres 3:");
    fflush(stdin);
    gets(cadenaux3);


    strcpy(cadena1,cadenaux1);
    strcpy(cadena2,cadenaux2);
    strcpy(cadena3,cadenaux3);

    pausa();
    system("cls");

    do{
        repetir=0;
        printf("Debes introducir 10 numeros distintos:\n\n");
        for(j=0;j<10;j++){
                printf("\nIntroduzca el numero en la posicion %i:",j);
                fflush(stdin);
                scanf("%i",&numerosaux[j]);
            }
    for(t=0;t<5;t++){
        for(p=5;p<10;p++){
            if(numerosaux[t]==numerosaux[p]){
                repetir=1;
                printf("Numero repetido. Introduzca de nuevo los numeros.\n\n");
                pausa();
                system("cls");
                }
            }
        }
    }while(repetir==1);

    i=0;

    do{
        numeros1[i]=numerosaux[i];
        i++;
    }while(i<5);

    do{
        numeros2[i-5]=numerosaux[i];
        i++;
    }while(i<10);

    system("cls");
    printf("La cadena de caracteres 1 es: %s\n",cadena1);
    printf("La cadena de caracteres 2 es: %s\n",cadena2);
    printf("La cadena de caracteres 3 es: %s\n",cadena3);

    printf("El primer array de numeros es:");
    for(k=0;k<5;k++){
        printf("%i ",numeros1[k]);
    }

    printf("\nEl segundo array de numeros es:");
    for(k=0;k<5;k++){
        printf("%i ",numeros2[k]);
    }

    pausa();
    system("cls");

}

void ContarApariciones(char cadena1[30],char cadena2[30],char cadena3[30]){


    system("cls");

    char cadenaselcc[30];
    int opcion;
    char caracter;
    int contador=0;
    int i=0;

    printf("BIENVENIDO A CONTAR APARICIONES\n\n");

    do{
        printf("Primero deberas seleccionar una de las cadenas:\n\n");

        printf("Cadena 1: %s\n",cadena1);
        printf("Cadena 2: %s\n",cadena2);
        printf("Cadena 3: %s\n",cadena3);

        printf("Selecciona una cadena:");
        scanf("%i",&opcion);

        if(opcion==1){
            strcpy(cadenaselcc,cadena1);
        }else{if(opcion==2){
                strcpy(cadenaselcc,cadena2);
            }else{if(opcion==3){
                    strcpy(cadenaselcc,cadena3);
                }else{
                    printf("\n\nDebes escoger una cadena de 1-3\n\n");
                    pausa();
                    system("cls");
                }
            }
        }
    }while((opcion!=1)&&(opcion!=2)&&(opcion!=3));

    printf("La cadena seleccionada es: %s\n\n",cadenaselcc);

    pausa();
    system("cls");

    printf("Introduce el caracter que quieres contabilizar:");
    fflush(stdin);
    scanf("%c",&caracter);

    contador=Contar(cadenaselcc,caracter,i,contador);

    printf("\n\nEl caracter '%c' aparece %i veces ",caracter,contador);
    printf("en la cadena '%s'\n\n",cadenaselcc);

    pausa();
    system("cls");

}

//*******************************************************************************************************************
//Subprograma:Contar                                 Tipo:funcion
//Objetivo: contar apariones de una carcter
//Prerequisito: char caracter, char cadenaselecc
//Valor retornado: contador
//*******************************************************************************************************************

int  Contar(char cadenaselcc[30],char caracter,int i,int contador){


    if(i<strlen(cadenaselcc)){
        if(cadenaselcc[i]==caracter){
                contador++;
           return Contar(cadenaselcc,caracter,i+1,contador);
        }else{
           return  Contar(cadenaselcc,caracter,i+1,contador);
        }
    }else
    return contador;
}

void CambiarCaracteres(char cadena1[30],char cadena2[30],char cadena3[30]){

    system("cls");

    char cadenaselcc[30];
    int opcion;
    int i=0;
    int num=0;
    int j,t;

    char caracternuevo[5];
    char caracterviejo[5];
    char cadenamod[30];


    printf("BIENVENIDO A CAMBIAR CARACTERES\n\n");

    do{
        printf("Primero deberas seleccionar una de las cadenas:\n\n");

        printf("Cadena 1: %s\n",cadena1);
        printf("Cadena 2: %s\n",cadena2);
        printf("Cadena 3: %s\n",cadena3);

        printf("Selecciona una cadena:");
        scanf("%i",&opcion);

        if(opcion==1){
            strcpy(cadenaselcc,cadena1);
        }else{if(opcion==2){
                strcpy(cadenaselcc,cadena2);
            }else{if(opcion==3){
                    strcpy(cadenaselcc,cadena3);
                }else{
                    printf("\n\nDebes escoger una cadena de 1-3\n\n");
                    pausa();
                    system("cls");
                }
            }
        }
    }while((opcion!=1)&&(opcion!=2)&&(opcion!=3));

    printf("La cadena seleccionada es: %s\n\n",cadenaselcc);

    printf("Cuantos caracteres deseas cambiar??\n");
    fflush(stdin);
    scanf("%i",&num);

    for(i=0;i<num;i++){
        printf("\nIntroduzca el caracter nuevo numero %i:",i+1);
        fflush(stdin);
        scanf("%c",&caracternuevo[i]);

        printf("\nIntroduzca el caracter a cambiar numero %i:",i+1);
        fflush(stdin);
            scanf("%c",&caracterviejo[i]);
    }

    strcpy(cadenamod,cadenaselcc);
    j=0;
    t=0;

    Cambiar(cadenamod,num,t,j,caracternuevo,caracterviejo);

    printf("\n\nCadena de caracteres ORIGINAL: %s\n\n",cadenaselcc);
    printf("Cadena de caracteres MODIFICADA: %s",cadenamod);

    pausa();
    system("cls");

}

//*******************************************************************************************************************
//Subprograma:Cambiar                                 Tipo:procedimiento
//Objetivo:reemplazar uno o varios carteres que el usuario elija.
//Prerequisito: caracternuevo,caracternuevo,cadenamod,num(numero de caracteres)
//Valor retornado:
//Advertencias:
//*******************************************************************************************************************



void Cambiar(char cadenamod[30],int num,int t,int j,char caracternuevo[5],char caracterviejo[5]){

    if(t<=strlen(cadenamod)){
        if(cadenamod[t]==caracterviejo[j]){
            cadenamod[t]=caracternuevo[j];
            if(j<num){
                Cambiar(cadenamod,num,t,j+1,caracternuevo,caracterviejo);
            }else{
                j=0;
                Cambiar(cadenamod,num,t+1,j,caracternuevo,caracterviejo);
            }
        }else{
            if(j<num){
                Cambiar(cadenamod,num,t,j+1,caracternuevo,caracterviejo);
            }else{
                j=0;
                Cambiar(cadenamod,num,t+1,j,caracternuevo,caracterviejo);
            }
        }
    }
}

void ReducirCadena(char cadena1[30],char cadena2[30],char cadena3[30]){

    system("cls");

    char cadenaselcc[30];
    int opcion;
    int i=0;
    char cadenamod[30];


    printf("BIENVENIDO A REDUCIR CADENA\n\n");

    do{
        printf("Primero deberas seleccionar una de las cadenas:\n\n");

        printf("Cadena 1: %s\n",cadena1);
        printf("Cadena 2: %s\n",cadena2);
        printf("Cadena 3: %s\n",cadena3);

        printf("Selecciona una cadena:");
        scanf("%i",&opcion);

        if(opcion==1){
            strcpy(cadenaselcc,cadena1);
        }else{if(opcion==2){
                strcpy(cadenaselcc,cadena2);
            }else{if(opcion==3){
                    strcpy(cadenaselcc,cadena3);
                }else{
                    printf("\n\nDebes escoger una cadena de 1-3\n\n");
                    pausa();
                    system("cls");
                }
            }
        }
    }while((opcion!=1)&&(opcion!=2)&&(opcion!=3));

    printf("La cadena seleccionada es: %s\n\n",cadenaselcc);

    strcpy(cadenamod,cadenaselcc);


    Reducir(cadenaselcc,cadenamod,i);


    printf("\n\nCadena de caracteres ORIGINAL: %s\n\n",cadenaselcc);
    printf("Cadena de caracteres MODIFICADA: %s\n\n",cadenamod);

    pausa();
    system("cls");

}

//*******************************************************************************************************************
//Subprograma:Reducir                                Tipo:procedimiento
//Objetivo:reducir la cdena seleccionada si hay caractres repetidos.
//Prerequisito: cadenaselecc
//Valor retornado:
//Advertencias:
//*******************************************************************************************************************

void Reducir(char cadenaselcc[30],char cadenamod[30],int i){


    if(i<=strlen(cadenaselcc)){
         if(cadenaselcc[i]==cadenaselcc[i+1]){
            cadenamod[i]=-1;
            Reducir(cadenaselcc,cadenamod,i+1);
         }else{
             Reducir(cadenaselcc,cadenamod,i+1);
         }
    }


}

void MostrarPosicionTotalImpares(int numeros1[5],int numeros2[5]){

    int numeroselc[5];
    int i=0,j,k,t=0;
    int contImp=0;
    int opcion=0;
    int confirmacion=0;
    int posicion=0;

    system("cls");

    do{
        printf("Primero deberas seleccionar una de las cadenas:\n\n");
        printf("Numeros 1: ");
        for(k=0;k<5;k++){

            printf("%i ",numeros1[k]);
        }
        printf("\nNumeros 2: ");
        for(k=0;k<5;k++){
            printf("%i ",numeros2[k]);
        }
        printf("\nSelecciona una cadena:");
        scanf("%i",&opcion);

        if(opcion==1){
            for(j=0;j<5;j++)
                numeroselc[j]=numeros1[j];
        }else{if(opcion==2){
                for(j=0;j<5;j++)
                    numeroselc[j]=numeros2[j];
            }else{
                    printf("\n\nDebes escoger una cadena de 1-2\n\n");
                    pausa();
                    system("cls");
            }
        }
    }while((opcion!=1)&&(opcion!=2));
    system("cls");


    Impares(numeroselc,i,&contImp,&confirmacion,t,&posicion);

    if(confirmacion==1){
            printf("La cadena seleccionada es: ");
            for(k=0;k<5;k++)
                printf("%i ",numeroselc[k]);
            printf("\n\nNumero total de elementos impares: %i\n",contImp);
            printf("Elemento %i encontrado en la posicion %i del array\n\n",numeroselc[posicion],posicion);
        }else{
            printf("Elemento no encontrado\n");
        }

    pausa();
    system("cls");


}

//*******************************************************************************************************************
//Subprograma:Reducir                                Tipo:procedimiento
//Objetivo:mostrar posicion y numero de impares que hay en la cadena si es que hay
//Prerequisito: numeroselc
//Valor retornado:
//Advertencias:
//*******************************************************************************************************************

void Impares(int numeroselc[5],int i,int *contImp,int *confirmacion,int t,int *posicion){

    if((i==5)){
    if(numeroselc[t]==*contImp){
        if(t>5){//Si pasa del largo del array significa que no ha encontrado el elemento
            confirmacion=0;//entonces la confirmacion es 0
        }else{
            *posicion=t;
            *confirmacion=1;
        }
    }else{
        Impares(numeroselc,i,&*contImp,&*confirmacion,t+1,&*posicion);
    }

    }else{
        if(numeroselc[i]%2==0){
             Impares(numeroselc,i+1,&*contImp,&*confirmacion,t,&*posicion);
        }else{
            *contImp=*contImp+1;
            Impares(numeroselc,i+1,&*contImp,&*confirmacion,t,&*posicion);
        }
    }
}







