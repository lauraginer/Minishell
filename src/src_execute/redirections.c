/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:42:23 by lauragm           #+#    #+#             */
/*   Updated: 2025/07/30 22:07:13 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int execute_redirection(t_ast_node **node, t_ms *ms)
{
	/* Para redirecciones:
1. Abrir archivo (open)
2. Configurar FD con dup2  
3. Ejecutar comando con execute_ast()
4. Cerrar archivo

 NO necesitas fork (diferencia clave con pipes):
Las redirecciones modifican el FD actual
El comando se ejecuta en el mismo proceso
Más simple que los pipes

Conceptos:
entrada <
- open(filename, O_RDONLY)
- dup2(fd, STDIN_FILENO)  // stdin lee del archivo
- Comando lee de stdin normal
salida >
- open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)
- dup2(fd, STDOUT_FILENO)  // stdout escribe al archivo
- O_TRUNC: sobrescribe el archivo
append >>
- open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644)
- dup2(fd, STDOUT_FILENO)
- O_APPEND: añade al final del archivo
heredoc <<
// Conceptos más complejos:
- Crear pipe temporal
- Escribir contenido al pipe
- dup2(pipe[0], STDIN_FILENO)
- Simula entrada desde archivo*/
}

int handle_input(t_ast_node **node);
int handle_output(t_ast_node **node);
int handle_append(t_ast_node **node);
int handle_heredoc(t_ast_node **node);