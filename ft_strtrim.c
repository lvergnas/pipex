/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:00:35 by lvergnas          #+#    #+#             */
/*   Updated: 2023/04/27 14:01:03 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_findstart(char const *s1, char const *set)
{
	int				found;
	int				index;
	unsigned int	iset;

	index = -1;
	found = -1;
	while (index < (int)ft_strlen(s1) && found == index)
	{
		index++;
		iset = 0;
		while (found != index && iset < ft_strlen(set))
		{
			if (set[iset] == s1[index])
				found = index;
			iset++;
		}
	}
	if (found == (int)ft_strlen(s1) - 1)
		return (0);
	return (found + 1);
}

static int	ft_findend(char const *s1, char const *set)
{
	int				found;
	int				index;
	unsigned int	iset;

	index = ft_strlen(s1);
	found = ft_strlen(s1);
	if (found != 0)
	{
		while (index >= 0 && found == index)
		{
			index--;
			iset = 0;
			while (found != index && iset < ft_strlen(set))
			{
				if (set[iset] == s1[index])
					found = index;
				iset++;
			}
		}
	}
	return (found);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char			*str;
	int				index;
	unsigned int	founds;
	unsigned int	founde;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	index = 0;
	founds = ft_findstart(s1, set);
	founde = ft_findend(s1, set);
	str = (char *)malloc((founde - founds + 1) * sizeof(char));
	if (!str)
		return (str);
	while (founds < founde)
	{
		str[index] = s1[founds];
		founds++;
		index++;
	}
	str[index] = '\0';
	return (str);
}
