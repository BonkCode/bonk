/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:27:33 by rtrant            #+#    #+#             */
/*   Updated: 2020/06/05 16:18:30 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"
#include "libftprintf.h"

char		*get_what_to_print(va_list argptr, t_directive *directive)
{
	if (directive->conversion_character == 'c')
		return (get_char_print(directive, va_arg(argptr, int)));
	else if (directive->conversion_character == 's')
		return (get_string_print(directive, va_arg(argptr, char *)));
	else if (directive->conversion_character == 'u' ||
	directive->conversion_character == 'x' ||
	directive->conversion_character == 'X')
	{
		if (ft_strchr(directive->length_modifier, 'l'))
		{
			if (ft_strlen(directive->length_modifier) == 1)
				return (get_unsigned_int_print(directive, va_arg(argptr,
				unsigned long int)));
			else
				return (get_unsigned_int_print(directive, va_arg(argptr,
				unsigned long long int)));
		}
		return (get_unsigned_int_print(directive, va_arg(argptr,
		unsigned int)));
	}
	else if (directive->conversion_character == 'd' ||
	directive->conversion_character == 'i')
	{
		if (ft_strchr(directive->length_modifier, 'l'))
		{
			if (ft_strlen(directive->length_modifier) == 1)
				return (get_int_print(directive, va_arg(argptr,
				long int)));
			else
				return (get_int_print(directive, va_arg(argptr,
				long long int)));
		}
		return (get_int_print(directive, va_arg(argptr, int)));
	}
	else if (ft_strchr("feg", directive->conversion_character))
		return (get_float_print(directive, va_arg(argptr, double)));
	else if (directive->conversion_character == '%')
		return (get_int_print(directive, '%'));
	else if (directive->conversion_character == 'p')
		return (get_pointer_print(directive,
		va_arg(argptr, unsigned long int)));
	else
		return (ft_strdup(""));
}

static int	print_formatted(const char **format_string, va_list argptr)
{
	t_directive	*directive;
	char		*what_to_print;
	int			return_value;

	directive = get_directive(format_string);
	if (directive == NULL)
		return_value = -1;
	else
	{
		if (directive->field_width == -2)
		{
			directive->field_width = va_arg(argptr, int);
			if (directive->field_width < 0)
				directive->flags = ft_strjoin(directive->flags, "-");
			directive->field_width = ft_abs(directive->field_width);
		}
		if (directive->precision == -2)
			directive->precision = va_arg(argptr, int);
		what_to_print = get_what_to_print(argptr, directive);
		ft_putstr_fd(what_to_print, 1);
		return_value = ft_strlen(what_to_print);
	}
	return (return_value);
}

int			ft_printf(const char *format_string, ...)
{
	va_list		argptr;
	int			return_value;

	return_value = 0;
	va_start(argptr, format_string);
	while (*format_string != '\0')
	{
		if (*format_string == '%')
		{
			return_value += print_formatted(&format_string, argptr);
		}
		else
		{
			ft_putchar_fd(*format_string, 1);
			++return_value;
			++format_string;
		}
	}
	va_end(argptr);
	return (return_value);
}

/*
** int	main(void)
** {
** 	int sum;
** 	char flags[] = "-0";
** 	char conversion_character[] = "cspdiuxX%";
** 	for (int i = -10; i < 10; ++i)printf ("no flag");
** 			for (int k = 1; k < 254; ++k)
** 			{
** 				for (int t = 1; t < 254; ++t)
** 				{
** 					char input[100];
** 					char character1[2];
** 					char character2[2];
** 					character1[1] = '\0';
** 					character2[1] = '\0';
** 					ft_bzero(input, 100);
** 					ft_strlcat(input, "%", ft_strlen(input) + 2);
** 					character1[0] = (char)k;
** 					ft_strlcat(input, character1, ft_strlen(input) + 2);
** 					ft_strlcat(input, ft_itoa(i), 100);
** 					ft_strlcat(input, ".", ft_strlen(input) + 2);
** 					ft_strlcat(input, ft_itoa(j), 100);
** 					character2[0] = (char)t;
** 					ft_strlcat(input, character2, ft_strlen(input) + 2);
** 					sum = (int)character1[0] + (int)character2[0] + i + j;
** 					if (i <= 0 || j < 0 || !ft_strchr(flags,
** character1[0]) || !ft_strchr(conversion_character, character2[0]))
** 						sum = -1;
** 					if(ft_printf(input) != sum)
** 					{number_to_print = malloc(get_max(2,
** ft_strlen(ft_itoa(variable)), directive->precision) + 1);
** 	number_to_print[get_max(2, ft_strlen(ft_itoa(variable)),
** directive->precision)] = '\0';
** 	ft_memset(number_to_print, '0', ft_strlen(number_to_print));e:
** %s your output: %i  desired output: %i\n", input, ft_printf(input), sum);
** 						return (0);
** 					}
** 				}
** 			}
** 		}
** 	}
** 	printf ("All correct, tests performed:\ntested output of all
** \"get\" functions\n");
** 	return (0);
** }
*/

/*
int			main(void)
{
 	int a;
 	int	*ptr;
 	int	my_value;
 	int	orig_value;
 
 	a = 5;
 	ptr = &a;
 	my_value = ft_printf("%s %5c %05u %-5.1i %-.5X %% %-*p qew\n",
 	"my name's jeff", 'A', 42u, -21, 0xff, 20, ptr); 	orig_value = printf("%s %5c %05u %-5.1i %-.5X %% %-*p qew\n",
 	"my name's jeff", 'A', 42u, -21, 0xff, 20, ptr);
 	ft_printf("\nmy value: %i\noriginal value: %i\n", my_value, orig_value);
 	return (0);
}
*/