/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:45:47 by rtrant            #+#    #+#             */
/*   Updated: 2020/05/07 19:46:51 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_elem;

	if (!del)
		return ;
	while ((*lst) != NULL)
	{
		next_elem = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next_elem;
	}
}
