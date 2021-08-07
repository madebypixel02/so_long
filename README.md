# so_long
*And thanks for all the fish!*

### Table of Contents

* [Introduction](#introduction)
* [How it Works](#how-it-works)
* [Bonus](#bonus)
* [Gameplay](#gameplay)
* [Other Maps](#other-maps)
* [Installation](#installation)
* [Technical Issues](#technical-issues)
* [Summary](#summary)

## Introduction
In this project, we'll code a simple 2D game to get familiar with interfaces. In my case, it will be Pacman.

### Game Rules
The game we choose must follow a set of rules. The executable ``so_long`` will receive a map as the only argument, and this map will have a .ber filetype.

The ber file also must follow the following rules:
- Only *1* (wall), *0* (empty), *P* (player), *C* (collectible), and *E* (exit) will be accepted characters in our map (except if you add enemies as bonus)
- The map must be rectangular, i.e. all rows must have the same length
- There must be at least one exit, one player, and one collectible on the map
- The map must be closed, i.e. surrounded by walls

If any of these checks fail, the game must end with a custom message.

The goal is for the player(s) to collect all the collectibles on the map before going to an exit

## How it Works
For the graphics part of the project we used a library called ``minilibx``. It's fairly basic and somewhat limited, but was still fun to use in the project



* Part one: reading the map

In this part of the code I checked that the given map was properly opened, that it had a ``.ber`` filetype, and then continued by reading the file one line at a time with ``get_next_line``.
Once that was done I filled a struct ``t_lay`` with some basic map attributes like number of players, exits, collectibles, number of rows and columns, etc. During the reading process I also created a string containin the entire map, whcih was then very useful to create a matrix with ``ft_split`` with ``\n`` as the separator.



* Part 2: starting the game

For this part I took the ``t_lay`` and my map matrix to build my main ``t_game`` struct. This struct includes more detailed information about my game state, such a list of pacmans, a list of ghosts, the number of loop repetitions (frames), and other info. From here I initialized a window with the mlx function and started drawing the static elements of the map (walls, spaces and collectibles) on the window. The mlx library, as other graphic libraries, has an infinite loop where the game events happen. Frem here I check the state of the game to re-print certain elements of the map or to manage special events, such as when pacman dies or when ghosts are in panic mode.
The mlx library has hooks, which essentially link certain events on the computer (keypress, mouse clicks, etc) with functions we implement. In my case I 'hooked' the end of the game function to pressing the ``x`` button to close a window. Also, I used a key hook to link keypresses with pacman's movements.


* Part 3: game mechanics

When esc/Q is pressed, the game ends. When R is pressed, the map resets to the initial state. If the arrow keys or the WASD keys are pressed, every pacman on the map changes its directions and tries to move in that direction. Also, every fraction of a second the pacmans will all try to keep movin in the same direction they're moving, to make the keys just change pacman's directions and they will move forward till they hit a wall.
Ghosts behave similarly, but instead of responding the keypress, they use a basic algorithm to find the closest pacman and try to catch it. Whenever either pacman is caught by a ghost, the attribute ``pac_dying`` is set to 1 in the ``t_game`` struct and all pacmans will die with a short animation.
Ghosts load in seven different colors, and each new ghost will have a different color. To do this, I had to load every sprite of every color with the mlx library and assign a new color to every new ghost with ``ghost_number % number_of_colors``.


* Part 4: animations

There are two animations in the game, as well as the small direction changes in pacman and ghosts. The harder to make was the dying one. It is an animation of over ten sprites and had to be perfectly timed. I ended up making a linked list with every sprite of the animation as content. When pacman is dying, a function is called to animate every pacman to the next sprite, and the next one is ready for the next iteration. I had to keep a copy of the animation to free those sprites afterwards.
The second animation is for the ghosts' panic mode. Whenever there are less than 1/3 of the pacdots (collectibles) remaining, the game speed increases slightly and ghosts change their look to the panic mode flashes. The animation consists of two sprites, which was much easier to implement.
