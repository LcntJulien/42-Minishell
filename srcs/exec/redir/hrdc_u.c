/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:08:10 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/20 18:40:27 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_hrdc(t_token *tk)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->next && cp->type != PIPE)
	{
		if (cp->next && (cp->type == INPUT || cp->type == HEREDOC))
			cur = cp->next;
		cp = cp->next;
	}
	if (cur && cur->prev->type == HEREDOC)
		return (1);
	return (0);
}

int	nb_hrdc(t_shell *mini)
{
	t_token	*cp;
	int		i;
	int		r;

	cp = mini->token;
	i = -1;
	r = 0;
	while (++i < mini->ncmd)
	{
		if (is_redir(cp, 1) && is_hrdc(cp))
			r++;
		cp = next_cmd(cp);
	}
	return (r);
}

t_token	*next_hrdc(t_token *tk, int i)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	if (i != 0)
		cp = next_pipe(cp);
	while (cp && !is_hrdc(cp))
		cp = cp->next;
	while (cp && cp->next && cp->type != PIPE)
	{
		if (cp->next && cp->type == HEREDOC)
			cur = cp->next;
		cp = cp->next;
	}
	return (cur);
}
