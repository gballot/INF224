# INF224 : TP C++/OBJET

## Photos et Videos

### Méthodes abstraites

> Comme pour la fonction d'affichage, la fonction pour jouer l'objet ne modifie pas
> l'objet et elle doit être déclarée dans les classes Photo et Video et dans la classe
> de base afin de permettre un appel polymorphique sur la hiérarchie de classes.
> Cependant, contrairement à la fonction d'affichage, elle ne peut pas avoir d'implementation
> au niveau de la classe de base (car a priori chaque type d'objet nécessite un
> utilitaire différent pour être joué). Comment appelle-t'on ce type de méthode et
> comment faut-il les déclarer ?

Une méthode qui ne peut pas avoir d'implémentation dans la super-classe est appelée 
**méthode abstraite**. Une classe qui contient un méthode abstraite est appelé calsse 
abstraite et ne peut pas être instancié.  
On la déclare comme ceci :

    virtual <type> <methode>(<args>) [const] = 0;

> Si vous avez fait correctement ce qui précède, il ne sera plus possible
> d'instancer des objets de la classe de base. Pourquoi ? 

Comme dit plus haut on ne peut pas instancié une classe abstraite. En effet,
une méthode abstraite n'a pas d'implémentation dans la classe abstraite. Si on
essaie d'avoir une instance, alors sa vtable n'est pas complète...


## Traitement Générique en utilisant le polymorphisme


> Cette boucle n'a pas besoin de connaître le type des élements : elle doit pouvoir
> traiter de la même manière tous les objets dérivant de la classe de base.
> Quelle est la propriété caractéristique de l'orienté objet qui permet de faire
> cela ? Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ? Quel
> est le type des éléments du tableau : est-ce que ce tableau contient les objets
> ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java. 

Le **polymorphisme** permet de traiter de la même manière tous les objets de la classe
Media, qu'ils soient photo ou vidéo.  
En C++ il faut faire `delete` explicitement contrairement à Java pour liberer l'espace mémoire.
Le tableau continent des pointeurs vers les objets, comme c'est souvent le cas en 
C++. On ne connait pas la taille des objets de type Media car c'est une classe abstraite, il
faut donc mettre des pointeurs dans le tableau.
En java, on ne manipule que des pointeurs vers les objets, tandis qu'en C++ on a le choix de
manipuler des objet ou des pointeurs.


## Films et tableaux


> Que faut-il faire pour que l'objet Film ait plein contrôle sur ses données
> et que son tableau de durées des chapitres ne puisse pas être modifié (ou pire,
> détruit) à son insu ? (c'est l'objet qui doit pouvoir modifier ce qui
> lui appartient, pas les autres !)

Pour que le film garde contrôle sur son tableau il faut qu'il le recopie

> Attention, le même problème se pose si un accesseur retourne directement ce
> tableau sans prendre les précautions nécessaires : la encore le contenu du tableau
> n'est pas récopié et l'appelant peut le modifier à sa guise. Quelle est la
> solution très simple que propose C/C++ pour éviter ce problème ?

Pour éviter ce problème, c'est l'appelant qui créée le tableau d'une longeur
maximale fixée et qui le donne en arguement à la fonction `getChapters` ainsi
que cette taille maximale.
