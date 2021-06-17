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