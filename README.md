# ProjetPOO
Un projet : Modélisation simplifiée d’un système de transport de type « VAL »x

## Introduction
Le véhicule automatique léger (VAL) – anciennement acronyme du projet
Villeneuve-d’Ascq - Lille– est une technologie de métro de capacité intermédiaire
roulant sur pneumatiques et totalement automatique. Ce système de transport permet
l'exploitation d'un ensemble de véhicules circulant en ordre immuable sur une ligne
propre en circuit fermé.
## Présentation du projet
L’objet de ce projet est de modéliser la gestion des rames de métro en relation avec les
indications ci-dessous.
Le modèle de gestion proposé repose sur une supervision globale du système de
transport (le superviseur), un fonctionnement de chaque rame relativement autonome
(la rame) et un réseau de station autonome (la station) destiné à gérer l'afflux des
passagers entrant et sortant dans chaque rame.
Chaque rame gère en relative autonomie son fonctionnement et elle :
- circule sur un circuit fermé composé de station où elle doit bien évidemment
s’arrêter ;
- Gère son accélération (décélération) et sa vitesse.
En outre, les rames se suivent en circuit fermé en conservant une distance de sécurité
entre chaque rame. Chaque rame parcourt le même trajet aller et retour sur des lignes
séparées (logique !). A chaque terminus, la rame fait demi-tour en suivant un trajet
particulier consistant à aller dans une voie de réserve dans un sens et à repartir dans
l’autre sens pour se positionner au départ de la ligne sur le quai opposé.

![projet](https://github.com/AntoineHERBAUX/ProjetPOO/assets/112757413/0936f01b-dfeb-4a02-927c-65b9ae08a80f)

Le déplacement de chaque rame est régi par une phase d’accélération, une phase
éventuelle de parcours à une vitesse de fonctionnement constante (vitesse de croisière)
et une décélération en vue d’atteindre son prochain objectif (distance de sécurité,
arrivée dans une station…).
La vitesse de fonctionnement est donc fixée. L’accélération et la décélération sont
considérées comme constantes en valeur absolue sauf en cas d'arrêt d’urgence lors de
laquelle la décélération peut être plus brutale. L’arrêt d’urgence est initié aléatoirement
par le superviseur.
Le superviseur est informé en continu par chaque rame de leur position sur le parcours.
Cette information est disponible à l’ensemble des rames. Il peut également ordonner à
une rame d'effectuer un arrêt d’urgence en cas de défaut de sécurité (rame trop proche
l’une de l’autre, accident…). Egalement, un utilisateur peut interroger le superviseur
pour connaître la position de chaque rame, sa vitesse …
A chaque station, un nombre aléatoire de passagers sort et entre dans la rame. Le
nombre de passagers sortant de la rame ne peut bien évidemment pas être supérieur à
celui étant dans la rame et chaque rame ne peut contenir qu’un nombre limité de
passagers. Il est considéré que tout passager sortant de la rame sort également de la
station, et que si la rame est pleine, les passagers ne pouvant entrer dans la rame
restent sur le quai. Egalement, le temps d’arrêt est proportionnel au nombre de
passagers entrant et sortant de la rame. Chaque station suit en continu le flux des
passagers sur le quai.
## Travail à effectuer
Ce projet laisse beaucoup de liberté sur son implémentation. Les principales contraintes
reposent sur l’autonomie des différents acteurs et la synchronisation de leurs actions
respectives. A priori, au moins deux possibilités peuvent être envisagées pour assurer
l’autonomie de ces acteurs :
- Utilisation de « thread » modélisant chaque acteur avec un partage des
informations (vecteurs, tableaux …) entre chacun d’entre eux;
- Lancement de programmes indépendants qui communiquent par l’intermédiaire
de messages transmis par des « sockets » (via des interfaces réseaux).
Quelques indications pour débuter le projet :
- Dans un premier temps, définir les données pour chaque acteur et les
informations à échanger avec les autres acteurs.
- Par exemple, une rame peut avoir comme caractéristiques : son numéro, sa
position, vitesse, son nombre de passagers;
- Chaque station doit connaître le nombre de passagers sur le quai, savoir si une
rame est présente, et doit indiquer à la rame quand elle peut quitter le quai.
- Le superviseur doit pouvoir récupérer l’ensemble de ces informations et lancer
une procédure d’arrêt d’urgence le cas échéant. Il doit notamment indiquer à
chaque rame la position de toutes les rames pour assurer qu’une distance de
sécurité est maintenue entre chacune d’entre elles.
De plus, afin de donner un aspect ludique au projet, un plan simplifié du réseau avec le
positionnement des stations devra montrer graphiquement et en continu la position des
rames.

## Attendus du projet
Ce projet doit répondre au cahier des charges ci-dessus et être réalisé dans un temps
imparti. Il faut adopter une démarche assez conservatrice et ne pas se lancer dans des
procédures/projets trop complexes. A l’issue de ce projet, il est impératif que les
programmes fonctionnent soit en totalité ou pour le moins en partie. Utilisez les dépôts
git pour conserver les branches de projet qui fonctionnent correctement avant de vous
lancer dans de nouvelles implémentations.
Le projet est réalisé par un groupe de 2 étudiants. De plus, l’ensemble des programmes
devra pouvoir être compilé en C++ avec des outils standards indifféremment sous
Linux, MacOSX, Windows. En outre, il est impératif d’utiliser l’outil cmake pour la
gestion de la compilation des projets. Enfin, les programmes seront complétés par la
réalisation d’une capsule vidéo présentant votre projet.
