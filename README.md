# Instructions

Pour générer les fichiers plot et les fichiers image, lancez le script exec.sh de chaque TP.

Les script peut prendre des arguments. le premier argument indique le nom de l'expérience, il est commun à tous les TP.

le script exec.sh génére les fichiers plot et images dans le repertoire ./plots/exp_"arg1"/

## TP1

Le test sur tous les languages de programmation du TP1 s'effectu comme suit:
```bash
./exec.sh "experience1" 4
```
Le second argument indique le nombre de fois qu'on doit repété l'expérience (c'est pour étudier la répétabilité)

Concernant les modification apportées dans le code C: on peut par exemple faire varier alpha dans les sources puis on lance le script suivant.


```bash
./exec_c.sh "experience1"
```
## TP2

Le script du TP2 réalise le test mais on faisant varier la probabilité p d'avoir un ajout de 0.1 à 1.0:

```bash
./exec.sh "experience1"
```

## TP3

```bash
./exec.sh "experience1" ordre p
```
p : probabilité d'avoir un ajout (0.5 par défaut)

ordre = 0: ordre croissant des valeurs à insérer (choix par défaut)

ordre = 1: ordre décroissant des valeurs à insérer

ordre = 2: ordre aléatoire des valeurs à insérer

## TP4

pareil que le TP3