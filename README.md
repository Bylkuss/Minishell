# minishell 42 - documentation

1. [Sujet](#sujet)
2. [Notes](#notes)

## Sujet
Écrivez un shell qui doit :
- Afficher un prompt en l’attente d’une nouvelle commande
- Chercher et lancer le bon executable (basé sur une variable d’environnement `PATH` ou en utilisant un path absolu), comme dans `bash`
- Vous devez implémenter les builtins suivants :
  - `echo` et l’option `-n`
  - `cd` uniquement avec un chemin absolu ou relatif
  - `pwd` sans aucune option
  - `export` sans aucune option
  - `unset` sans aucune option
  - `env` sans aucune option ni argument
  - `exit` sans aucune option
- `;` dans la ligne de commande doit séparer les commandes
- `'` et `"` doivent marcher comme dans bash, à l’exception du multiligne
- Les redirections `<`, `>`et `>>` doivent marcher comme dans bash, à l’exception des aggrégations de fd
- `|` doit marcher comme dans bash
- Les variables d’environnement (`$variable`) doivent marcher comme dans bash
- `$?` doit marcher comme dans bash
- `ctrl-C`, `ctrl-D` et `ctrl-\` doivent afficher le même résultat que dans bash

## Notes

### Fonctions autorisées
- `fork` : créé un nouveau processus enfant
- `wait` : attend un signal d'arrêt d'un processus, wait4 pour attendre la fin d'un processus précis
- `exit` : termine le processus
- `getcdw` : pour obtenir le pwd
- `stat` : donne toutes les infos d'un fichier comme un ls
- `lstat` : same sauf que dans le cas d'un lien donne les infos sur le lien et pas le fichier pointé
- `ftat` : donne toutes les infos sur un fichier comme un ls, mais cette fois on lui passe en argument le file descriptor
- `kill` : envoie un signal d'arrêt au processus indiqué
- `signal` : exécute  si `sig` est reçu
- `execve` : exécuter un exécutable, avec ses arguments et l'environnement en paramètres
- `dup` : duplique le descripteur d'un objet, i.e. attribue un nouveau descripteur qui pointe vers le même objet, ainsi lorsque l'on read sur l'un on avance sur les deux
- `dup2` : permet en plus de spécifier la valeur du descripteur
- `chdir` :  change le répertoire courant
- `opendir` : ouvre le fichier descriptif du dossier
- `readdir` : lit l'entrée suivante dans le fichier descriptif du dossier
- `closedir` : referme le ficher descriptif du dossier
- `pipe` : rempli un tableau avec deux nouveaux file descriptors qui vont être utiles pour changer l'entrée standard et la sortie standard