/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro-lo <jcaro-lo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:40:55 by jcaro-lo          #+#    #+#             */
/*   Updated: 2024/05/01 12:47:13 by jcaro-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	str_cpy(char *dest, const char *src, int start, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		str_size;
	int		start_str;
	char	*str;

	i = 0;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (count_trim(set, s1[i]))
		i++;
	start_str = i;
	i = ft_strlen(s1) - 1;
	while (count_trim(set, s1[i]))
		i--;
	str_size = i + 1 - start_str;
	if (str_size <= 0 || start_str >= ft_strlen(s1))
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (str_size + 1));
	i = 0;
	if (!str)
		return (NULL);
	str_cpy(str, s1, start_str, str_size);
	return (str);
}

/*int main(void)
{
	printf("%s", ft_strtrim("lorem ipsum dolor sit amet","te"));
}*/
