/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvergnas <lvergnas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:49:27 by lvergnas          #+#    #+#             */
/*   Updated: 2023/02/27 14:42:57 by lvergnas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <unistd.h> //read/write
#include <fcntl.h> //open
#include <stdlib.h> //malloc/free/exit
#define BUFFERSIZE 1000

size_t	ft_strlen(const char *str);
char	*ft_strchr(char *str, int ch);
char	*ft_strjoin(char *s1, char *s2);

#endif