

parse
        chek_arg  -> init_split
                                : *input -> **tab->node
                  -> node_type
                                : *input => space-padding       << node_num
                                : *input => etype-padding     << tkn_num
        pars_arg
                  -> split_all
                                : tab->node[i]  => expd_var     << excpt_meta
                                                => expd_path    << path_builtins
                  -> div_token  
                                : *tab->node    => token_fill   << etype_behavior
                  
                                : *tab->token   => substr / strjoin 
                                : **token->cmd  => 	cmd [0] == command args {builtin}
                                :			cmd [1] == str to pass as args {if}
                                :			cnd [2] == etype of token {redir/close}
                                			
                                : ***tab->cmds 		*[tk_id] **[token->cmd[n]]
                                :				**tab->token->cmd = {"ls","-lta","|"}
                                :					"ls" 	: command  -> builtin -> path
                                : 					"-lat"	: args	   -> follow camand ...
                                :					"|"	: redir    -> fork/dup2/ set outfile/infile next cmd...	
                    




parse.c         : check_arg, parse_arg, split_all, token_etype.

init_split      : init_split, node_count, node_fill.

div_token       : div_token, token_count, token_fill

nodes           : token_node, ...type_check, ...type_padd 



	
