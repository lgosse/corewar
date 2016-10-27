/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosse <lgosse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 16:05:09 by lgosse            #+#    #+#             */
/*   Updated: 2016/07/17 16:22:37 by lgosse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	ft_getinstr(char *fmt, t_instr *instr, int *i, va_list ap)
{
	ft_getattributes((char *)fmt, instr, i);
	ft_getflag((char *)fmt, instr, i);
	ft_getwidth((char *)fmt, instr, i, ap);
	ft_getprec((char *)fmt, instr, i, ap);
	ft_getlm((char *)fmt, instr, i);
	if (ft_getcs((char *)fmt, instr, i) == 1)
		return (1);
	return (0);
}

static void	ft_getstr(const char *fmt, int *i, t_print *print)
{
	while (fmt[*i] != '%' && fmt[*i] != '\0')
	{
		if (print->i % print->sz++ * 32 == 0)
			print->res = ft_realloc(print->res, print->i, print->sz++ * 32);
		print->res[print->i] = fmt[*i];
		print->i++;
		(*i)++;
	}
	if (fmt[*i] != '\0')
		(*i)++;
}

static int	ft_treatinstr(t_instr *instr, t_print *print, va_list ap)
{
	if (instr->cs == 'T')
		ft_treatattributes(instr, print);
	else if (instr->cs == '@')
		return (va_arg(ap, int));
	else if (instr->cs == 'c' || instr->cs == 'C' || instr->cs == '%')
		ft_treatchar(instr, print, ap);
	else if (instr->cs == 's' || instr->cs == 'S')
		ft_treatstr(instr, print, ap);
	else
		ft_redirectnb(instr, print, ap);
	return (1);
}

static char	*ft_quit_properly(t_instr *instr, t_print *print, int *i)
{
	char	*ret;

	ret = print->res;
	ret[print->i] = '\0';
	free(i);
	free(instr);
	free(print);
	return (ret);
}

char		*ft_sprintf(const char *fmt, ...)
{
	va_list		ap;
	t_print		*print;
	t_instr		*instr;
	int			*i;

	if ((i = (int *)malloc(sizeof(int))) == NULL)
		return (0);
	*i = 0;
	if ((print = ft_init_print()) == NULL)
		return (0);
	instr = NULL;
	va_start(ap, fmt);
	while (fmt[*i] != '\0')
	{
		ft_getstr(fmt, i, print);
		if ((instr = ft_init_instr(instr)) == NULL)
			return (0);
		if (ft_getinstr((char *)fmt, instr, i, ap))
			ft_treatinstr(instr, print, ap);
	}
	va_end(ap);
	return (ft_quit_properly(instr, print, i));
}
