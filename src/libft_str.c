/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:42:35 by mbenjell          #+#    #+#             */
/*   Updated: 2019/03/27 18:34:52 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_strequ(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s == (char)c)
			return ((char *)s);
		else
			s++;
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
