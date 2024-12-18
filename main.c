#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Struktur untuk Tamu (Linked List)
typedef struct Guest {
    char name[50];
    char id[20];
    char phone[15];
    struct RoomNode *room;
    struct Guest *next;
} Guest;

// Struktur untuk Kamar (Tree)
typedef struct RoomNode {
    char roomType[30];
    char roomNumber[10];
    int isAvailable;
    struct RoomNode *left, *right;
} RoomNode;

// Struktur untuk Antrean Check-in (Queue)
typedef struct QueueNode {
    Guest *guest;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front, *rear;
    int count;
} Queue;

void createGuestList(Guest **head);
void createRoomTree(RoomNode **root);
void createQueue(Queue *queue);
int isIDUnique(Guest *head, char *id);
void inputUniqueID(Guest *guestList, char *id);
void addGuest(Guest **head, char *name, char *id, char *phone);
void displayGuests(Guest *head);
void addRoom(RoomNode **root, char *roomType, char *roomNumber);
void initRoomData(RoomNode **root);
void displayRooms(RoomNode *root);
void displayAvailableRooms(RoomNode *root);
Guest* findGuestByID(Guest *head, char *id);
void enqueue(Queue *queue, Guest *guestList);
int isQueueEmpty(Queue *queue);
void displayQueue(Queue *queue);
RoomNode* chooseRoom(RoomNode *root);
void dequeue(Queue *queue, RoomNode *root);
int displayCheckedInGuests(Guest *guestList);
void checkoutGuest(Guest **guestList, Queue *queue);

int main() {
    Guest *guestList = NULL;
    RoomNode *roomTree = NULL;
    Queue queue;
    int choice;
    char name[50], id[20], phone[15];

    createGuestList(&guestList);
    createRoomTree(&roomTree);
    createQueue(&queue);
    initRoomData(&roomTree);

    do {
        system("cls");
        printf("Sistem Reservasi Hotel:\n");
        printf("1. Tambah Tamu Baru\n");
        printf("2. Tampilkan Daftar Tamu\n");
        printf("3. Tambah Kamar Baru\n");
        printf("4. Tampilkan Semua Kamar\n");
        printf("5. Tampilkan Kamar Tersedia\n");
        printf("6. Tambah ke Antrean Check-in\n");
        printf("7. Tampilkan Antrean Check-in\n");
        printf("8. Proses Check-in\n");
        printf("9. Tampilkan Tamu yang Sudah Check-in\n");
        printf("10. Check-out Tamu\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nama: ");
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                inputUniqueID(guestList, id);
                printf("Masukkan telepon: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0;
                addGuest(&guestList, name, id, phone);
                getch();
                break;
            case 2:
                displayGuests(guestList);
                getch();
                break;
			case 3:
			    printf("Masukkan tipe kamar: ");
			    fflush(stdin);
			    fgets(name, sizeof(name), stdin);
			    name[strcspn(name, "\n")] = 0;
			
			    printf("Masukkan nomor kamar: ");
			    fgets(id, sizeof(id), stdin);
			    id[strcspn(id, "\n")] = 0;
			
			    addRoom(&roomTree, name, id);
			    getch();
			    break;
            case 4:
                printf("+-------------------+-------------------+-------------------+\n");
                printf("| %-17s | %-17s | %-17s |\n", "Nomor Kamar", "Tipe Kamar", "Status");
                printf("+-------------------+-------------------+-------------------+\n");
                displayRooms(roomTree);
                printf("+-------------------+-------------------+-------------------+\n");
                getch();
                break;
            case 5:
                printf("+-------------------+-------------------+-------------------+\n");
                printf("| %-17s | %-17s | %-17s |\n", "Nomor Kamar", "Tipe Kamar", "Status");
                printf("+-------------------+-------------------+-------------------+\n");
                displayAvailableRooms(roomTree);
                printf("+-------------------+-------------------+-------------------+\n");
                getch();
                break;
            case 6:
                enqueue(&queue, guestList);
                getch();
                break;
            case 7:
                displayQueue(&queue);
                getch();
                break;
            case 8:
                dequeue(&queue, roomTree);
                getch();
                break;
            case 9:
                if (displayCheckedInGuests(guestList) == 0) {
                    printf("Tidak ada tamu yang sedang check-in.\n");
                }
                getch();
                break;
            case 10:
                checkoutGuest(&guestList, &queue);
                getch();
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getch();
        }
    } while (choice != 0);

    return 0;
}

void createGuestList(Guest **head) {
    *head = NULL;
}

void createRoomTree(RoomNode **root) {
    *root = NULL;
}

void createQueue(Queue *queue) {
    queue->front = queue->rear = NULL;
    queue->count = 0;
}

int isIDUnique(Guest *head, char *id) {
    Guest *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

void inputUniqueID(Guest *guestList, char *id) {
    int isUnique = 0;

    do {
        printf("Masukkan ID: ");

        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = 0;

        if (isIDUnique(guestList, id)) {
            isUnique = 1;
        } else {
            printf("ID %s sudah digunakan. Silakan masukkan ID yang berbeda.\n", id);
        }
    } while (!isUnique);
}

void addGuest(Guest **head, char *name, char *id, char *phone) {
    Guest *newGuest = (Guest *)malloc(sizeof(Guest));
    if (!newGuest) {
        printf("Alokasi memori gagal untuk tamu baru.\n");
        return;
    }

    strcpy(newGuest->name, name);
    strcpy(newGuest->id, id);
    strcpy(newGuest->phone, phone);
    newGuest->room = NULL;

    newGuest->next = *head;
    *head = newGuest;

    printf("Tamu berhasil ditambahkan.\n");
}

void displayGuests(Guest *head) {
    if (head == NULL) {
        printf("Daftar tamu kosong.\n");
        return;
    }

    Guest *temp = head;
    printf("+-------------------+-------------------+-------------------+-------------------+\n");
    printf("| %-17s | %-17s | %-17s | %-17s |\n", "Nama", "ID", "Telepon", "Kamar");
    printf("+-------------------+-------------------+-------------------+-------------------+\n");

    while (temp != NULL) {
        printf("| %-17s | %-17s | %-17s | %-17s |\n", 
               temp->name, temp->id, temp->phone, 
               temp->room ? temp->room->roomNumber : "Belum Check-in");
        temp = temp->next;
    }

    printf("+-------------------+-------------------+-------------------+-------------------+\n");
}

void addRoom(RoomNode **root, char *roomType, char *roomNumber) {
    int isAdded = 0;

    do {
        if (*root == NULL) {
            *root = (RoomNode *)malloc(sizeof(RoomNode));
            if (*root == NULL) {
                printf("Alokasi memori gagal. Tidak dapat menambahkan kamar.\n");
                return;
            }
            strcpy((*root)->roomType, roomType);
            strcpy((*root)->roomNumber, roomNumber);
            (*root)->isAvailable = 1;
            (*root)->left = (*root)->right = NULL;
            printf("Kamar dengan nomor %s berhasil ditambahkan.\n", roomNumber);
            isAdded = 1;
        } else if (strcmp(roomNumber, (*root)->roomNumber) < 0) {
            addRoom(&(*root)->left, roomType, roomNumber);
            isAdded = 1;
        } else if (strcmp(roomNumber, (*root)->roomNumber) > 0) {
            addRoom(&(*root)->right, roomType, roomNumber);
            isAdded = 1;
        } else {
            printf("Kamar dengan nomor %s sudah ada. Silakan masukkan nomor kamar yang berbeda.\n", roomNumber);
            printf("Masukkan nomor kamar baru: ");
            fgets(roomNumber, 10, stdin);
            roomNumber[strcspn(roomNumber, "\n")] = 0;
        }
    } while (!isAdded);
}

void initRoomData(RoomNode **root) {
    addRoom(root, "Single", "101");
    addRoom(root, "Single", "102");
    addRoom(root, "Double", "201");
    addRoom(root, "Double", "202");
    addRoom(root, "Suite", "301");
    addRoom(root, "Suite", "302");
}

void displayRooms(RoomNode *root) {
    if (root != NULL) {
        displayRooms(root->left);
        
        printf("| %-17s | %-17s | %-17s |\n", root->roomNumber, root->roomType, root->isAvailable ? "Tersedia" : "Terisi");
        
        displayRooms(root->right);
    }
}

void displayAvailableRooms(RoomNode *root) {
    if (root != NULL) {
        displayAvailableRooms(root->left);
        
        if (root->isAvailable) {
            printf("| %-17s | %-17s | %-17s |\n", root->roomNumber, root->roomType, "Tersedia");
        }
        
        displayAvailableRooms(root->right);
    }
}

Guest* findGuestByID(Guest *head, char *id) {
    Guest *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->id, id) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void enqueue(Queue *queue, Guest *guestList) {
    char id[20];
    Guest *guest;

    displayGuests(guestList);
    do{	
	    printf("Masukkan ID tamu untuk check-in: ");
	    
	    fflush(stdin);
	    fgets(id, sizeof(id), stdin);
	    id[strcspn(id, "\n")] = 0;
	
	    guest = findGuestByID(guestList, id);
	    if (guest != NULL) {
	        QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
	        newNode->guest = guest;
	        newNode->next = NULL;
	        if (queue->rear == NULL) {
	            queue->front = queue->rear = newNode;
	        } else {
	            queue->rear->next = newNode;
	            queue->rear = newNode;
	        }
	        queue->count++;
	        printf("Tamu %s berhasil ditambahkan ke antrean check-in.\n", guest->name);
	    } else {
	        printf("Tamu dengan ID %s tidak ditemukan.\n", id);
	    }
	}while(guest == NULL);
}

int isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void displayQueue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Antrean kosong.\n");
        return;
    }

    QueueNode *temp = queue->front;

    printf("+-------------------+\n");
    printf("| %-17s |\n", "Nama Tamu");
    printf("+-------------------+\n");

    while (temp != NULL) {
        printf("| %-17s |\n", temp->guest->name);
        temp = temp->next;
    }

    printf("+-------------------+\n");
}

RoomNode* chooseRoom(RoomNode *root) {
    RoomNode *current;
    char roomNumber[10];

    printf("+-------------------+-------------------+-------------------+\n");
    printf("| %-17s | %-17s | %-17s |\n", "Nomor Kamar", "Tipe Kamar", "Status");
    printf("+-------------------+-------------------+-------------------+\n");
    displayAvailableRooms(root);
    printf("+-------------------+-------------------+-------------------+\n");

    do {
        printf("Masukkan nomor kamar yang dipilih: ");
        fflush(stdin);
        fgets(roomNumber, sizeof(roomNumber), stdin);
        roomNumber[strcspn(roomNumber, "\n")] = 0;

        current = root;
        while (current != NULL) {
            if (strcmp(current->roomNumber, roomNumber) == 0 && current->isAvailable) {
                current->isAvailable = 0;
                printf("Kamar %s berhasil dipilih.\n", current->roomNumber);
                return current;
            } else if (strcmp(roomNumber, current->roomNumber) < 0) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        printf("Kamar tidak ditemukan atau sudah terisi. Silakan pilih ulang.\n");
    } while (1);
}

void dequeue(Queue *queue, RoomNode *root) {
    if (isQueueEmpty(queue)) {
        printf("Antrean kosong.\n");
    } else {
        QueueNode *temp = queue->front;

        printf("Proses check-in untuk tamu: %s\n", temp->guest->name);
        RoomNode *chosenRoom = chooseRoom(root);
        if (chosenRoom != NULL) {
            temp->guest->room = chosenRoom;
            printf("Tamu %s berhasil check-in ke kamar %s.\n", temp->guest->name, chosenRoom->roomNumber);
        } else {
            printf("Proses check-in gagal. Kamar tidak valid.\n");
        }

        queue->front = queue->front->next;
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        free(temp);
        queue->count--;
    }
}

int displayCheckedInGuests(Guest *guestList) {
    if (guestList == NULL) {
        printf("Daftar tamu kosong.\n");
        return 0;
    }

    Guest *temp = guestList;
    int count = 0;

    printf("+-------------------+-------------------+-------------------+\n");
    printf("| %-17s | %-17s | %-17s |\n", "ID", "Nama", "Kamar");
    printf("+-------------------+-------------------+-------------------+\n");

    while (temp != NULL) {
        if (temp->room != NULL) {
            printf("| %-17s | %-17s | %-17s |\n", temp->id, temp->name, temp->room->roomNumber);
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        printf("| %-51s |\n", "Tidak ada tamu yang sedang check-in.");
    }

    printf("+-------------------+-------------------+-------------------+\n");

    return count;
}

void checkoutGuest(Guest **guestList, Queue *queue) {
    int count = displayCheckedInGuests(*guestList);
    if (count > 0) {
         char id[20];
        Guest *guest;

        do {
            printf("Masukkan ID tamu yang akan check-out: ");
            fflush(stdin);
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = 0;

            guest = findGuestByID(*guestList, id);
            if (guest == NULL) {
                printf("Tamu dengan ID %s tidak ditemukan.\n", id);
            } else if (guest->room == NULL) {
                printf("Tamu dengan ID %s tidak sedang menginap.\n", id);
            }
        } while (guest == NULL || guest->room == NULL);

        guest->room->isAvailable = 1;
        printf("Tamu %s telah check-out dari kamar %s.\n", guest->name, guest->room->roomNumber);
        guest->room = NULL;
    }
}