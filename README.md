Schema


-------------				-> Update Gamestate
|			| -------> Game -> Entities
| Engine	|
|			| -------> Dynamic GraphicLibrary
------------- <------- Handle User Events / Inputs

Salut !

Comme tu vas le voir dans les fichiers / commit. J'ai passe la classe AEntity en abstract class. J'ai enlever l'idee dans snake vus que la class Game contient toutes les entities on pourra attribuer l'ID a partir de cette derniere.

Concernant la suite je pense encapsuler la class game dans une class Engine qui fera le lien entre le jeu et la gestion dynamique des librairies. En gros l'Engine gere le tick appelle l'update du jeu en fonction qui gere les relations entre les entitee, file le resultat a la lib graphique qui affiche le bouzin. Il recupere les entree utilisateur et re-dispatch au jeu. End of story.

On voit ca demain (;
