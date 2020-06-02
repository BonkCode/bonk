/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unsigned_int_print.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:13:41 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/02 19:36:43 by rtrant           ###   ########.fr       */
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
									unsigned long long int variable)
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
	if (directive->precision == 0 && variable == 0)
		number_to_print = ft_strjoin(zeroes, "");
	else
		number_to_print = ft_strjoin(zeroes, directive->conversion_character ==
		'u' ? ft_uitoa(variable) :
	get_hex(variable, directive->conversion_character));
	string_size = get_max(3, directive->field_width, directive->precision,
	ft_strlen(number_to_print));
	return_string = malloc((string_size + 1) * sizeof(char));
	return_string[string_size] = '\0';
	ft_memset(return_string, (ft_strchr(directive->flags, '0') && directive->precision < 0) || directive->precision >
	(int)ft_strlen(number_to_print) ? '0' : ' ', string_size);
	justify_return_string(directive, &return_string, number_to_print,
	string_size);
	if (variable != 0 && ft_strchr("xX", directive->conversion_character) && ft_strchr(directive->flags, '#') && !ft_strchr(directive->flags, '-'))
	{
		if (directive->precision < directive->field_width && ft_strchr(return_string, ' '))
		{
			if (ft_strrchr(return_string, ' ') == return_string)
			{
				*return_string = directive->conversion_character;
				return_string = ft_strjoin("0", return_string);
			}
			else
				ft_memcpy(ft_strrchr(return_string, ' ') - 1, directive->conversion_character == 'x' ? "0x" : "0X", 2);
		}
		else if (*return_string == '0' && directive->precision < 0)
		{
			if (*(return_string + 1) == '0')
				ft_memcpy(return_string, directive->conversion_character == 'x' ? "0x" : "0X", 2);
			else
			{
				*return_string = directive->conversion_character;
				return_string = ft_strjoin("0", return_string);
			}
		}
		else
		{
			return_string = ft_strjoin(directive->conversion_character == 'x' ? "0x" : "0X", return_string);
		}
		return (return_string);
	}
	if (variable != 0 && ft_strchr("xX", directive->conversion_character) && ft_strchr(directive->flags, '#'))
	{
		if ((return_string[0] == '0' && return_string[1] == '0' && directive->precision < 0) || (return_string[0] == ' ' && return_string[1] == ' '))
			ft_memcpy(return_string, directive->conversion_character == 'x' ? "0x" : "0X", 2);
		else if ((return_string[0] == '0' && directive->precision < 0) || return_string[0] == ' ')
		{
			return_string[0] = directive->conversion_character;
			return_string = ft_strjoin("0", return_string);
		}
		else
		{
			if (ft_strrchr(return_string, ' '))
			{
				if (*(ft_strrchr(return_string, ' ') - 1) == ' ')
					*(ft_strrchr(return_string, ' ') - 1) = '\0';
				else
				{
					*(ft_strrchr(return_string, ' ')) = '\0';
				}
			}
			return_string = ft_strjoin(directive->conversion_character == 'x' ? "0x" : "0X", return_string);
		}
	}
	return (return_string);
}
