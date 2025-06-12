# FaceitAnalyserApp

## Overview

FaceitAnalyserApp is a C++/Qt6 **GUI application**. It fetches and displays player statistics from [Faceit](www.faceit.com), an esports platform popular in CS2 as an alternative to official in-game matchmaking.
- Users can analyse player's CS2 statistics.
- Requires a `nickname` and optionally `match id` or `matchroom link` to generate output.
- Not that since the application fetches CS2 data only, any Faceit account with no CS2 matches will be treated as invalid input - there is no data to analyse.

## Features

- Player's __lifetime__ stats and data:
    - `avatar` - Player's Faceit profile picture.
    - `elo` - player's Faceit rating. Based on [elo system](https://en.wikipedia.org/wiki/Elo_rating_system).
    - `level` - Skill level (1-10) determined by `elo`.
    - `level progress bar` - Progress towards the next level.
    - `KDR` - Kill per death ratio.
    - `ADR` - Average damage per round
    - `HLTV 1.0` - Performance rating used by [hltv.org](www.hltv.org) to assess profesional player's performance. *(Calculation details explained later)*.
- Player's data and avarage stats __50 matches back__, containing same data as lifetime
- Single __match__ statistics:
    - `Map` played in given match.
    - `Score` (always in format: `YOUR_TEAM / ENEMY_TEAM`).
    - `K/A/D` - kills / assists / deaths.
    - `HLTV` - hltv rating for the match.

## Usage

### API FACEIT KEY
- ToDo

### Compilation (using [CMake](https://cmake.org/documentation/))
- Install [Qt library](https://doc.qt.io/qt-6/get-and-install-qt.html) on your device.
- The easiest way is to use `Qt Creator` - an IDE providing easy and intuitive access to Qt library. 
*(File -> Open Project -> FaceitAnalyserApp -> CMakeLists.txt)*.
- Compilation through terminal:
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

### Detailed application overview
- Default page contains input panel (put your nickname there) and last 50 checkbox - meaning statistics for last 50 matches only. Request is generated every time you push OK button, press `Return` on your keyboard or change checkbox state.