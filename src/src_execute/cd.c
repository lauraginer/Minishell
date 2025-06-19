/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:48:05 by lginer-m          #+#    #+#             */
/*   Updated: 2025/06/17 19:02:31 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int builtin_cd(char **args);

/*Para que cd funcione correctamente, necesitas tener acceso
a las variables de entorno ya disponibles (como HOME, OLDPWD, PWD)

cd → ir al HOME del usuario (lo obtienes con getenv("HOME"), cd /ruta/absoluta → ir directamente a esa ruta, 
cd ruta/relativa → se interpreta desde el directorio actual, cd - → volver al directorio anterior (usa la variable de entorno OLDPWD), 
cd ~ → equivale a cd $HOME, FUNCIONES: chdir() → cambia el directorio actual, getcwd() → para obtener la ruta actual (puede servir para actualizar PWD), 
setenv() / export (o tus propias funciones) → actualizar PWD y OLDPWD. 

ERRORES COMUNES A CONTROLAR: Ruta inexistente → muestra mensaje tipo cd: no such file or directory, Permisos denegados, 
Demasiados argumentos (cd a b) → debes avisar, Falta de HOME o OLDPWD definidos*/