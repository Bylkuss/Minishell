/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gehebert <gehebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/10 21:53:30 by gehebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int main(int argc, char const *argv[])
// {
//     if(argc)
//     {
//         printf("%s\n", &argv[0][2]);
//         for ( int loop = 0; loop <= 3; ++loop) {
//         for ( int each = 0; each <= 3; ++each) {
//             printf ( "\rloading%.*s   \b\b\b", each, "...");
//             fflush ( stdout);//force printing as no newline in output
//             sleep ( 1);
//         }
//     }
//     printf ( "\n");
//     }
//     return 0;
// }


int main(int ac, char ** av)
{
    // Configure readline to auto-complete paths when the tab key is hit.
    if (ac)
    {
        rl_bind_key('\t', rl_complete);

        while (av)
        {
            // Display prompt and read input
            char* input = readline("prompt> ");

            // Check for EOF.
            if (!input)
                break;

            // Add input to readline history.
            add_history(input);

            // Do stuff...

            // Free buffer that was allocated by readline
            free(input);
        }
    }
    return (0);
}