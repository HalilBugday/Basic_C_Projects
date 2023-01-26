#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamic_array
{
    int capacity;
    int size;
    void** elements;
} dynamic_array;

void init_array(dynamic_array* array)
{
    array->size=0; //initial size.
    array->capacity=2; //initial capacity.
    array->elements=(void*)malloc(array->capacity * sizeof(void));
    int i;
    for (i=array->size;i<array->capacity; i++)
    {
        array->elements[i]=NULL; //put NULL.
    }
}
void put_element(dynamic_array* array, void* element) 
{
    if (array->size == array->capacity)
    {
       array->capacity = array->capacity*2;
        array->elements=realloc(array->elements,array->capacity* sizeof(array->elements)*array->capacity); 
    }
    array->elements[array->size]=element;
    array->size=array->size+1;
    printf("New song added to the array!\n");
    printf("Capacity of the array--> %d\n",array->capacity);
    printf("Size of the array--> %d\n",array->size);
    printf("\n");
}
void remove_element(dynamic_array* array, int position) 
{
    if (array->size == array->capacity/2)
    {
        array->capacity = array->capacity/2;
        array->elements=realloc(array->elements,array->capacity* sizeof(array->elements)*array->capacity);
    }
    int i;
    for (i=position; i<array->size-1; i++) 
    {
        array->elements[i] = array->elements[i+1];
    }
    array->elements[array->size-1] = NULL;
    array->size=array->size-1;
    printf("The song deleted from the array!\n");
    printf("Capacity of the array--> %d\n",array->capacity);
    printf("Size of the array--> %d\n",array->size);
    printf("\n");
}
void* get_element(dynamic_array* array, int position) 
{
    return array->elements[position];
}

typedef struct song {
    char* name;
    float duration;
} song;

int main()
{
    int input;
    dynamic_array songs;
    init_array(&songs);
    do 
    {
        printf("1.Add a song to the list.\n");
        printf("2.Delete a song from the list.\n");
        printf("3.Display all songs.\n");
        printf("4.Exit.\n");
        printf("Enter a valid number: ");
        scanf("%d", &input);
        
        switch(input) 
        {
            case 1:
            {
                song* addSong;
                addSong= (song*)malloc(sizeof(song));
                addSong->name = (char*)malloc(250 * sizeof(char));
                printf("Enter name of the song: ");
                scanf("%s",addSong->name);
                printf("Enter duration of the song: ");
                scanf("%f", &addSong->duration);
                put_element(&songs,addSong);
                break;
            }
            case 2: 
            {
                char* name;
                name= (char*)malloc(250 * sizeof(char));
                printf("Enter name of the song: ");
                scanf("%s",name);
                int j;
                for (j = 0; j<songs.size; j++) 
                {
                    song* mySong;
                    mySong= (song*)get_element(&songs,j);
                    if (strcmp(mySong->name,name)==0) 
                    {
                        remove_element(&songs,j);
                        free(mySong->name);
                        free(mySong);
                        break;
                    }
                }
            }
                break;
            case 3: 
                for (int j=0; j<songs.size; j++) 
                {
                    song* mySong;
                    mySong=(song*)get_element(&songs,j);
                    printf("Song name: %s",mySong->name);
                    printf("  <->  Duration: %f\n",mySong->duration);
                }
                printf("\n");
                break;
            case 4:
                printf("Program terminated!\n");
                break;
                exit(0);
            default:
                printf("You entered an invalid number!");
                break;
                exit(0);
        }
    } while(input>0&&input<4);
return 0;
}