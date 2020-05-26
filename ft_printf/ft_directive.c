/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_directive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 05:08:55 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/24 21:14:33 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static char	*get_flag(const char **format_string)
{
	int		i;
	char	format_characters[5];
	char	*flags;

	format_characters[0] = '-';
	format_characters[1] = '+';
	format_characters[2] = ' ';
	format_characters[3] = '0';
	format_characters[4] = '#';
	i = -1;
	flags = ft_calloc(4, sizeof(char));
	while (ft_strchr(format_characters, **format_string))
	{
		if (**format_string == '-')
		{
			if (!ft_strchr(flags, '-' && !ft_strchr(flags, '0')))
				flags[++i] = **format_string;
			else if (ft_strchr(flags, '0'))
				*(ft_strchr(flags, '0')) = **format_string;
		}
		if (**format_string == '0' && !ft_strchr(flags, '0') && !ft_strchr(flags, '-'))
			flags[++i] = **format_string;
		if (**format_string == ' ' && !ft_strchr(flags, ' ') && !ft_strchr(flags, '+'))
			flags[++i] = **format_string;
		if (**format_string == '+')
		{
			if (!ft_strchr(flags, '+' && !ft_strchr(flags, ' ')))
				flags[++i] = **format_string;
			else if (ft_strchr(flags, ' '))
				*(ft_strchr(flags, ' ')) = **format_string;
		}
		if (**format_string == '#')
			flags[++i] = **format_string;
		++(*format_string);
	}
	return (flags);
}

static int	get_field_width(const char **format_string)
{
	int	field_width;

	if ((field_width = ft_atoi(*format_string)) && field_width > 0)
	{
		while (ft_isdigit(**format_string))
			++(*format_string);
		return (field_width);
	}
	else if (**format_string == '*')
	{
		++(*format_string);
		return (-2);
	}
	return (0);
}

static int	get_precision(const char **format_string)
{
	int	precision;

	if (**format_string == '.')
	{
		++(*format_string);
		if (**format_string == '*')
		{
			++(*format_string);
			return (-2);
		}
		precision = ft_atoi(*format_string);
		while (ft_isdigit(**format_string))
			++(*format_string);
		return (precision);
	}
	return (-1);
}

static char	get_conversion_character(const char **format_string)
{
	char	conversion_character;

	if (ft_strchr("cspdiuxX%", **format_string) && **format_string != '\0')
	{
		conversion_character = **format_string;
		++(*format_string);
		return (conversion_character);
	}
	++(*format_string);
	return (ERROR);
}

t_directive	*get_directive(const char **format_string)
{
	t_directive	*directive;

	++(*format_string);
	directive = (t_directive *)malloc(sizeof(t_directive));
	directive->flags = get_flag(format_string);
	directive->field_width = get_field_width(format_string);
	directive->precision = get_precision(format_string);
	if (**format_string == '\0')
		return (NULL);
	directive->conversion_character = get_conversion_character(format_string);
	return (directive);
}
