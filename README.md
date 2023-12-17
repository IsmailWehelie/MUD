# MUD
Develop a simple text-based Multi-User Dungeon (MUD) game in C where a player can navigate through rooms, examine and pickup objects, and view their inventory.

Specifications:
Data Format:

Use the given JSON-like data structure to load rooms and objects.

You cannot use any external JSON library to read in the file. You must read in and load the contents into your program. HINT: you do not need to support all JSON file formats, just the format used by the provided files. 

Two files are provided in the template miniworld.json and world.json. We suggest you start with the miniworld.json and then eventually move on to the world.json. All the tests will require that you load the world.json.

It is not expected that the JSON reading will be any more robust than necessary to read in the miniworld.json and world.json.

This is a simple version of the json that is found in miniworld.txt in the template.

{"rooms":

[

       {

           "id": 1,

           "name": "The Temple Of Mota",

           "description": "You are in the southern end of the temple hall in the Temple of Mota. The temple has been constructed from giant marble blocks, eternal in appearance, and most of the walls are covered by ancient wall paintings picturing gods, giants and peasants. Large steps lead down through the grand temple gate, descending the huge mound upon which the temple is built and ends on the temple square below. Equally large steps lead UP through a small door into the ENTRANCE to MUD SCHOOL.  (type 'up' to go to MUD SCHOOL.)  A small plaque is on this wall.",

           "south": null,

           "north": 4,

           "east": 3,

           "west": null,

           "object": 5,

           "starting": true

       },

    {

       "id": 3,

       "name": "Cleric's Bar",

       "description": "The bar is one of the finest in the land, lucky it is members only.  Fine furniture is set all around the room.  A small sign is hanging on the wall. ",

       "south": null,

       "north": null,

       "east": 1,

       "west": 1,

       "object": 22,

       "starting": false

   },

   {

       "id": 4,

       "name": "Entrance to Cleric's Guild",

       "description": "The entrance hall is a small modest room, reflecting the true nature of the Clerics.  The exit leads east to the temple square.  A small entrance to the bar is in the northern wall. ",

       "south": 1,

       "north": null,

       "east": null,

       "west": null,

       "object": 365,

       "starting": false

   }

],

"objects":

[

       {

       "id": 5,

       "name": "scimitar blade",

       "description": "Hassan's scimitar lies upon the ground, waiting for its owner."

   }, {

       "id": 22,

       "name": "sword long",

       "description": "A long sword has been left here."

   },

       {

       "id": 365,

       "name": "banner war merc",

       "description": "A war banner is on the floor here."

   }

]}



Data Design

The program must implement a Room structure that should mimic the json design of a room (e.g., id, name, description…). The structure can use typedef.

The program must implement an Object structure that mimics the json design of an object (e.g., id, name, description). The structure can use typedef.

The program must implement  a global pointer with the name rooms and the a global pointer with the named objects. 

struct Room *rooms;

struct Object *objects;

Data Loading:

The rooms and objects pointers must be allocated with sufficient room on the heap.

The room or object's id should be used as the index. 

Initialize the structure's such that you can identify rooms that have been loaded from the ones that are empty. 

Load the provided data into these structures.

The function that loads the data from a file must be called loadData 

Player Starting Point:

When the game starts, the character should be placed in the room where "starting": true.

Navigation:

Display the room name and description to the player.

Indicate possible directions to navigate by placing them in brackets (e.g., [n,e]). Only show directions that are valid (not null).

Use commands 'n', 's', 'e', 'w' (and north, south, east, west) for navigation. Up and Down are are not required.

Handle invalid commands gracefully with an appropriate message.

Object Interaction:

If there is an item in a room, display its name, like this 

printf(" \t You see a %s\n", XXXXX.name);

Allow the player to use the command 'look' to view an item's description.

Allow the player to pick up the object and put it into their inventory, it should no longer be displayed in the room but should be shown in their inventory

Inventory

Allow the player to view the items in their inventory by typing in `i` or `inventory` the inventory entry should show the item plus the item's id. It should look like this 

Your backpack of infinite holding contains:
+ [5] scimitar blade
+ [10] pit
+ [135] fountain water
+ [365] banner war merc
+ [22] sword long


A player can 'drop' an item to the ground in a new location if they choose. When they enter in `drop` the game should, show the inventory, and ask them to enter in the id number of the item.

Each room should only store the most recent item, thus, if an item is dropped in a room with an item stored in it the dropped item will remove it.

If nothing is in the inventory, it should say, "You currently have nothing in your backpack"

Program Flow:

Continuously prompt the player for a command.

Process the command and update the game state.

If the player types 'quit', terminate the game.

On each iteration of the Game Loop:

Display the current room's #id, name, description, and possible commands (a direction should only be shown if its available).

#1 : The Temple Of Mota
You are in the southern end of the temple hall in the Temple of Mota. The temple has been constructed from giant marble blocks, eternal in appearance, and most of the walls are covered by ancient wall paintings picturing gods, giants and peasants.    Large steps lead down through the grand temple gate, descending the huge mound upon which the temple is built and ends on the temple square below.    A small plaque is on this wall.
 You see a scimitar blade
[ [n]orth, [s]outh,  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]
>


Prompt the player for a command.

Handle navigation commands.

Handle 'look' command for object interaction.

Handle 'drop' command

Terminate on 'quit' command.

Main() testing requirements

In the main() function you must provide the following entry after the gameloop but before any free's 

// INSERT TEST HERE



Example

int main() {

    . . .

   

    gameLoop(rooms, objects, startingRoomId);



    // INSERT TEST HERE



    free(rooms);

    free(objects);



    return 0;

}



Test cases
Test cases that are similar to the ones used on the submission server have been included in /usercode/tests

To run test1.sh for example from the /usercode directory and then see the DEBUG output and RESULT output.

coder@/usercode$ bash tests/test1.sh ; cat DEBUG RESULT
/usercode/tests
Testing the standard input   s  s  s  e  e  s  s  s  quit   
        1. ✔ ️PASSED, found all expected output
Exiting tester.
p
Sample Session
#1 : The Temple Of Mota
You are in the southern end of the temple hall in the Temple of Mota. The temple has been constructed from giant marble blocks, eternal in appearance, and most of the walls are covered by ancient wall paintings picturing gods, giants and peasants.    Large steps lead down through the grand temple gate, descending the huge mound upon which the temple is built and ends on the temple square below.    Equally large steps lead UP through a small door into the ENTRANCE to MUD  SCHOOL.  (type 'up' to go to MUD SCHOOL.)  A small plaque is on this wall.
 You see a scimitar blade
[ [n]orth, [s]outh,  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]
> get
You picked up a scimitar blade and put it into your backpack

#1 : The Temple Of Mota
You are in the southern end of the temple hall in the Temple of Mota. The temple has been constructed from giant marble blocks, eternal in appearance, and most of the walls are covered by ancient wall paintings picturing gods, giants and peasants.    Large steps lead down through the grand temple gate, descending the huge mound upon which the temple is built and ends on the temple square below.    Equally large steps lead UP through a small door into the ENTRANCE to MUD  SCHOOL.  (type 'up' to go to MUD SCHOOL.)  A small plaque is on this wall.
[ [n]orth, [s]outh,  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]
> s

#5 : The Temple Square
You are standing on the temple square.  Huge marble steps lead up to the temple gate.  The entrance to the Clerics Guild is to the west, and the old Grunting Boar Inn, is to the east.  Just south of here you see the market square, the center of Midgaard.
 You see a fountain water
[ [n]orth, [s]outh, [e]ast, [w]est,  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]
> i
Your backpack of infinite holding contains:
+ [5] scimitar blade

#5 : The Temple Square
You are standing on the temple square.  Huge marble steps lead up to the temple gate.  The entrance to the Clerics Guild is to the west, and the old Grunting Boar Inn, is to the east.  Just south of here you see the market square, the center of Midgaard.
 You see a fountain water
[ [n]orth, [s]outh, [e]ast, [w]est,  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]
> w

#4 : Entrance to Cleric's Guild
The entrance hall is a small modest room, reflecting the true nature of the Clerics.  The exit leads east to the temple square.  A small entrance to the bar is in the northern wall.
 You see a banner war merc
[ [n]orth, [e]ast,  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]
> q
