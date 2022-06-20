/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:38:04 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/13 21:18:16 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	return (0);
}

static int	ft_issign(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	size_t	i;
	long	nb;
	t_bool	sign;

	i = 0;
	nb = 0;
	sign = FALSE;
	while (ft_isspace(str[i]))
		++i;
	if (ft_issign(str[i]))
	{
		if (str[i] == '-')
			sign = TRUE;
		++i;
	}
	if (sign)
		while (ft_isdigit(str[i]))
			nb = nb * 10 - (str[i++] - '0');
	else
		while (ft_isdigit(str[i]))
			nb = nb * 10 + (str[i++] - '0');
	return (nb);
}
