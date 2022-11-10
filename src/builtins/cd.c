/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bylkus <bylkus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:38:29 by loadjou           #+#    #+#             */
/*   Updated: 2022/11/10 09:36:31 by bylkus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int argc, char const *argv[])
{
    char *ptr;
    if(argc)
    {
        printf("%s\n", &argv[0][2]);
        /*
        for ( int loop = 0; loop <= 3; ++loop) {
        for ( int each = 0; each <= 3; ++each) {
            printf ( "\rloading%.*s   \b\b\b", each, "...");
            fflush ( stdout);//force printing as no newline in output
            sleep ( 1);
            }
        */
    // ptr = fgets(s, 100, 0);
    while(1)
    {
        ptr = readline("prompt>");
        add_history(ptr);
        // ptr = readline("prompt>");
        if(!ptr)
            break ;
        free(ptr);
    }
    printf("testcli> ");
    printf ( "\n");
    // scanf("%s", command buf);
    }
    return 0;
}
