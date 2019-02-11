/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:22:41 by lchappon          #+#    #+#             */
/*   Updated: 2017/11/18 12:27:43 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	length;
	char	*str;
	size_t	i;

	if (s && f)
	{
		length = 0;
		while (s[length])
			length++;
		str = (char *)malloc(sizeof(*str) * (length + 1));
		if (str == NULL)
			return (NULL);
		i = 0;
		while (i < length)
		{
			str[i] = f(s[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
