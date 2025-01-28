#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void Menu_principal();
void Menu_2(char ruta[]);
void Nuevo_archivo();
void Abrir_archivo();
int Capturar_dato(char ruta[]);
void Consultar_dato(char ruta[],int tam);

int main(int argc, char *argv[]) {
	//char ruta[200] = "C:\\Users\\USUARIO DELL\\Documents\\UASLP\\Semestre 2024 - 2025 II\\Lenguajes de programacion\\1er avance de proyecto\\";
	Menu_principal();
	printf("Hasta luego");
	return 0;
}

void Menu_principal()
{
	int opcion;
	do
	{
		printf("*************** MENU PRINCIPAL ***************");
		printf("\n     1.- Nuevo archivo\n     2.- Abrir archivo\n     3.- Salir\n     > ");
		scanf("%d",&opcion);
		switch(opcion)
		{
			case 1:
				Nuevo_archivo();
				break;
			case 2:
				Abrir_archivo();
				break;
			case 3:
				system("cls");
				break;
			default:
				printf("Opcion ingresada incorrecta\n\n");
		}
	} while(opcion != 3);
}

void Menu_2(char ruta[])
{
	//system("cls");
	int opcion,letras;
	
	do{
		printf("********************************************");
		printf("\n\n     1.- Capturar dato.\n     2.- Consultar dato\n     3.- Regresar al menu principal\n     > ");
		scanf("%d",&opcion);
		
		switch(opcion)
		{
			case 1:
				letras = Capturar_dato(ruta);
				break;
			case 2:
				Consultar_dato(ruta,letras);
				break;
			case 3:
				system("cls");
				break;
			default:
				printf("Opcion ingresada incorrecta");
		}
	} while(opcion != 3);
	
	
}

void Nuevo_archivo()
{
	system(CLEAR);
	setbuf(stdin,NULL);
	FILE *archivo;
	char nombre[50],ruta[200] = "C:\\Users\\USUARIO DELL\\Documents\\UASLP\\Semestre 2024 - 2025 II\\Lenguajes de programacion\\1er avance de proyecto\\";
	printf("Ingresa el nombre del archivo a crear\n> ");
	scanf("%[^\n]",nombre);
	
	strcat(ruta,nombre);
	strcat(ruta,".bin");
	
	archivo = fopen(ruta,"rb");
	
	if(archivo == NULL)
	{
		archivo = fopen(ruta,"wb+");
		printf("Nuevo archivo ''%s'' creado satisfactoriamente\n\n",nombre);
	}else
		{
			printf("Error al crear nuevo archivo, archivo ya existente\n\n");
			fclose(archivo);
		}
	fclose(archivo);
	Menu_2(ruta);
}

void Abrir_archivo()
{
	system(CLEAR);
	setbuf(stdin,NULL);
	FILE *archivo;
	char nombre[50],ruta[200] = "C:\\Users\\USUARIO DELL\\Documents\\UASLP\\Semestre 2024 - 2025 II\\Lenguajes de programacion\\1er avance de proyecto\\";
		
	printf("Ingresa el nombre del archivo para abrir\n> ");
	scanf("%[^\n]",nombre);
	
	strcat(ruta,nombre);
	strcat(ruta,".bin");
	
	archivo = fopen(ruta,"rb");
	
	if(archivo == NULL)
	{
		printf("Error al abrir el archivo, archivo no existente\n\n");
		fclose(archivo);
	}else
		{
			printf("Archivo ''%s'' abierto de manera exitosa\n\n",nombre);
			fclose(archivo);
			Menu_2(ruta);
		}
}

int Capturar_dato(char ruta[])
{
	system(CLEAR);
	
	FILE *archivo;
	int direccion,opcion,letras,num;
	char dato[50];
	float decimales;
	double doble;
	long int largo;
		
	printf("Indica la direccion a ingresar el nuevo dato\n> ");
	scanf("%d",&direccion);
	
	archivo = fopen(ruta,"wb+");
	
	if(archivo == NULL)
	{
		printf("Error\n\n");
	}else
		{
			if(direccion >= 0)
			{
				printf("\n\nIngresar el tipo de dato\n   1.- Char(cadena)\n   2.- Entero\n   3.- Numero con decimales\n   4.- Cantidad cientifica(double)\n   5.- Entero enorme(long)\n> ");
				scanf("%d",&opcion);
		
				switch(opcion)
				{
					case 1:																//falta revisar si funcionan correctamente las opciones
						printf("Ingresa la cantidad de letras del nuevo dato\n> ");
						scanf("%d",&letras);
						//char dato[letras];
						printf("Ingresa el nuevo dato\n> ");
						setbuf(stdin,NULL);
						scanf("%[^\n]%*c",dato);
						dato[letras + 1] = '\0';
						//datos.tipo = letras;
						fseek(archivo,direccion,SEEK_SET);
						fwrite(&opcion,sizeof(int),1,archivo);
						fwrite(&dato,sizeof(char) * (letras+1),1,archivo);
						break;
					case 2:
						printf("Ingresa el nuevo dato\n> ");
						scanf("%d",&num);
						fseek(archivo,direccion,SEEK_SET);
						fwrite(&opcion,sizeof(int),1,archivo);
						fwrite(&num,sizeof(int),1,archivo);
						break;
					case 3:
						printf("Ingresa el nuevo dato\n> ");
						scanf("%f",&decimales);
						fseek(archivo,direccion,SEEK_SET);
						fwrite(&opcion,sizeof(int),1,archivo);
						fwrite(&decimales,sizeof(float),1,archivo);
						break;
					case 4:
						printf("Ingresa el nuevo dato\n> ");
						scanf("%lf",&doble);
						fseek(archivo,direccion,SEEK_SET);
						fwrite(&opcion,sizeof(int),1,archivo);
						fwrite(&doble,sizeof(double),1,archivo);
						break;
					case 5:
						printf("Ingresa el nuevo dato\n> ");
						scanf("%ld",&largo);
						fseek(archivo,direccion,SEEK_SET);
						fwrite(&opcion,sizeof(int),1,archivo);
						fwrite(&largo,sizeof(long),1,archivo);
						break;
					default:
						printf("Opcion ingresada incorrecta\n\n");
				}
				fclose(archivo);
			}else
				{
					printf("Direccion no admitida\n\n");
				}
		}
	return letras;
}

void Consultar_dato(char ruta[],int tam)
{
	system(CLEAR);
		
	FILE *archivo;
	int direccion,tipo = 0,numero;
	char letras[50];
	float decimales;
	double doble;
	long int largo;
	
	printf("Indica la direccion del dato a consultar\n> ");
	scanf("%d",&direccion);
	
	archivo = fopen(ruta,"rb");
	
	if(archivo == NULL)
	{
		printf("Error\n\n");
	}else
	{
		if(direccion >= 0)
		{
			fseek(archivo,direccion,SEEK_SET);
			fread(&tipo,sizeof(int),1,archivo);
			//printf("tipo es: %d\n\n",tipo);
			switch(tipo)
			{
				case 1:
					fread(&letras,sizeof(char) * tam,1,archivo);
					letras[tam] = '\0';
					printf("\nContenido de archivo\n     %d %s\n\n",tipo,letras);
					break;
				case 2:
					fread(&numero,sizeof(int),1,archivo);
					printf("\nContenido de archivo\n     %d %d\n\n",tipo,numero);
					break;
				case 3:
					fread(&decimales,sizeof(float),1,archivo);
					printf("\nContenido de archivo\n     %d %f\n\n",tipo,decimales);
					break;
				case 4:
					fread(&doble,sizeof(double),1,archivo);
					printf("\nContenido de archivo\n     %d %lf\n\n",tipo,doble);
					break;
				case 5:
					fread(&largo,sizeof(long int),1,archivo);
					printf("\nContenido de archivo\n     %d %ld\n\n",tipo,largo);
					break;			
			}
			fclose(archivo);
		}else
			{
				printf("Direccion ingresada incorrecta\n\n");
			}
	}
	
}
