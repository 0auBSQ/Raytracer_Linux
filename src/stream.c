/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 16:42:35 by mbenjell          #+#    #+#             */
/*   Updated: 2019/01/12 18:33:24 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int		init_stream(t_stream *s, int fd)
{
	ft_memset(s, 0, sizeof(t_stream));
	s->fd = fd;
	s->nread = read(s->fd, s->buff, BUFFER_SIZE);
	if (s->nread == ERROR || s->nread == 0)
		return (ERROR);
	return (SUCCESS);
}

int		flusher(t_stream *s)
{
	if (s->i >= s->nread)
	{
		s->i = 0;
		ft_memset(s->buff, 0, BUFFER_SIZE);
		s->nread = read(s->fd, s->buff, BUFFER_SIZE);
		if (s->nread == ERROR || s->nread == 0)
			return (0);
	}
	return (1);
}

int		ft_getc(t_stream *s)
{
	if (s->nread > 0 && flusher(s))
		return (s->buff[s->i++]);
	else
		return (0);
}

int		ft_getchar(t_stream *s)
{
	if (s->nread > 0 && flusher(s))
		return (s->buff[s->i]);
	else
		return (0);
}

int		skip_space(t_stream *s)
{
	int	c;

	c = ft_getchar(s);
	while (ft_memchr(SPACE, c, sizeof(SPACE) - 1))
		c = ft_getc(s);
	if (s->i > 0 && !ft_strchr(SPACE, c))
		s->i--;
	return (SUCCESS);
}
