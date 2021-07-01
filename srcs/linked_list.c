/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:33:58 by mishin            #+#    #+#             */
/*   Updated: 2021/06/29 07:12:27 by shin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_ll	*ll_new(char c)
{
	t_ll	*ret;

	ret = (t_ll *)malloc(sizeof(t_ll));
	if (!ret)
		return (NULL);
	ret->c = c;
	ret->next = NULL;
	return (ret);
}

void	ll_push(t_ll **ll, t_ll *new)
{
	t_ll	*cur;

	if (!ll)
		return ;
	if (!*ll)
	{
		*ll = new;
		return ;
	}
	cur = *ll;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int		ll_clear(t_ll **ll)
{
	t_ll	*cur;
	t_ll	*tmp;

	if (!ll)
		return (-1);
	cur = *ll;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	*ll = NULL;
	return (-1);
}
