/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/06 14:43:12 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/05 19:00:06 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char *dest;

	dest = NULL;
	if (s1)
	{
		dest = ft_strnew(ft_strlen(s1));
		if (dest != NULL)
			ft_strcpy(dest, s1);
	}
	return (dest);
}
