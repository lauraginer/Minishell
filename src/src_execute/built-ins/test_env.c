/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:05:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/16 21:48:39 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

// Declaraciones para evitar errores de compilación
t_list *copy_env_var(char **envp)
{
	int		i;
	t_list	*new_node;
	t_list	*my_env;
	char	*copy;

	i = -1;
	my_env = NULL;
	while (envp[++i])
	{
		copy = ft_strdup(envp[i]);
		if (!copy)
		{
			free_env_list(my_env);
			return (NULL);
		}
		new_node = ft_lstnew(copy);
		if (!new_node)
		{
			free(copy);
			free_env_list(my_env);
			return (NULL);
		}
		ft_lstadd_back(&my_env, new_node);
	}
	return (my_env);
} 
void free_env_list(t_list *env_list)
{
	t_list	*aux;

	while (env_list)
	{
		aux = env_list->next;
		free (env_list->content);
		free (env_list);
		env_list = aux;
	}
}
// Función para imprimir el directorio actual (ayuda a ver si el cd funcionó)
void print_current_dir(void)
{
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, PATH_MAX) != NULL)
        printf("📂 Directorio actual: \033[1;34m%s\033[0m\n", cwd);
    else
        perror("getcwd");
}

// Función para imprimir un mensaje de ayuda
void print_help(void)
{
    printf("\n\033[1;33mUso del comando cd de prueba:\033[0m\n");
    printf("  ./test_env cd               - Ir al HOME\n");
    printf("  ./test_env cd ruta          - Ir a la ruta especificada\n");
    printf("  ./test_env cd ~             - Ir al HOME\n");
    printf("  ./test_env cd -             - Ir al directorio anterior\n");
    printf("  ./test_env cd ..            - Ir al directorio padre\n\n");
}

int main(int argc, char **argv, char **envp)
{
   /*t_list *my_env = NULL;
    char *cd_args[3] = {0};  // Array para pasar a builtin_cd, inicializamos todo a 0
    
    // Preparamos los argumentos para builtin_cd
    cd_args[0] = "cd";  // El primer argumento es "cd"
    
    if (argc > 1) {
        cd_args[1] = argv[1];  // Si hay un argumento, lo usamos
    } else {
        cd_args[1] = NULL;     // Si no, NULL (ir a HOME)
    }
    cd_args[2] = NULL;  // Terminamos el array con NULL
    
    // Verificamos si envp es válido antes de intentar copiarlo
    if (envp && envp[0]) {
        my_env = copy_env_var(envp);
    }
    
    // Mostrar el directorio actual antes del cambio
    printf("\033[1;32m=== ANTES DEL CD ===\033[0m\n");
    print_current_dir();
    
    // Ejecutar cd
    printf("\033[1;32m=== EJECUTANDO CD ===\033[0m\n");
    int result = builtin_cd(cd_args);
    printf("Resultado del comando cd: %d\n", result);
    
    // Mostrar el directorio actual después del cambio
    printf("\033[1;32m=== DESPUÉS DEL CD ===\033[0m\n");
    print_current_dir();*/
    
	t_list	*my_env;
	t_ms ms;
	char *test_args[4];
	
	(void)argc;
	my_env = copy_env_var(envp);
	ms.my_env = my_env;
    ms.exit_status = 0;

    // Comprobar si se pasan argumentos específicos o usar los de la línea de comandos
    if (argc > 1) {
        // Crear un array de argumentos que incluya "export" como primer elemento
        char **export_args = malloc(sizeof(char*) * (argc + 1));
        export_args[0] = "export";
        for (int i = 1; i < argc; i++) {
            export_args[i] = argv[i];
        }
        export_args[argc] = NULL;
        
        printf("Ejecutando: export");
        for (int i = 1; i < argc; i++) {
            printf(" %s", argv[i]);
        }
        printf("\n");
        
        builtin_export(export_args, &my_env, &ms);
        
        // Mostrar el resultado
        printf("\n=== Variables después del export ===\n");
        char *show_args[2] = {"export", NULL};
        builtin_export(show_args, &my_env, &ms);
        
        free(export_args);
    } else {
        // Pruebas automáticas de casos especiales
        printf("===== Pruebas de casos especiales con export =====\n\n");
        
        printf("TEST 1: Añadir una variable sin valor (exportable)\n");
        test_args[0] = "export";
        test_args[1] = "VAR_WITHOUT_VALUE";
        test_args[2] = NULL;
        builtin_export(test_args, &my_env, &ms);
        
        printf("\nTEST 2: Añadir una variable con valor\n");
        test_args[1] = "VAR_WITH_VALUE=hello";
        builtin_export(test_args, &my_env, &ms);
        
        printf("\nTEST 3: Actualizar la variable anterior\n");
        test_args[1] = "VAR_WITH_VALUE=updated_value";
        builtin_export(test_args, &my_env, &ms);
        
        printf("\nTEST 4: Nombre inválido que empieza con número\n");
        test_args[1] = "1INVALID_VAR=value";
        builtin_export(test_args, &my_env, &ms);
        
        printf("\nTEST 5: Nombre inválido con carácter no permitido\n");
        test_args[1] = "INVALID-VAR=value";
        builtin_export(test_args, &my_env, &ms);
        
        printf("\nTEST 6: Múltiples variables en un solo comando\n");
        test_args[1] = "MULTI_VAR1=value1";
        test_args[2] = "MULTI_VAR2=value2";
        test_args[3] = NULL;
        builtin_export(test_args, &my_env, &ms);
        
        printf("\nTEST 7: Mostrar todas las variables\n");
        test_args[1] = NULL;
        builtin_export(test_args, &my_env, &ms);
        
        printf("\n\n===== Pruebas de UNSET =====\n\n");
        
        printf("TEST 8: Eliminar una variable existente\n");
        test_args[0] = "unset";
        test_args[1] = "VAR_WITH_VALUE";
        test_args[2] = NULL;
        builtin_unset(test_args, &my_env, &ms);
        printf("Exit status: %d\n", ms.exit_status);
        
        printf("\nTEST 9: Intentar eliminar una variable que no existe\n");
        test_args[1] = "NONEXISTENT_VAR";
        builtin_unset(test_args, &my_env, &ms);
        printf("Exit status: %d\n", ms.exit_status);
        
        printf("\nTEST 10: Eliminar con nombre inválido\n");
        test_args[1] = "123INVALID";
        builtin_unset(test_args, &my_env, &ms);
        printf("Exit status: %d\n", ms.exit_status);
        
        printf("\nTEST 11: Eliminar múltiples variables\n");
        test_args[1] = "VAR_WITHOUT_VALUE";
        test_args[2] = "MULTI_VAR1";
        test_args[3] = NULL;
        builtin_unset(test_args, &my_env, &ms);
        printf("Exit status: %d\n", ms.exit_status);
        
        printf("\nTEST 12: Mostrar variables después de unset\n");
        test_args[0] = "export";
        test_args[1] = NULL;
        test_args[2] = NULL;
        builtin_export(test_args, &my_env, &ms);
    }

    // Liberar memoria si se creó el entorno
    if (my_env) {
        free_env_list(my_env);
    }
    return (0);
}
