/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loadjou <loadjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/08 13:16:58 by loadjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char const *argv[])
{
    if(argc)
    {
        printf("%s\n", &argv[0][2]);
        for ( int loop = 0; loop <= 3; ++loop) {
        for ( int each = 0; each <= 3; ++each) {
            printf ( "\rloading%.*s   \b\b\b", each, "...");
            fflush ( stdout);//force printing as no newline in output
            sleep ( 1);
        }
    }
    printf ( "\n");
    }
    return 0;
}
