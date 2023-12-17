#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int id;
    char *name;
    char *description;
    int south, north, east, west;
    int object;
    bool starting;
} Room;

typedef struct 
{
    int id;
    char *name;
    char *description;
} Object;

Room *rooms;
Object *objects;
char *inventory;
int check;
int dropChecker;

int extractInt(char * line)
    {
        char *copy = strdup(line);
        char * token = NULL;
        token = strtok(copy, ":");
        token = strtok(NULL, ":");

        token[strlen(token)-1] = 0;
        int extractedInt = 0;
        sscanf(token, "%d", &extractedInt);
        free(copy);
        return extractedInt;
    }

char * extractString(char * line)
    {
        char *copy = strdup(line);
        char *token = NULL;
        token = strtok(copy, ":");
        token = strtok(NULL, ":");

        token[strlen(token)-1] = 0;
        token++;
        token++;
        token[strlen(token)-1] = 0;

        char *output = strdup(token);
        free(copy);
        return output;
    }

bool loadData()
{
    FILE *file = fopen("world.json", "r");

    if(!file)
    {
        printf("Failed to open file\n");
        return false;
    }

    char *line = NULL;
    size_t read;
    size_t len;

    inventory = NULL;
    inventory = malloc(1000);  
    inventory[0] = '\0';
    check = 0;
    dropChecker = 0;

    while ((read = getline(&line, &len, file)) != -1)
    {
        if(line[read - 1] == '\n')
        {
            line[read - 1] = 0;
            read --;
        }

        Room r;


        if(strstr(line, "\"id\""))
        {
            r.name = NULL;
            r.description = NULL;
            r.north = -1;
            r.south = -1;
            r.east = -1;
            r.west = -1;
            r.object = -1;
            r.id = extractInt(line);
            r.starting = NULL;
        }
        if(strstr(line, "\"name\""))
        {
            r.name = extractString(line);
        }
        if(strstr(line, "\"description\""))
        {
            r.description = extractString(line);
        }
        if(strstr(line, "\"south\""))
        {
            r.south = extractInt(line);
        }
        if(strstr(line, "\"north\""))
        {
            r.north = extractInt(line);
        }
        if(strstr(line, "\"east\""))
        {
            r.east = extractInt(line);
        }
        if(strstr(line, "\"west\""))
        {
            r.west = extractInt(line);
        }
        if(strstr(line, "\"object\""))
        {
            r.object = extractInt(line);
        }
        if(strstr(line, "\"starting\""))
        {
           if(r.id == 1)
           {
               r.starting = true;
           }
           else
           {
                r.starting = false;
           }
           //r.inventory = malloc(1000);  
            //r.inventory[0] = '\0';
        }
        

        if(strstr(line, "}"))
        {
            rooms[r.id] = r;
            //printf("%s\n", rooms[r.id].name);
            //printf("%s\n", rooms[r.id].description);
        }

        if(strstr(line, "\"objects\""))
        {
            break;
        }

        //printf("%s\n", line);
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        if(line[read - 1] == '\n')
        {
            line[read - 1] = 0;
            read --;
        }

        Object obj;

        if(strstr(line, "]"))
        {
            break;
        }


        if(strstr(line, "\"id\""))
        {
            obj.id = extractInt(line);
        }
        if(strstr(line, "\"name\""))
        {
            obj.name = extractString(line);
        }
        if(strstr(line, "\"description\""))
        {
            obj.description = extractString(line);
        }
        

        if(strstr(line, "}"))
        {
            objects[obj.id] = obj;
            //printf("%s\n", objects[obj.id].name);
        }


        //printf("%s\n", line);
    }

    return true;
    
}



void showRoom(int current)
{
    printf("#%d %s %s\n",current, rooms[current].name, rooms[current].description );
    printf("\n");

    
    if(check == 0)
    {
    for (int i = 0; i < 1000; i++)
    {
        if (objects[i].id != -1 && objects[i].id == rooms[current].object)
        {
            printf("You see a %s\n", objects[i].name);
            check = 5;
        }
        
    
    }
    printf("\n");
    }

    if(dropChecker ==1)
    {
    for (int i = 0; i < 1000; i++)
    {
        if (objects[i].id != -1 && objects[i].id == rooms[current].object)
        {
            printf("You see a %s\n", objects[i].name);
            check = 5;
            dropChecker = 0;
        }
        
    
    }
    printf("\n");
    }
    

    printf("[");
    if (rooms[current].north != 0)
    {
        printf(" [n]orth,");
    }
    if (rooms[current].south != 0)
    {
        
        printf(" [s]outh,");
    }
    if (rooms[current].east != 0)
    {
        printf(" [e]ast,");
    }
    if (rooms[current].west != 0)
    {
        printf(" [w]est,");
    }
    printf("  [l]ook, [g]et, [i]nventory, [d]rop, [q]uit ]\n");
    return;
}

void addToInventory(int idNum, char *idName, char *inventory)
{
    char itemInput[100];
    sprintf(itemInput, "+ [%d] %s\n", idNum, idName);
    strcat(inventory, itemInput);
}

void showInventory(char *inventory)
{
    if (inventory[0] == '\0') 
    {
        printf("You currently have nothing in your backpack.\n");
    } 
    else 
    {
        printf("Your backpack of infinite holding contains:\n%s", inventory);
        printf("\n");
    }
}

void removeFromInventory(int idNum, char *inventory)
{
    char itemToRemove[100];
    sprintf(itemToRemove, "+ [%d]", idNum);

    char *position = strstr(inventory, itemToRemove);

    if (position != NULL) {
        char *endOfLine = strchr(position, '\n');

        if (endOfLine != NULL) {
            size_t lengthToRemove = endOfLine - position + 1;
            size_t lengthAfterRemove = strlen(position + lengthToRemove);

            
            memcpy(position, position + lengthToRemove, lengthAfterRemove + 1);
        }
    }


}

void gameLoop()
{
    char input[100];
    int currentRoom;
    currentRoom = -1;

    for (int i = 0; i < 1000; i++)
    {
        if(rooms[i].starting)
        {
            currentRoom = i;
            break;
        }
    }
    //printf("curr=%d\n", currentRoom);

    while(true)
    {
        showRoom(currentRoom);
        printf("> ");
        
        fgets(input, sizeof(input), stdin);
        if(input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = 0;
        }

        if(strcmp(input,"quit") == 0 || strcmp(input, "q") == 0)
        {
            printf("Thanks for playing!!!\n");
            break;
        }

        if(strcmp(input,"north") == 0 || strcmp(input, "n") == 0)
        {
            
            if(rooms[currentRoom].north != -1)
            {
            currentRoom = rooms[currentRoom].north;
            }
            continue;
        }

        if(strcmp(input,"south") == 0 || strcmp(input, "s") == 0)
        {   
            
            if(rooms[currentRoom].south != 0)
            {
            currentRoom = rooms[currentRoom].south;
            }
            continue;
        }

        if(strcmp(input,"west") == 0 || strcmp(input, "w") == 0)
        {
            
            if(rooms[currentRoom].west != -1)
            {
            currentRoom = rooms[currentRoom].west;
            }
            continue;
        }

        if(strcmp(input,"east") == 0 || strcmp(input, "e") == 0)
        {
            
            if(rooms[currentRoom].east != -1)
            {
            currentRoom = rooms[currentRoom].east;
            }
            continue;
        }

        if(strcmp(input,"look") == 0 || strcmp(input, "l") == 0)
        {
            
            if (objects[rooms[currentRoom].object].description != NULL)
            {
            printf("%s\n", objects[rooms[currentRoom].object].description);
            }
            continue;
        }

        if (strcmp(input, "inventory") == 0 || strcmp(input, "i") == 0)
        {
            showInventory(inventory);
            continue;
        }

        if (strcmp(input, "get") == 0 || strcmp(input, "g") == 0)
        {
            if(inventory[0] == '\0')
            {
                //printf("inven: %s", objects[rooms[currentRoom].object].name);
            if (objects[rooms[currentRoom].object].name != NULL)
            {
            addToInventory(objects[rooms[currentRoom].object].id, objects[rooms[currentRoom].object].name, inventory);
            printf("You picked up a %s and put it into your backpack\n", objects[rooms[currentRoom].object].name);
            printf("\n");
            //showInventory(inventory);
            }
            continue;
            }
            else
            {
            printf("\n");
            if (objects[rooms[currentRoom].object].name != NULL)
            {
            addToInventory(objects[rooms[currentRoom].object].id, objects[rooms[currentRoom].object].name, inventory);
            printf("You picked up a %s and put it into your backpack\n", objects[rooms[currentRoom].object].name);
            printf("\n");
            //showInventory(inventory);
            }
            continue;
            }
        }

        if (strcmp(input, "drop") == 0 || strcmp(input, "d") == 0)
        {
           if (objects[rooms[currentRoom].object].name != NULL)
            {
                if (inventory[0] == '\0') 
                {
                    printf("You currently have nothing in your backpack.\n");
                } 
                else
                {
                char idInput[100];
                int idToRemove;
                printf("Enter in the id number of the item\n");
                printf("> ");
                showInventory(inventory);
                fgets(idInput, sizeof(idInput), stdin);
                if(idInput[strlen(idInput) - 1] == '\n')
                {
                    idInput[strlen(idInput) - 1] = 0;
                }
                sscanf(idInput, "%d", &idToRemove);
                char droppedItemName[100];
                for (int i = 0; i < 1000; i++)
                {
                    if (objects[i].id != -1 && objects[i].id == idToRemove)
                    {
                        strcpy(droppedItemName, objects[i].name);
                        break;
                    }
                }
                removeFromInventory(idToRemove, inventory);
                showInventory(inventory);
                for (int i = 0; i < 1000; i++)
                {
                    if (objects[i].name != NULL && strcmp(objects[i].name, droppedItemName) == 0)
                    {
                        rooms[currentRoom].object = objects[i].id;
                        break;
                    }
                }
                dropChecker = 1;
                }
                }
                continue;
        }

        


    }
}

int main()
{

    rooms = malloc(sizeof(Room)*1000);
    objects = malloc(sizeof(Object)*1000);

    if(loadData())
    {
        //yes
    }
    else
    {
        //no
        return 99;
    }
    
    gameLoop();

    free(rooms);
    free(objects);
    return 0;
}
