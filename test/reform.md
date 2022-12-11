

parse
        chek_arg  -> init_split
                                : *input -> **tab->node
                  -> node_type
                                : *input => space-padding       << node_num
                                : *input => endtype-padding     << tkn_num
        pars_arg
                  -> split_all
                                : tab->node[i]  => expd_var     << excpt_meta
                                                => expd_path    << path_builtins
                  -> div_token  
                                : *tab->node    => token_fill   << endtype_behavior
                  
                                : *tab->token   => substr / strjoin 
                                : **token->cmd  => cmd[n[0]], arg[n[1]], etype[n[2]]
                                : ***tab->cmds[tk_id][token->cmd[n]]
                    

parse.c         : check_arg, parse_arg, split_all, token_endtype.

init_split      : init_split, node_count, node_fill.

div_token       : div_token, token_count, token_fill

nodes           : token_node, ...type_check, ...node_padd 