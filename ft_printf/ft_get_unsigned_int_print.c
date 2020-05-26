/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unsigned_int_print.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:13:41 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/24 17:06:37 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static void	justify_return_string(t_directive *directive, char **return_string,
									char *number_to_print, size_t string_size)
{
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(*return_string, number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
		if (ft_strlen(number_to_print) != string_size)
			(*return_string)[ft_strlen(number_to_print)] = ft_strchr(directive->flags,
			'0') || directive->precision > (int)ft_strlen(number_to_print) ?
			'0' : ' ';
	}
	else
	{
		ft_strlcpy(*return_string + string_size - ft_strlen(number_to_print),
		number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
	}
}

char		*get_unsigned_int_print(t_directive *directive,
									unsigned int variable)
{
	int		zeroes_count;
	size_t	string_size;
	char	*number_to_print;
	char	*return_string;
	char	*zeroes;

	zeroes_count = directive->precision -
	ft_strlen(directive->conversion_character == 'u' ? ft_uitoa(variable) :
	get_hex(variable, directive->conversion_character));
	zeroes = zeroes_count >= 0 ? ft_calloc(zeroes_count + 1, sizeof(char)) :
	ft_strdup("");
	ft_memset(zeroes, '0', zeroes_count >= 0 ? zeroes_count : 0);
	number_to_print = ft_strjoin(zeroes, directive->conversion_character ==
	'u' ? ft_uitoa(variable) :
	get_hex(variable, directive->conversion_character));
	string_size = get_max(3, directive->field_width, directive->precision,
	ft_strlen(number_to_print));
	return_string = malloc((string_size + 1) * sizeof(char));
	return_string[string_size] = '\0';
	ft_memset(return_string, ft_strchr(directive->flags, '0') || directive->precision >
	(int)ft_strlen(number_to_print) ? '0' : ' ', string_size);
	justify_return_string(directive, &return_string, number_to_print,
	string_size);
	return (return_string);
}
