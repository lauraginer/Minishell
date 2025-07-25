/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execute_pid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 01:30:00 by lauragm          #+#    #+#             */
/*   Updated: 2025/07/25 01:30:00 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

// Función auxiliar para crear un nodo AST de prueba
t_ast_node *create_test_node(char **args)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    
    node->type = TOKEN_WORD;
    node->args = args;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

// Función auxiliar para copiar el entorno
t_list *copy_env_var(char **envp)
{
    int i = 0;
    t_list *my_env = NULL;
    t_list *new_node;
    char *copy;

    while (envp[i])
    {
        copy = ft_strdup(envp[i]);
        if (!copy)
            return (NULL);
        new_node = ft_lstnew(copy);
        if (!new_node)
        {
            free(copy);
            return (NULL);
        }
        ft_lstadd_back(&my_env, new_node);
        i++;
    }
    return (my_env);
}

// Función auxiliar para liberar el entorno
void free_env_list(t_list *env_list)
{
    t_list *aux;

    while (env_list)
    {
        aux = env_list->next;
        free(env_list->content);
        free(env_list);
        env_list = aux;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_ms ms;
    t_ast_node *node;
    t_list *my_env;
    
    (void)argc;
    (void)argv;
    
    // Inicializar la estructura ms
    ms.exit_status = 0;
    
    // Copiar variables de entorno
    my_env = copy_env_var(envp);
    if (!my_env)
    {
        printf("Error: No se pudo copiar el entorno\n");
        return (1);
    }
    
    printf("=== PRUEBAS DE EXECUTE_PID ===\n\n");
    
    // Test 1: Probar get_env_value
    printf("TEST 1: get_env_value\n");
    char *path_value = get_env_value("PATH", my_env);
    if (path_value)
        printf("✅ PATH encontrado: %.50s...\n", path_value);
    else
        printf("❌ PATH no encontrado\n");
    
    char *home_value = get_env_value("HOME", my_env);
    if (home_value)
        printf("✅ HOME encontrado: %s\n", home_value);
    else
        printf("❌ HOME no encontrado\n");
    
    // Test 2: Probar manage_relative_or_absolute_path
    printf("\nTEST 2: manage_relative_or_absolute_path\n");
    char *abs_path = manage_relative_or_absolute_path("/bin/ls");
    if (abs_path)
    {
        printf("✅ Ruta absoluta /bin/ls: %s\n", abs_path);
        free(abs_path);
    }
    else
        printf("❌ /bin/ls no encontrado\n");
    
    char *rel_path = manage_relative_or_absolute_path("./minishell");
    if (rel_path)
    {
        printf("✅ Ruta relativa ./minishell: %s\n", rel_path);
        free(rel_path);
    }
    else
        printf("ℹ️  ./minishell no encontrado (normal si no existe)\n");
    
    // Test 3: Probar get_command_path
    printf("\nTEST 3: get_command_path\n");
    char *ls_path = get_command_path("ls", my_env);
    if (ls_path)
    {
        printf("✅ Comando 'ls' encontrado en: %s\n", ls_path);
        free(ls_path);
    }
    else
        printf("❌ Comando 'ls' no encontrado\n");
    
    char *cat_path = get_command_path("cat", my_env);
    if (cat_path)
    {
        printf("✅ Comando 'cat' encontrado en: %s\n", cat_path);
        free(cat_path);
    }
    else
        printf("❌ Comando 'cat' no encontrado\n");
    
    char *fake_path = get_command_path("comando_inexistente", my_env);
    if (!fake_path)
        printf("✅ Comando inexistente correctamente devuelve NULL\n");
    else
    {
        printf("❌ Error: comando inexistente devolvió: %s\n", fake_path);
        free(fake_path);
    }
    
    // Test 4: Probar execute_external_command (con echo)
    printf("\nTEST 4: execute_external_command\n");
    char *echo_args[] = {"echo", "¡Hola desde execute_pid!", NULL};
    node = create_test_node(echo_args);
    
    if (node)
    {
        printf("Ejecutando: echo ¡Hola desde execute_pid!\n");
        t_ms *ms_ptr = &ms;
        int result = execute_external_command(&node, &ms_ptr, my_env);
        printf("Resultado: %d, Exit status: %d\n", result, ms.exit_status);
        free(node);
    }
    
    // Test 5: Probar con comando inexistente
    printf("\nTEST 5: Comando inexistente\n");
    char *fake_args[] = {"comando_que_no_existe", NULL};
    node = create_test_node(fake_args);
    
    if (node)
    {
        printf("Ejecutando comando inexistente...\n");
        t_ms *ms_ptr = &ms;
        int result = execute_external_command(&node, &ms_ptr, my_env);
        printf("Resultado: %d, Exit status: %d\n", result, ms.exit_status);
        free(node);
    }
    
    printf("\n=== FIN DE PRUEBAS ===\n");
    
    // Limpiar memoria
    free_env_list(my_env);
    
    return (0);
}
