/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:05:00 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/23 19:43:01 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Declaraciones para evitar errores de compilación
t_list *copy_env_var(char **envp); // Ajusta la firma según tu implementación real

int main(int argc, char **argv, char **envp)
{
	t_list *my_env;
	
	(void)argc;
	
	// Crear una copia de las variables de entorno
	/*my_env = copy_env_var(envp);
	if (!my_env)
	{
		ft_printf("Error: No se pudo copiar el entorno\n");
		return (1);
	}
	
	// Llamar a la función env con los argumentos pasados
	int result = builtin_env(argv, my_env);
	
	// Liberar memoria (ajusta según tu implementación)
	// free_env_list(my_env);

	//builtin_echo(argv);*/
	builtin_pwd(argv);
	return (0);
}
