# MiniShell42
Mimic of Shell command
* Makefile
  * Libft
  * Readline

## Shell(main)
  * Envp
    * user, path, ...
  * Main loop    				__(prompt)
    * readline       		__(input)
  * Signal       		  	__(errSystm)
    * handling error    __(sigaction)
## Parsing
   * Init. args   			__(enum char)
   * Manage quotes		  __(split_able)
   * Node split	    	  __(space_divide)
      * Meta_char  “|” , “<” , “>” ...
   * Token_izer      		__(command line)
      * “JOB”:”ARGS”:”REDIR”...
   * Endtype redirs     __(behavior_ctrl)
     * redirs <,<<,>>,>,| 
## Execute
   * Token Event
    * ...cmds :: args :: endtype...
   * Signal Event
    * Error 
   * Builtins
    * parent, child
   * pid, path 
