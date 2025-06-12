# FaceitAnalyserApp
---
### Overwiev
---
FaceitAnalyserApp is a GUI application designed to fetch and display player statistics on Faceit. 
- [Faceit](www.faceit.com) is an esports platform used as an alternative to official in-game matchmaking. It's most popular in CS2.
- With this application user can analyse player's statistics in CS2 matches played on Faceit.
---
### Features
---
- Player __lifetime__ stats, including:
    - `KDR` - kill per death ratio
    - `ADR` - avarage damage per round
    - `HLTV 1.0` - rating used by [hltv.org](www.hltv.org) page to assess profesional player's performance (more info of how its calculated later on)
- Player avarage stats __50 matches back__, containing same data as lifetime
- Player's statistic for given __match__, including:
    - `Map` played in given match
    - `Score` (always in format: `YOUR / ENEMY`)
    - `K/A/D` - kills / assists / deaths
    - `HLTV` - hltv rating for single match
