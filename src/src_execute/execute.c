/*Lo que se nos da básicamente en la parte de ejecución es un AST (Árbol de Sintaxis Abstracta),
y la forma en que lo ejecutamos es recorriéndolo recursivamente. Aquí hay un pseudocódigo que recorre un AST aritmético
construido previamente en la fase de parseo:*/

int eval(t_node node)
{
 if (node.type == PLUS)
   return (node.left + node.right);
 else
   return (node.value);
}

//El pseudocódigo sería algo así:

int execute(t_node node)
{
 if (node.type == PIPE)
   return (execute_pipe(node.left, node.right));
 else
   return (execute_simple_command(node.value));
}

/*Para manejar file descriptors y crear procesos con fork():
Esto es el núcleo de la parte de ejecución, además de trabajar un poco con las redirecciones,
donde bbásicamente abrimos un archivo y luego redirigimos (usando dup2) la entrada o salida estándar a ese archivo.
En el caso de here-doc (<<), redirigimos la entrada estándar a un pipe.*/
int execute_pipe()
{
   pipe(pipe_fds);
   left_pid = fork();
   if (pid == 0) // estamos en el hijo izquierdo
   {
      // hacer lo necesario
      close(pipe_fds[0]); // según corresponda
      close(pipe_fds[1]); // según corresponda
   }
   else // estamos de nuevo en el padre
   {
      // hacer lo mismo para el hijo derecho
      // asegurarse de cerrar también los pipe_fds en el padre
   }
}
