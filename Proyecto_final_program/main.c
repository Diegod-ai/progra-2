#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pasajeros.h"
#include "vuelos.h"

/* --- mainMenu:--- */
int mainMenu() {
    int op;
    
    system("cls");  // Para Windows
    
    printf("\n----- MENU DE OPCIONES -----\n");
    printf("1. Cargar informacion desde archivos\n");
    printf("2. Adicionar vuelo\n");
    printf("3. Adicionar pasajero\n");
    printf("4. Listar pasajeros de un vuelo\n");
    printf("5. Listar vuelos programados\n");
    printf("6. Listar vuelos realizados\n");
    printf("7. Buscar vuelos por cedula del pasajero\n");
    printf("8. Marcar vuelo como realizado\n");
    printf("9. Registrar pasajero a bordo\n");
    printf("10. Guardar y salir\n");
    printf("Seleccione una opcion: ");
    
    if (scanf("%d", &op) == 1) {
        while (getchar() != '\n' && getchar() != EOF);
    } else {
        while (getchar() != '\n' && getchar() != EOF);
        op = -1;
    }
    return op;
}

int main() {
    Pasajero listaPasajeros[MAX_PASAJEROS];
    Vuelo listaVuelos[MAX_VUELOS];
    int cantPasajeros = 0;
    int cantVuelos = 0;
    int op;

    /* Cargar al inicio (si existen) */
    cargarPasajeros(listaPasajeros, &cantPasajeros);
    cargarVuelos(listaVuelos, &cantVuelos);

    system("cls");  // Para Windows
    
    printf("Bienvenido operario a la Aerolinea VIAJAR.\n");

    do {    
        op = mainMenu();
         
        if (op < 1 || op > 10) {
            printf("Opcion invalida. Intente de nuevo.\n");
            printf("\nPresione Enter para continuar...");
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
            case 1:
                system("cls");  // Para Windows
                
                /* recarga desde archivos */
                cargarPasajeros(listaPasajeros, &cantPasajeros);
                cargarVuelos(listaVuelos, &cantVuelos);
                printf("Informacion cargada: %d pasajeros, %d vuelos.\n", cantPasajeros, cantVuelos);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;

            case 2:
                system("cls");
                adicionarVuelo(listaVuelos, &cantVuelos);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;

            case 3:
                system("cls");
                adicionarPasajero(listaPasajeros, &cantPasajeros, listaVuelos, cantVuelos);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;

            case 4: {
                system("cls");
                int nro;
                printf("Ingrese nro de vuelo: ");
                if (scanf("%d", &nro) != 1) { while (getchar() != '\n'); break; }
                listarPasajerosDeVuelo(listaPasajeros, cantPasajeros, nro);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;
            }

            case 5:
                system("cls");
                listarVuelosProgramados(listaVuelos, cantVuelos);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;

            case 6:
                system("cls");
                listarVuelosRealizados(listaVuelos, cantVuelos);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;

            case 7: {
                system("cls");
                int ced;
                printf("Ingrese cedula: ");
                if (scanf("%d", &ced) != 1) { while (getchar() != '\n'); break; }
                int idxP = buscarPasajeroPorCedula(listaPasajeros, cantPasajeros, ced);
                if (idxP == -1) {
                    printf("Pasajero no encontrado.\n");
                } else {
                    int nro = listaPasajeros[idxP].nroVuelo;
                    int idxV = buscarVuelo(listaVuelos, cantVuelos, nro);
                    if (idxV == -1) printf("Vuelo %d no existe en la base de vuelos.\n", nro);
                    else {
                        /* mostrar datos basicos del vuelo */
                        printf("Pasajero en vuelo %d: %s -> %s, fecha %s, hora %s, estado %d\n",
                            listaVuelos[idxV].nroVuelo,
                            listaVuelos[idxV].origen,
                            listaVuelos[idxV].destino,
                            listaVuelos[idxV].fecha,
                            listaVuelos[idxV].hora,
                            listaVuelos[idxV].estado);
                    }
                }
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;
            }

            case 8: {
                system("cls");
                marcarVueloRealizado(listaVuelos, cantVuelos);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;
            }

            case 9: {
                system("cls");
                int ced;
                printf("Ingrese cedula del pasajero: ");
                if (scanf("%d", &ced) != 1) { while (getchar() != '\n'); break; }
                registrarPasajeroABordo(listaPasajeros, cantPasajeros, ced);
                
                printf("\nPresione Enter para continuar...");
                while (getchar() != '\n');
                break;
            }

            case 10:
                system("cls");
                /* guardar y salir */
                guardarPasajeros(listaPasajeros, cantPasajeros);
                guardarVuelos(listaVuelos, cantVuelos);
                printf("Datos guardados. Saliendo...\n");
                break;
        }
        
    } while (op != 10);

    return 0;
}