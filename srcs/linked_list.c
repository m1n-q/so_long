/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:33:58 by mishin            #+#    #+#             */
/*   Updated: 2021/07/01 17:40:00 by mishin           ###   ########.fr       */
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

void	ll_push(t_ll **head, t_ll *new)
{
	t_ll	*cur;

	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int		ll_clear(t_ll **head)
{
	t_ll	*cur;
	t_ll	*tmp;
	
	if (!head)
		return (-1);
	cur = *head;
	while (cur)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	*head = NULL;
	return (-1);
}
