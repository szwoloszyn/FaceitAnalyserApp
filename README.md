# FaceitAnalyserApp

## Overwiev

FaceitAnalyserApp is a GUI application written in C++ Qt6 library. Designed to fetch and display player statistics on Faceit. 
- [Faceit](www.faceit.com) is an esports platform used as an alternative to official in-game matchmaking. It's most popular in CS2.
- With this application user can analyse player's statistics in CS2 matches played on Faceit.
- To generate output you need player's `nickname` and optionally `match id` / `matchroom link`

## Features

- Player's __lifetime__ stats and data, including:
    - `avatar` - player's profile picture set on faceit account
    - `elo` - player's rating on faceit. [General idea](https://en.wikipedia.org/wiki/Elo_rating_system)
    - `level` - number in range 1-10 indicating player's skill, based on `elo` amount
    - `level progress` - shows how close the player is to reaching next level
    - amount of matches played on faceit
    - `KDR` - kill per death ratio
    - `ADR` - avarage damage per round
    - `HLTV 1.0` - rating used by [hltv.org](www.hltv.org) page to assess profesional player's performance (more info of how its calculated later on)
- Player's data and avarage stats __50 matches back__, containing same data as lifetime
- Player's statistic for given __match__, including:
    - `Map` played in given match
    - `Score` (always in format: `YOUR / ENEMY`)
    - `K/A/D` - kills / assists / deaths
    - `HLTV` - hltv rating for single match

## Usage

#### Compilation using [cmake](https://cmake.org/documentation/)
- Install [Qt library](https://doc.qt.io/qt-6/get-and-install-qt.html) on your device
- The easiest way is to use `Qt Creator` - an IDE providing easy and intuitive access to Qt library. *(File -> Open Project -> FaceitAnalyserApp -> CMakeLists.txt)*
- To compile through terminal we need to know Qt library files location:
```sh
# for linux-based systems
git clone https://github.com/szwoloszyn/FaceitAnalyserApp.git
cd path/to/project/FaceitAnalyserApp
PATH_TO_QT=$(qtpaths6 --qt-version)
mkdir build && cd build
cmake ../CMakeLists.txt -DCMAKE_PREFIX_PATH=$PATH_TO_QT
cmake --build .
```
*Note that `qtpaths6 --qt-version` will not always exist on your device, especially if you installed Qt library along with Qt Creator through wizard, you might be forced to look for the files manually*

#### Application overview
