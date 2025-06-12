# FaceitAnalyserApp

## Overwiev

FaceitAnalyserApp is a GUI application designed to fetch and display player statistics on Faceit. 
- [Faceit](www.faceit.com) is an esports platform used as an alternative to official in-game matchmaking. It's most popular in CS2.
- With this application user can analyse player's statistics in CS2 matches played on Faceit.

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

## Next

