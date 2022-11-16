
#include "../../includes/minishell.h"

// int main(int ac, char ** av)
// {
//     // Configure readline to auto-complete paths when the tab key is hit.
//     if (ac > 0)
//     {
//         rl_bind_key('\t', rl_complete);

//         while (av)
//         {
//             // Display prompt and read input
//             char* input = readline("prompt> ");

//             // Check for EOF.
//             if (!input)
//                 break;

//             // Add input to readline history.
//             add_history(input);

//             // Do stuff...

//             // Free buffer that was allocated by readline
//             free(input);
//         }
//     }
//     return (0);
// }