# ?
`Gartic` is a team project currently in development for the MC++ 2023-2024 (**M**odern **C++**) course held at Transilvania University of Brasov's [Faculty of Mathematics and Computer Science](https://mateinfo.unitbv.ro) (study programme: Computer Science).

# Team members
- Teglas Dennis-Vlăduț • [github](https://github.com/tdenniss) • [dennis.teglas@student.unitbv.ro](mailto:dennis.teglas@student.unitbv.ro)
- Stoica David-Ioan • [github](https://github.com/stoica-david) • [david.stoica@student.unitbv.ro](mailto:david.stoica@student.unitbv.ro)
- Tufeanu Andrei-Ionuț • [github](https://github.com/andreitufeanu) • [andrei.tufeanu@student.unitbv.ro](mailto:andrei.tufeanu@student.unitbv.ro)
- Sas Vlad-Ștefan • [github](https://github.com/vlsts) • [vlad.sas@student.unitbv.ro](mailto:vlad.sas@student.unitbv.ro) • [pgp key](https://keys.openpgp.org/search?q=F8D3E2ADBA5E662AB903A09B1E36736E712E97C7) (commits signed with this key)

# Project info
- Duration: 10 weeks, 23rd of October -> 14th of January
- Project coordinator: Popa Iulian
- Points:
    - Base requirements: max. 8 pts
    - Advanced requirements: max. 2 pts
    - Custom element: max. 1 pt
- Demo Video explaining code segments + showcasing app functionality required (deadline: 14th of January)
- Allowed libraries / frameworks
    - [SDL](https://www.libsdl.org/)
    - [SFML](https://www.sfml-dev.org/)
    - [Qt](https://qt.io)
    - [nlohmann/json](https://github.com/nlohmann/json)
    - [fnc12/sqlite_orm](https://github.com/fnc12/sqlite_orm)
    - others, if the project coordinator allows using them

# Base requirements (max. 8 pts)
- 🕥 Networking: respect client-server architecture (at least 2 client instances + 1 server)
- 🕥 Login / Register page
- 🕥 Game Page: console app that substitutes drawing the word with describing it while not using words in the lexical family of said word
- 🕥 Use at least 500 words, each match will have unique and random words
- 🕥 Database: must use SQLite through [fnc12/sqlite_orm](https://github.com/fnc12/sqlite_orm)

# Advanced components (max. 2 pts)
- 🕥 Meeting room: player uses a code to join other players
- 🕥 Profile page: the profile page contains a game history (scores for each game and average of said scores)
- 🕥 GUI: drawing version of the game using Qt

# Custom element ideas (max. 1 pt)
- 🕥 Difficulty setting: Easy/Medium/Hard; this should affect the number of hints and the dynamics of the game
- 🕥 Buying clues using points obtained during the game, the cost of each being stored in the database with the cost being related to each word
- 🕥 Handling more than 2 games at once on the server
- 🕥 Handling exceptions and implementing unit tests (coverage 50%)

# UML Diagram
![UML Diagram](uml.jpg)