/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:36:54 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 04:59:59 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

t_scal		g_thr = 0.5;

void		write_zeros(int fd, int nb, char c)
{
	int				i;

	i = 0;
	while (i < nb)
	{
		write(fd, &c, 1);
		i++;
	}
}

void		print_head(int fd)
{
	int				size;
	static int		w = DEFAULT_WINDOW_WIDTH;
	static int		h = DEFAULT_WINDOW_HEIGHT;

	size = 54 + 3 * h * w;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write_zeros(fd, 4, 0);
	write_zeros(fd, 1, 54);
	write_zeros(fd, 3, 0);
	write_zeros(fd, 1, 40);
	write_zeros(fd, 3, 0);
	write(fd, &w, 4);
	write(fd, &h, 4);
	write_zeros(fd, 1, 1);
	write_zeros(fd, 1, 0);
	write_zeros(fd, 1, 24);
	write_zeros(fd, 1, 0);
	write_zeros(fd, 34, 0);
}

void		save_image(t_instance *inst)
{
	int				fd;
	int				i;

	i = 0;
	fd = open("output.bmp", O_RDWR | O_CREAT | O_NOFOLLOW | O_TRUNC, 0644);
	if (fd < 0)
	{
		write(2, "Save image failed\n", ft_strlen("Save image failed\n"));
		return ;
	}
	print_head(fd);
	while ((i + 4) < 4 * DEFAULT_WINDOW_WIDTH * DEFAULT_WINDOW_HEIGHT)
	{
		write(fd, &(inst->win.buf[i + 1]), 1);
		write(fd, &(inst->win.buf[i + 2]), 1);
		write(fd, &(inst->win.buf[i]), 1);
		i += 4;
	}
	write(2, "Image saved\n", ft_strlen("Image saved\n"));
	close(fd);
}

int			event_filtre(int k, t_instance *inst)
{
	if (k == KEY_0)
		inst->cam.pf_filtre = NULL;
	else if (k == KEY_1)
		inst->cam.pf_filtre = filtre_sepia;
	else if (k == KEY_2)
		inst->cam.pf_filtre = filtre_cartoon;
	else if (k == KEY_3)
		g_thr += 0.05;
	else if (k == KEY_4)
		g_thr -= 0.05;
	else if (k == KEY_5)
		save_image(inst);
	else if (k == KEY_6)
		inst->cam.pf_filtre = filtre_stereoscopy;
	else if (k == KEY_7)
		inst->cam.pf_filtre = filtre_cell;
	else if (k == KEY_8)
		inst->cam.pf_filtre = filtre_do_nothing;
	else if (k == KEY_9)
		inst->cam.pf_filtre = black_to_alpha;
	else
		return (0);
	if (k != KEY_3 && k != KEY_4 && k != KEY_5)
		inst->win.redraw_required = 1;
	return (0);
}

t_vec4		filtre_cartoon(t_vec4 color)
{
	t_vec4			new;
	t_scal			tot;

	tot = color.x + color.y + color.z;
	if (tot > g_thr)
	{
		new.x = 1.;
		new.y = 1.;
		new.z = 1.;
	}
	else
	{
		new.x = 0;
		new.y = 0;
		new.z = 0;
	}
	return (new);
}
