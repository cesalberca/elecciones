#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pointeraser.h"

FILE *ficheroImportado;
FILE *ficheroHtml;

#define MAX_PROVINCIAS 51
// Numero de partidos politicos en estas elecciones.
#define MAX_PARTIDOS 6

struct Provincia {
  char nombre[100];
  int diputados;
  char votosPP[100];
  char votosPsoe[100];
  char votosIu[100];
  char votosUpyd[100];
  char votosPodemos[100];
  char votosCiudadanos[100];
  int diputadosArray[6];
};

// Generamos un array de la estructura Provincia.
struct Provincia provincias[MAX_PROVINCIAS];
// Ya que los votos son recogidos en forma de caracter, éstos han de ser pasados a int para poder operar con ellos. Los guardamos en un array de int.
int arrayVotos[MAX_PROVINCIAS][MAX_PARTIDOS];

void mostrarMenu();
void inicializacionDiputados();
void importarFichero();
void rellenarVotosProvincias();
void dhondt();
void generarHtml();
int quitarPuntos();

struct Provincia madrid = {"Madrid", 36, "0", "0", "0", "0", "0", "0"};
struct Provincia barcelona = {"Barcelona", 34, "0", "0", "0", "0", "0" ,"0"};
struct Provincia valencia = {"Valencia", 16, "0", "0", "0", "0", "0", "0"};
struct Provincia alicante = {"Alicante", 12, "0", "0", "0", "0", "0", "0"};
struct Provincia sevilla = {"Sevilla", 12, "0", "0", "0", "0", "0", "0"};
struct Provincia malaga = {"Malaga", 10, "0", "0", "0", "0", "0", "0"};
struct Provincia murcia = {"Murcia", 10, "0", "0", "0", "0", "0", "0"};
struct Provincia cadiz = {"Cadiz", 8, "0", "0", "0", "0", "0", "0"};
struct Provincia vizcaya = {"Vizcaya", 8, "0", "0", "0", "0", "0", "0"};
struct Provincia laCoruna = {"La Coruna", 8, "0", "0", "0", "0", "0", "0"};
struct Provincia palmas = {"Las Palmas", 8, "0", "0", "0", "0", "0", "0"};
struct Provincia asturias = {"Asturias", 8, "0", "0", "0", "0", "0", "0"};
struct Provincia tenerife = {"Santa Cruz de Tenerife", 7, "0", "0", "0", "0", "0", "0"};
struct Provincia zaragoza = {"Zaragoza", 7, "0", "0", "0", "0", "0", "0"};
struct Provincia pontevedra = {"Pontevedra", 7, "0", "0", "0", "0", "0", "0"};
struct Provincia granada = {"Granada", 7, "0", "0", "0", "0", "0", "0"};
struct Provincia tarragona = {"Tarragona", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia cordoba = {"Cordoba", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia gerona = {"Gerona", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia guipuzcoa = {"Guipuzcoa", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia toledo = {"Toledo", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia almeria = {"Almeria", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia badajoz = {"Badajoz", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia jaen = {"Jaen", 6, "0", "0", "0", "0", "0", "0"};
struct Provincia navarra = {"Navarra", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia castellon = {"Castellon", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia cantabria = {"Cantabria", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia valladolid = {"Valladolid", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia ciudadReal = {"Ciudad Real", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia huelva = {"Huelva", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia leon = {"Leon", 5, "0", "0", "0", "0", "0", "0"};
struct Provincia lerida = {"Lerida", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia caceres = {"Caceres", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia albacete = {"Albacete", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia burgos = {"Burgos", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia salamanca = {"Salamanca", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia lugo = {"Lugo", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia orense = {"Orense", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia laRioja = {"La Rioja", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia alava = {"Alava", 4, "0", "0", "0", "0", "0", "0"};
struct Provincia guadalajara = {"Guadalajara", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia huesca = {"Huesca", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia cuenca = {"Cuenca", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia zamora = {"Zamora", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia avila = {"Avila", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia palencia = {"Palencia", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia segovia = {"Segovia", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia teruel = {"Teruel", 3, "0", "0", "0", "0", "0", "0"};
struct Provincia soria = {"Soria", 2, "0", "0", "0", "0", "0", "0"};
struct Provincia ceuta = {"Ceuta", 1, "0", "0", "0", "0", "0", "0"};
struct Provincia melilla = {"Melilla", 1, "0", "0", "0", "0", "0", "0"};

int main(int argc, char *argv[]) {
  provincias[0] = madrid;
  provincias[1] = barcelona;
  provincias[2] = valencia;
  provincias[3] = alicante;
  provincias[4] = sevilla;
  provincias[5] = malaga;
  provincias[6] = murcia;
  provincias[7] = cadiz;
  provincias[8] = vizcaya;
  provincias[9] = laCoruna;
  provincias[10] = palmas;
  provincias[11] = asturias;
  provincias[12] = tenerife;
  provincias[13] = zaragoza;
  provincias[14] = pontevedra;
  provincias[15] = granada;
  provincias[16] = tarragona;
  provincias[17] = cordoba;
  provincias[18] = gerona;
  provincias[19] = guipuzcoa;
  provincias[20] = toledo;
  provincias[21] = almeria;
  provincias[22] = badajoz;
  provincias[23] = jaen;
  provincias[24] = navarra;
  provincias[25] = castellon;
  provincias[26] = cantabria;
  provincias[27] = valladolid;
  provincias[28] = ciudadReal;
  provincias[29] = huelva;
  provincias[30] = leon;
  provincias[31] = lerida;
  provincias[32] = caceres;
  provincias[33] = albacete;
  provincias[34] = burgos;
  provincias[35] = salamanca;
  provincias[36] = lugo;
  provincias[37] = orense;
  provincias[38] = laRioja;
  provincias[39] = alava;
  provincias[40] = guadalajara;
  provincias[41] = huesca;
  provincias[42] = cuenca;
  provincias[43] = zamora;
  provincias[44] = avila;
  provincias[45] = palencia;
  provincias[46] = segovia;
  provincias[47] = teruel;
  provincias[48] = soria;
  provincias[49] = ceuta;
  provincias[50] = melilla;

  int opcion;

  do {
    mostrarMenu();
    scanf("%i", &opcion);

    // Bloqueamos al usuario de entrar un numero fuera de rango.
    while (opcion < 1 || opcion > 3) {
      puts("Opcion incorrecta. Introduce otra opcion:");
      scanf("%i", &opcion);
    }

    switch (opcion) {
      case 1:
        inicializacionDiputados();
        importarFichero();
        rellenarVotosProvincias();
        dhondt();
        break;
      case 2:
        generarHtml();
        break;
      case 3:
        puts("Gracias por usar nuestro programa.");
        break;
    }
  } while(opcion != 3);
}

void mostrarMenu() {
  // system("cls");
  puts("1. Importar archivo");
  puts("2. Exportar archivo");
  puts("3. Salir");
}

void inicializacionDiputados() {
  int i;
  for (i = 0; i < MAX_PROVINCIAS; i++) {
    int j;
    for (j = 0; j < MAX_PARTIDOS; j++) {
      // Inicializamos los diputados de cada partido a 0.
      provincias[i].diputadosArray[j] = 0;
    }
  }
}

void importarFichero() {
  char nombre[200];
  char linea1[100],
       linea2[100],
       linea3[100],
       linea4[100],
       linea5[100],
       linea6[100],
       linea7[100],
       linea8[100],
       linea9[100],
       linea10[100],
       linea11[100],
       linea12[100],
       linea13[100];
  int eofReturn = 0;

  puts("Introduce el nombre del archivo txt a importar. No hace falta que pongas la extension:");
  scanf("%s", nombre);
  // system("cls");
  puts("Datos importados con exito, pulse una tecla para continuar...");
  getch();
  // Concatenamos el nombre con .txt
  strcat(nombre, ".txt");

  ficheroImportado = fopen(nombre, "r");

  do {
    eofReturn = fscanf(ficheroImportado, "%s", linea1);
    // Leemos de 13 en 13 líneas hasta que se termine el archivo.
    fscanf(ficheroImportado, "%s", linea2);
    fscanf(ficheroImportado, "%s", linea3);
    fscanf(ficheroImportado, "%s", linea4);
    fscanf(ficheroImportado, "%s", linea5);
    fscanf(ficheroImportado, "%s", linea6);
    fscanf(ficheroImportado, "%s", linea7);
    fscanf(ficheroImportado, "%s", linea8);
    fscanf(ficheroImportado, "%s", linea9);
    fscanf(ficheroImportado, "%s", linea10);
    fscanf(ficheroImportado, "%s", linea11);
    fscanf(ficheroImportado, "%s", linea12);
    fscanf(ficheroImportado, "%s", linea13);

    int i;
    for (i = 0; i < MAX_PROVINCIAS; i++) {
      if (strcmp(linea1, provincias[i].nombre) == 0) {
        // Rellenamos cada posición del array de estructuras con los datos importados.
        strcpy(provincias[i].votosPP, linea3);
        strcpy(provincias[i].votosPsoe, linea5);
        strcpy(provincias[i].votosIu, linea7);
        strcpy(provincias[i].votosUpyd, linea9);
        strcpy(provincias[i].votosPodemos, linea11);
        strcpy(provincias[i].votosCiudadanos, linea13);
      }
    }
  } while((eofReturn != EOF));

  fclose(ficheroImportado);
}

void rellenarVotosProvincias() {
  int i;
  for (i = 0; i < MAX_PROVINCIAS; i++) {
    // Llenamos el array con los votos importados en la estructura.
    // printf("%s\n", provincias[i].votosPP);
    arrayVotos[i][0] = quitarPuntos(provincias[i].votosPP);
    arrayVotos[i][1] = quitarPuntos(provincias[i].votosPsoe);
    arrayVotos[i][2] = quitarPuntos(provincias[i].votosIu);
    arrayVotos[i][3] = quitarPuntos(provincias[i].votosUpyd);
    arrayVotos[i][4] = quitarPuntos(provincias[i].votosPodemos);
    arrayVotos[i][5] = quitarPuntos(provincias[i].votosCiudadanos);
  }
}

void dhondt() {
  int i;
  int j;
  int k;
  int l;
  int m;

  int mayor = 0;
  // Recorremos el array de estructuras provincias
  for (i = 0; i < MAX_PROVINCIAS; i++) {
    float divisionesVotos[provincias[i].diputados][MAX_PARTIDOS];
    // Este bucle for realiza las divisiones y coloca los numeros en una tabla.
    for (j = 0; j < provincias[i].diputados; j++) {
          divisionesVotos[j][0] = arrayVotos[i][0] / (j + 1);
          divisionesVotos[j][1] = arrayVotos[i][1] / (j + 1);
          divisionesVotos[j][2] = arrayVotos[i][2] / (j + 1);
          divisionesVotos[j][3] = arrayVotos[i][3] / (j + 1);
          divisionesVotos[j][4] = arrayVotos[i][4] / (j + 1);
          divisionesVotos[j][5] = arrayVotos[i][5] / (j + 1);
    }
    // Recorremos la tabla en busca del numero del resultado de la division de los votos mas alta.
    for (k = 0; k < provincias[i].diputados; k++) {
      mayor = 0;
      for (l = 0; l < MAX_PARTIDOS; l++) {
        if (divisionesVotos[0][l] > divisionesVotos[0][mayor]) {
          mayor = l;
        }
      }

      // En caso de encontrar el mayor, corremos la fila entera del array, eliminando la primera posicion para las subsecuentes operaciones del algoritmo.
      for (m = 0; m < provincias[i].diputados; m++) {
        divisionesVotos[m][mayor] = divisionesVotos[m + 1][mayor];
      }

      // Este switch asignara los escanios de cada partido.
      if (arrayVotos[i][mayor] != 0) {
        switch (mayor) {
          case 0:
          provincias[i].diputadosArray[0] += 1;
          break;
          case 1:
          provincias[i].diputadosArray[1] += 1;
          break;
          case 2:
          provincias[i].diputadosArray[2] += 1;
          break;
          case 3:
          provincias[i].diputadosArray[3] += 1;
          break;
          case 4:
          provincias[i].diputadosArray[4] += 1;
          break;
          case 5:
          provincias[i].diputadosArray[5] += 1;
          break;
        }
      }
    }
  }
}

void generarHtml() {
  char nombre[100];

  printf("Introduce el nombre del archivo a exportar. No hace falta poner la extension\n");
  scanf("%s", nombre);
  strcat(nombre, ".html");
  ficheroHtml = fopen(nombre, "w");

  fputs("<!doctype html>\n", ficheroHtml);
  fputs("<html>\n", ficheroHtml);
  fputs("\t<head>\n", ficheroHtml);
  fputs("\t\t<meta charset='utf-8'>\n", ficheroHtml);
  fputs("\t\t<meta http-equiv='x-ua-compatible' content='ie-edge'>\n", ficheroHtml);
  fputs("\t\t<title>Práctica Programación | Adrían de la Gala y César Alberca</title>\n", ficheroHtml);
  fputs("\t\t<meta name='description' content='Tablas con diputados por partido y por comunidad según la ley de Dhont.'>\n", ficheroHtml);
  fputs("\t\t<meta name='viewport' content='width=device-width, initial-scale=1'>\n\n", ficheroHtml);
  fputs("\t\t<link rel='stylesheet' href='styles.css", ficheroHtml);
  fputs("'/>\n", ficheroHtml);
  fputs("\t</head>\n", ficheroHtml);
  fputs("\t<body>\n", ficheroHtml);
  fputs("\t\t<div>\n", ficheroHtml);

  int i;
  for (i = 0; i < MAX_PROVINCIAS; i++) {
    fputs("\t\t\t\t<table rules='all' border='1'>\n", ficheroHtml);
    fputs("\t\t\t\t\t<tr>\n", ficheroHtml);
    fputs("\t\t\t\t\t\t<th colspan='2' align='center'>", ficheroHtml);
    // Nombre de cada provincia
    fprintf(ficheroHtml, "%s", provincias[i].nombre);
    fputs("</th>\n", ficheroHtml);
    fputs("\t\t\t\t\t</tr>\n", ficheroHtml);

    int j;
    for (j = 0; j < MAX_PROVINCIAS; j++) {
      fputs("\t\t\t\t\t<tr>\n", ficheroHtml);
      switch (j) {
        case 0:
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fputs("PP", ficheroHtml);
          fputs("</td>", ficheroHtml);
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fprintf(ficheroHtml, "%i\n", provincias[i].diputadosArray[0]);
          fputs("</td>", ficheroHtml);
          break;
        case 1:
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fputs("PSOE", ficheroHtml);
          fputs("</td>", ficheroHtml);
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fprintf(ficheroHtml, "%i\n", provincias[i].diputadosArray[1]);
          fputs("</td>", ficheroHtml);
          break;
        case 2:
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fputs("IU", ficheroHtml);
          fputs("</td>", ficheroHtml);
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fprintf(ficheroHtml, "%i\n", provincias[i].diputadosArray[2]);
          fputs("</td>", ficheroHtml);
          break;
        case 3:
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fputs("UPYD", ficheroHtml);
          fputs("</td>", ficheroHtml);
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fprintf(ficheroHtml, "%i\n", provincias[i].diputadosArray[3]);
          fputs("</td>", ficheroHtml);
          break;
        case 4:
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fputs("Podemos", ficheroHtml);
          fputs("</td>", ficheroHtml);
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fprintf(ficheroHtml, "%i\n", provincias[i].diputadosArray[4]);
          fputs("</td>", ficheroHtml);
          break;
        case 5:
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fputs("Ciudadanos", ficheroHtml);
          fputs("</td>", ficheroHtml);
          fputs("\t\t\t\t\t\t<td>", ficheroHtml);
          fprintf(ficheroHtml, "%i\n", provincias[i].diputadosArray[5]);
          fputs("</td>", ficheroHtml);
          break;
      }
      fputs("</tr>\n", ficheroHtml);
    }

    fputs("</td>\n", ficheroHtml);
    fputs("\t\t\t\t\t</tr>\n", ficheroHtml);
    fputs("\t\t\t\t</table>\n", ficheroHtml);
  }
  fputs("\t\t</div>\n", ficheroHtml);
  fputs("\t</body>\n", ficheroHtml);
  fputs("</html>\n", ficheroHtml);

  fclose(ficheroHtml);
  // system("cls");
  puts("Datos exportados con exito, pulse una tecla para continuar...");
  getch();
}

int quitarPuntos(char *cadenaConPuntos) {
  int i=0;//Iterador del array de origen
	int iArrayDestino=0;//Iterador del array de destino
	char sCifraSP[100];//Array de char con la cifra Sin Puntos
	int lCifra;//Cifra destino

  if(strcmp(cadenaConPuntos, "0") == 0) {
    strcpy(sCifraSP, "0");
  } else {
    for (i=0;i<strlen(cadenaConPuntos);i++){
  		if (cadenaConPuntos[i]!='.') {
  			sCifraSP[iArrayDestino]=cadenaConPuntos[i];
  			iArrayDestino++;
        // printf("%c\n", sCifraSP[i]);
  		}
  	}
  }

	lCifra = atol(sCifraSP);
  printf("%i\n", lCifra);
	return lCifra;
}
