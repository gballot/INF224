# Protocole de commmunication client serveur

On ferme la connection entre chaque requette.

### Requettes de client :
* create photo [<name> <path> <latitude> <longitude>]
* create video [<name> <path> <length>]
* create film [<name> <path> [<length> [<nb_chapters> <tab>]]]
* create film <name> <path> null <nb_chapters> <tab>
* create group [<name>]
* get media <name>
* get group <name>
* open media <name>
* delete media <name>
* delete group <name>

**Remarque :** <tab>
<tab> est un tableau d'entier, il s'agit simplement d'une suite d'entier
séparés par des espaces

### Réponses du serveur :

#### Pour les requettes de type create

réponse : "done"

#### Pour les requettes de type get media

réponse :
<media type> <name> <path> <info>

où <info> dépend du type de media :
* photo : <info> = <latitude> <longitude>
* video : <info> = <length>
* film : <info> = <nb_chapters> <length chap 1> <length chap 2> etc...

#### Pour les requettes de type get group

réponse : la liste des medias avec la syntaxe de get media

#### Pour les requettes de type detete

réponse : "done"
