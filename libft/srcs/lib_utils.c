/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vleida <vleida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:07:55 by vleida            #+#    #+#             */
/*   Updated: 2021/10/06 16:18:37 by vleida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	@brief	return the length up to the char с if char = 0 work like ft_strlen
**	
**	@param	str		pointer to string
**	@param	c		char
**	@return	size_t	lenght string
*/
size_t	ft_strlen_m(const char *str, int c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	if (!c)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != (unsigned char)c)
			i++;
		if (!str[i])
			i = 0;
	}
	return (i);
}

static void	ft_join_helper(char const *s1, char const *s2, int c)
{
	if (s1 && (c == 1 || c == 3))
	{
		free ((char *)s1);
		s1 = NULL;
	}
	if (s2 && (c == 2 || c == 3))
	{
		free ((char *)s2);
		s2 = NULL;
	}
}

/*
**	@brief	allocates memory and contactination two strings
**			and free string depending on int c
**	
**	@param	s1		pointer to string
**	@param	s2		pointer to string
**	@param	c		c = 1 free(s1), c = 2 free(s2), c = 3 free(s1 and s2)
**	@return	char*	pointer to new result string or NULL
*/
char	*ft_strjoin_m(char const *s1, char const *s2, int c)
{
	size_t	i;
	size_t	j;
	char	*rez;

	rez = malloc(sizeof(char) * (ft_strlen_m(s1, 0) + ft_strlen_m(s2, 0) + 1));
	if (!rez)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		rez[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		rez[i] = s2[j];
		i++;
		j++;
	}
	rez[i] = 0;
	ft_join_helper(s1, s2, c);
	return (rez);
}

/*
**	@brief	checks if there is a character in the string
**	
**	@param	c		character
**	@param	str		pointer to set characters (string)
**	@return	int		0 if checks fail, else 1
*/
int	ft_ch_for_coinc(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

/*
** @brief free all alocated pointer in split
** 
** @param arr pointer to pointers (array of strings)
*/
void	ft_free_split(char **rez)
{
	int	i;

	if (!rez)
		return ;
	i = 0;
	while (rez[i])
	{
		if (rez[i])
		{
			free(rez[i]);
			rez[i] = NULL;
		}
		i++;
	}
	free(rez);
	rez = NULL;
}
