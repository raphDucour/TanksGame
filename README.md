# ToonTanks - Unreal Engine 5.5 - Date 2024/2025


Un jeu de combat de tanks arcade développé sous Unreal Engine 5.5. Ce projet est basé sur une base tutorielle de Stephen Ulibarri, que j'ai étendue avec des mécaniques de gameplay originales et des systèmes avancés en C++.

## 🚀 Fonctionnalités implémentées (Au-delà du tutoriel)

Pour me familiariser avec l'architecture C++ d'Unreal, j'ai ajouté les modules suivants :

### 1. Système de Projectiles Avancés
* **Rebond Dynamique :** Implémentation d'une logique de réflexion vectorielle permettant aux obus de rebondir sur les surfaces (`FMath::GetReflectionVector`).
* **Gestion des Rebonds :** Le nombre de rebonds est paramétrable via une variable `NumRebound`.
* **Effets de Recul :** Ajout d'un recul visuel sur le mesh de la tourelle et d'une impulsion physique sur le tank (`LaunchCharacter`) lors du tir.

### 2. IA Ennemie : "Tank Evil"
* **Poursuite Dynamique :** Création d'une classe `ATankEvilCharacter` utilisant l'AI Controller pour suivre activement le joueur (différent des tourelles statiques de base).
* **Rotation Indépendante :** Gestion de la rotation de la base et de la tourelle de manière asynchrone pour un comportement plus fluide.

### 3. Système d'Upgrades & Power-ups
* **Loot Système :** À la destruction d'un acteur, un objet d'upgrade peut apparaître (`UpgradeClass`).
* **Multi-Tir :** Gestion de patterns de tir complexes (jusqu'à 6 projectiles simultanés) avec calcul automatique du décalage spatial des obus.

### 4. Améliorations de Feedback (GameFeel)
* **Destruction Physique :** Intégration de *Geometry Collections* pour une destruction plus réaliste des tanks ennemis(ils se divisent en pleins de morceaux lors de l'explosion).

## 🛠️ Stack Technique
* **Moteur :** Unreal Engine 5.5
* **Langage :** C++ (Architecture basée sur l'héritage : `BasePawn` -> `TankPlayer` / `Tower`)
* **Input System :** Enhanced Input (Mapping dynamique)

## 📂 Structure du Code Source
* `Projectile.cpp/.h` : Logique des rebonds et des dégâts.
* `TankCharacter.cpp/.h` : Comportement de base, gestion du recul et du multi-tir.
* `HealthComponent.cpp/.h` : Système de vie générique, communication via délégués dynamiques (`OnTakeAnyDamage`).

---
*Projet réalisé par Raphaël Ducour dans le cadre d'un apprentissage approfondi de l'API C++ d'Unreal Engine.*
