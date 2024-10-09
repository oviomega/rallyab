#include <STDIO.H>
#include <CONIO.H>
#include <STRING.H>
#include <STDLIB.H>
#include <ratoli.h>
#include <graphics.h>

struct piloto
	{
		char nom[25];
		float ttc[30];
		float media;
		float totc;
		int desc;
	};

struct piloto * cargar(char [], struct piloto *array, int *, int *, float *);
struct piloto * masdatos(char [], struct piloto *, int *, int *, float *);
void modificar(char [], struct piloto *, int *, int *, float *);
struct piloto * eliminar(char [], struct piloto *,int *);
void ver(char [], struct piloto *, int *, int *, float *);
void abrir(char [], char[]);
void html(char [], struct piloto *, struct piloto *, int *, int *, float *);
void guardar(char [], struct piloto *, int *, int *, float *);
struct piloto * ordenar(struct piloto *, int *, int *);
struct piloto * scratch (struct piloto *, int *, int *, float *, int);
int menuraton(int);
char * dir(char *);

/*Funci¢n main*/
void main()
{
float *o=NULL;
char nombre[13]="", cont;
struct piloto *array=NULL, *aux=NULL;
int numreg=0, numtram, sw=0, opc=100, rat;
float dist=0;
int i,j;

textmode(C80);
InitMouse();
SetMousePos(1,1);

do
	{
		clrscr();
		textcolor(BLUE);
		textbackground(CYAN);
		sw=0;
		/*Recuadro del men£*/
		for(i=0; i<=24; i++)
			for(j=0; j<=80; j++)
				{
				gotoxy(j,i);
				cprintf(" ");
				}
		gotoxy(80,25); cprintf("¼");
		gotoxy(1,1); insline(); cprintf("É");
		for(i=2; i<80; i++)
			{
				gotoxy(i, 1);
				cprintf("Í");
			}
		cprintf("»");
		for(i=2; i<25; i++)
			{
				gotoxy(1, i); cprintf("º");
				gotoxy(80, i); cprintf("º");
			}
		cprintf("È");
		for(i=2; i<80; i++)
			{
				gotoxy(i, 25);
				cprintf("Í");
			}
		/*Hasta aqu¡*/
		textcolor(RED);
		gotoxy(2, 2); cprintf("TRallye v1.0Alfa"); gotoxy(2, 3); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
		gotoxy(70, 2); cprintf("Por OviOne");
		gotoxy(32,3); cprintf("ELIGE OPCI¢N:");
		gotoxy(31,4); cprintf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
		gotoxy(20, 6); cprintf("1.- Nuevo archivo");
		gotoxy(20, 8); cprintf("2.- Abrir archivo de datos (binario)");
		gotoxy(20, 10); cprintf("3.- A¤adir piloto");
		gotoxy(20, 12); cprintf("4.- Modificar datos");
		gotoxy(20, 14); cprintf("5.- Eliminar registro");
		gotoxy(20, 16); cprintf("6.- Guardar archivo de datos (binario)");
		gotoxy(20, 18); cprintf("7.- Visualizar");
		gotoxy(20, 20); cprintf("8.- Exportar a HTML");
		gotoxy(20, 23); cprintf("0.- Salir");
		gotoxy(79, 24);
		mouseon();
		fflush(stdin);

		while (sw == 0)
			{
			mouseon();
			if(kbhit())
				{
					fflush(stdin);
					scanf("%d", &opc);
					sw = 1;
				}
			if((boto()) == 1)
				{
					rat=1;
					opc = menuraton(rat);
					if(opc!=100)
						sw=1;
				}
			}
		mouseoff();
		switch(opc)
			{
				case 1:
					if(numreg!=0)
						{
							do
								{
									clrscr();
									printf("Si continuas se perderan los datos no guardados");
									printf("\n\n¨Continuar (s/n)?");
									fflush(stdin);
									cont=getch();
									cont=tolower(cont);
								}
							while(cont!='s' && cont!='n');
							if(cont=='s')
								{
									strcpy(nombre, "NUEVO");
									numreg=0;
									array = masdatos(nombre, array, &numreg, &numtram, &dist);
									aux = ordenar(array, &numreg, &numtram);
									break;
								}
						}
					else
						{
							array = masdatos(nombre, array, &numreg, &numtram, &dist);
							aux = ordenar(array, &numreg, &numtram);
							break;
						}
					break;
				case 2:
					array = cargar(nombre, array, &numreg, &numtram, &dist);
					break;
				case 3:
					if(numreg==0)
						{
							clrscr();
							printf("No hay datos cargados");
							getch();
							break;
						}
					array = masdatos(nombre, array, &numreg, &numtram, &dist);
					aux = ordenar(array, &numreg, &numtram);
					break;
				case 4:
					modificar(nombre, array, &numreg, &numtram, &dist);
					aux = ordenar(array, &numreg, &numtram);
					break;
				case 5:
					array = eliminar(nombre, array, &numreg);
					aux = ordenar(array, &numreg, &numtram);
					break;
				case 6:
					guardar(nombre, array, &numreg, &numtram, &dist);
					break;
				case 7:
					aux = ordenar(array, &numreg, &numtram);
					ver(nombre, array, &numreg, &numtram, &dist);
					break;
				case 8:
					aux = ordenar(array, &numreg, &numtram);
					abrir(nombre, ".rly");
					html(nombre, array, aux, &numreg, &numtram, &dist);
					break;
			}
	}
while(opc!=0);
free(array);
free(aux);
}


/*Cargar datos del archivo*/
struct piloto * cargar(char nombre[], struct piloto *array, int *numreg, int *numtram, float *dist)
{
FILE *pf;
int i;
char nom[13];

strcpy(nom, nombre);
clrscr();
printf("Archivos de tiempos encontrados en el directorio actual:\n\n");
system("dir *.rly /B /O /W");
fflush(stdin);
printf("\n\nNombre del archivo: "); gets(nombre);
abrir(nombre, ".rly");

if((pf = fopen(nombre, "rb")) == NULL)
	{
		printf("Error al abrir el archivo %s", nombre);
		getch();
		if (*numreg==0)
			{
				nombre="";
				return(NULL);
			}
		else
			{
				strcpy(nombre, nom);
				return(array);
			}
	}

else
	{
		fread(numreg, sizeof(int), 1, pf);
		fread(numtram, sizeof(int), 1, pf);
		fread(dist, sizeof(float), 1, pf);

		free(array);
		array = (struct piloto *) malloc (*numreg *(sizeof(struct piloto)));

		for (i=0; i<*numreg; i++)
			fread(&array[i], sizeof(struct piloto), 1, pf);

		fclose(pf);
		printf("Se ha cargado el archivo %s", nombre);
		getch();
		return(array);
	}
}


/*A¤adir datos*/
struct piloto * masdatos(char nombre[], struct piloto *array, int *numreg, int *numtram, float *dist)
{
int i, j, l=1;
long int mt, ct, st;
char prueba, rally[25];

clrscr();

if (*numreg == 0)
	{
		printf("ARCHIVO: NUEVO");
		printf("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
		printf("\n\nN£mero de pilotos participantes: "); scanf("%d", numreg);
		array = (struct piloto *) malloc (*numreg *(sizeof(struct piloto)));
		printf("\nN£mero de tramos del rallye: "); scanf("%d", numtram);
		printf("\nDistancia total (Km.): "); scanf("%f", dist);

		for(i=0; i<*numreg; i++)
		{
			fflush(stdin);
			array[i].desc=0;
			printf("\nNombre del piloto: "); gets(&*array[i].nom);
			array[i].totc = 0;
			for (j=0; j<*numtram; j++)
				{
					l+=2;
					printf("Tiempo del tramo %d (mm:ss.cc) (0:00.00 si abandon¢): ", j+1); scanf("%ld : %ld . %ld", &mt, &st, &ct);
					array[i].ttc[j] = mt*6000 + st*100 + ct;
					array[i].totc = array[i].totc + array[i].ttc[j];
				}
			if(array[i].totc!=0)
				array[i].media = (*dist / (array[i].totc/100))*3600;
			else
				array[i].desc = 1;
		}
	}

else
	{
		printf("ARCHIVO: %s", nombre);
		printf("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
		array = (struct piloto *) realloc (array, (*numreg+1) *(sizeof(struct piloto)));
		fflush(stdin);
		printf("\n\n\nNombre del piloto: "); gets(array[*numreg].nom);
		array[*numreg].totc = 0;
		for (j=0; j<*numtram; j++)
			{
				printf("Tiempo del tramo %d (mm:ss.cc) (0:00.00 si abandon¢): ", j+1); scanf("%ld : %ld . %ld", &mt, &st, &ct);
				array[*numreg].ttc[j] = mt*6000 + st*100 + ct;
				array[*numreg].totc = array[*numreg].totc + array[*numreg].ttc[j];
			}
		if(array[*numreg].totc!=0)
			{
				array[*numreg].media = (*dist / (array[*numreg].totc/100))*3600;
				array[*numreg].desc = 0;
			}
		else
			array[*numreg].desc = 1;
		*numreg = *numreg + 1;
	}

return(array);
}



/*Modificar el array cargado*/
void modificar(char nombre[], struct piloto *array, int *numreg, int *numtram, float *dist)
{
int i, opc=100, opc2=100, pos, mt, st, ct, rat, sw;
char nom[25];

if(*numreg==0)
	{
		clrscr();
		printf("No hay datos cargados");
		getch();
		return;
	}

do
{
clrscr();
if((strcmp(nombre, ""))==0)
	{
		printf("ARCHIVO: NUEVO");
		printf("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
	}
else
	{
		printf("ARCHIVO: %s", nombre);
		printf("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
	}
gotoxy(31, 4); printf("SELECCIONA OPCI¢N:");
gotoxy(30, 5); printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
gotoxy(15, 8); printf("1.- Modificar distancia total");
gotoxy(15, 11); printf("2.- Modificar un registro");
gotoxy(15, 15); printf("0.- Volver al men£ principal\n\n");
sw=0;

		while (sw == 0)
			{
			mouseon();
			if(kbhit())
				{
					fflush(stdin);
					scanf("%d", &opc);
					sw = 1;
				}
			if((boto()) == 1)
				{
					rat=2;
					opc = menuraton(rat);
					if(opc!=100)
						sw=1;
						mouseoff();
				}
			}
switch(opc)
	{
		case 1:
			clrscr();
			printf("Valor actual de distancia: %6.2f", *dist);
			printf("\n\nNuevo valor: "); scanf("%f", dist);
			for(i=0; i<*numreg; i++)
				array[i].media = (*dist / (array[i].totc/100))*3600;
			break;
		case 2:
			clrscr();
			printf("Nombre del piloto del registro a modificar: ");
			fflush(stdin);
			gets(nom);
			pos = -1;
			for (i=0; i<*numreg; i++)
				if(strcmp(nom, array[i].nom)==0)
					{
						pos = i;
						i=*numreg;
					}
			if(pos>=0 && pos<*numreg)
				{
					clrscr();
					printf("Tiempos de %s:", array[pos].nom);
				}
			else
				{
					printf("\n\nNombre no encontrado"); getch();
					return;
				}
			for (i=0; i<*numtram; i++)
				{
					mt = (long int)(array[pos].ttc[i]/100) / 60;
					st = (long int)(array[pos].ttc[i]/100) % 60;
					ct = (long int)array[pos].ttc[i] % 100;
					gotoxy(4,i+3); printf("\nTiempo en el tramo %d: %02d:%02d.%02d", i+1, mt, st, ct);
				}
			do
			{
				gotoxy(1,24);clreol();
				gotoxy(1,18); printf("¨Qu‚ quieres modificar?");
				gotoxy(5, 20); printf("1.- Nombre");
				gotoxy(5, 22); printf("2.- Tiempo");
				gotoxy(5, 24); printf("0.- Volver al men£ anterior"); gotoxy(40,24); clreol();
				fflush(stdin);
				sw=0;

				while (sw == 0)
				{
						mouseon();
						if(kbhit())
						{
							fflush(stdin);
							scanf("%d", &opc2);
							sw = 1;
						}
				if((boto()) == 1)
					{
					rat=3;
					opc2 = menuraton(rat);
					if(opc2!=100)
						sw=1;
						mouseoff();
					}
				}
				
				switch(opc2)
					{
						case 1:
							clrscr();
							gotoxy(1,18);clreol();gotoxy(1,19);clreol();gotoxy(1,21);clreol();
							gotoxy(1,24); printf("Escribe el nuevo nombre: "); fflush(stdin); gets(array[pos].nom);
							break;
						case 2:
							do
								{
									gotoxy(1,18); delline(); delline(); delline(); delline();delline(); delline(); delline(); delline();
									gotoxy(1, 24); clreol(); printf("N£mero de tramo a modificar: "); scanf("%d", &i);
								}
							while (i>*numtram || i==0);
							gotoxy(1,24); clreol(); printf("Nuevo tiempo de tramo: %d (mm:ss.cc) (0:00.00 si abandon¢): ", i); scanf("%d : %d . %d", &mt, &st, &ct); clreol();
							array[pos].totc = 0;
							array[pos].ttc[i-1] = (long int)mt*6000 + (long int)st*100 + (long int)ct;
							for(i=0; i<*numtram; i++)
								array[pos].totc = array[pos].totc + array[pos].ttc[i];
							if(array[i].totc!=0)
								{
									array[pos].media = (*dist / (array[pos].totc/100))*3600;
									array[pos].desc = 0;
									break;
								}
							else
								array[pos].desc = 1;
								break;
					}
			}
			while(opc2!=0);
			break;
	}
 }
	while(opc!=0);
	mouseoff();
}



/*Eliminar un registro*/
struct piloto * eliminar(char nombre[], struct piloto *array, int *numreg)
{
char nom[25];
int i,j, sw=0;

clrscr();
if(*numreg==0)
	{
		printf("No hay datos cargados");
		getch();
		return(NULL);
	}
printf("ARCHIVO: %s", nombre);
printf("\nÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");
printf("\n\nNombre del piloto cuyo registro se borrar : ");
fflush(stdin); gets(nom);

for(i=0; i<*numreg; i++)
	if((strcmp(nom, array[i].nom))==0)
		{
			for(j=i; j<*numreg-1; j++)
				array[j] = array[j+1];
			*numreg = *numreg - 1;
			array = (struct piloto *) realloc (array, (*numreg) *(sizeof(struct piloto)));
			printf("\n\nRegistro de %s eliminado\n\n", nom);
			getch();
			sw=1;
		}

	if(sw==0)
		{
			printf("\n\nNombre no encontrado");
			getch();
		}

return(array);
}


/*Visualizar array de datos*/
void ver (char nombre[], struct piloto *array, int *numreg, int *numtram, float *dist)
{
float resta;
int i, mt, ct, st, lin=9, mf, sf, cf;

clrscr();
if(*numreg==0)
	{
		printf("No hay datos cargados");
		getch();
		return;
	}
gotoxy(1,1); printf("ARCHIVO: %s", nombre);
gotoxy(23, 1); printf("TIEMPOS DEL RALLYE Y VELOCIDAD MEDIA");
gotoxy(22, 2); printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");

gotoxy(1, 7); printf("Puesto   Piloto            Tiempo           Diferencia           Vel. Media");
gotoxy(1, 8); printf("ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ");

gotoxy(1, 5); printf("Distancia total: %6.2f Km.", *dist);
gotoxy(35, 5); printf("N£mero de tramos: %d", *numtram);

for(i=0; i<*numreg; i++)
	{
	if(lin==20 && i!=*numreg-1)
		{
			gotoxy(1, lin+1);
			printf("Pulsa una tecla para mostrar los siguientes pilotos");
			getch();
			delline();
			for(lin=9; lin<=20; lin++)
				{
					gotoxy(1,lin);
					clreol();
				}
			lin=8;
		}
	else
	{
	gotoxy(10, lin); printf("%s", array[i].nom);
	if(array[i].desc==0)
		{
			gotoxy(1, lin); printf("%d", i+1);

			mt = (unsigned long int)(array[i].totc/100) / 60;
			st = (unsigned long int)(array[i].totc/100) % 60;
			ct = (unsigned long int)array[i].totc % 100;

			gotoxy(28, lin); printf("%02d:%02d.%02d", mt, st, ct);

			if (i > 0)
				{
					resta = array[i].totc - array[0].totc;
					cf = (long int)resta % 100;
					sf = ((long int)resta/100) % 60;
					mf = ((long int)resta/100) / 60;
					gotoxy(45, lin); printf("+%02d:%02d.%02d", mf, sf, cf);
				}

			gotoxy(66, lin); printf("%5.2f", array[i].media);

			fflush(stdin);
		}
	else
		{
			gotoxy(35, lin); printf("No Finaliz¢");
			//gotoxy(76, lin); printf("0.00");
		}
	}
 lin++;
 }
 gotoxy(5, 22); printf("Para ver tiempos detallados, guarda el archivo en HTML");
 gotoxy(5, 24); clreol(); printf("Pulsa una tecla para volver al men£ principal");
 getch();
}



/*Poner nombre al archivo y a¤adir extensi¢n*/
void abrir(char nombre[], char ext[])
{
char nom[13];
int i;

clrscr();
strcpy(nom, nombre);
for(i=0; i<strlen(nom); i++)
	if(nom[i] =='.')
		nom[i] = '\0';

ext[4]='\0';
nombre[0] = '\0';

strcat(nombre, nom);
strcat(nombre, ext);
}


/*Exportar p gina web*/
void html(char nombre[], struct piloto *array, struct piloto *aux, int *numreg, int *numtram, float *dist)
{
FILE *pf, *phtm;
int i, j, mt, st, ct, scr;
char rally[25], ruta[100];
float resta;

clrscr();

if(*numreg==0)
	{
		clrscr();
		printf("No hay datos cargados");
		getch();
		return;
	}

if((pf = fopen(nombre, "rb")) == NULL)
	{
		printf("Debes guardar un archivo binario para poder exportar");
		getch();
		return;
	}
fclose(pf);

abrir(nombre, ".htm");
if((phtm = fopen(nombre, "wt")) == NULL)
	{
		printf("Error al crear el archivo %s", nombre);
		getch();
		return;
	}

	fflush(stdin);
	printf("Nombre del rallye: "); gets(rally);
	fprintf(phtm, "<HTML>\n<HEAD><TITLE>%s</TITLE></HEAD>\n<BODY>\n", rally);
	fprintf(phtm, "<BODY bgcolor=\"#99CCFF\" text=\"#000000\"><center><h1><a name=\"arriba\"></a>Rallye de %s</h1></center>\n", rally);
	fprintf(phtm, "<hr color=\"blue\" size=\"5\" width=\"100%\">\n");
	fprintf(phtm, "<b><div align=\"center\"><table width=\"313\" border=\"1\">\n");
	fprintf(phtm, "<tr><td align=\"left\" valign=\"middle\"><strong><font face=\"Verdana, Arial, Helvetica, sans-serif\">N&uacute;mero de pilotos:</font></strong></td><td align=\"right\" valign=\"middle\"><strong>%d</strong></td></tr>", *numreg);
	fprintf(phtm, "<tr><td align=\"left\" valign=\"middle\"><strong><font face=\"Verdana, Arial, Helvetica, sans-serif\">N&uacute;mero de tramos:</font></strong></td><td align=\"right\" valign=\"middle\"><strong>%d</strong></td></tr>", *numtram);
	fprintf(phtm, "<tr><td align=\"left\" valign=\"middle\"><strong><font face=\"Verdana, Arial, Helvetica, sans-serif\">Distancia total (km.):</font></strong></td><td align=\"right\" valign=\"middle\"><strong>%7.3f</strong></td></tr>", *dist);	
	fprintf(phtm, "</table></div><div align=\"left\"></div></b>");
	/*fprintf(phtm, "<b><center>\nNúmero de pilotos:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%d<br>\n", *numreg);
	fprintf(phtm, "Número de tramos:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%d<br>\n", *numtram);
	fprintf(phtm, "Kilómetros totales:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%7.3f<br>\n</b></center>\n", *dist);*/
	fprintf(phtm, "<h2><u>CLASIFICACIÓN</u></h2>\n");

	for(i=0; i<*numreg; i++)
		{
			fprintf(phtm, "<u><font size=\"5\">%dº&nbsp;&nbsp;%s:</font></u><br>\n<ul>", i+1, array[i].nom);
				for(j=0; j<*numtram; j++)
					{
						if(array[i].desc==0 || array[i].ttc[j]!=0)
						{
							mt = (long int)(array[i].ttc[j]/100) / 60;
							st = (long int)(array[i].ttc[j]/100) % 60;
							ct = (long int) array[i].ttc[j] % 100;
							aux = scratch(aux, &scr, numreg, &array[i].ttc[j], j);
							if(scr==0)
								fprintf(phtm, "<li><font size=\"4\">Tramo %02d:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%02d:%02d.%02d (Scratch)<br>\n", j+1, mt, st, ct);
							else
								fprintf(phtm, "<li><font size=\"4\">Tramo %02d:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%02d:%02d.%02d (%dº)<br>\n", j+1, mt, st, ct, scr+1);

							mt = (long int)(array[i].totc/100) / 60;
							st = (long int)(array[i].totc/100) % 60;
							ct = (long int) array[i].totc % 100;
						}
						else
							{
								fprintf(phtm, "<li><font size=\"4\">Tramo %02d:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--:--.--<br>\n", j+1);
							}
					}

						if(array[i].desc==0)
						{
						fprintf(phtm, "<hr color=\"blue\" size=\"2\" width=\"250\" align=left>\n");
						fprintf(phtm, "\n<font size=\"4\">TOTAL:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%02d:%02d.%02d", mt, st, ct);
						if(i>0)
							{
								resta = array[i].totc - array[0].totc;
								ct = (long int)resta % 100;
								st = ((long int)resta/100) % 60;
								mt = ((long int)resta/100) / 60;
								fprintf(phtm, "<br>DIF.:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+%02d:%02d.%02d", mt, st, ct);
							}
						fprintf(phtm, "<br>V. MEDIA:&nbsp;&nbsp;%6.2f Km/h</font><br>\n", array[i].media);
						fprintf(phtm, "</ul>\n<BR>\n");
						}
						else
						{
                            fprintf(phtm, "<hr color=\"blue\" size=\"2\" width=\"250\" align=left>\n");
							fprintf(phtm, "\n<font size=\"4\">TOTAL:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;--:--.--");
							fprintf(phtm, "<br>DIF.:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;+--:--.--");
							fprintf(phtm, "<br>V. MEDIA:&nbsp;&nbsp;-- Km/h</font><br>\n");
							fprintf(phtm, "</ul>\n<BR>\n");
						}
		}
fprintf(phtm, "<center><a href=\"#arriba\">Volver al principio</a></center>\n</body>");

dir(ruta);
printf("\n\nArchivo guardado en:\n%s\\%s\n%ld bytes escritos", ruta, nombre, ftell(phtm));
getch();

fclose(phtm);
}


/*Guardar en el archivo binario*/
void guardar (char nombre[], struct piloto *array, int *numreg, int *numtram, float *dist)
{
FILE *pf;
char nom[13], opc, ruta[100];
int lon, i;

strcpy(nom, nombre);

clrscr();
if (*numreg == 0)
	{
		printf("No hay datos cargados");
		getch();
		return;
	}

do
	{
		clrscr();
		printf("Nombre del archivo: ");
		fflush(stdin); gets(nombre);
		abrir(nombre, ".rly");
		if ((pf = fopen(nombre, "r")) != NULL)
			{
				gotoxy(1, 3); clreol();
				gotoxy(1, 1);
				printf("El archivo %s ya existe, ¨quieres sobreescribirlo (s/n)?\n\n", nombre);
				fflush(stdin);
				opc = getch();
				if(opc=='n' || opc=='N')
					opc=1;
				if(opc=='s' || opc=='S')
					opc=0;
			}
		else
			opc=0;
	}
while(opc!=0);

fclose(pf);

if ((pf = fopen(nombre, "wb")) == NULL)
	{
		printf("Error al crear el archivo %s", nombre);
		strcpy(nombre, nom);
		getch();
		return;
	}

fwrite(numreg, sizeof(int), 1, pf);
fwrite(numtram, sizeof(int), 1, pf);
fwrite(dist, sizeof(float), 1, pf);

for(i=0; i<*numreg; i++)
	fwrite(&array[i], sizeof(struct piloto), 1, pf);
	
dir(ruta);
printf("Archivo guardado en:\n%s\\%s\n%ld bytes escritos", ruta, nombre, ftell(pf));
getch();
fclose(pf);
}


/*Ordenar el array por tiempo total (totc)*/
struct piloto * ordenar(struct piloto *array, int *numreg, int *numtram)
{
struct piloto *aux, var;
int i, j, k;
float auxf;

if (*numreg == 0)
	{
		/*clrscr();
		printf("No hay datos cargados");
		getch();*/
		return(NULL);
	}

aux = (struct piloto *) malloc (*numreg*(sizeof(struct piloto)));

for (i=0; i<*numreg; i++)
	aux[i] = array[i];

for(i=0; i<*numreg; i++)
	for(j=0; j<*numtram; j++)
		if (array[i].ttc[j] == 0 || array[i].ttc[j] == 5999999)
			{
				array[i].totc = 5999999;
				array[i].desc = 1;
				aux[i].ttc[j] = 5999999;
			}

for (i=0; i<*numreg; i++)
	for(j=0; j<*numreg-1; j++)
		if(array[j].totc > array[j+1].totc)
			{
				var = array[j];
				array[j] = array[j+1];
				array[j+1] = var;
			}


for (i=0; i<*numreg; i++)
	for (j=0; j<*numtram; j++)
		{
			for (k=0; k<*numreg-1; k++)
				if(aux[k].ttc[j] > aux[k+1].ttc[j])
					{
						auxf = aux[k].ttc[j];
						aux[k].ttc[j] = aux[k+1].ttc[j];
						aux[k+1].ttc[j] = auxf;
					}
		}
return(aux);
}


/*Funci¢n que determina el puesto de un piloto en un tramo dado el tiempo*/
struct piloto * scratch (struct piloto *aux, int *scr, int *numreg, float *ttc, int tramo)
{
int i, j;
int pos;
float auxi;

auxi = *ttc;

if(*ttc==0)
	auxi=5999999;
           
for (i=0; i<*numreg; i++)
	if(auxi==aux[i].ttc[tramo])
			{
				*scr = i;
				return(aux);
			}

return(aux);
}


/*Definir limites del raton en los menues*/
int menuraton (int rat)
{

	if(rat==1)
		{
			if((eixx()) >= 152 && (eixx()) <= 287 && (eixy())>= 40 && (eixy())<=47)
				return(1);
			if((eixx()) >= 152 && (eixx()) <= 439 && (eixy())>= 56 && (eixy())<=63)
				return(2);
			if((eixx()) >= 152 && (eixx()) <= 287 && (eixy())>= 72 && (eixy())<=79)
				return(3);
			if((eixx()) >= 152 && (eixx()) <= 303 && (eixy())>= 88 && (eixy())<=95)
				return(4);
			if((eixx()) >= 152 && (eixx()) <= 319 && (eixy())>= 104 && (eixy())<=111)
				return(5);
			if((eixx()) >= 152 && (eixx()) <= 455 && (eixy())>= 120 && (eixy())<=127)
				return(6);
			if((eixx()) >= 152 && (eixx()) <= 263 && (eixy())>= 136 && (eixy())<=143)
				return(7);
			if((eixx()) >= 152 && (eixx()) <= 303 && (eixy())>= 152 && (eixy())<=159)
				return(8);
			if((eixx()) >= 152 && (eixx()) <= 223 && (eixy())>= 176 && (eixy())<=183)
				return(0);
		}
		if(rat==2)
		{
			if((eixx()) >= 112 && (eixx()) <= 343 && (eixy())>= 56 && (eixy())<=63)
				return(1);
			if((eixx()) >= 112 && (eixx()) <= 311 && (eixy())>= 80 && (eixy())<=87)
				return(2);
			if((eixx()) >= 112 && (eixx()) <= 335 && (eixy())>= 120 && (eixy())<=127)
				return(0);
		}
		if(rat==3)
		{
			if((eixx()) >= 32 && (eixx()) <= 111 && (eixy())>= 160 && (eixy())<=167)
				return(1);
			if((eixx()) >= 32 && (eixx()) <= 111 && (eixy())>= 176 && (eixy())<=183)
				return(2);
			if((eixx()) >= 32 && (eixx()) <= 255 && (eixy())>= 192 && (eixy())<=199)
				return(0);

		}
return(100);
}



/*Funci¢n "directorio actual"*/
char *dir(char *ruta)
{
	 strcpy(ruta, "X:\\");      /* fill string with form of response: X:\ */
	 ruta[0] = 'A' + getdisk();    /* replace X with current drive letter */
	 getcurdir(0, ruta+3);  /* fill rest of string with current directory */
	 return(ruta);
}
