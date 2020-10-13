/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:51:34 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/06 21:44:53 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prototypes.h"

static int			type_instr(char *keyword, int ret)
{
	ret = (ft_strequ("plane", keyword) ? PLANE : ret);
	ret = (ft_strequ("sphere", keyword) ? SPHERE : ret);
	ret = (ft_strequ("cylindre", keyword) ? CYLINDRE : ret);
	ret = (ft_strequ("cone", keyword) ? CONE : ret);
	ret = (ft_strequ("quadric", keyword) ? QUADRIC : ret);
	ret = (ft_strequ("light", keyword) ? LUMIERE : ret);
	ret = (ft_strequ("translate", keyword) ? TRANSLATE : ret);
	ret = (ft_strequ("rotate", keyword) ? ROTATE : ret);
	ret = (ft_strequ("scale", keyword) ? SCALE : ret);
	ret = (ft_strequ("specular", keyword) ? SPECULAR : ret);
	ret = (ft_strequ("ambiant", keyword) ? AMBIANT : ret);
	ret = (ft_strequ("texture", keyword) ? TEXTURE : ret);
	ret = (ft_strequ("union", keyword) ? UNION : ret);
	ret = (ft_strequ("section", keyword) ? SECTION : ret);
	ret = (ft_strequ("invert", keyword) ? INVERT : ret);
	ret = (ft_strequ("material", keyword) ? MATERIAL : ret);
	ret = (ft_strequ("damier", keyword) ? DAMIER : ret);
	ret = (ft_strequ("perlin", keyword) ? PERLIN : ret);
	ret = (ft_strequ("wood", keyword) ? WOOD : ret);
	ret = (ft_strequ("bump", keyword) ? BUMP : ret);
	ret = (ft_strequ("wave", keyword) ? WAVE : ret);
	ret = (ft_strequ("dice", keyword) ? DICE : ret);
	return (ret);
}

static int			extract_instr(t_stream *s)
{
	char			keyword[10];
	int				k;

	k = 0;
	while ((ft_getchar(s)))
	{
		if (ft_strchr(SPACE, ft_getchar(s)))
			break ;
		keyword[k++] = ft_getc(s);
		if (k == 10)
			return (ERROR);
	}
	keyword[k] = '\0';
	return (type_instr(keyword, ERROR));
}

static int			parse_it(t_instance *inst, t_qunion **q, t_stream *s)
{
	int				type_instr;

	while (flusher(s))
	{
		skip_space(s);
		if (flusher(s) == 0)
			break ;
		type_instr = extract_instr(s);
		if (type_instr == ERROR)
			return (ERROR);
		if (type_instr == SUCCESS)
			return (SUCCESS);
		if (type_instr == DIAMANT || type_instr == DICE
			|| type_instr == CUBE)
		{
			if (store_preset(inst, q, s, type_instr) == ERROR)
				return (ERROR);
		}
		else if (store_obj(inst, q, s, type_instr) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

void				parse_files(t_environment *env, int argc, char *argv[])
{
	int				i;
	t_stream		st;
	t_instance		*inst;
	t_qunion		*q;

	i = 0;
	while (++i < argc)
	{
		q = NULL;
		if ((inst = add_instance(env, argv[i])) == NULL)
			print_error(env, "Echec creation instance\n");
		st.fd = open(argv[i], O_RDONLY);
		if (st.fd == ERROR)
			print_error(env, "Echec ouverture fichier\n");
		if (init_stream(&st, st.fd) == ERROR)
			print_error(env, "Erreur fichier\n");
		if (parse_it(inst, &q, &st) == ERROR)
		{
			free_qunion_list(q);
			print_error(env, "Erreur format fichier\n");
		}
		close(st.fd);
		fill_instance(inst, q);
		free_qunion_list(q);
	}
}
