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

int main() {
    Guest *guestList = NULL;
    RoomNode *roomTree = NULL;
    Queue queue;
    int choice;
    char name[50], id[20], phone[15];

    createGuestList(&guestList);
    createRoomTree(&roomTree);
    createQueue(&queue);

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
			    break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
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