/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 15:25:18 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 11:29:08 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"
#include <pthread.h>

/*
** set_sample_offset: (Questionable magic)
** Sets x and y to coords of a sample indexed by `inst->win.isample` by
** spitting its odds and even bits between x and y so that samples are roughly
** equally spaced at every step of the per-sample-subset rendering.
** Example isample values for a 8 by 4 tile of samples:
** *----------------------------------------> x
** | 00 | 16 ' 04 | 20 : 01 | 17 ' 05 | 21 :
** | ` ` ` ` ' ` ` ` ` : ` ` ` ` ' ` ` ` ` :
** | 08 | 24 ' 12 | 28 : 09 | 25 ' 13 | 29 :
** | ................. : ................. :
** | 02 | 18 ' 06 | 22 : 03 | 19 ' 07 | 23 :
** | ` ` ` ` ' ` ` ` ` : ` ` ` ` ` ` ` ` ` :
** | 10 | 26 ' 14 | 30 : 11 | 27 ' 15 | 31 :
** | ................. : ................. :
** V y
*/

static void		set_sample_offset(t_instance *inst, int *x, int *y, int isample)
{
	int		xd;
	int		yd;
	int		i;

	xd = inst->win.dxsample + 1;
	yd = inst->win.dysample + 1;
	i = isample;
	*x = 0x00;
	*y = 0x00;
	while (--xd > yd - 1)
	{
		*x = (*x << 1) | (i & 0x0001);
		i >>= 1;
	}
	while (--yd > xd)
	{
		*y = (*y << 1) | (i & 0x0001);
		i >>= 1;
	}
	while (xd-- > 0)
	{
		*x = (*x << 1) | (i & 0x0001);
		*y = (*y << 1) | ((i & 0x0002) >> 1);
		i >>= 2;
	}
}

static int		store_v4colored_pixel(t_instance *inst, int x, int y, t_vec4 v)
{
	int	color;

	color = 0;
	color |= (int)(fmin(fmax(v.x, +0.0), 1.0) * 255.) << 16;
	color |= (int)(fmin(fmax(v.y, +0.0), 1.0) * 255.) << 8;
	color |= (int)(fmin(fmax(v.z, +0.0), 1.0) * 255.) << 0;
	color |= (int)(fmin(fmax(v.w, +0.0), 1.0) * 255.) << 24;
	color = mlx_get_color_value(inst->env->mlx, color);
	((int *)inst->win.rbuf)[y * inst->win.s_l / 4 + x] = color;
	return (color);
}

static void		extrapolate_sample(t_instance *inst, int x, int y, int color)
{
	int		xoffset;
	int		yoffset;
	int		depth;
	int		n;
	int		i;

	depth = log2i(inst->win.isample);
	n = 1 << (inst->win.dxsample + inst->win.dysample - depth);
	i = -1;
	while (++i < n)
	{
		set_sample_offset(inst, &xoffset, &yoffset,
				(i << depth) | inst->win.isample);
		if (x + xoffset >= inst->win.w || y + yoffset >= inst->win.h)
			continue ;
		((int *)inst->win.buf)[(y + yoffset) * inst->win.s_l / 4
			+ (x + xoffset)] = color;
	}
}

/*
** render():
** Renders to a `inst->win.isample` specified subset of `inst->win.rbuf` then
** extrapolate what is rendered to `inst->win.buf`.
** TODO (cdittric): Make the function clean again.
*/

void			*trender(void *tab)
{
	size_t			*ptr;
	t_instance		*inst;
	int				x;
	int				y;
	t_raytrace_data	rt;

	ptr = (size_t *)tab;
	inst = (t_instance *)ptr[0];
	set_sample_offset(inst, &x, &y, inst->win.isample);
	y += ptr[2] * ptr[1];
	while (y < inst->win.h && y < ((int)ptr[3] * (int)ptr[1]))
	{
		x = x % (1 << inst->win.dxsample);
		while (x < inst->win.w)
		{
			rt = get_rt_data(inst, x, y);
			extrapolate_sample(inst,
				x / (1 << inst->win.dxsample) * (1 << inst->win.dxsample),
				y / (1 << inst->win.dysample) * (1 << inst->win.dysample),
				store_v4colored_pixel(inst, x, y, get_color(inst, rt)));
			x += (1 << inst->win.dxsample);
		}
		y += (1 << inst->win.dysample);
	}
	pthread_exit("ok");
}

void			render(t_instance *inst)
{
	pthread_t	thid[4];
	size_t		ptr[4][4];
	int			i;
	void		*ret;

	i = 0;
	while (i < 4)
	{
		ptr[i][0] = (size_t)inst;
		ptr[i][1] = 1 << inst->win.dysample;
		ptr[i][2] = ((inst->win.h - 1) / ptr[i][1] + 1) * i / 4;
		ptr[i][3] = ((inst->win.h - 1) / ptr[i][1] + 1) * (i + 1) / 4;
		if (pthread_create(&thid[i], NULL, trender, &ptr[i][0]))
			exit(1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(thid[i], &ret))
			exit(1);
		i++;
	}
	inst->win.isample++;
}
