/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:13:09 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/24 17:05:46 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

char		*get_string_print(t_directive *directive, char *variable)
{
	size_t	var_len;
	size_t	string_size;
	char	*return_string;

	if (variable == NULL)
		variable = directive->precision < 6 && directive->precision >= 0 ? ft_strdup("") : ft_strdup("(null)");
	var_len = (size_t)get_min(2, ft_strlen(variable), directive->precision >= 0 ? (size_t)directive->precision : ft_strlen(variable));
	string_size = get_max(2, directive->field_width, var_len);
	return_string = malloc((string_size + 1) * sizeof(char));
	return_string[string_size] = '\0';
	ft_memset(return_string, ' ', string_size);
	if (ft_strchr(directive->flags, '-'))
	{
		ft_strlcpy(return_string, variable, directive->precision >= 0 ?
		(size_t)directive->precision + 1 : string_size + 1);
		if (var_len != string_size)
			return_string[var_len] = ' ';
	}
	else
	{
		ft_strlcpy(return_string + string_size - var_len, variable,
		var_len + 1);
	}
	return (return_string);
}
