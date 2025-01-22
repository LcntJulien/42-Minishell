/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:46:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/26 11:20:47 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	space(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t') || (line[*i] == '\r'
			|| line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

void	token_idx(t_shell *mini)
{
	t_token	*cp;
	int		i;

	cp = mini->token;
	i = 0;
	while (cp != NULL)
	{
		cp->idx = i++;
		cp = cp->next;
	}
}

void	clean_tokens(t_token *tk)
{
	t_token	*cp;
	char	*s;

	cp = tk;
	s = NULL;
	while (cp)
	{
		if (is_quote(cp->s))
		{
			s = ft_strdup(cp->s);
			free(cp->s);
			cp->s = NULL;
			cp->s = clean_s(s);
			free(s);
		}
		cp = cp->next;
	}
}

t_token	*new_token(char *line, int *i, int j)
{
	t_token	*tk;

	tk = malloc(sizeof(t_token));
	if (!tk)
		return (NULL);
	tk->s = ft_calloc(sizeof(char), (str_alloc(line, i) + 1));
	if (!tk->s)
		return (NULL);
	while (line[*i])
	{
		if (line[*i] == ' ' && quote_state(line, *i) == 0)
			break ;
		if (line[*i + 1] && line[*i + 2] && ((line[*i] == '<'
					&& line[*i + 2] == '<') || (line[*i] == '>'
					&& line[*i + 2] == '>'))
			&& (line[*i - 1] != '<' || line[*i - 1] != '>'))
		{
			tk->s[j++] = line[*i + 2];
			(*i)++;
		}
		else
			tk->s[j++] = line[*i];
		(*i)++;
	}
	return (tk);
}

void	*get_token(char *line)
{
	t_token	*prev;
	t_token	*tk;
	int		i;

	prev = NULL;
	tk = NULL;
	i = 0;
	space(line, &i);
	while (line[i])
	{
		tk = new_token(line, &i, 0);
		if (!tk)
			return (NULL);
		tk->prev = prev;
		if (prev)
			prev->next = tk;
		tk_type(tk);
		prev = tk;
		space(line, &i);
	}
	if (tk)
		tk->next = NULL;
	while (tk && tk->prev)
		tk = tk->prev;
	return (tk);
}
