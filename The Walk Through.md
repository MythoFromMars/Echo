## ECHO

*(I tried to fully comment at my code so if you're interested on how I chose to do something it will be explained somewhere in the code)*



#### What is Echo?



This is an ASCII Dungeon but everything is invisible!



To reveal your surroundings echolocate.

The Echolocation moves on its own so don't feel like you have to stand still while echolocating

BEWARE There are enemies that move towards sounds they hear.



Navigate the dungeon, find the sword, and strike back against your tormentor



#### Controls:

* WASD to Move
* ARROW KEYS to Echolocate revealing anything in the direction of your echolocation
* X to open Key Code and Inventory
* C to open Map
* V to open a more detailed hint menu
* E to attack once you've unlocked the sword



#### Walkthrough



Important things to remember:

* Scan walls and doors as you go
* Try to memorize enemies starting locations (They get reset when you die so you'll always know where they start)
* If you get stuck die and reset
* The Key Code, Map, and Hint Menus are there to help if you get stuck read the hints



Room 1 (The Glade):

* There is a door in the top left and bottom right corner
* Proceed up through the door in the top left corner



Room 2 (The Library:

* This is the first room with enemies. They are near the top left and right corners respectively
* Hug the bottom wall and head right until you reach the wall
* Head up the wall until you reach what appears to be the corner of a room
* There is a gap up and to the left head through it then immediately head back right through the door to room 3



Room 3 (The Market):

* This room is T shaped with a locked door directly ahead and two branching pathes heading up and down
* Enemies block doors at either entrance
* One enemy blocks the north entrance
* Two block the south entrance
* Head to the far wall and hug the wall heading north
* Once you reach the top right corner echolocate to your left to attract the enemy to the corner then head down and around and up through the door to Room 4



Room 4 (Clockmaker's Shop) and Room 3 (Again):

* Collect the key piece in this room
* There are no enemies to worry about
* Head back down to Room 3 and as soon as enter the room echolocate directly down to lure the bottom enemy up
* quickly head down and then right to the locked door and wait until the enemy has passed (You won't be able to see it so just spam the space bar a couple times
* Then head down to the bottom left corner and into room 5



Room 5 (Candlemaker's Shop) and Room 3 (Again):

* Collect the key piece in this room
* There are no enemies to worry about
* Head out and up to and through the locked door
* Don't worry about dying (you don't lose your keys so just retrace your steps)



Room 6 (Sword Room)

* Collect the sword
* You can now kill the enemies by pressing E to attack in the direction you're facing
* Echolocating changes the direction you're facing
* Head back to Room 1 and down through the bottom Exit



Room 7 (The Parapet)

* There's a ghost in this room so don't echolocate
* Walk down two spaces and then attack to kill the enemy below you
* Walk right two spaces then attack to kill the ghost
* Head through the right door



Room 8 (The Castle)

* This room is tricky
* There's two ghosts and 3 enemies
* Once you enter the room echolocate then follow your echolocation until it reveals an enemy
* Kill that enemy
* You've lured the ghosts to the entrance of the room so you don't have to worry about them any more
* Head up and take the first left
* Echolocate until you hit and enemy and kill it
* Head up and take the first left and walk eft until you hit a wall then head up and collect the lever to unlock the door
* There's an door to Room 2 at the top of the room right next to the lever



Room 2 (Again)

* Navigate to the top left corner of the room killing and avoiding enemies
* There's a new door along the left wall that takes you to room 9



Room 9 (The Climb)

* There's nothing in this room other than the entrance to room 10



Room 10 (The Mountain Top)

* This is the final boss fight
* The boss has 6 health and 6 weak points that shoot lightning in a straight line
* Avoid the lightning and kill the weak points
* Destroy all the weak points and YOU WIN!!!



##### Lose State:



* I wasn't able to account for everything or perfectly bug test so there are some glitches
* You lose if the game crashes or get soft locked and things most often break when you die, so don't die too much otherwise it might crash



### Unique Features



##### Echolocation

* Everything in the game (With a few exceptions) is printed in black. When the player echolocates they add the coordinates of echolocation to a scanned list.
* When the game prints the screen it compares each coordinate to scanned list and if the coordinates match the character is printed as the appropriate color if not it's printed as black.
* This allows the player to interact with the game without being able to see anything. It can actually be beaten without scanning a single wall (You do need to scan enemies twice)



##### Enemies

* The Enemies add and remove themselves from the scanned list when their target location is changed (By default it's the location they're at)
* This allows them to be briefly visible but disappear as they move towards the player
* The Enemies have a fading number so they stay visible for 2 actions before they disappear. This is so the player can get a sense on the direction they move

###### Normal Enemy

* The normal enemy moves when hit by the echolocation and moves to the position the player was at when they echolocated. This allows the player to "kite" the enemies. Manipulating their position to move around them.

###### Ghost/Lost Soul

* The ghost moves when ever the player echolocates and doesn't immediately hit something (The echo symbol must spawn in)
* The ghost can hear and move through walls and moves to where the player was when they echolocated.
* The ghosts are much more difficult to kite because their movement is not as limited as the players, but they can be manipulated just the same
* The ghosts also replace whatever they move through after they move through it. This allows them to move through walls without completely destroying the level

###### 

##### Sword

* Once the player picks up the sword they can attack in the last direction facing with the sword.
* Moving and echolocating change direction facing to the direction pressed.
* The sword also overrides any character so you'll see it even if you stab a wall, but it immediately replaces it before the player can input again so you can't glitch through the wall
* If the sword hits an enemy it turns red to signify you killed it



##### Auto Pick Up

* There are 3 unique items with unique logic for each and are all deleted permanently when the you walk into them and display some text updating the player on what changed
* The Key adds to your key number (2 make a key)
* The sword unlocks the attack ability
* The switch adds two new exits to room 2



##### Unique Colors

* For visual clarity and to keep everything hidden everything has unique colors
* The Player is light blue, The Echo is Purple, the Walls are white, Any not scanned objects and the floor are black, etc.
