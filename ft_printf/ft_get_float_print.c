/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_float_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:14:15 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/03 08:44:24 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "libftprintf.h"

static long long int	ft_abs(long int n)
{
	return (n < 0 ? -n : n);
}

static long long int	ten_pow(int size)
{
	long long int	res;

	res = 1;
	if (size <= 0)
		return (1);
	while (size-- > 0)
		res *= 10;
	return (res);
}

static char	*static_itoa(long long int n, int field_size)
{
	long long int	n_copy;
	char		*res;
	int			size;

	n_copy = n;
	size = 1;
	while (ft_abs(n_copy) / ten_pow(size) > 0)
		size++;
	if (n_copy < 0)
		size++;
	size = field_size > 0 ? field_size : size;
	if (!(res = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	res[size] = '\0';
	if (n_copy < 0)
		res[0] = '-';
	while (size-- > 0 && ft_abs(n_copy) >= 10)
	{
		res[size] = (ft_abs(n_copy) % 10) + '0';
		n_copy /= 10;
	}
	res[size] = (ft_abs(n_copy) % 10) + '0';
	while (size-- > 0)
		res[size] = '0';
	return (res);
}

static char	*setup_return_string(t_directive *directive, double variable,
									size_t *string_size, char **number_to_print)
{
	int		zeroes_count;
	char	*zeroes;
	char	*return_string;
	long long int	int_part;
	long long int	decimal_part;
	char			*decimal_part_string;
	int		scientific_size;

	if ((variable >= 100.0 || ((int)variable == 0 && variable - 0.00001 <= 0.000000001 && variable - 0.00001 >= -0.000000001)) && directive->conversion_character == 'g')
		directive->conversion_character = 'e';
	scientific_size = 0;
	while (directive->conversion_character == 'e' && variable >= 10.0)
	{
		++scientific_size;
		variable /= 10.0;
	}
	while (directive->conversion_character == 'e' && variable < 1)
	{
		--scientific_size;
		variable *= 10.0;
	}
	variable = variable > 0 ? variable : variable * -1;
	int_part = (long long int)variable;
	variable -= int_part;
	if ((variable >= 0.5 && directive->precision == 0) || (variable - 0.9999999 <= 0.000000001 && variable - 0.9999999 >= -0.000000001 && directive->precision < 0))
		++int_part;
	decimal_part = (long long int)(ten_pow(directive->precision >= 0 ? directive->precision : 6)  * variable + 0.5);
	decimal_part_string = static_itoa(decimal_part, directive->precision >= 0 ? directive->precision : 6);
	decimal_part_string[directive->precision >= 0 ? directive->precision : 6] = '\0';
	*number_to_print = ft_strjoin(static_itoa(int_part, -1), directive->precision == 0 && !ft_strchr(directive->flags, '#') ? "" : ".");
	*number_to_print = ft_strjoin(*number_to_print, decimal_part_string);
	zeroes_count = directive->precision - ft_strlen(decimal_part_string);
	zeroes = zeroes_count >= 0 ? ft_calloc(zeroes_count + 1, sizeof(char)) :
	ft_strdup("");
	ft_memset(zeroes, '0', zeroes_count >= 0 ? zeroes_count : 0);
	if (directive->conversion_character == '%')
		*number_to_print = ft_strjoin(zeroes, "%");
	else
		*number_to_print = ft_strjoin(*number_to_print, zeroes);
	if (directive->conversion_character == 'e')
	{
		*number_to_print = ft_strjoin(*number_to_print, scientific_size >= 0 ? "e+" : "e-");
		if (scientific_size < 10)
		{
			*number_to_print = ft_strjoin(*number_to_print, "0");
			*number_to_print = ft_strjoin(*number_to_print, ft_itoa(ft_abs(scientific_size)));
		}
		else
			*number_to_print = ft_strjoin(*number_to_print, ft_itoa(ft_abs(scientific_size)));
	}
	*string_size = get_max(3, directive->field_width, directive->precision,
												ft_strlen(*number_to_print));
	return_string = malloc((*string_size + 1) * sizeof(char));
	return_string[*string_size] = '\0';
	ft_memset(return_string, (ft_strchr(directive->flags, '0')) ? '0' :
													' ', *string_size);
	free(zeroes);
	return (return_string);
}

static void	justify_return_string(t_directive *directive, char **return_string,
									char *number_to_print, size_t string_size)
{
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(*return_string, number_to_print,
		directive->precision > (int)ft_strlen(number_to_print) ?
		(size_t)directive->precision + 1 : string_size + 1);
		if (ft_strlen(number_to_print) != string_size)
			(*return_string)[ft_strlen(number_to_print)] =
			ft_strchr(directive->flags, '0') || directive->precision >
			(int)ft_strlen(number_to_print) ? '0' : ' ';
	}
	else
	{
		ft_strlcpy(*return_string + string_size - ft_strlen(number_to_print),
		number_to_print, directive->precision >
		(int)ft_strlen(number_to_print) ? (size_t)directive->precision + 1 :
		string_size + 1);
	}
}

char		*get_float_print(t_directive *directive, double variable)
{
	size_t	string_size;
	char	*number_to_print;
	char	*return_string;
	char	*ptr_to_free;

	
	return_string = setup_return_string(directive, variable, &string_size, &number_to_print);
	justify_return_string(directive, &return_string, number_to_print,
	string_size);
	free(number_to_print);
	if (variable < 0 && !ft_strchr(directive->flags, '-'))
	{
		if (ft_strchr(return_string, ' '))
			*(ft_strrchr(return_string, ' ')) = '-';
		else if (*return_string == '0' && variable <= -1.0)
			*return_string = '-';
		else
		{
			ptr_to_free = return_string;
			return_string = ft_strjoin("-", ptr_to_free);
			free(ptr_to_free);
		}
		return (return_string);
	}
	if (variable < 0 && ((return_string[0] == '0') || return_string[0] == ' '))
		return_string[0] = '-';
	else if (variable < 0)
	{
		if (ft_strrchr(return_string, ' '))
			*(ft_strrchr(return_string, ' ')) = '\0';
		ptr_to_free = return_string;
		return_string = ft_strjoin("-", ptr_to_free);
		free(ptr_to_free);
		return (return_string);
	}
	if (ft_strchr(directive->flags, ' ') || ft_strchr(directive->flags, '+'))
	{
		if (!ft_strchr(directive->flags, '-'))
		{
			if (ft_strchr(return_string, ' '))
				*(ft_strrchr(return_string, ' ')) = ft_strchr(directive->flags, '+') ? '+' : ' ';
			else if (*return_string == '0'  && (variable >= 1.0  || variable <= -1.0 || ft_strrchr(return_string, '0') != return_string))

				*return_string = ft_strchr(directive->flags, '+') ? '+' : ' ';
			else
			{
				ptr_to_free = return_string;
				return_string = ft_strjoin(ft_strchr(directive->flags, '+') ? "+" : " ", ptr_to_free);
				free(ptr_to_free);
			}
			return (return_string);
		}
		if (((return_string[0] == '0') || return_string[0] == ' ') && (variable >= 1.0  || variable <= -1.0 || ft_strrchr(return_string, '0') != return_string))
			return_string[0] = ft_strchr(directive->flags, '+') ? '+' : ' ';
		else
		{
			if (ft_strrchr(return_string, ' '))
				*(ft_strrchr(return_string, ' ')) = '\0';
			ptr_to_free = return_string;
			return_string = ft_strjoin(ft_strchr(directive->flags, '+') ? "+" : " ", return_string);
			free(ptr_to_free);
			return (return_string);
		}
	}
	return (return_string);
}
