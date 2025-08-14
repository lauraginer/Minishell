/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:14:09 by jcaro-lo          #+#    #+#             */
/*   Updated: 2025/02/01 15:59:45 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*my_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

char	*updatestack(char *stack)
{
	char	*aux;
	char	*new_stack;
	size_t	i;

	i = 0;
	new_stack = ft_strchr_gnl(stack, '\n');
	if (new_stack == NULL)
		return (my_free(stack));
	new_stack++;
	aux = (char *)malloc((ft_strlen_gnl(new_stack) +1) * sizeof(char));
	if (!aux)
		return (my_free(stack));
	while (new_stack[i])
	{
		aux[i] = new_stack[i];
		i++;
	}
	aux[i] = '\0';
	my_free(stack);
	if (aux[0] == '\0')
		return (my_free(aux));
	return (aux);
}

char	*extractline(char *stack)
{
	size_t	i;
	char	*line;

	i = 0;
	if (stack == NULL || stack[i] == '\0')
		return (NULL);
	while (stack[i] != '\n' && stack[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (my_free(stack));
	i = 0;
	while (stack[i] && stack[i] != '\n')
	{
		line[i] = stack[i];
		i++;
	}
	if (stack[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*fillstack(char *buf, int fd, char *stack)
{
	ssize_t	len;

	len = 1;
	while (len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len > 0)
			stack = ft_strjoin_gnl(stack, buf);
		if (checkstack(stack) == 1)
			break ;
		ft_bzero(buf, BUFFER_SIZE);
	}
	my_free(buf);
	if (len == -1)
		return (my_free(stack));
	return (stack);
}

char	*get_next_line(int fd)
{
	static char	*stack[4096] = {NULL};
	char		*line;
	char		*buf;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (my_free(stack[fd]));
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE + 1);
	stack[fd] = fillstack(buf, fd, stack[fd]);
	line = extractline(stack[fd]);
	stack[fd] = updatestack(stack[fd]);
	return (line);
}

/*int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;
	
	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);
	line = get_next_line(fd1);
	if (line)
	{
		printf("%s", line);
		my_free(line);
	}
	line = get_next_line(fd2);
	if (line)
	{
		printf("%s", line);
		my_free(line);
	}
	line = get_next_line(fd1);
	if (line)
	{
		printf("%s", line);
		my_free(line);
	}
	line = get_next_line(fd1);
	if (line)
	{
		printf("%s", line);
		my_free(line);
	}
	line = get_next_line(fd1);
	if (line)
	{
		printf("%s", line);
		my_free(line);
	}
	line = get_next_line(fd3);
	if (line)
	{
		printf("%s", line);
		my_free(line);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/