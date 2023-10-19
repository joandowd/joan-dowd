#include <stdio.h>
#include <stdlib.h>

typedef struct
{
int caloriasQuemadas;
char nombreCiclista[30];
char apellidoCiclista[30];
int edad;
int tipoEntrenamiento; /// 1 adentro - 2 afuera
int peso;
int kilometros;
}Entrenamiento;


Entrenamiento carga();
int cargarArreglo(Entrenamiento arreglo[]);
void muestra(Entrenamiento dato);
void mostrarArreglo(Entrenamiento arreglo[],int validos);
void cargarArchivos(Entrenamiento arreglo[],int validos);
int cantRegistros2();
int cantRegistros1();
void modifCalorias(int cant,int pos);
void mostraraArchivo2();
void promediosCalorias(float *prom1,float *prom2,int cant1,int cant2);
void arregloALarchivo(Entrenamiento arreglo[]);
void mostrarArchivoCCarreglo(Entrenamiento arreglo[],int validos);



int main()
{
    int validos,cant1,cant2;
    Entrenamiento arreglo[20];
    float prom1,prom2;

    validos=cargarArreglo(arreglo);
    mostrarArreglo(arreglo,validos);

    cargarArchivos(arreglo,validos);

    cant1=cantRegistros1();
    printf("Cantidad de registros 1: |%d| \n",cant1);

    cant2=cantRegistros2();
    printf("Cantidad de registros 2: |%d| \n",cant2);

    modifCalorias(cant2,1);
    mostraraArchivo2();

    promediosCalorias(&prom1,&prom2,cant1,cant2);
    printf("PROM 1: %.2f \n",prom1);
    printf("PROM 2: %.2f \n",prom2);

    return 0;
}

Entrenamiento carga()
{
    int edad=10;
    int tipo=3;
    Entrenamiento dato;
    printf("Ingrese su nombre \n");
    fflush(stdin);
    scanf("%s",&dato.nombreCiclista);
    printf("Ingrese su apellido \n");
    fflush(stdin);
    scanf("%s",&dato.apellidoCiclista);
    while(edad<18)
    {
        printf("Ingrese su edad \n");
        scanf("%d",&edad);
        if(edad>18)
        {
            dato.edad=edad;
        }
    }

    printf("Ingrese sus calorias quemada \n");
    scanf("%d",&dato.caloriasQuemadas);
    printf("Ingrese sus km recorridos \n");
    scanf("%d",&dato.kilometros);
    printf("Ingrese su peso \n");
    scanf("%d",&dato.peso);

    while(tipo!=1 && tipo!=2)
    {
        printf("Ingrese el tipo de entrenamiento [1:ADENTRO]-[2:AFUERA] \n");
        scanf("%d",&tipo);
        if(tipo==1 || tipo==2)
        {
            dato.tipoEntrenamiento=tipo;
        }
    }

    return dato;
}

int cargarArreglo(Entrenamiento arreglo[])
{
    char continuar='s';
    int i=0;
    while(continuar=='s')
    {
        arreglo[i]=carga();
        i++;
        printf("Seguir canrgando entrenamientos? \n");
        fflush(stdin);
        scanf("%c",&continuar);
    }
    return i;
}

void muestra(Entrenamiento dato)
{
    printf("\n");
    printf("Nombre :%s \n",dato.nombreCiclista);
    printf("Apellido :%s \n",dato.apellidoCiclista);
    printf("Edad :%d \n",dato.edad);
    printf("Calorias qumadas :%d \n",dato.caloriasQuemadas);
    printf("Km recorridos :%d \n",dato.kilometros);
    printf("Peso :%d \n",dato.peso);
    printf("Tipo de entrenamiento :%d \n\n",dato.tipoEntrenamiento);
    printf("---------------------------------------- \n");

}

void mostrarArreglo(Entrenamiento arreglo[],int validos)
{
    for(int i=0;i<validos;i++)
    {
        muestra(arreglo[i]);
    }
}

void cargarArchivos(Entrenamiento arreglo[],int validos)
{
    FILE *fp=fopen("archivo1.bin","ab");
    FILE *pf=fopen("archivo2.bin","ab");
    Entrenamiento dato;
    if(fp!=NULL && pf!=NULL)
    {
        for(int i=0;i<validos;i++)
        {
            if(arreglo[i].tipoEntrenamiento==1)
            {
                fwrite(&arreglo[i],sizeof(Entrenamiento),1,fp);
            }else if(arreglo[i].tipoEntrenamiento==2)
            {
                fwrite(&arreglo[i],sizeof(Entrenamiento),1,pf);
            }
        }
        fclose(pf);
        fclose(fp);
    }
}

int cantRegistros2()
{
    FILE *fp=fopen("archivo2.bin","rb");
    Entrenamiento dato;
    int cant=0;
    if(fp)
    {
        fseek(fp,0,2);
        cant=ftell(fp)/(sizeof(Entrenamiento));
        fclose(fp);
    }
    return cant;
}

int cantRegistros1()
{
    FILE *fp=fopen("archivo1.bin","rb");
    Entrenamiento dato;
    int cant=0;
    if(fp)
    {
        fseek(fp,0,2);
        cant=ftell(fp)/(sizeof(Entrenamiento));
        fclose(fp);
    }
    return cant;
}

void mostraraArchivo2()
{
    FILE *fp=fopen("archivo2.bin","rb");
    Entrenamiento dato;
    if(fp)
    {
        while(fread(&dato,sizeof(Entrenamiento),1,fp)>0)
        {
            muestra(dato);
        }
    }
}

void modifCalorias(int cant,int pos)
{
    if(cant<pos)
    {
        printf("ERROR \n");
        main();
    }
    FILE *fp=fopen("archivo2.bin","r+b");
    Entrenamiento dato;

    if(fp)
    {
        int i=pos*(sizeof(Entrenamiento));
        fseek(fp,i,0);
        fread(&dato,sizeof(Entrenamiento),1,fp);
        printf("Ingrese la nueva cantidad de calorias quemadas \n");
        scanf("%d",&dato.caloriasQuemadas);
        fseek(fp,i,0);
        fwrite(&dato,sizeof(Entrenamiento),1,fp);

        fclose(fp);
    }
}

void promediosCalorias(float *prom1,float *prom2,int cant1,int cant2)
{
    FILE *fp=fopen("archivo1.bin","rb");
    FILE *pf=fopen("archivo2.bin","rb");
    Entrenamiento dato;
    int suma1=0;
    int suma2=0;
    if(fp && pf)
    {
        while(fread(&dato,sizeof(Entrenamiento),1,fp)>0)
        {
            suma1+=dato.caloriasQuemadas;
        }
        while(fread(&dato,sizeof(Entrenamiento),1,pf)>0)
        {
            suma2+=dato.caloriasQuemadas;
        }
        fclose(fp);
        fclose(pf);
    }
    *prom1=suma1/cant1;
    *prom2=suma2/cant2;
}
