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
méthode abstraite. Une classe qui contient un méthode abstraite est appelé calsse 
abstraite et ne peut pas être instancié.  
On la déclare comme ceci :

    virtual <type> <methode>(<args>) [const] = 0;

> Si vous avez fait correctement ce qui précède, il ne sera plus possible
> d'instancer des objets de la classe de base. Pourquoi ? 

    Comme dit plus haut on ne peut pas instancié une classe abstraite. En effet,
    une méthode abstraite n'a pas d'implémentation dans la classe abstraite. Si on
    essaie d'avoir une instance, alors sa vtable n'est pas complète...
