/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelbyfunc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 17:12:27 by lgosse            #+#    #+#             */
/*   Updated: 2016/07/13 17:29:35 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_lstdelbyfunc(t_list **alst, void (*del)(void **content))
{
	t_list		**tmp;
	t_list		**tmp2;

	tmp = alst;
	while (*tmp)
	{
		if (del)
			del((&(*tmp)->content));
		tmp2 = tmp;
		tmp = &((*tmp)->next);
		ft_memdel((void**)tmp2);
	}
}
