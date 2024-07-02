/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kai11 <kai11@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:47:04 by kai11             #+#    #+#             */
/*   Updated: 2024/06/25 15:11:20 by kai11            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_char(char **s, char c)
{
	char	*new_word;
	size_t	len;

	len = strlen(*s) + 2;
	new_word = malloc(len * sizeof(char));
	if (new_word == NULL)
		fatal_error("malloc");
	strlcpy(new_word, *s, len);
	new_word[len - 2] = c;
	new_word[len - 1] = '\0';
	free(*s);
	*s = new_word;
}

void	handle_single_quote(char **dst, char **rest, char *word)
{
	append_char(dst, *word);
	word++;
	while (*word != SINGLE_QUOTE && *word)
		append_char(dst, *(word++));
	if (*word == '\0')
		assert_error("unclosed single quote");
	append_char(dst, *(word++));
	*rest = word;
}

void	handle_double_quote(char **dst, char **rest, char *word)
{
	append_char(dst, *word);
	word++;
	while (*word != DOUBLE_QUOTE && *word)
	{
		if (is_env_name(word))
			expand_env_name(dst, &word, word);
		else if (is_exit_var(word))
			expand_exit_var(dst, &word, word);
		else
			append_char(dst, *(word++));
	}
	if (*word == '\0')
		assert_error("unclosed double quote");
	append_char(dst, *word);
	word++;
	*rest = word;
}

void	expand_tok(t_token *tok)
{
	char	*new_word;
	char	*word;

	if (tok == NULL || tok->kind == TK_EOF || tok->word == NULL)
		return ;
	word = tok->word;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*word && !is_metacharacter(*word))
	{
		if (*word == SINGLE_QUOTE)
			handle_single_quote(&new_word, &word, word);
		else if (*word == DOUBLE_QUOTE)
			handle_double_quote(&new_word, &word, word);
		else if (is_env_name(word))
			expand_env_name(&new_word, &word, word);
		else if (is_exit_var(word))
			expand_exit_var(&new_word, &word, word);
		else
			append_char(&new_word, *(word++));
	}
	free(tok->word);
	tok->word = new_word;
	expand_tok(tok->next);
}
