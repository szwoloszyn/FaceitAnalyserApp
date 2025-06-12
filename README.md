# FaceitAnalyserApp

## Overview

FaceitAnalyserApp is a C++/Qt6 **GUI application**. It fetches and displays player statistics from [Faceit](www.faceit.com), an esports platform popular in CS2 as an alternative to official in-game matchmaking. It uses faceit api key that can be obtained by anyone with no limits *(Generating own api key explained later on)*
- Users can analyse player's CS2 statistics.
- Requires a `nickname` and optionally `match id` or `matchroom link` to generate output.
- Not that since the application retrieved CS2 data only, any Faceit account with no CS2 matches will be treated as invalid input - there is no data to analyse.

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
- In order to use the app you need to generate your own Faceit Data Api Key. 
Faceit for developers is avaible at https://developers.faceit.com/.
- Application expects to found `.faceit_api_key.txt` in `$HOME` directory.
- It can be easily changed in `main.cpp` file - `QString PATH_TO_KEY` variable

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
##### 1. GUI 
- Default (Player) page contains **input panel** (put your nickname there) and **last 50 checkbox** (statistics for last 50 matches only). Api request is generated every time you push OK button, press `Return` on your keyboard or change checkbox state.
- Match page contains **input panel** (put matchroom link there). Generated output will display match details and statistics for the given player. Note that match page operates on data retrieved from player page, so you need to define the player first, and then provide matchroom in which he played.
- You can switch between the pages from menu bar in `View` tab.

##### 2. DATA AND CALCULATIONS
- While hltv.org service now uses HLTV 2.0 rating (which better reflects player impact) this application calculates the `HLTV 1.0` rating instead, as the formula for the newer version isn't publicly available. The calculation follows these rules:
```
HLTV 1.0 = (KillRating + 0.7*SurvivalRating + RoundsWithMultipleKillsRating) / 2.7

KillRating = (Kills/Rounds)/AverageKPR
SurvivalRating = ((Rounds-Deaths)/Rounds)/AverageSPR
RoundsWithMultipleKillsRating = ((1K + 4*2K + 9*3K + 16*4K + 25*5K)/Rounds)/AverageRMK

AverageKPR = 0.679 (average kills per round)
AverageSPR = 0.317 (average survived rounds per round)
AverageRMK = 1.277 (average value calculated from rounds with multiple kills: (1K + 4*2K + 9*3K + 16*4K + 25*5K)/Rounds)

1K = Number of rounds with single kill
2K = Number of rounds with double kill
3K = Number of rounds with triple kill
4K = Number of rounds with quadro kill
5K = Number of rounds with penta kill (an ace)
```
- an avarageX values are constants that were specifically chosen 
so that avarage rating among player would be equal to 1.0