/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:06:38 by csnowbal          #+#    #+#             */
/*   Updated: 2020/06/02 18:56:04 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int	main(void)
{
	int a = 5;
	ft_printf("|");
	ft_printf("%hhi", 45);
	printf("|\n|");
	printf("%hhi", 45);
	printf("|\n");
	return (0);
}
