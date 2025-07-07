/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:05:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/07/07 21:58:08 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	
	(void)argc;
	my_env = copy_env_var(envp);
	builtin_export(argv, my_env); // Pasamos argumentos y variables de entorno
    // Liberar memoria si se creó el entorno
    if (my_env) {
        free_env_list(my_env);
    }
    return (0);
}
