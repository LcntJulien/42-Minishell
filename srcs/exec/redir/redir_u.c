/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:52 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/21 10:56:51 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	redir_close(t_shell *mini, t_token *tk)
{
	if (!is_redir(tk, 1))
		close(mini->in);
	if (!is_redir(tk, 2))
		close(mini->out);
}

t_token	*del_arg(t_token *tk)
{
	t_token	*tmp;

	tmp = tk;
	if (tk->prev && tk->next)
	{
		tmp = tk->next;
		tmp->prev = tk->prev;
		tk->prev->next = tmp;
	}
	else if (tk->next)
	{
		tmp = tk->next;
		tmp->prev = NULL;
	}
	else if (tk->prev)
	{
		tmp = tk->prev;
		tmp->next = NULL;
	}
	else
		tmp = NULL;
	return (tmp);
}

t_token	*del_redir(t_token *tk)
{
	tk = del_arg(tk);
	tk = del_arg(tk);
	return (tk);
}

void	args_redir(t_shell *mini, t_token *tk)
{
	t_token	*cp;
	int		i;

	cp = tk;
	i = 0;
	while (cp && cp->type != PIPE)
	{
		while (cp && (cp->type == INPUT || cp->type == HEREDOC
				|| cp->type == OUTPUT || cp->type == APPEND))
			cp = del_redir(cp);
		if (!cp || !cp->next)
			break ;
		cp = cp->next;
	}
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	mini->args = args_alloc(cp);
	while (cp && cp->type != PIPE)
	{
		mini->args[i++] = cp->s;
		cp = cp->next;
	}
	if (mini->args)
		mini->args[i] = NULL;
}

int	is_redir(t_token *tk, int mode)
{
	t_token	*cp;
	int		in;
	int		out;

	cp = tk;
	in = 0;
	out = 0;
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == INPUT || cp->type == HEREDOC)
			in++;
		if (cp->type == OUTPUT || cp->type == APPEND)
			out++;
		cp = cp->next;
	}
	if (!mode && (in || out))
		return (1);
	if (mode == 1 && in)
		return (1);
	if (mode == 2 && out)
		return (1);
	return (0);
}
