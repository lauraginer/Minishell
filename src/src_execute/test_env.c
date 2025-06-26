/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:05:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/26 18:22:30 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Declaraciones para evitar errores de compilación
t_list *copy_env_var(char **envp); 
void free_env_list(t_list *env_list);
int builtin_cd(char **args, t_list *my_env);

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
    t_list *my_env;
    (void)argc;
    
    // Crear una copia de las variables de entorno
    my_env = copy_env_var(envp);
    if (!my_env)
    {
        printf("Error: No se pudo copiar el entorno\n");
        return (1);
    }
    
    // Mostrar el directorio actual antes del cambio
    printf("\033[1;32m=== ANTES DEL CD ===\033[0m\n");
    print_current_dir();
    
    // Si el comando es "cd", llamar a builtin_cd

        printf("\033[1;32m=== EJECUTANDO CD ===\033[0m\n");
        int result = builtin_cd(argv + 1, my_env); // argv+1 para que argv[0] sea "cd"
        printf("Resultado del comando cd: %d\n", result);
        
        // Mostrar el directorio actual después del cambio
        printf("\033[1;32m=== DESPUÉS DEL CD ===\033[0m\n");
        print_current_dir();
    
    // Liberar memoria
    free_env_list(my_env);
    
    return (0);
}
