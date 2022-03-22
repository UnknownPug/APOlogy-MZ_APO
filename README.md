# This game was created as a semester project of the APO 

### (CTU - OI summer semester 2021)

##### Authors: Ivan Teslenko, Dmitry Rastvorov
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- - 
## Watch the video here:
[![Watch the video](https://img.youtube.com/vi/CkSvRmklnfM/maxresdefault.jpg)](https://youtu.be/CkSvRmklnfM)


## <ins>Installing and running the game (Linux/MacOS):</ins>

   1) Install the game (code) by following the [link](https://gitlab.fel.cvut.cz/rastvdmy/apology)

   
   2) Connect `MZ_APO` to your internet network


   3) Create a new Terminal in the project folder on your PC or use: `cd path/to/the/project`

   
   4) Open the _run.sh file_ in the text editor and fill in the MZ_APO IP address and the required paths:
      
   - `path/to/the/local/project/*` is a path to your local project files on your PC.
   
   - `path/to/MZ_APO/folder/` is a path to MZ_APO folder the project files will be sent to.


   5) Type the following command: `./run.sh`


   6) The script will generate a new SSH key, the game files will be sent to MZ_APO and compiled.
      
      After that, the program will automatically run.


## <ins>Game description:</ins>

   Snake is a game where you have to collect bananas to grow longer.

   The opponent is an artificial intelligence, whose task is to effectively collect bananas and hinder the player. With each banana eaten, the size of our snake, as well as the size of the enemy snake, increases, which subsequently complicates the game. 


## <ins>Main menu:</ins>

   The player is prompted to choose a difficulty level: 

   - <ins>_KIDDO_</ins>

   - <ins>_MASTER_</ins>

   - <ins>_SNAKE GOD_</ins>

   
   Increasing the difficulty level increases the speed of the game.
   
   The main menu also features an EXIT button for complete game exit.


#### <ins>Controls:</ins>

 - **Blue button** - move up 

 - **Red button** - move down

 - **Green button** - select an option (game mode/exit).


#### <ins>Peripherals:</ins>

- **Red button pressed** - left RGB LED flashes red

- **Blue button pressed** - right RGB LED flashes blue

- **Green button pressed** - LED line flashes with all LEDs


## <ins>Game:</ins>

   Both snakes start the game from the up position. Depending on the chosen difficulty, the snakes move around the field at each time interval. Eating the fruit increases the snake's points as well as its length by 1 unit. Eaten fruit is recovered at an random unoccupied point on the field.
   
   Both players' points are displayed on the top panel. If the AI is ahead of the player, a warning message is displayed.


#### <ins>Defeat conditions:</ins>

- The AI has gained 32 points before you.

- Collision with AI, boundaries of the field or yourself.

**When defeated,**
the <ins>"YOU LOSE"</ins> screen is displayed with the number of points gained by each player, pending exit to the main menu.


#### <ins>Victory conditions:</ins>

- The player has gained 32 points before the AI.

**When the player wins,**
the <ins>"YOU WIN"</ins> screen is displayed with the number of points scored by each player, pending exit to the main menu.


#### <ins>Controls:</ins>

- **Blue button** - turns the player snake clockwise.

- **Red button** - turns the player snake counterclockwise.

- **Green button** - pause, the game can be continued or exit to the main menu.


#### <ins>Controls (pause):</ins>

- **Blue button** - move to the right

- **Red button** - move to the left

- **Green button** - select an option


#### <ins>Peripherals:</ins>

- The player's score is displayed on the LED line

- During the game the RGB LEDs flash yellow one by one

- Loss - both RGB LEDs light up red

- Win - both RGB LEDs light up green


## <ins>Technical documentation:</ins>

- <ins>Images.c</ins> and <ins>images.h</ins> are used to connect pictures. 

- To connect the colours is used file <ins>colors.h</ins>

- To compile the project a <ins>makefile</ins> file is used.

- File <ins>run.sh</ins> is used to run the game.

- For file interactions see the diagram **below**:


##### Have fun! :yum: 
