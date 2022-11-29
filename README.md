# MiniShell42
Mimic of Shell command
Makefile

  ## Shell(main)
  * while loop    				__(prompt)
    * getline user     		__(input)
    * linebuffer define	
  * signal checker 		  	__(errSystm)
  * treeNode 				      __(jobList)
  ## Lexer
   * Token Type init.			__(enum char)
   * Lexer_Builer				  __(table command)
      * Buffer_split		  __(Tree_node)
        * Quotes, “|” , “&” , “$” …
      * Token _list 		(Linked_list)
        * “JOB”:”ARGS”:”REDIR”...
      * Wrap_Command	(Complete_Final)
        * Call _Exec 
  ## Parser
   * Tree_Node_Set	
   * Seq_Job_Exec
  ## Execute
   * Seq. Event
    * ...cmds :: args :: endtype...
   * Sig. Event
    * parent, child, error
  ## Command
   * Path = /bin 
   * Pid  = 0
   * Redir <,<<,>>,>,|,(EOT) ... end Of Type 
