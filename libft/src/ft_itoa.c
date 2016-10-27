/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:25:06 by lgosse            #+#    #+#             */
/*   Updated: 2016/06/04 11:16:47 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_itoa(int n)
{
	char	*nb;
	int		i;

	nb = NULL;
	i = ft_get_nb_length(n, 10);
	if (n == -2147483648 || n == 0)
		return (n == 0 ? ft_strdup("0") : ft_strdup("-2147483648"));
	if ((nb = ft_strnew(i--)))
	{
		if (n < 0)
		{
			n = -n;
			nb[0] = '-';
		}
		while (i >= 0 && nb[i] != '-')
		{
			if (i >= 0)
			{
				nb[i] = n % 10 + '0';
				n /= 10;
			}
			i--;
		}
	}
	return (nb);
}
