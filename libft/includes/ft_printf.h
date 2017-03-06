/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjose <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:00:35 by tjose             #+#    #+#             */
/*   Updated: 2017/02/22 14:33:38 by tjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <wchar.h>
# include "libft.h"

typedef enum
{
	none,
	hh,
	h,
	l,
	ll,
	j,
	z,
}	t_conversion;

typedef enum
{
	no,
	yes,
	o,
	x,
	X
}	t_hash;

typedef struct		s_flags
{
	int				left_justify;
	int				show_sign;
	int				show_space;
	t_hash			hash;
	int				fill_zeroes;
}					t_flags;

typedef struct		s_mods
{
	t_flags			flags;
	int				width;
	int				precision;
	t_conversion	length;
	char			specifier;
}					t_mods;

int					ft_printf(const char *format, ...);
int					handle_flags(const char *str, t_mods *mods);
int					handle_width(const char *str, t_mods *mods, va_list tags);
int					handle_precision(const char *str,
		t_mods *mods, va_list tags);
int					handle_length(const char *str, t_mods *mods);
int					handle_specifier(char c, t_mods *mods);
int					handle_nospec(t_mods *mods);
int					handle_number(va_list tags, t_mods *mods);
int					handle_char(va_list tags, t_mods *mods);
int					handle_str(va_list tags, t_mods *mods);
int					place_sign(t_mods *mods, char **ans, int i, char *n);
int					place_number(t_mods *mods, char **ans, int i, char *n);
int					get_size(char *str, t_mods *mods);
int					is_mb(char *s);
char				*convert_length(va_list tags, t_mods *mods, char c);
char				*convert_ulength(va_list tags, t_mods *mods, char c);
void				place_right(t_mods *mods, char **ans, int size, char *n);
void				place_left(t_mods *mods, char **ans, int size, char *n);
#endif
