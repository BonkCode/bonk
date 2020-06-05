/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_char_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:12:28 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/03 07:47:26 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

char	*get_char_print(t_directive *directive, char variable)
{
	size_t	string_size;
	char	*return_string;

	string_size = directive->field_width > 1 ? directive->field_width : 1;
	return_string = malloc(string_size + 1 * sizeof(char));
	return_string[string_size] = '\0';
	ft_memset(return_string, ' ', string_size);
	return_string[ft_strchr(directive->flags, '-') ? 0 : string_size - 1] = variable == 0 ? '\x00' : variable;
	if (variable == 0)
	{
		while (*return_string != '\0')
		{
			ft_putchar_fd(*return_string, 1);
			++return_string;
		}
		ft_putchar_fd(*return_string, 1);
		++return_string;
		while (*return_string != '\0')
		{
			ft_putchar_fd(*return_string, 1);
			++return_string;
		}
		return (ft_strdup(""));
	}
	return (return_string);
}
