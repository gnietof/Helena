#include <stdio.h>
#include <stdlib.h>
//GNF: Añado esta librería para usar el toupper que convierte a mayúsculas
#include <ctype.h> 
	//GNF: Añado esta otra librería que nos va a ser útil para, por 
// ejemplo ,calcular la longitud de una palabra
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define NOM_MAX 50
#define LLETRES_MAX 100
#define GUIO_MAX 100
#define MAX_INTENTS 10

int main()
{
	int i, j, n_intents, n_lletres, n_parfit, n_aleat;
	char nom[NOM_MAX], paraula[LLETRES_MAX], lletra, guio[GUIO_MAX];
	FILE * fit;

	//obrim fitxer//

	fit = fopen("paraules.txt", "r");

	// GNF: Debes  tener en cuenta es que no puedes leer de un fichero 
	// sin haber antes comprobado que lo has abierto correctamente. 
	//    fscanf (fit, "%s", paraula);

	// mirem si el fitxer esta buit o no//

	if (fit == NULL)
	{
		printf("No s'ha trobat el fitxer.\n");
	}
	else
	{
		n_parfit = 0;

		//contem les paraules del fitxer per determinar el MIN i MAX de paraules//

		while (!feof(fit))
		{
			//GNF: Con el if nos aseguramos de que ha leido realmente una palabra
			if (fscanf(fit, "%s", paraula) > 0)
			{
				n_parfit++;
				//GNF: Mientras hacemos pruebas, compruebo que leo bien las palabras del fichero
				printf("%d %s\n", n_parfit, paraula);
			}
		}

		//GNF: Acuérdate de cerrar lo que abras cuando dejes de usarlo. Cerramos el fichero
		fclose(fit);

		if ((n_parfit < 1) || (n_parfit > 10))
		{
			printf("El joc no esta disponible.\n");
		}
		else
		// GNF: Aquí se te ha olvidado abrir la {
		{
			printf("Benvolgut/da al joc del penjat. Com et dius? ");
			scanf("%s", nom);

			//paraula aleatoria//
			// GNF: Piensa que en este punto ya has leído todo el fichero (cuando contabas todas
			// las palabras. No puedes volver a leerlo sin cerrarlo y abrilo o mover el punto
			// de lectura al principio

			// GNF: Ya sabes que hay n_parfit palabras en el fichero. Yo no volvería a usar la misma 
			// variable para moverme por el fichero porque una variable que se usa para más de 
			// una cosa hace difícil entender el programa
			// Perdón. No lo había entendido. En realidad, no entiendo muy bien porqué lees de nuevo 
			// las palabras para contarlas. Ya lo hiciste antes.
			// De hecho, como ya habías llegado al final, este bucle no hace nada. 
			// Quítalo
			/*
			                while (!feof(fit))
			                    {

			                    fscanf(fit,"%s",paraula);    	//numero paraules fitx//
			                    n_parfit++;
			                    }
			*/

			srand(time(NULL));
			n_aleat = rand() % n_parfit;
			printf("Rand: %d/%d\n", n_aleat, n_parfit);

			// GNF: Yo quizás, en lugar de leer el fichero cada vez, guardaria todas las palabras
			// en una matriz de palabras una sola vez.

			fit = fopen("paraules.txt", "r");

			// GNF: Has contado las palabras. Lo has guardado en n_parfit. Ahora poner n_parfit a 
			// cero. Pierdes el contador. Te comento la línea
			//                 n_parfit=0;

			// GNF: El 'while' se usa cuando no sabes cuántas veces vas a tener que hacer algo. En 
			// este caso sí sabes que has de leer n_aleat palabras. Podrías usar un 'for'
			//                while (n_parfit < n_aleat)
			for (int i = 0; i < n_aleat; i++)
			{
				fscanf(fit, "%s", paraula);
				// GNF: El contador del número de palabras no debes tocarlo. No hace falta y pierdes el 
				// valor que ya habías encontrado.
				//                    n_parfit++;
			}
			//GNF: Acuérdate de cerrar lo que abras cuando dejes de usarlo. Cerramos el fichero
			fclose(fit);

			//GNF: Mientras hacemos pruebas, compruebo que tengo la palabra leída
			printf("Oculta: %s\n", paraula);

			//guions//

			//GNF: En realidad no hace falta que busques el '\0' para saber la longitud de la cadena.
			// A menos que os hayan dicho que lo hagáis así, yo usaría strlen()
			// Cambio tu codigo
			// GNF: No me gusta declarar las variables al principio porque luego cuesta ver
			// si ya la has declarado o no. Y puedes tener problemas si las reutilizas sin darte cuenta.
			// Yo pondría: int j=0;
			/*
				j=0;
			        while (paraula[j]!='\0')
			        {
			        	guio[j]= '-';
			            j++;
			        }
			*/
			n_lletres = strlen(paraula);
			for (int j = 0; j < n_lletres; j++)
			{
				guio[j] = '-';
			}
			guio[n_lletres] = '\0';

			//Numero de lletres de la paraula

			//GNF: Te falta la parte del juego (propiamente dicho). Déjame que le dé una pensada.
			// La parte que tiene algo más de complejidad es 'rellenar las letras y detectar que el 
			// juego ha terminado'.
			// Entiendo que podéis usar las funciones existentes en las librerías que has incluido
			// al principio del programa (stdio y stdlib). 
			// Esas funciones nos ayudarán a detectar de manera sencilla si una palabra contiene una 
			// letra (una o más veces) y a detectar si la palabra ya no tiene guiones que rellenar. 
			//GNF: El código que sigue lo podrías substituir simplemente por la función strlen que 
			// devuelve la longitud de una cadena (https://www.tutorialspoint.com/c_standard_library/c_function_strlen.htm). 
			// Uy, eso ya te lo había explicado antes. No se pueden dejar las cosas a medias

			/*
			  	n_lletres=0, i=0;
			  	while (paraula[i]!= '\0')
				    {
				    	n_lletres ++;
					i++;
				    }
			*/
			i = 0;
			char lletra;

//GNF: El juego continua mientras no hayamos superado el número de intentos y los guiones
// (que iremos substituyendo por letras) no sean iguales a la palabra buscada. 
// && es la forma de unir condiciones que se han de cumplir las dos
// || sería la forma de unirlas cuando sea una condición o la otra.
			while ((i < MAX_INTENTS) && strcmp(paraula, guio))
			{
// GNF: Incremento el contador de intentos
				i++;
// En cada intento imprimo los guiones. A medida que se aciertan letras habrá menos guiones
				printf("%s\n", guio);
// Pedimos la letra. es importante el espacio que va delante de %c para evitar cosas raras.
				printf("Intent %d. Lletra? ", i);
				scanf(" %c", &lletra);
// Busco la letra que me han  dado en cada una de las letras de la palabra
				for (int j = 0; j < n_lletres; j++)
				{
//GNF: Usamos toupper para asegurar que utilizamos caracteres en mayúsculas
// Si encuentro la letra, la substituyo por un guion en los guiones
					if (paraula[j] == toupper(lletra))
					{
						guio[j] = toupper(lletra);
					}
				}
			}

//GNF: Cuando el juego ha terminado y he salido del bucle puede haber sido porque haya 
// adivinado la palabra o haya llegado al límite de intentos. 
// Utilizo la función strmp para comparar los guiones con la palabra oculta. Si coinciden 
// la función strcmp devuelve un cero. El ! me permite negar (cambiar de falso a verdadero y
// de verdadero a falso) el resultado. En C un cero se considera FALSO. Lo niego y así si son
// iguales me devuelve cierto. Entonces muestro un mensaje de felicitación. En caso contrario ... 
			if (!strcmp(paraula, guio))
			{
				printf("Molt be.\n");
			}
			else
			{
				printf("Oh! La paraula era %s.\n", paraula);
			}

			//GNF: Ya lo habíamos calculado antes para 
			//	  n_lletres = strlen(paraula);
		}

		// GNF: Falta la parte del desarrollo del juego
	}

	//GNF: Uy. Lo cerrabas aquí lo comento.
	//  fclose(fit);
	return 0;
}   
