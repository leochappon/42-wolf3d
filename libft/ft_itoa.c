/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:23:46 by lchappon          #+#    #+#             */
/*   Updated: 2018/04/18 22:34:17 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*str;
	int		length;
	int		is_neg;

	is_neg = (n < 0) ? -1 : 1;
	length = ft_nbrlen(n);
	str = (char *)malloc(sizeof(*str) * length + 1);
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	length--;
	while (length >= 0)
	{
		str[length] = ft_abs(n % 10) + '0';
		n = ft_abs(n / 10);
		length--;
	}
	if (is_neg == -1)
		str[0] = '-';
	return (str);
}
