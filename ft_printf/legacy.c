/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 20:17:41 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/03 05:44:16 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_float_print(t_directive *directive, float variable)
{
	char			*decimal_part_string;
	char			*number_to_print;
	char			*return_string;
	long long int	int_part;
	long long int	decimal_part;

	int_part = (long long int)variable;
	variable -= int_part;
	decimal_part = (long long int)(1000000000000000000 * variable);
	while (decimal_part % 10 == 0)
		decimal_part /= 10;
	decimal_part_string = static_itoa(decimal_part);
	decimal_part_string[directive->precision >= 0 ? directive->precision : 6] = '\0';
	number_to_print = ft_strjoin(static_itoa(int_part), ".");
	number_to_print = ft_strjoin(number_to_print, decimal_part_string);
	return_string = ft_calloc(get_max(2, ft_strlen(number_to_print), directive->field_width), sizeof(char));
	return (number_to_print);
}