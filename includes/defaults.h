/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdittric <cdittric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:28:30 by cdittric          #+#    #+#             */
/*   Updated: 2019/04/07 06:26:17 by cdittric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTS_H
# define DEFAULTS_H

# define SPACE			"\n\t "

# define SUCCESS		0
# define ERROR			-1

# define TRUE			1
# define FALSE			0
# define BUFFER_SIZE	4096

# define CUBE_MAPPING	1

# define ON 			1
# define OFF 			0

# define NORD			0
# define SUD			1
# define EST			2
# define OUEST			3
# define HAUT			4
# define BAS			5

# define PLANE			2
# define SPHERE			3
# define CYLINDRE		4
# define CONE			5
# define QUADRIC		6
# define LUMIERE		7
# define CAMERA			8
# define TRANSLATE		9
# define ROTATE			10
# define SCALE			11
# define SPECULAR 		12
# define AMBIANT 		13
# define TEXTURE		14
# define UNION			15
# define SECTION		16
# define INVERT			17
# define MATERIAL		18
# define DAMIER 		19
# define PERLIN 		20
# define WOOD 			21
# define BUMP 			22
# define WAVE 			23

# define DIAMANT		24
# define DICE	 		25
# define CUBE			26

# define READ_BUFFER_SIZE			4096
# define DEFAULT_WINDOW_WIDTH		900
# define DEFAULT_WINDOW_HEIGHT		600

# define MAX_DSAMPLE				15
# define DEFAULT_DXSAMPLE			4
# define DEFAULT_DYSAMPLE			4
# define MAX_DSSAMPLE				8
# define DEFAULT_DSSAMPLE			4
# define MAX_NREFLEXIONS			8
# define DEFAULT_NREFLEXIONS		4
# define DEFAULT_NTRANSPARENCY		4

# define DEFAULT_VELOCITY			1.0
# define DEFAULT_VELOCITY_MODIFIER	32.0
# define DEFAULT_YFOV				60.0

# define KEY_PRESS				2
# define KEY_RELEASE			3
# define MOUSE_PRESS			4
# define MOUSE_RELEASE			5
# define MOUSE_MOVE				6
# define EXPOSE_EVENT			12
# define CLOSE_EVENT			17

# define BUTTON_LEFT			1
# define BUTTON_RIGHT			2
# define BUTTON_OTHER			3
# define BUTTON_SCROLLUP		4
# define BUTTON_SCROLLDOWN		5

# define KEY_P			112
# define KEY_Q			113
# define KEY_W			119
# define KEY_E			101
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_Z			122
# define KEY_R			114
# define KEY_C			99
# define KEY_G			103
# define KEY_K			107
# define KEY_L			108
# define KEY_M			109
# define KEY_N			110
# define KEY_O			111
# define KEY_B			98
# define KEY_MINUS		45
# define KEY_EQUAL		61
# define KEY_TAB		65289
# define KEY_BACKQUOTE	232
# define KEY_LCONTROL	65507
# define KEY_RCONTROL	65508
# define KEY_LALT		65513
# define KEY_RALT		65027
# define KEY_LSHIFT		65505
# define KEY_RSHIFT		65506
# define KEY_LOS		65515
# define KEY_ROS		65383
# define KEY_SPACE		32
# define KEY_RETURN		65239
# define KEY_DELETE		65288
# define KEY_SUPPRESS	65535
# define KEY_UP			65362
# define KEY_LEFT		65361
# define KEY_DOWN		65364
# define KEY_RIGHT		65363
# define KEY_ESCAPE		65307
# define KEY_NUM0		65438
# define KEY_NUM1		65436
# define KEY_NUM2		65433
# define KEY_NUM3		65435
# define KEY_NUM4		65430
# define KEY_NUM5		65437
# define KEY_NUM6		65432
# define KEY_NUM7		65429
# define KEY_NUM8		65431
# define KEY_NUM9		65434
# define KEY_NUMPLUS	65451
# define KEY_NUMMINUS	65453
# define KEY_PAGEUP		0
# define KEY_PAGEDOWN	0
# define KEY_HOME		0
# define KEY_END		0
# define KEY_0			224
# define KEY_1			38
# define KEY_2			233
# define KEY_3			34
# define KEY_4			39
# define KEY_5			40
# define KEY_6			45
# define KEY_7			232
# define KEY_8			95
# define KEY_9			231

# define KEY_F			3
# define PIXELS			64

#endif
