/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 03:24:21 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/30 00:43:44 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_malloc(void **ptr, size_t n)
{
	*ptr = malloc(n);
	if (*ptr)
		return (TRUE);
	return (FALSE);
}

t_bool	ft_calloc(void **ptr, size_t n)
{
	if (!ft_malloc(ptr, n))
		return (FALSE);
	ft_memset(*ptr, 0, n);
	return (TRUE);
}
