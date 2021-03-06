/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_int_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:14:15 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/05 16:15:23 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static char	*static_itoa(long long int n)
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
	return (res);
}

static char	*setup_return_string(t_directive *directive, long long int variable,
									size_t *string_size, char **number_to_print)
{
	int		zeroes_count;
	char	*zeroes;
	char	*return_string;

	zeroes_count = directive->precision - ft_strlen(static_itoa(ft_abs(variable)));
	zeroes = zeroes_count >= 0 ? ft_calloc(zeroes_count + 1, sizeof(char)) :
	ft_strdup("");
	ft_memset(zeroes, '0', zeroes_count >= 0 ? zeroes_count : 0);
	if (directive->conversion_character == '%')
		*number_to_print = ft_strjoin(zeroes, "%");
	else
		*number_to_print = ft_strjoin(zeroes, variable == 0 && directive->precision == 0 ? "" : static_itoa(ft_abs(variable)));
	*string_size = get_max(3, directive->field_width, directive->precision,
												ft_strlen(*number_to_print));
	return_string = malloc((*string_size + 1) * sizeof(char));
	return_string[*string_size] = '\0';
	ft_memset(return_string, (ft_strchr(directive->flags, '0') && directive->precision < 0) ||
	directive->precision > (int)ft_strlen(*number_to_print) ? '0' :
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

char		*get_int_print(t_directive *directive, long long int variable)
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
		if (directive->precision < directive->field_width && ft_strchr(return_string, ' '))
			*(ft_strrchr(return_string, ' ')) = '-';
		else if (*return_string == '0' && directive->precision < 0 )
			*return_string = '-';
		else
		{
			ptr_to_free = return_string;
			return_string = ft_strjoin("-", ptr_to_free);
			free(ptr_to_free);
		}
		return (return_string);
	}
	if (variable < 0 && ((return_string[0] == '0' && directive->precision < 0) || return_string[0] == ' '))
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
			if (directive->precision < directive->field_width && ft_strchr(return_string, ' '))
				*(ft_strrchr(return_string, ' ')) = ft_strchr(directive->flags, '+') ? '+' : ' ';
			else if (*return_string == '0' && directive->precision <= directive->field_width && (variable != 0 || ft_strrchr(return_string, '0') != return_string))
				*return_string = ft_strchr(directive->flags, '+') ? '+' : ' ';
			else
			{
				ptr_to_free = return_string;
				return_string = ft_strjoin(ft_strchr(directive->flags, '+') ? "+" : " ", ptr_to_free);
				free(ptr_to_free);
			}
			return (return_string);
		}
		if (((return_string[0] == '0' && directive->precision < 0) || return_string[0] == ' ') && (variable != 0 || ft_strrchr(return_string, '0') != return_string))
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
