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

int main() {
    Guest *guestList = NULL;
    RoomNode *roomTree = NULL;
    Queue queue;
    int choice;

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
                break;
            case 2:
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