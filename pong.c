//PROGRAMA BASADO EN ANTIGUO JUEGO DE PONG

#include<stdio.h>
#include<string.h>
#include<windows.h>
#define V 25
#define H 95
#define P 5

typedef struct{
	int x, y;
	int modY, modX;
	int tam;
	char imagen;
}discos;

discos yo;
discos IA;
discos pelota[P];

void inicio(char campo[V][H], int *N);
void intro_campo(char campo[V][H]);
void intro_datos(char campo[V][H], int *N);
void movimiento(char campo[V][H]);
void toca(char campo[V][H], int *muerto, int *N);
void dibujar(char campo[V][H]);

int main(){
	
	char campo[V][H];
	int muerto = 0;
	int N = 0;
	
	inicio(campo, &N);
	intro_datos(campo,&N);
	dibujar(campo);
	
	while(muerto!=1){
		system("cls");
		movimiento(campo);//movemos
		toca(campo, &muerto, &N); //vemos si rebota
		intro_campo(campo);//borramos todo y reescribimos campo
		intro_datos(campo, &N); //reescribimos el resto de datos: pelota, jugadores, etc.
		dibujar(campo); //dibujamos
	}	
}


/**************FUNCIÓN: DONDE VOY A INICIALIZAR ALGUNAS PARTES. INTRODUZCO FUNCIONES PARA EMPEZAR ***************/
void inicio(char campo[V][H], int *N){
	
	int i, j;
	
	yo.y = 2;
	yo.x = 3;
	
	IA.y = 2;
	IA.x = H - 4;
	
	(*N)++;
	pelota[0].y = 10;
	pelota[0].x = 40;
	pelota[0].modY = 1;
	pelota[0].modX = 1;


	IA.modY = 1;	
	
	intro_campo(campo);
	intro_datos(campo, N);
		
}


/**************FUNCIÓN: INICIO LOS VALORES DE MI CAMPO ***************/
void intro_campo(char campo[V][H]){
	
	int i, j;
	
	for(i=0;i<V;i++)
	{
		for(j=0;j<H;j++)
		{
			if(i==0 || i ==V-1)
			{
				campo[i][j] = '-';
			}
			else
			{
				if(j==0 || j==H-1)
				{
					campo[i][j] = '|';
				}
				else
				{
					campo[i][j] = ' ';
				}
			}	
			
		}
	}
}


/**************FUNCIÓN: INICIO LOS VALORES RESTANTES: MARCADORES,PELOTA,...  ***************/
void intro_datos(char campo[V][H], int *N){
	
	int i, j;
	
	yo.tam = yo.y + 7;
	IA.tam = IA.y + 20;
	
	for(i=0;i<*N;i++){
		pelota[i].x = pelota[i].x + pelota[i].modX;
		pelota[i].y = pelota[i].y + pelota[i].modY;
		pelota[i].imagen = 'O';
		
		campo[pelota[i].y][pelota[i].x] = pelota[i].imagen;
	}
	
	for(i=0;i<H;i++){
		if(i==yo.x){
			for(j=yo.y;j<yo.tam;j++){
				campo[j][i] = 'X';
			}
		}
		if(i==IA.x)
		{
			for(j=IA.y;j<IA.tam;j++){
				campo[j][i] = 'X';
			}
		}
	}
	
	
}


/**************FUNCIÓN: GENERAR LOS MOVIMIENTOS  ***************/
void movimiento(char campo[V][H]){
	int i, j, key;
		
		if(kbhit()==1) //con esto si pulsas un botón te devuelve un 1
		{
			key=getch(); //lo mismo que el scanf pero sin tener que pulsar intro
			if( (key == '8') && (yo.y>1) ){
				yo.y = yo.y - 1;
			}
			
			if( (key == '2') && (yo.tam < V-1) ){
				yo.y = yo.y + 1;
			}
		}
		
		if(IA.y==1 || IA.tam == 24){
			IA.modY = IA.modY * (-1);
		}
		
		IA.y = IA.y + IA.modY;
		
}


/**************FUNCIÓN: SABER SI LA PELOTA REBOTA O NO ***************/
void toca(char campo[V][H], int *muerto, int *N){
		
		int i;
		
		for(i=0;i<=*N;i++)
		{
			if( (pelota[i].x) == 3)
			{
				if(pelota[i].y > yo.y && pelota[i].y < yo.tam )
				{
					pelota[i].modX = pelota[i].modX * (-1);
					
				}
			}
		
			if(pelota[i].x == H-4)
			{
				if(pelota[i].y > IA.y && pelota[i].y < IA.tam)
				{
					pelota[i].modX = pelota[i].modX * (-1);
					
					if(*N<P){
					
						(*N)++;
				
						
						pelota[*N-1].y = 10;
						pelota[*N-1].x = 40;
						pelota[*N-1].modY = 1;
						pelota[*N-1].modX = 1;
					}
				}
			}
			
			if(pelota[i].y == 1 || pelota[i].y==24 )
			{
				pelota[i].modY = pelota[i].modY * (-1);
			}
			
			if(pelota[i].x == 1 || pelota[i].x == H-1){
				*muerto = 1;
			}
		}
		
}


/**************FUNCIÓN: DIBUJO LOS DATOS ***************/
void dibujar(char campo[V][H]){
	int i, j;
	
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			printf("%c",campo[i][j]);
		}
		printf("\n");
	}
}
