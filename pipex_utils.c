/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:39:37 by lvergnas          #+#    #+#             */
/*   Updated: 2023/05/03 14:14:03 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	index;

	if (!str)
		return (0);
	index = 0;
	while (((char *)str)[index])
		index++;
	return (index);
}

char	*ft_strchr(char *str, int ch)
{
	unsigned int	index;
	char			*ptr;
	unsigned int	len;

	if (!str)
		return (0);
	ptr = (char *)str;
	len = ft_strlen(ptr);
	index = 0;
	while (index <= len)
	{
		if (ptr[index] == ((char)ch))
			return (&ptr[index]);
		index++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	index;
	unsigned int	indexs2;
	size_t			lentotal;

	if (!s1 || !s2)
		return (0);
	lentotal = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(lentotal);
	if (!str)
		return (str);
	index = 0;
	indexs2 = 0;
	while (index < lentotal)
	{
		if (index < ft_strlen(s1))
			str[index] = s1[index];
		else
		{
			str[index] = s2[indexs2];
			indexs2++;
		}
		index++;
	}
	return (str);
}

int	find_path_in_env(char **env, char *tofind)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (j < (int)ft_strlen(tofind))
		{
			if (env[i][j] != tofind[j])
				break ;
			j++;
		}
		if (j == (int)ft_strlen(tofind))
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned int	index;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	index = 0;
	while (index < (count * size))
	{
		((char *)ptr)[index] = '\0';
		index++;
	}
	return (ptr);
}
