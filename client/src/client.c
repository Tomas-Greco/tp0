#include "client.h"
#include <readline/readline.h>
#include <commons/config.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* clave;

	t_log* logger = iniciar_logger();
	t_config* config = iniciar_config();

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	//log_info(logger, "Hola soy un log");

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	clave = config_get_string_value(config,"CLAVE");

	// Loggeamos el valor de config
	/*log_info(logger, "IP: %s", ip);
	log_info(logger, "PUERTO: %s", puerto);
	log_info(logger, "CLAVE: %s", clave);/*

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(clave, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* logger = log_create("tp0.log", "tp0", true, LOG_LEVEL_INFO);
	if (logger == NULL){
		printf("No se pudo crear el logger");
		abort();
	}
	return logger;
}

t_config* iniciar_config(void)
{
	t_config* config = config_create("cliente.config");
	if (config == NULL){
		printf("No se pudo crear la config");
		abort();
	}

	return config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	leido = readline("> ");
	while(strcmp(leido,"") != 0){
		free(leido);
		leido = readline("> ");
		log_info(logger, "Ingresaste: %s", leido);
	}

		free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	leido = readline("> ");
	while(strcmp(leido,"") != 0){
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
		leido = readline("> ");
	}

	free(leido);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
