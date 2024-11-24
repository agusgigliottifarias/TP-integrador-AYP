#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>


#define MAX_PALABRAS 20
#define MAX_LONGITUD 50
#define INTENTOS 6
#define MAX_JUGADORES 50


//---------------Struct para guradar el puntaje--------------
typedef struct {
    char nombre[50];
    int puntaje;
} Jugador;

//-------------------Declaración de funciones----------------
void leerRanking(char *archivo, Jugador jugadores[], int *cantidad);
void actualizarPuntaje(Jugador jugadores[], int *cantidad, char *nombre, int puntos);
void ordenarRanking(Jugador jugadores[], int *cantidad);
void guardarRanking(char *archivo, Jugador jugadores[], int *cantidad);
void mostrarRanking(Jugador jugadores[], int cantidadJugadores);
void cargando(void);
void munieco(int intentosRestantes);
void progreso(char *palabraEnjuego,int *LetrasAdivinadas);
int verificacion(char* palabraEnjuego,int* LetrasAdivinadas,char letra);
int puntaje(int tiempo,int intentosrestantes,int tamanio);
int play(int intentos, int tamanio, char* palabraEnJuego);
FILE* abrirArchivo();
void nombreJugador(char *usuario);
void reglasDeJuego(void);
void logo(void);
void eleccionPalabra(FILE *archivo, char palabras1[MAX_PALABRAS][MAX_LONGITUD], char palabraEnJuego[MAX_LONGITUD]);




//-------------------------Función para leer el ranking---------------------------------
void leerRanking(char *archivo, Jugador jugadores[], int *cantidad) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("No se encontró el archivo. Se creará uno nuevo.\n");
        (*cantidad) = 0; //No hay jugadores
        return;
    }


    (*cantidad) = 0;  // Inicializa el contador de jugadores
    while (fscanf(fp, "%s %d", jugadores[*cantidad].nombre, &jugadores[*cantidad].puntaje) == 2) {
        (*cantidad)++;
    }


    fclose(fp);
};




//--------------------Función para actualizar el puntaje de un jugador-----------------
void actualizarPuntaje(Jugador jugadores[], int *cantidad, char *nombre, int puntos) {
    //Existe
    for (int i = 0; i < *cantidad; i++) {
        if (strcmp(jugadores[i].nombre, nombre) == 0) {
            if (puntos > jugadores[i].puntaje) {  //Puntaje mayor
                jugadores[i].puntaje = puntos;
            }
            return;  
        }
    }


    //No existe
    strncpy(jugadores[*cantidad].nombre, nombre, sizeof(jugadores[*cantidad].nombre) - 1);
    jugadores[*cantidad].nombre[sizeof(jugadores[*cantidad].nombre) - 1] = '\0'; //
    jugadores[*cantidad].puntaje = puntos;
    (*cantidad)++;  // Aumenta la cantidad de jugadores
};




//--------------Función para ordenar el ranking por puntaje ------------------------
void ordenarRanking(Jugador jugadores[], int *cantidad) {
    for (int i = 0; i < *cantidad - 1; i++) {
        for (int j = 0; j < *cantidad - i - 1; j++) {
            if (jugadores[j].puntaje < jugadores[j + 1].puntaje) {
                Jugador temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }
};



//-----------------Función guardar ranking----------------------------
void guardarRanking(char *archivo, Jugador jugadores[], int *cantidad) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("El archivo no existe, se creará uno nuevo.\n");
    }

    
    Jugador jugadoresExistentes[100]; 
    int cantidadExistente = 0;


    if (fp) {
        while (fscanf(fp, "%s %d", jugadoresExistentes[cantidadExistente].nombre,
                      &jugadoresExistentes[cantidadExistente].puntaje) != EOF) {
            cantidadExistente++;
        }
        fclose(fp);
    }


    //Busca si el jugador existe o no 
    for (int i = 0; i < *cantidad; i++) {
        int encontrado = 0;
        for (int j = 0; j < cantidadExistente; j++) {
            if (strcmp(jugadores[i].nombre, jugadoresExistentes[j].nombre) == 0) {
                if (jugadores[i].puntaje > jugadoresExistentes[j].puntaje) {
                    jugadoresExistentes[j].puntaje = jugadores[i].puntaje;
                }
                encontrado = 1;
                break;
            }
        }
        // Si no se encontró, se agrega
        if (!encontrado) {
            jugadoresExistentes[cantidadExistente++] = jugadores[i];
        }
    }


    //pasa al archivo el ranking actualizado
    fp = fopen(archivo, "w");
    if (!fp) {
        printf("Error al guardar el archivo.\n");
        return;
    }


    for (int i = 0; i < cantidadExistente; i++) {
        fprintf(fp, "%s %d\n", jugadoresExistentes[i].nombre, jugadoresExistentes[i].puntaje);
    }


    fclose(fp);
}



//-----------------Función mostrar Ranking---------------------------------
void mostrarRanking(Jugador jugadores[], int cantidadJugadores) {
    printf("*********************************\n");
    printf("*         ¡RANKING!             *\n");
    printf("*********************************\n");
   
    printf("\nRanking actualizado:\n");
    for (int i = 0; i < cantidadJugadores; i++) {
        printf("%d. %s - %d puntos\n", i + 1, jugadores[i].nombre, jugadores[i].puntaje);
    }
};


//-----------------Función motrar cargando------------------
void cargando(void){
    printf("cargando");
    for (int i = 0; i < 72; i++){
        printf("-");
        fflush(stdout);
        Sleep(30);
       
    }
    printf("\n");    
    printf("\033[A\033[K");


};
//--------------------Función para moestrar el muñieco---------------------
void munieco(int intentosRestantes){
  switch(intentosRestantes)
  {
    case 5:
            printf("\t\t  _____\n");  
            printf("\t\t  |   \n");      
            printf("\t\t  |   \n");      
            printf("\t\t  |   \n");      
            printf("\t\t  O\n");        
            break;
        case 4:
            printf("\t\t  _____\n");  
            printf("\t\t  |   \n");   
            printf("\t\t  |   \n");   
            printf("\t\t  |   \n");   
            printf("\t\t  O\n");
            printf("\t\t  |\n");      
            break;
        case 3:
            printf("\t\t  _____\n");  
            printf("\t\t  |   \n");      
            printf("\t\t  |   \n");      
            printf("\t\t  |   \n");      
            printf("\t\t  O\n");
            printf("\t\t  |\\\n");      
            break;
        case 2:
            printf("\t\t  _____\n");  
            printf("\t\t  |   \n");    
            printf("\t\t  |   \n");    
            printf("\t\t  |   \n");    
            printf("\t\t  O\n");
            printf("\t\t /|\\\n");    
            break;
        case 1:
        printf("\t\t  _____\n");  
        printf("\t\t  |   \n");  
        printf("\t\t  |   \n");  
        printf("\t\t  |   \n");  
        printf("\t\t  O\n");
        printf("\t\t /|\\\n");    
        printf("\t\t / \n"); 
        break;

        case 0:
            printf("\033[0;31m");    
            printf("\t\t  _____\n");
            printf("\t\t  |   \n");  
            printf("\t\t  |   \n");      
            printf("\t\t  |   \n");      
            printf("\t\t  O\n");
            printf("\t\t /|\\\n");      
            printf("\t\t / \\\n");      
            printf("\033[0;0m");  
            break;
        default:
            break;
  }
};


//----------Función para muestrar el progreso de la palabra--------------
void progreso(char *palabraEnjuego,int *LetrasAdivinadas){
    int longitud = strlen(palabraEnjuego)-1;
    printf("Progreso: ");
    for (int i = 0; i < longitud ; i++) {
        if (LetrasAdivinadas[i]) {
            printf("%c ", palabraEnjuego[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
   


};


//-----------------Función que verifica si la letra se encontro------------------------
int verificacion(char* palabraEnjuego,int* LetrasAdivinadas,char letra){
    int encontrado = 0;
    int largo = strlen(palabraEnjuego);
    for (int i = 0; i < largo; i++) {
        if (palabraEnjuego[i] == letra && !LetrasAdivinadas[i]) {
            LetrasAdivinadas[i] = 1;
            encontrado = 1;
        }
    }
    return encontrado;


};


//--------------------------Función que realiza el puntaje------------------------------
int puntaje(int tiempo,int intentosrestantes,int tamanio){


    int puntajefinal = ((40*intentosrestantes)+20*tamanio)/(log10(tiempo+1));
    return puntajefinal;
};


//---------------------------Función del juego-------------------------------------------
int play(int intentos, int tamanio, char* palabraEnJuego) {
    int intentosRestantes = intentos;
    char letra;
    int letrasAdivinadas[tamanio];
    memset(letrasAdivinadas, 0, sizeof(letrasAdivinadas));
   
    int completado = 0;  // Inicializa completado como 0 (palabra no adivinada)
    time_t inicio = time(NULL);


    while(intentosRestantes >= 1 && completado == 0 ) {
        progreso(palabraEnJuego, letrasAdivinadas);
        printf("Intentos restantes: %d\n", intentosRestantes);
        printf("Ingrese la siguiente letra: ");
        scanf(" %c", &letra);


        printf("\033[2J");  
        printf("\033[H");  
        // Verifica si la letra está en la palabra
        if (!verificacion(palabraEnJuego, letrasAdivinadas, letra)) {
            intentosRestantes--;
            printf("La letra '%c' no está en la palabra.\n", letra);
        } else {
            printf("¡Bien hecho! La letra '%c' está en la palabra.\n", letra);
        }
       


        // Verifica si se completo
        completado = 1;
        for (int i = 0; i < tamanio; i++) {
            //printf("\nVR(%d): %d\n",i, letrasAdivinadas[i]); (depuración)
            if (!letrasAdivinadas[i]) {
                completado = 0; // Marca como no completada
            }
        }


        if (completado) {
            printf("¡Felicidades! Has adivinado la palabra: %s\n", palabraEnJuego);
            break;
        }


        munieco(intentosRestantes);
    }


    time_t final = time(NULL);
    if(intentosRestantes == 0){
        printf("Lo siento, te quedaste sin intentento, la palabra era: %s\n", palabraEnJuego);
       
    }


    double segundos = difftime(final, inicio);  
    //printf("Tiempo transcurrido: %.2f segundos\n", segundos); //mostrar tiempo (depuración)


    int puntajefinal = puntaje(segundos,intentosRestantes,tamanio);


    //printf("%d",puntajefinal); (depuración)
   
    return puntajefinal;
};




//---------------------------------Función para la temática y difultad---------------------------
FILE* abrirArchivo(){
    FILE *archivo = NULL;


    int dificultad, tematica,idioma;
    do{
        printf("Seleccione la temática:\n");
        printf("1: Países\n2: Marcas\n3: Comidas\n");
        printf("Ingrese la opción (1-3): ");
        scanf("%d",&tematica);
        if (tematica < 1 || tematica > 3) {
            printf("\033[0;31m"); //cambia de color a rojo
            printf("Recuerde que 1 es países, 2 es marcas, 3 es comidas.\n");
            printf("\033[0;0m");// color normal
            Sleep(4000); //4000 = 4seg
            printf("\033[A\033[K");
            printf("\n");
        }
    } while (tematica < 1 || tematica >3 );


    printf("\n");
    cargando();
   
    do{
        printf("Seleccione la dificultad:\n");
        printf("1: Fácil\n2: Medio\n3: Difícil\n");
        printf("Ingrese la opción (1-3): ");
        scanf("%d",&dificultad);
       if (dificultad < 1 || dificultad > 3) {
            printf("\033[0;31m");
            printf("Recuerde que 1 es fácil, 2 es medio, 3 es difícil.\n");
            printf("\033[0;0m");
            Sleep(4000);
            printf("\033[A\033[K");
            printf("\n");
        }
       
    } while (dificultad < 1 || dificultad> 3);


    printf("\n");
    cargando();


    do{
        printf("Seleccione el idioma de la palabra:\n");
        printf("1: Español\n2: Ingles\n");
        printf("Ingrese la opción (1-2): ");
        scanf("%d",&idioma);
        if (idioma < 1 || idioma > 3) {
            printf("\033[0;31m");
            printf("Recuerde que 1 es Español, 2 es Ingles.\n");
            printf("\033[0;0m");
            Sleep(4000);
            printf("\033[A\033[K");
            printf("\n");
        }
    } while (idioma < 1 || idioma >2 );


    printf("\n");
    cargando();
   
    switch (tematica) {
    case 1:  // Caso de países
        switch (dificultad) {
            case 1:
                if (idioma == 1) {
                    archivo = fopen("tematicas/paises/español/paisesfacil.txt", "r");
                } else {
                    archivo = fopen("tematicas/paises/ingles/paisesfacil.txt", "r");    
                }
                break;
            case 2:
                if (idioma == 1) {
                    archivo = fopen("tematicas/paises/español/paisesmedio.txt", "r");
                } else {
                    archivo = fopen("tematicas/paises/ingles/paisesmedio.txt", "r");
                }
                break;
            case 3:
                if (idioma == 1) {
                    archivo = fopen("tematicas/paises/español/paiseshardcore.txt", "r");
                } else {
                    archivo = fopen("tematicas/paises/ingles/paisesdificil.txt", "r");
                }
                break;
            default:
                break;
        }
        break;


    case 2:  // Caso de marcas
        switch (dificultad) {
            case 1:
                if (idioma == 1) {
                    archivo = fopen("tematicas/marcas/español/marcafacil.txt", "r");
                } else {
                    archivo = fopen("tematicas/marcas/ingles/marcafacil.txt", "r");
                }
                break;
            case 2:
                if (idioma == 1) {
                    archivo = fopen("tematicas/marcas/español/marcamedio.txt", "r");
                } else {
                    archivo = fopen("tematicas/marcas/ingles/marcamedio.txt", "r");
                }
                break;
            case 3:
                if (idioma == 1) {
                    archivo = fopen("tematicas/marcas/español/marcahardcore.txt", "r");
                } else {
                    archivo = fopen("tematicas/marcas/ingles/marcadificil.txt", "r");
                }
                break;
            default:
                break;
        }
        break;


    case 3:  // Caso de comidas
        switch (dificultad) {
            case 1:
                if (idioma == 1) {
                    archivo = fopen("tematicas/comidas/español/comidafacil.txt", "r");
                } else {
                    archivo = fopen("tematicas/comidas/ingles/comidafacil.txt", "r");
                }
                break;
            case 2:
                if (idioma == 1) {
                    archivo = fopen("tematicas/comidas/español/comidamedio.txt", "r");
                } else {
                    archivo = fopen("tematicas/comidas/ingles/comidamedio.txt", "r");
                }
                break;
            case 3:
                if (idioma == 1) {
                    archivo = fopen("tematicas/comidas/español/comidahardcore.txt", "r");
                } else {
                    archivo = fopen("tematicas/comidas/ingles/comidadificil.txt", "r");
                }
                break;
            default:
                break;
        }
        break;
    }


    if (archivo == NULL) {
        system("cls");
        printf("\033[0;31m");
        printf("No se pudo abrir el archivo. Verifique la temática,la dificultad o el idioma.\n");
        printf("\033[0;0m");
    }


    return archivo;
};


//-----------------------------------Función nombre del jugador-------------------------------
void nombreJugador(char *usuario) {
    printf("Ingrese su nombre: ");
    scanf("%99s", usuario); //99 para evitar overflow


    
    printf("Bienvenido");
    printf("\033[0;31m");
    printf(" %s", usuario);  
    printf("\033[0;0m"); //Rojo
    printf(" al ahorcado\n");
    printf("\n");
}


//---------------------------------------Función regla de juego------------------------------------
void reglasDeJuego(void){
    printf ("Las reglas son las siguientes, debe adivinar la palabra dentro del limite de intentos disponibles. \nSi se agotan los intentos la partida finalizara. Buena suerte... la va a necesitar \n");
    printf("Presione enter para continuar");
    while (getchar() != '\n');
    getchar();
};


//----------------------------------------Función logo-------------------------------------------
void logo(void){
    printf("\033[0;34m");
    printf ("\n\n");


    printf ("_________________________________________________________________________________________ \n");
    printf ("|    ____      _                                                          _              |\\ \n");
    printf ("|   / __ \\    | |        ____     _   ___    _____     _____  __         | |     ____    | \\ \n");
    printf ("|  / /  \\ \\   | |       / __ \\   | | / __|  / ___ \\   /  __ `/ /         | |    / __ \\   | |\n");
    printf ("| / /____\\ \\  | |___   / /  \\ \\  | |/ /    / /   \\_\\  | /  \\  |    _____ | |   / /  \\ \\  | |\n");
    printf ("| |  ____  |  |  __ \\  | |  | |  |   /     | |        | |  |  |   /  _  \\' |   | |  | |  | |\n");
    printf ("| | /    \\ |  | |  \\ \\ | |  | |  |  /      | |    _   | |  |  |   | / \\    |   | |  | |  | |\n");
    printf ("| | |    | |  | |  | | \\ \\__/ /  | |       \\ \\___/ /  | \\__/  |   | \\_/    |   \\ \\__/ /  | |\n");
    printf ("| |_|    |_|  |_|  |_|  \\____/   |_|        \\_____/   \\_____,\\_\\  \\____/\\_/     \\____/   | |\n");
    printf ("|________________________________________________________________________________________| |\n");
    printf (" \\_________________________________________________________________________________________|\n");




    printf("\033[0;0m");


};


//-------------------------------------------Función para elección palabra-----------------------------------
void eleccionPalabra(FILE *archivo, char palabras1[MAX_PALABRAS][MAX_LONGITUD], char palabraEnJuego[MAX_LONGITUD]) {
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
   
    srand(time(NULL)); 
    int random1 = rand() % MAX_PALABRAS; 
    int contador1 = 0;
   
    while (fgets(palabras1[contador1], sizeof(palabras1[contador1]), archivo)) {
        palabras1[contador1][strcspn(palabras1[contador1], "\n")] = 0;  
        if (contador1 == random1) {
            strcpy(palabraEnJuego, palabras1[contador1]); 
            break; //sale del bloque while
        }
        contador1++;
    }
};


//------------------------------Función main-------------------------------------
int main () {
    logo ();
    Jugador jugadores[MAX_JUGADORES];
    int cantidad = 0; // variable cantidad de jugadores
    char *archivoRanking = "ranking.txt";
    leerRanking(archivoRanking, jugadores, &cantidad);
    char usuario[100];
    int terminado;
   
    do {
        nombreJugador(usuario);
        reglasDeJuego();
        char palabras[MAX_PALABRAS][MAX_LONGITUD],palabraEnJuego[MAX_LONGITUD];
        int contador = 0;
        cargando();
        FILE* archivo = abrirArchivo();
        if (archivo != NULL) {
            eleccionPalabra(archivo, palabras, palabraEnJuego);
            fclose(archivo);
        }    
       
        char caracteres[MAX_LONGITUD];
        int tamanio = strlen(palabraEnJuego);
        tamanio--; //le restamos 1 ya que toma el \0
       
        for (int i = 0; i < tamanio; i++) {
            caracteres[i] = palabraEnJuego[i];
        }
       
       
        int intentos = INTENTOS;
       
        int puntaje = play(intentos, tamanio, palabraEnJuego);
       
        do {
       
        printf("Desea volver a jugar o terminar el juego\n");
        printf("Presione (1) para terminar o (0) para continuar: ");
           
       
        scanf("%d", &terminado);
       
       
       
       
        if (terminado != 0 && terminado != 1) {
            printf("\033[0;31m");
            printf("Entrada inválida\n");
            printf("\033[0;0m");
            Sleep(4000);  
            printf("\033[A\033[K");
            printf("\n");
        }


        } while (terminado != 0 && terminado != 1);  
       
        printf("\n\n");
       
        //Ranking
        actualizarPuntaje(jugadores, &cantidad, usuario, puntaje);
        ordenarRanking(jugadores, &cantidad);
        guardarRanking(archivoRanking, jugadores, &cantidad);
       
    } while (terminado == 0);  
       
        mostrarRanking(jugadores, cantidad);
        printf("Juego terminado. ¡Gracias por jugar!\n");


    return 0;
 
}