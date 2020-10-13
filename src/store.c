/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:02:16 by mbenjell          #+#    #+#             */
/*   Updated: 2019/04/07 09:14:29 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

int			nb_param(int instr)
{
	int		ret;

	ret = 0;
	ret = (instr == PLANE ? 5 + 3 : ret);
	ret = (instr == SPHERE ? 4 + 3 : ret);
	ret = (instr == CYLINDRE ? 6 + 3 : ret);
	ret = (instr == CONE ? 6 + 3 : ret);
	ret = (instr == QUADRIC ? 10 + 3 : ret);
	ret = (instr == CAMERA ? 6 : ret);
	ret = (instr == LUMIERE ? 6 : ret);
	ret = (instr == TRANSLATE ? 3 : ret);
	ret = (instr == ROTATE ? 3 : ret);
	ret = (instr == SCALE ? 3 : ret);
	ret = (instr == SPECULAR ? 2 : ret);
	ret = (instr == AMBIANT ? 1 : ret);
	ret = (instr == TEXTURE ? 3 : ret);
	ret = (instr == UNION ? 1 : ret);
	ret = (instr == SECTION ? 1 : ret);
	ret = (instr == INVERT ? 0 : ret);
	ret = (instr == MATERIAL ? 3 : ret);
	ret = ((instr == DAMIER) || (instr == PERLIN) ? 1 : ret);
	ret = ((instr == WOOD) || (instr == BUMP) ? 1 : ret);
	ret = (instr == WAVE ? 1 : ret);
	ret = (instr == DICE ? 3 : ret);
	return (ret);
}

int			extract_param(t_stream *s, t_scal *n)
{
	t_scal	decimal;
	t_scal	fractional;
	t_scal	sign;
	int		c;
	int		e;

	sign = (ft_getchar(s) == '-' ? -1.0 : 1.0);
	if (ft_getchar(s) == '+' || ft_getchar(s) == '-')
		ft_getc(s);
	if (ft_getchar(s) == 0)
		return (ERROR);
	decimal = 0.0;
	while ((c = ft_getchar(s)) && c >= '0' && c <= '9' && ft_getc(s) >= 0)
		decimal = decimal * 10.0 + (t_scal)(c - '0');
	e = 0;
	fractional = 0.0;
	if (ft_getchar(s) == '.' && ft_getc(s) >= 0)
		while ((c = ft_getchar(s)) && c >= '0' && c <= '9' && ft_getc(s) >= 0)
			fractional = fractional * 10.0 + (t_scal)(c - '0' + e++ * 0);
	if (ft_strchr(SPACE, c) == NULL)
		return (ERROR);
	*n = sign * (decimal + fractional / pow(10.0, (t_scal)e));
	return (SUCCESS);
}

int			create_quadric(t_instance *inst, t_qunion **q, int type_instr,
			t_scal param[])
{
	t_quadric	quadric;
	t_scal		quad_param[15];

	if (type_instr == PLANE)
		plan_to_quad(param, quad_param, &quadric);
	else if (type_instr == SPHERE)
		sphere_to_quad(param, quad_param, &quadric);
	else if (type_instr == CYLINDRE)
		cylindre_to_quad(param, quad_param, &quadric);
	else if (type_instr == CONE)
		cone_to_quad(param, quad_param, &quadric);
	else if (type_instr == QUADRIC)
		quadric_to_quad(param, quad_param, &quadric);
	else
		return (ERROR);
	inst->scn.nranges += 1;
	inst->scn.n += 1;
	return (add_quadric(q, quad_param, &quadric) == NULL ? ERROR : SUCCESS);
}

static int	store_param(t_stream *s, t_scal *param, int instr)
{
	int		ret;
	int		nb;

	nb = nb_param(instr);
	ft_memset(param, 0, sizeof(param));
	while (nb)
	{
		skip_space(s);
		ret = extract_param(s, &param[--nb]);
		if (ret == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int			store_obj(t_instance *i, t_qunion **q, t_stream *s, int instr)
{
	t_scal	param[13];

	if (store_param(s, param, instr) == ERROR)
		return (ERROR);
	if (instr == LUMIERE)
		return (add_light(&(i->scn.light_list), param));
	else if (instr == TRANSLATE || instr == ROTATE || instr == SCALE
		|| instr == SPECULAR)
		return (transformation(*q, param, instr));
	else if (instr == UNION || instr == SECTION || instr == INVERT)
		return (manipulate_qunion(i, q, param, instr));
	else if (instr == AMBIANT)
		i->scn.ambiant = param[0];
	else if (instr == TEXTURE)
		store_texture(*q, param);
	else if (instr == MATERIAL)
		store_material(*q, param);
	else if (instr == DAMIER || instr == PERLIN || instr == WOOD
		|| instr == BUMP || instr == WAVE)
		perturbation(*q, param, instr);
	else
		return (create_quadric(i, q, instr, param));
	return (SUCCESS);
}
