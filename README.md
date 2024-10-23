<!-- @format -->

# Tic Tac Toe Game

<div align="center">
    <img src="project/res/img3.png" alt="Tic Tac Toe" width="200"/>
    <img src="project/res/img2.png" alt="Tic Tac Toe" width="200"/>
</div>

## Overview

This is a Tic Tac Toe game implemented in C++ using SDL 1.2 for graphics and CMake with Ninja as the build system. The game allows the player to compete against the computer on a 3x3 grid, aiming to align three of their marks (Kayori or Enemy) horizontally, vertically, or diagonally.

## Used tech

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![SDL1.2](https://img.shields.io/badge/SDL1.2-%2307405e.svg?style=for-the-badge&logo=sqlite&logoColor=white)

## Features

- player-computer gamePlay (Player X and Player O)
- User-friendly graphical interface powered by SDL
- Input validation to ensure valid moves
- Restart option to play multiple rounds

## Prerequisites

Before running the game, ensure you have the following installed:

- C compiler (e.g., gcc)
- CMake (version 3.0 or higher)
- Ninja build system
- SDL 1.2 library

## Project Structure

```bash
.tic-tac-toe
├── bin
│   ├── build
│   │   └── CMakeFiles
│   │       ├── 3.30.3
│   │       │   ├── CompilerIdC
│   │       │   │   └── tmp
│   │       │   └── CompilerIdCXX
│   │       │       └── tmp
│   │       ├── app.dir
│   │       └── pkgRedirects
│   ├── debug
│   ├── release
│   └── test
├── doc
│   └── pdf
├── pkg
└── project
    ├── doc
    ├── inc
    ├── models
    ├── res
    └── src

32 directories
```

## Installation

1. **Clone the repository:**

   ```bash
   git clone https://github.com/ZouariOmar/tic-tac-toe
   cd tic-tac-toe
   ```

2. **Run the game**

   ```bash
   chmod +x run.sh
   ./run.sh ninja
   ```

## Contributing

Contributions are welcome! If you have suggestions for improvements or features, feel free to fork the repository and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENCE) file for details.

## Acknowledgments

- SDL for the graphics library.
- Thanks to everyone who contributed to the development of this game!
