/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:35:06 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/20 11:59:00 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_token	*next_pipe(t_token *tk)
{
	while (tk && tk->next && tk->type != PIPE)
		tk = tk->next;
	if (!tk)
		return (NULL);
	else if (tk->type == PIPE)
		tk = tk->next;
	return (tk);
}

t_token	*prev_cmd(t_token *tk)
{
	t_token	*cp;

	cp = tk;
	if (cp && cp->prev)
	{
		cp = cp->prev;
		while (cp && cp->type != CMD && cp->type != BUILTIN)
			cp = cp->prev;
	}
	return (cp);
}

t_token	*find_cmd(t_token *tk)
{
	t_token	*cp;

	cp = tk;
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->next && cp->type != PIPE)
	{
		if (cp->type == CMD || cp->type == BUILTIN)
			return (cp);
		cp = cp->next;
	}
	return (tk);
}

t_token	*next_cmd(t_token *tk)
{
	while (tk && tk->next && tk->type != PIPE)
		tk = tk->next;
	if (!tk)
		return (NULL);
	else if (tk->type == PIPE)
	{
		tk = tk->next;
		tk = find_cmd(tk);
	}
	return (tk);
}

int	get_htab(t_shell *mini, int i)
{
	t_token	*cp;
	int		j;
	int		r;

	cp = mini->token;
	j = -1;
	r = 0;
	while (++j < i)
	{
		if (is_redir(cp, 1) && is_hrdc(cp))
			r++;
		cp = next_cmd(cp);
	}
	return (r);
}
