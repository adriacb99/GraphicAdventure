#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define MAX_LEN 200

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int escena;
int tieneFlorRoja = 0;
int tieneFlorAmarilla = 0;
int tieneHerradura = 0;
int entregadaFlorRoja = 0;
int entregadaFlorAmarilla = 0;
int encendidoFaro = 0;
int puestaHerradura = 0;
int florCogidaR = 0;
int florCogidaA = 0;
int herraduraCogida = 0;

int mapa[6][3] = {{2,6,3}, {1}, {1,5,4}, {3}, {3}, {1}};
int posxy[6][2] = {{33,12}, {21,10}, {26,18}, {36,19}, {14,16}, {45,8}};

int fin = 1;
int escenas[3];

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void print_image(FILE *fptr, int linea, int size)
{
    char read_string[MAX_LEN];
	int i = 0;
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
	{
        if(i >= linea && i <= size) printf("%s",read_string);
		++i;
	}
}

void Objeto(int obj)
{
	char ch;
	if (obj == 1 && escena == 2) 
	{
		printf("> Puedes colocar el objeto en el buzón, quieres hacerlo? (y/n) \n");
		char sino = 0;
		while (!sino)
		{
			scanf("%c", &ch);
			if (ch == 110) 
			{
				sino = 1;
			}
			if (ch == 121)
			{
				printf("\n> Has colocado la flor en el buzón.\n");
				Sleep(2000);
				sino = 1;
				tieneFlorRoja = 0;
				entregadaFlorRoja = 1;
			}
		}
	}
	else if (obj == 2 && escena == 2) 
	{
		printf("> Puedes colocar el objeto en el buzón, quieres hacerlo? (y/n) \n");
		char sino = 0;
		while (!sino)
		{
			scanf("%c", &ch);
			if (ch == 110) 
			{
				sino = 1;
			}
			if (ch == 121)
			{
				printf("\n> Has colocado la flor en el buzón.\n");
				Sleep(2000);
				sino = 1;
				tieneFlorAmarilla = 0;
				entregadaFlorAmarilla = 1;
			}
		}
	}
	else if (obj == 3 && escena == 3 && encendidoFaro) 
	{
		printf("> Puedes colocarle la herradura azul a BlueDonkey, quieres hacerlo? (y/n) \n");
		char sino = 0;
		while (!sino)
		{
			scanf("%c", &ch);
			if (ch == 110) 
			{
				sino = 1;
			}
			if (ch == 121)
			{
				printf("\n> Le has colocado la herradura a BlueDonkey.\n");
				Sleep(2000);
				sino = 1;
				tieneHerradura = 0;
				puestaHerradura = 1;
			}
		}
	}
	else 
	{
		printf("> No puede usar este objeto aquí.\n");
		Sleep(2000);
	}
}

void Usar()
{
	char exit = 0;
	while(!exit && !puestaHerradura)
	{
		system("cls");
		printf("+------------------------------------------------------------------+\n");
		printf("                             INVENTARIO                             \n");
		printf("+------------------------------------------------------------------+\n");
		printf("> Selecciona que objeto quieres utilizar.\n");
		printf("+------------------------------------------------------------------+\n\n");
		int inv[3] = {0};
		int index = 1;
		if(tieneFlorRoja) 
		{
			printf(" ["ANSI_COLOR_CYAN"%d"ANSI_COLOR_RESET"] Flor roja "ANSI_COLOR_RED"♣"ANSI_COLOR_RESET"\n",index);
			inv[index - 1] = 1;
			++index;		
		}
		if(tieneFlorAmarilla)
		{
			printf(" ["ANSI_COLOR_CYAN"%d"ANSI_COLOR_RESET"] Flor amarilla "ANSI_COLOR_YELLOW"♣"ANSI_COLOR_RESET"\n",index);
			inv[index - 1] = 2;
			++index;
		}
		if(tieneHerradura)
		{
			printf(" ["ANSI_COLOR_CYAN"%d"ANSI_COLOR_RESET"] Herradura azul "ANSI_COLOR_BLUE"Ω"ANSI_COLOR_RESET"\n",index);
			inv[index - 1] = 3;
			++index;
		}
		if(index == 1)
		{
			printf("\033[3A");
			printf("\033[100D                                                      ");
			printf("\n> No puedes utilizar un objeto, tienes el inventario vacío.                   \n");
		}
		printf("\n+------------------------------------------------------------------+\n");
		printf(" ["ANSI_COLOR_RED"4"ANSI_COLOR_RESET"] Salir del inventario\n");
		printf("+------------------------------------------------------------------+\n");
		printf(">");
		char ch;
		scanf(" %c", &ch);
		if (ch == 4 + 48) exit = 1;
		if ((ch == 1 + 48) && inv[ch-49]!=0) Objeto(inv[ch-1-48]);
		if ((ch == 2 + 48) && inv[ch-49]!=0) Objeto(inv[ch-1-48]);
		if ((ch == 3 + 48) && inv[ch-49]!=0) Objeto(inv[ch-1-48]);
	}
}

void Recoger()
{
	printf("+------------------------------------------------------------------+\n");
	printf("                              RECOGER                               \n");
	printf("+------------------------------------------------------------------+\n");
	if (escena == 5 && !florCogidaA)
	{
		printf("> Seleccciona que objeto quieres coger.\n");
		printf("+------------------------------------------------------------------+\n\n");
		int ch;
		printf(ANSI_COLOR_YELLOW"                                _ _\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_YELLOW"                              _{ ' }_\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_YELLOW"                             { `.!.` }\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_YELLOW"                             ',_/Y\\_,'\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_YELLOW"                               {_,_}\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                                 |\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                               (\\|  /)\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                                \\| //\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                                 |//\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                              \\\\ |/  //\n"ANSI_COLOR_RESET);
		printf("                          ^^^^^^^^^^^^^^^\n");
		printf("                         ["ANSI_COLOR_CYAN"1"ANSI_COLOR_RESET"] Flor amarilla\n");
		printf("\n+------------------------------------------------------------------+\n");
		printf(">");
		scanf("%d", &ch);
		if (ch == 1) 
		{
			printf("> Has guardado Flor amarilla en el inventario.\n");
			tieneFlorAmarilla = 1;
			florCogidaA = 1;
		}
	}
	else if (escena == 6 && !florCogidaR)
	{
		printf("> Seleccciona que objeto quieres coger.\n");
		printf("+------------------------------------------------------------------+\n\n");
		int ch;
		printf(ANSI_COLOR_RED"                                _ _\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED"                              _{ ' }_\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED"                             { `.!.` }\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED"                             ',_/Y\\_,'\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_RED"                               {_,_}\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                                 |\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                               (\\|  /)\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                                \\| //\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                                 |//\n"ANSI_COLOR_RESET);
		printf(ANSI_COLOR_GREEN"                              \\\\ |/  //\n"ANSI_COLOR_RESET);
		printf("                          ^^^^^^^^^^^^^^^\n");
		printf("                           ["ANSI_COLOR_CYAN"1"ANSI_COLOR_RESET"] Flor roja\n");
		printf("\n+------------------------------------------------------------------+\n");
		printf(">");
		scanf("%d", &ch);
		if (ch == 1) 
		{
			printf("> Has guardado Flor roja en el inventario.\n");
			tieneFlorRoja = 1;
			florCogidaR = 1;
		}
	}
	else 
	{
		printf("\n> Aquí no hay nada que puedas coger.\n");
	}
	printf("\n+------------------------------------------------------------------+\n");
    printf(ANSI_COLOR_GREEN" Presiona cualquier tecla para volver...\n"ANSI_COLOR_RESET);
	getch();
}

void muestraAcciones()
{
	printf("+------------------------------------------------------------------+\n");
	printf("> Que quieres hacer?\n");
	printf("+------------------------------------------------------------------+\n");
	printf(" ["ANSI_COLOR_CYAN"1"ANSI_COLOR_RESET"] Hablar con Madeleine.                          ["ANSI_COLOR_YELLOW"i"ANSI_COLOR_RESET"] Inventario\n");
	printf(" ["ANSI_COLOR_CYAN"2"ANSI_COLOR_RESET"] Hablar con Esparrou.                           ["ANSI_COLOR_YELLOW"r"ANSI_COLOR_RESET"] Recoger\n");
	printf(" ["ANSI_COLOR_CYAN"3"ANSI_COLOR_RESET"] Hablar con Kaneda.\n");
	printf(" ["ANSI_COLOR_CYAN"4"ANSI_COLOR_RESET"] Moverse.\n");
	printf("+------------------------------------------------------------------+\n");
	printf(">");
}

void HablarMadeleine(FILE *fptr)
{
	printf("+------------------------------------------------------------------+\n");
	printf("                             MADELEINE                              \n");
	printf("+------------------------------------------------------------------+\n\n");
	rewind(fptr);
	print_image(fptr, 145, 156);
	printf("+------------------------------------------------------------------+\n\n");
	char nota = 0;
	if (escena == 1)
	{
		printf("Madeleine no tiene nada que decirte.\n");
	}
	if (escena == 2 && !encendidoFaro)
	{
		char salir = 0;
		printf("  Mira la puerta de la casa, hay una hoja colgada! \n\n");
		printf("  Quieres leerla? (y/n) \n");
		printf("\n+------------------------------------------------------------------+\n");
		char ch;
		printf("\033[1B");
		while(!salir)
		{
			ch = 0;
			scanf("%c", &ch);
			if (ch == 121)
			{
				rewind(fptr);
				system("cls");
				printf("+------------------------------------------------------------------+\n");
				printf("                         NOTA EN LA PUERTA                          \n");
				printf("+------------------------------------------------------------------+\n\n");
				print_image(fptr, 167, 180);
				salir = 1;
				nota = 1;
			}
			else if (ch == 110) 
			{
				printf("+------------------------------------------------------------------+\n\n");
				printf("  Vale, cuando quieras nos vamos.\n");
				salir = 1;
			}
			else if (ch == 10) 
			{
				printf("\033[1A");
				printf("                                                                                              ");
				printf("\033[100D");
			}
		}		
	}
	if (escena == 3)
	{
		printf("Madeleine no tiene nada que decirte.\n");
	}
	if (escena == 4)
	{
		printf("Madeleine no tiene nada que decirte.\n");
	}
	if (escena == 5)
	{
		printf("Madeleine no tiene nada que decirte.\n");
	}
	if (escena == 6 && !herraduraCogida)
	{
		char salir = 0;
		printf("  Mira que he encontrado, es una herradura azul como\n");
		printf("  de la que habla la leyenda de BlueDonkey! \n\n");
		printf("  Quieres cogerla? (y/n) \n");
		printf("\n+------------------------------------------------------------------+\n");
		char ch;
		printf("\033[1B");
		while(!salir)
		{
			ch = 0;
			scanf("%c", &ch);
			if (ch == 121)
			{
				printf("+------------------------------------------------------------------+\n\n");
				printf("> Has guardado Herradura azul en el inventario.\n");
				tieneHerradura = 1;
				herraduraCogida = 1;
				salir = 1;
			}
			else if (ch == 110) 
			{
				printf("+------------------------------------------------------------------+\n\n");
				printf("  Vale, la dejo donde estaba.\n");
				salir = 1;
			}
			else if (ch == 10) 
			{
				printf("\033[1A");
				printf("                                                                                              ");
				printf("\033[100D");
			}
		}	
	}
	else if (escena == 6 && herraduraCogida)
	{
		printf("Madeleine no tiene nada que decirte.\n");
	}
	printf("\n+------------------------------------------------------------------+\n");
	if (!nota) printf(ANSI_COLOR_GREEN" Presiona cualquier tecla para dejar de hablar...\n"ANSI_COLOR_RESET);
	else printf(ANSI_COLOR_GREEN" Presiona cualquier tecla para dejar de leer...\n"ANSI_COLOR_RESET);
	getch();
}

void HablarEsparrou(FILE *fptr)
{
	printf("+------------------------------------------------------------------+\n");
	printf("                              ESPARROU                              \n");
	printf("+------------------------------------------------------------------+\n\n");
	rewind(fptr);
	print_image(fptr, 157, 166);
	printf("+------------------------------------------------------------------+\n\n");
	if (escena == 1)
	{
		printf("Esparrou no tiene nada que decirte.\n");
	}
	if (escena == 2)
	{
		printf("Esparrou no tiene nada que decirte.\n");
	}
	if (escena == 3)
	{
		printf("Esparrou no tiene nada que decirte.\n");
	}
	if (escena == 4)
	{
		printf("Esparrou no tiene nada que decirte.\n");
	}
	if (escena == 5)
	{
		printf("Esparrou no tiene nada que decirte.\n");
	}
	if (escena == 6)
	{
		printf("Esparrou no tiene nada que decirte.\n");
	}
	printf("\n+------------------------------------------------------------------+\n");
    printf(ANSI_COLOR_GREEN" Presiona cualquier tecla para dejar de hablar...\n"ANSI_COLOR_RESET);
	getch();
}

void HablarKaneda(FILE *fptr)
{
	printf("+------------------------------------------------------------------+\n");
	printf("                               KANEDA                               \n");
	printf("+------------------------------------------------------------------+\n\n");
	rewind(fptr);
	print_image(fptr, 133, 144);
	printf("+------------------------------------------------------------------+\n\n");
	if (escena == 1)
	{
		printf("  Algunos vecinos, cuando les he explicado sobre nuestra aventura,\n");
		printf("  me han dicho que si vamos al faro no podremos entrar ya que el \n");
		printf("  farero esta enfermo.\n");
	}
	if (escena == 2)
	{
		printf("Kaneda no tiene nada que decirte.\n");
	}
	if (escena == 3)
	{
		if (!encendidoFaro)
		{
			printf("  Recuerdas que la leyenda de BlueDonkey decia que tenias  \n");
			printf("  que ponerle la herradura azul para que se te mostrara el \n");
			printf("  camino al tesoro? Pues he escuchado que aparece en el \n");
			printf("  lago solo si el faro está encendido.\n");
			printf("  Lástima que el farero esté enfermo.\n");
		}
		else printf("Kaneda no tiene nada que decirte.\n");
	}
	if (escena == 4)
	{
		if (!encendidoFaro)
		{
			printf("  Recuerdas que la leyenda de BlueDonkey decia que tenias  \n");
			printf("  que ponerle la herradura azul para que se te mostrara el \n");
			printf("  camino al tesoro? Pues he escuchado que aparece en el \n");
			printf("  lago solo si el faro está encendido.\n");
			printf("  Lástima que el farero esté enfermo.\n");
		}
		else printf("Kaneda no tiene nada que decirte.\n");
	}
	if (escena == 5)
	{
		printf("Kaneda no tiene nada que decirte.\n");
	}
	if (escena == 6)
	{
		printf("Kaneda no tiene nada que decirte.\n");
	}
	printf("\n+------------------------------------------------------------------+\n");
    printf(ANSI_COLOR_GREEN" Presiona cualquier tecla para dejar de hablar...\n"ANSI_COLOR_RESET);
	getch();
}

void DescribeEscena(FILE *fptr)
{
	if (escena == 2) {
		rewind(fptr);
		printf("+------------------------------------------------------------------+\n");
		printf("                          CASA DEL FARERO                           \n");
		printf("+------------------------------------------------------------------+\n");
		print_image(fptr, 30, 44);
		printf("\n");
		rewind(fptr);
		print_image(fptr, 24, 29);
		printf("\n");
		printf(" Buzón:(");
		if (entregadaFlorAmarilla) printf(ANSI_COLOR_YELLOW"♣"ANSI_COLOR_RESET);
		if (entregadaFlorRoja) printf(ANSI_COLOR_RED"♣"ANSI_COLOR_RESET);
		printf(")\n");
	}
	if (escena == 1) {
		rewind(fptr);
		printf("+------------------------------------------------------------------+\n");
		printf("                            DONKEYVILLE                             \n");
		printf("+------------------------------------------------------------------+\n");
		print_image(fptr, 53, 64);
		printf("\n");
		rewind(fptr);
		print_image(fptr, 45, 52);
		printf("\n");
	}
	if (escena == 3) {
		rewind(fptr);
		printf("+------------------------------------------------------------------+\n");
		printf("                             LAGO TOGA                              \n");
		printf("+------------------------------------------------------------------+\n");
		print_image(fptr, 65, 86);
		printf("\n");
	}
	if (escena == 4) {
		rewind(fptr);
		printf("+------------------------------------------------------------------+\n");
		printf("                               FARO                                 \n");
		printf("+------------------------------------------------------------------+\n");
		print_image(fptr, 87, 101);
		printf("\n");
	}
	if (escena == 5) {
		rewind(fptr);
		printf("+------------------------------------------------------------------+\n");
		printf("                             BOSQUE SUR                             \n");
		printf("+------------------------------------------------------------------+\n\n");
		print_image(fptr, 103, 116);
		printf("\n");
	}
	if (escena == 6) {
		rewind(fptr);
		printf("+------------------------------------------------------------------+\n");
		printf("                            BOSQUE NORTE                            \n");
		printf("+------------------------------------------------------------------+\n\n");
		print_image(fptr, 118, 131);
		printf("\n");;
	}
	rewind(fptr);
}

int PuedeIr(int escena1, int escena2)
{
	int puede = 0;
	int i = 0;
	while (i < 3 && !puede)
	{
		if (mapa[escena1 - 1][i] == escena2 + 1) puede = 1;
		++i;
	}
	return puede;
}

void IrA()
{	
	printf("+------------------------------------------------------------------+\n");
	if (escena == 1) printf("> Ahora mismo estas en DonkeyVille, ");
	else if (escena == 2) printf("> Ahora mismo estas en la Casa del Farero, "); 
	else if (escena == 3) printf("> Ahora mismo estas en el Lago Toga, ");
	else if (escena == 4) printf("> Ahora mismo estas en el Faro, ");
	else if (escena == 5) printf("> Ahora mismo estas en el Bosque sur, ");
	else if (escena == 6) printf("> Ahora mismo estas en el Bosque norte, ");
	printf("a donde quieres ir?\n");
	printf("+------------------------------------------------------------------+\n");
	int lugar;
	int indice = 1;
	int i = 0;
	escenas[0] = 0;
	escenas[1] = 0;
	escenas[2] = 0;
	while (i < 6)
	{
		if (PuedeIr(escena, i) == 1) {
			if (i == 0) printf(" [" ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "] DonkeyVille\n", indice);
			else if (i == 1) printf(" [" ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "] Casa del Farero\n", indice);
			else if (i == 2) printf(" [" ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "] Lago Toga\n", indice);
			else if (i == 3) printf(" [" ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "] Faro\n", indice);
			else if (i == 4) printf(" [" ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "] Bosque sur\n", indice);
			else if (i == 5) printf(" [" ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "] Bosque norte\n", indice);
			escenas[indice - 1] = i;
			++indice;
		}
		++i;
	}
	printf("+------------------------------------------------------------------+\n");
	printf("> ");
}


void JuegoFinalizado()
{

}

void main()
{
	char *filename = "pantalla.txt";
    FILE *fptr = NULL;
 	if((fptr = fopen(filename,"r")) == NULL)
	{
		fprintf(stderr,"error opening file %s\n",filename);
		return 1;
	}
	
	system("cls");
	SetConsoleOutputCP(CP_UTF8);
	
	printf("\nLa leyenda de DonkeyVille\n");
	printf("\nPulsa cualquier tecla para empezar..\n");
	getch();
	escena = 1;
	char opcion;
	char acabado = 0;

	while (acabado == 0) 
	{
		system("cls");
		DescribeEscena(fptr);
		muestraAcciones();
		scanf("%c", &opcion);
		switch(opcion) {
			case 49:
				system("cls");
				HablarMadeleine(fptr);
				break;
			case 50:
				system("cls");
				HablarEsparrou(fptr);
				break;
			case 51:
				system("cls");
				HablarKaneda(fptr);
				break;
			case 52:
				fin = 1;
				clock_t time;
				time = clock();
				float t;
				system("cls");
				char lop = 1;
				printf("+------------------------------------------------------------------+\n");
				printf("                                MAPA                                \n");
				printf("+------------------------------------------------------------------+\n");
				print_image(fptr, 0, 23);
				IrA();
				
				COORD coord;
				coord.X = posxy[escena-1][0];
				coord.Y = posxy[escena-1][1];
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				printf(ANSI_COLOR_YELLOW"█"ANSI_COLOR_RESET);
				coord.X = 1;
				coord.Y = 34;	
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				
				int ch;

				while (fin)
				{
					if (kbhit()) {
						scanf("%d", &ch);
						printf("%d\n", ch);
						
						escena = escenas[ch-1]+1;
						fin = 0;
						rewind(fptr);
					}					
				}
				break;
			
			case 105:
				Usar();
				if (entregadaFlorRoja && entregadaFlorAmarilla) encendidoFaro = 1;
				if (puestaHerradura) acabado = 1;
				break;
			case 114:
			    system("cls");
				Recoger();
				break;
		}
		system("cls");
		printf("> HAS GANADO!!\n");
	}	
	fclose(fptr);
}











