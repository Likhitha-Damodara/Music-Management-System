#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100   // Maximum number of songs

struct Song {
    int id;
    char name[50];
    char artist[50];
    char album[50];
    float duration;
};

struct Song songs[MAX];
int count = 0;

// Function declarations
void addSong();
void displaySongs();
void searchSong();
void deleteSong();
void saveToFile();
void loadFromFile();
void playSong();

int main() {
    int choice;
    loadFromFile(); // Load songs at start

    do {
        printf("\n===== MUSIC SYSTEM =====\n");
        printf("1. Add Song\n");
        printf("2. Display Songs\n");
        printf("3. Search Song\n");
        printf("4. Delete Song\n");
        printf("5. Play Song (simulation)\n");
        printf("6. Save to File\n");
        printf("7. Exit\n");
        printf("========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addSong(); break;
            case 2: displaySongs(); break;
            case 3: searchSong(); break;
            case 4: deleteSong(); break;
            case 5: playSong(); break;
            case 6: saveToFile(); break;
            case 7: saveToFile(); printf("Exiting... Thank you!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function to add a song
void addSong() {
    if (count >= MAX) {
        printf("Library full!\n");
        return;
    }

    struct Song s;
    s.id = count + 1;

    printf("Enter song name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter artist name: ");
    fgets(s.artist, 50, stdin);
    s.artist[strcspn(s.artist, "\n")] = '\0';

    printf("Enter album name: ");
    fgets(s.album, 50, stdin);
    s.album[strcspn(s.album, "\n")] = '\0';

    printf("Enter duration (in minutes): ");
    scanf("%f", &s.duration);
    getchar();

    songs[count++] = s;
    printf("Song added successfully....!!!!\n");
}

// Function to display all songs
void displaySongs() {
    if (count == 0) {
        printf("No songs in library.\n");
        return;
    }

    printf("\n---- SONG LIST ----\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | %s - %s | Album: %s | Duration: %.2f mins\n",
               songs[i].id, songs[i].name, songs[i].artist, songs[i].album, songs[i].duration);
    }
}

// Function to search a song by name
void searchSong() {
    char name[50];
    printf("Enter song name to search: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(songs[i].name, name) == 0) {
            printf(" Song Found.....!!!!!\n");
            printf("ID: %d | %s - %s | Album: %s | Duration: %.2f mins\n",
                   songs[i].id, songs[i].name, songs[i].artist, songs[i].album, songs[i].duration);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Song not found....!!!!\n");
}

// Function to delete a song
void deleteSong() {
    int id;
    printf("Enter Song ID to delete: ");
    scanf("%d", &id);
    getchar();

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (songs[i].id == id) {
            found = 1;
            for (int j = i; j < count - 1; j++) {
                songs[j] = songs[j + 1];
                songs[j].id = j + 1;
            }
            count--;
            printf("Song deleted successfully....!!!!\n");
            break;
        }
    }

    if (!found)
        printf("Song not found.....!!!!\n");
}

// Function to simulate playing a song
void playSong() {
    int id;
    printf("Enter Song ID to play: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (songs[i].id == id) {
            printf("Now Playing: %s - %s\n", songs[i].name, songs[i].artist);
            for (int j = 0; j < 10; j++) {
                printf("#...#...#...#...#...#...#...#");
                fflush(stdout);
                for (long long int k = 0; k < 100000000; k++); // Delay
            }
            printf("\nFinished playing......!!!!\n");
            return;
        }
    }
    printf("Song not found...!!!!\n");
}

// Function to save songs to file
void saveToFile() {
    FILE *fp = fopen("songs.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%.2f\n", songs[i].id, songs[i].name,
                songs[i].artist, songs[i].album, songs[i].duration);
    }
    fclose(fp);
    printf("Songs saved successfully.....!!!!!!!\n");
}

// Function to load songs from file
void loadFromFile() {
    FILE *fp = fopen("songs.txt", "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%d,%49[^,],%49[^,],%49[^,],%f\n",
                  &songs[count].id, songs[count].name,
                  songs[count].artist, songs[count].album,
                  &songs[count].duration) == 5) {
        count++;
    }
    fclose(fp);
}