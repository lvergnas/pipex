/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:51:57 by lvergnas          #+#    #+#             */
/*   Updated: 2023/10/04 11:26:59 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	ft_counttab(char const *s, char c)
{
	unsigned int	count;
	unsigned int	index;

	index = 0;
	count = 0;
	while (index < ft_strlen(s) && s[index] == c)
		index++;
	while (index < ft_strlen(s))
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1] != '\0')
			count++;
		index++;
		if (s[index] == '\0')
			count++;
	}
	return (count);
}

static void	ft_conditioncp(const char *str, size_t *start, size_t *end, char c)
{
	while (str[*start] == c)
		(*start)++;
	*end = *start;
	while (str[*end] != c && str[*end] != '\0')
		(*end)++;
}

static char	**ft_copy(char **tab, size_t *itab, const char *str, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (*itab < ft_counttab(str, c))
	{
		ft_conditioncp(str, &start, &end, c);
		i = 0;
		tab[*itab] = (char *)malloc((end - start + 1) * sizeof(char));
		if (!(tab[*itab]))
		{
			while (tab[i])
				free(tab[(i)++]);
			free(tab);
			return (0);
		}
		while (start < end)
			tab[*itab][i++] = str[start++];
		tab[*itab][i] = '\0';
		(*itab)++;
	}
	return (tab);
}

char	**ft_split(char *s, char c)
{
	size_t	itab;
	char	**tab;
	size_t	nb_tab;

	if (!s)
		return (0);
	nb_tab = ft_counttab(s, c);
	tab = (char **)malloc((nb_tab + 1) * sizeof(char *));
	if (!tab)
		return (0);
	itab = 0;
	tab = ft_copy(tab, &itab, s, c);
	if (!tab)
		return (0);
	tab[itab] = NULL;
	return (tab);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && (s1[i] == s2[i]) && (i < n - 1))
		i++;
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}
