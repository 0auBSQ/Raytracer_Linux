/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:41:26 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/06 15:44:36 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

void	*ft_memset(void *b, int c, size_t len)
{
	while (len > 0)
		((unsigned char *)b)[--len] = (unsigned char)c;
	return (b);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n > 0)
	{
		n--;
		((char *)dst)[n] = ((char *)src)[n];
	}
	return (dst);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((unsigned char *)s) + i);
		i++;
	}
	return (NULL);
}

void	*ft_memalloc(size_t size)
{
	void *out;

	out = malloc(size);
	if (out == NULL)
		return (NULL);
	while (size > 0)
		((char *)out)[--size] = 0;
	return (out);
}

void	ft_memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}
