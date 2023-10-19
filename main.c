#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

typedef struct{
    int edad;
    char nombre[30];
    int cursa;
    int legajo;
}alumno;

void agregarArchivo();
void mostrarArchivo();
int  cantFiles();
alumno carga();
void cargarAlumno();
void muestra();
void mostrarAlumnos();
void agregarAlFinal();
void pasaje();
int cantMayores(int cant);
void mostrarNombresXrango(int x,int y);
int determinadoAnio(int anio);
void arregloAlarchivo(alumno arreglo[]);
int cargarArreglo(alumno arreglo[]);
void mostrarArreglo(alumno arreglo[],int val);
void filtrarAlumnos(alumno arreglo[],int val,int det);
int cantRegistros();
void moatrarRegistroDeterminado(int det);
void modificarRegistro(int det);



int main()
{
    int cant,edad,i,x=20,y=50,determ,anio=3,validos,cantidad;
    alumno arreglo[5];
    int opc;

    printf("1: Carga y muestra alumnos\n");
    printf("2: Agrega al final\n");
    printf("3: Pasaje a pila los legajos de los mayores\n");
    printf("4: Cant de mayores a una edad \n");
    printf("5: Muestra nombres de alumnos entre un rango de edades\n");
    printf("6: Cant de alumnos que cursan un anio determinado\n");
    printf("7: Copia el arreglo al archivo y pasa a otro arreglo los estudiantes de un anio en particular\n");
    printf("8 Devuelve la cantidad de registros del archivo \n");
    printf("9 Muestra un registro determinado \n");
    printf("10 Para modificar un registro \n");
    scanf("%d",&opc);
    system("pause");
    system("cls");

   switch(opc)
   {
   case 1:
       cargarAlumno();
       mostrarAlumnos();
    break;
    case 2:
        agregarAlFinal();
        mostrarAlumnos();
    break;
    case 3:
        pasaje();
    break;
    case 4:
        printf("Ingrese una edad \n");
        scanf("%d",&edad);
        i=cantMayores(edad);
        printf("Hay %d mayores a %d \n",i,edad);
    break;
    case 5:
        mostrarNombresXrango(x,y);
        mostrarAlumnos();
    break;
    case 6:
        determ=determinadoAnio(anio);
        printf("%d cursan el anio %d \n",determ,anio);
        mostrarAlumnos();
        break;
    case 7:
        validos=cargarArreglo(arreglo);
        arregloAlarchivo(arreglo);
        mostrarArreglo(arreglo,validos);
        filtrarAlumnos(arreglo,validos,4);
        break;
    case 8:
        cantidad=cantRegistros();
        printf("Cant de registros en el archivo  %d \n",cantidad);
        break;
    case 9:
        printf("DATO \n");
        moatrarRegistroDeterminado(2);
        break;
    case 10:
        modificarRegistro(1);
        mostrarAlumnos();
        break;

    default:
        system("cls");
        main();
   }

    return 0;
}

void agregarArchivo()
{
    FILE *fp=fopen("datos.bin","wb");
    int a=100,b=7;
    if(fp)
    {
        fwrite(&a,sizeof(int),1,fp);
        fwrite(&b,sizeof(int),1,fp);
        fclose(fp);
    }
}

void mostrarArchivo()
{
    FILE *fp=fopen("datos.bin","rb");
    int a;
    if(fp)
    {
        while(fread(&a,sizeof(int),1,fp)>0)
        {
            printf("a=%d \n",a);
        }
        fclose(fp);
    }
}

int cantFiles()
{
    FILE *fp=fopen("datos.bin","rb");
    int i=0,dato;
    if(fp)
    {
        while(fread(&dato,sizeof(int),1,fp)>0)
        {
            i++;
        }
        fclose(fp);
    }
    return i;
}

alumno carga()
{
    alumno pibe;
    printf("Ingrese su nombre \n");
    fflush(stdin);
    scanf("%s",&pibe.nombre);
    printf("Ingrese su edad \n");
    scanf("%d",&pibe.edad);
    printf("Ingrese anio que cursa \n");
    scanf("%d",&pibe.cursa);
    printf("Ingrese su legajo \n");
    scanf("%d",&pibe.legajo);
    return pibe;
}

void cargarAlumno()
{
    FILE *fp=fopen("datos.bin","ab");
    alumno dato;
    char continuar='s';


    if(fp)
    {
        while(continuar=='s')
        {
            dato=carga();
            fwrite(&dato,sizeof(alumno),1,fp);
            printf("Desea continuar ingresando alumnos? \n");
            fflush(stdin);
            scanf("%c",&continuar);
        }
        fclose(fp);
    }
}

void muestra(alumno dato)
{
    printf("Nombre: %s \n",dato.nombre);
    printf("Edad: %d \n",dato.edad);
    printf("Cursa: %d \n",dato.cursa);
    printf("Legajo: %d \n",dato.legajo);
    printf("--------------------------  \n");
}

void mostrarAlumnos()
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            printf("\n");
            muestra(dato);
        }
        fclose(fp);
    }
}

void agregarAlFinal()
{
    alumno dato;
    FILE *fp=fopen("datos.bin","ab");
    printf("Ahora agregaremos un alumno al final del archivo \n");
    system("pause");
    if(fp)
    {

        fseek(fp,0,2);
        dato=carga();
        fwrite(&dato,sizeof(alumno),1,fp);
        fclose(fp);
    }
}

void pasaje()
{
    Pila legajos;
    inicpila(&legajos);
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            if(dato.edad>=18)
            {
                apilar(&legajos,dato.legajo);
            }
        }
        fclose(fp);
    }
    printf("PILA LEGAJOS DE MAYORES \n");
    mostrar(&legajos);
}

int cantMayores(int cant)
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    int i=0;
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            if(cant<dato.edad)
            {
                i++;
            }
        }
        fclose(fp);
    }
    return i;
}

void mostrarNombresXrango(int x,int y)
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    printf("NOMBRE DE LAS PERSONAS ENTRE LAS EDADES %d y %d \n",x,y);
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            if( x<dato.edad && y>dato.edad)
            {
                printf("%s \n",dato.nombre);
            }
        }
        fclose(fp);
    }
}

int determinadoAnio(int anio)
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    int i=0;
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            if(anio == dato.cursa)
            {
                i++;
            }
        }
        fclose(fp);
    }
    return i;
}

int cargarArreglo(alumno arreglo[])
{
    alumno dato;
    int i=0;
    char continuar='s';
    while(continuar=='s')
    {
        arreglo[i]=carga();
        i++;
        printf("continuar ingresando alumnos? \n");
        fflush(stdin);
        scanf("%c",&continuar);
    }

    return i;
}

void arregloAlarchivo(alumno arreglo[])
{
    FILE *fp=fopen("datos.bin","ab");
    if(fp)
    {
        fwrite(&arreglo,sizeof(alumno),1,fp);
        fclose(fp);
    }
}

void mostrarArreglo(alumno arreglo[],int val)
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            for(int i=0;i<val;i++)
            {
                muestra(arreglo[i]);
            }
        }
        fclose(fp);
    }
}

void filtrarAlumnos(alumno arreglo[],int val,int det)
{
    FILE *fp=fopen("datos.bin","rb");
    alumno arrayDet[5];
    int y=0;
    if(fp)
    {
        for(int i=0;i<val;i++)
        {
            if(arreglo[i].cursa == det)
            {
              arrayDet[i]=arreglo[i];
              y++;
            }
        }
        fclose(fp);
    }

    for(int i=0;i<y;i++)
    {
        printf("Nombre %s \n",arrayDet[i].nombre);
        printf("Edad %d \n",arrayDet[i].edad);
        printf("Legajo %d  \n",arrayDet[i].legajo);
        printf("Cursa %d \n",arrayDet[i].cursa);
        printf(" \n");
    }
}

int cantRegistros()
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    int i=0,cant;
    if(fp)
    {
        while(fread(&dato,sizeof(alumno),1,fp)>0)
        {
            fseek(fp,0,2);
            i=ftell(fp) / sizeof(alumno);
        }
        fclose(fp);
    }
    return i;
}

///Dado un archivo de alumnos, que tenga al menos 10 registros,
///hacer una función que muestre el contenido de un registro,
///cuyo número (entre 0 y 9) se pase por parámetro.
///Controlar no sobrepasar los límites del archivo.
void moatrarRegistroDeterminado(int det)
{
    FILE *fp=fopen("datos.bin","rb");
    alumno dato;
    int i;
    if(fp)
    {
            i=det*(sizeof(alumno));
            fseek(fp,i,0);
                fread(&dato,sizeof(alumno),1,fp);
                printf("Nombre: %s \n",dato.nombre);
                printf("Edad: %d \n",dato.edad);
                printf("Cursa: %d \n",dato.cursa);
                printf("Legajo: %d \n",dato.legajo);
                printf("--------------------------  \n");
        fclose(fp);
    }
}


///Realice una (o varias) funciones que permitan modificar un registro existente
/// en el archivo de alumnos. La misma debe permitir modificar
/// uno o todos los campos de la estructura y sobreescribir
/// el registro existente en el archivo.
void modificarRegistro(int det) //DET ES EL NRO DE REGISTTO A MODIFICAR
{
    FILE *fp=fopen("datos.bin","r+b");
    alumno dato;
    int i=0,opc;
        printf("1 para cambiar el nombre \n");
        printf("2 para cambiar la edad \n");
        printf("3 para cambiar la cursada \n");
        printf("4 para cambiar el legajo \n");
        printf("5 para cambiar TODO \n");
        scanf("%d",&opc);
    if(fp)
    {
        i=det*(sizeof(alumno));
        fseek(fp,i,0);
        fread(&dato,sizeof(alumno),1,fp);
        if(opc==1)
        {
            printf(" \n Ingrese un nuevo NOMBRE \n");
            fflush(stdin);
            scanf("%s",&dato.nombre);
        }else if(opc==2)
        {
            printf("Ingrese nueva EDAD \n");
            scanf("%d",&dato.edad);
        }else if(opc==3)
        {
            printf("Ingrese nueva CURSADA \n");
            scanf("%d",&dato.cursa);
        }else if(opc==4)
        {
            printf("Ingrese nuevo LEGAJO \n");
            scanf("%d",&dato.legajo);
        }else if(opc==5)
        {
             printf(" \n Ingrese un nuevo NOMBRE \n");
            fflush(stdin);
            scanf("%s",&dato.nombre);
            printf("Ingrese nueva EDAD \n");
            scanf("%d",&dato.edad);
            printf("Ingrese nueva CURSADA \n");
            scanf("%d",&dato.cursa);
            printf("Ingrese nuevo LEGAJO \n");
            scanf("%d",&dato.legajo);
        }
        fseek(fp,i,0);
        fwrite(&dato,sizeof(alumno),1,fp);
        fclose(fp);
    }
}


