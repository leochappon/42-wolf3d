/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchappon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:08:52 by lchappon          #+#    #+#             */
/*   Updated: 2017/11/23 12:30:51 by lchappon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin;
	t_list	*new;
	t_list	*tmp;

	begin = NULL;
	if (!lst && !f)
		return (NULL);
	begin = f(lst);
	new = begin;
	lst = lst->next;
	while (lst)
	{
		tmp = f(lst);
		new->next = tmp;
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (begin);
}
