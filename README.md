```text
        :::      ::::::::
      :+:      :+:    :+:
    +:+ +:+         +:+
  +#+  +:+       +#+
+#+#+#+#+#+   +#+
     #+#    #+#
    ###   ########.fr
```
# Minishell

**As Beautiful as a Shell**

## 📝 Description

Minishell est un projet réalisé dans le cadre de l'École 42. L'objectif principal est de recréer un shell minimaliste inspiré de Bash. Ce projet permet de comprendre les mécanismes fondamentaux des systèmes d'exploitation, tels que la gestion des processus, les descripteurs de fichiers et les signaux, tout en respectant des contraintes de normes strictes.

Minishell propose les fonctionnalités de base suivantes :
- Affichage d'un prompt interactif.
- Historique des commandes.
- Exécution de commandes en recherchant les exécutables via `$PATH`.
- Gestion des redirections (`<`, `>`, `<<`, `>>`) et des pipes (`|`).
- Interprétation des variables d'environnement (`$VARIABLE`).
- Implémentation de commandes internes (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).
- Gestion des signaux (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) de manière conforme à Bash.

## 🎯 Objectifs

Ce projet met en évidence des compétences clés en programmation système, notamment :
- Manipulation des processus (`fork`, `execve`, `wait`, etc.).
- Gestion des descripteurs de fichiers pour les redirections et les pipes.
- Traitement des signaux pour assurer une interaction fluide en mode terminal.
- Respect des normes de codage strictes imposées par l'École 42.

## 🚀 Fonctionnalités Clés

- **Prompt interactif** : Affiche un prompt en attente de commandes utilisateur.
- **Historique** : Permet de parcourir les commandes précédentes grâce à `readline`.
- **Redirections** :
  - `<` : Redirection de l'entrée.
  - `>` : Redirection de la sortie.
  - `<<` : Lecture jusqu'à un délimiteur (`heredoc`).
  - `>>` : Append mode pour la sortie.
- **Pipes** : Permet de connecter plusieurs commandes entre elles.
- **Builtins** : Implémente des commandes essentielles sans appel système externe.
- **Gestion des signaux** : Comportement identique à Bash pour `Ctrl+C`, `Ctrl+D` et `Ctrl+\`.

## 💡 Défis Techniques

- **Gestion des processus** : Garantir l'exécution correcte des commandes tout en minimisant les fuites mémoire.
- **Conformité** : Implémenter les fonctionnalités demandées sans ajout inutile, en prenant Bash comme référence.
- **Optimisation** : Réduire l'utilisation des variables globales et gérer efficacement les signaux.

## 📂 Organisation des Fichiers

- `src/` : Contient le code source principal.
- `includes/` : Définitions des structures et des prototypes.
- `Makefile` : Script pour compiler le projet facilement.

## 🔧 Prérequis & Installation

### **1. Prérequis**
- **Installer Homebrew (macOS uniquement) :**
  ```bash
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  ```
- **Installer readline via Homebrew :**
    ```bash
    brew install readline
    ```
    (⚠️ vérifier correspondance entre le chemin de readline et celui utilisé dans le Makefile)
### **1. Installation**
- **Cloner le projet :**
    ```bash
    git clone https://github.com/LcntJulien/42-Minishell.git
    ```
- **Usage :**
    ```bash
    cd 42-Minishell
    ./minishell
    ```
