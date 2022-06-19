/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:21:23 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/18 18:22:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef enum s_bool
{
	FALSE,
	TRUE
}			t_bool;

t_bool	ft_malloc(void **ptr, size_t n);
long	ft_atol(const char *str);
void	ft_swap(int *a, int *b);

#endif
