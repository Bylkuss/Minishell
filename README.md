# Minishell 42 - documentation

<p align="center">
    <a href="https://www.cprogramming.com/"><img alt="Made with C" src="https://img.shields.io/badge/Made%20with-C-1f425f.svg"/></a>
    <img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/bylkuss/minishell?color=lightblue" />
    <img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/bylkuss/minishell?color=critical" />
    <img alt="Code language count" src="https://img.shields.io/github/languages/count/bylkuss/minishell?color=yellow" />
    <img alt="GitHub top language" src="https://img.shields.io/github/languages/top/bylkuss/minishell?color=blue" />
    <img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/bylkuss/minishell?color=green" />
</p>



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


***********************************************
 <footer>
    <p align=center style="float:left; width: 20%;">
        &copy; Lounes Adjou, Germain Hebert, 2023
    </p>
    <p align=center style="float:left; width: 20%;">
        For inquiries, please email me at: <a href="mailto:lounes.adjou@gmail.com">email</a>
    </p>
</footer>

 ***********************************************
