/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 03:21:08 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/03 06:46:34 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# define ERROR -10
# define MAX_UNSIGNED_INT 4294967295

typedef struct	s_directive
{
	int		field_width;
	int		precision;
	char	conversion_character;
	char	*length_modifier;
	char	*flags;
}				t_directive;

int				ft_printf(const char *format_string, ...);
int				get_max(int count, ...);
int				get_min(int count, ...);
t_directive		*get_directive(const char **format_string);
char			*get_char_print(t_directive *directive, char variable);
char			*get_int_print(t_directive *directive, long long int variable);
char			*get_pointer_print(t_directive *directive,
								unsigned long int variable);
char			*get_string_print(t_directive *directive, char *variable);
char			*get_unsigned_int_print(t_directive *directive,
								unsigned long long int variable);
char			*get_float_print(t_directive *directive, double variable);
char			*ft_uitoa(unsigned long long int n);
char			*get_hex(unsigned long long int variable, char conversion_character);

#endif
