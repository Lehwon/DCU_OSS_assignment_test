#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    char* data;
    struct LinkedList* next;
};

typedef struct LinkedList NODE;
typedef NODE* LINK;
LINK createNode(char* name);
LINK append(LINK head, LINK curr);

int printList(LINK head);
LINK createNode(char* name) {
    LINK curr;
    curr = (LINK)malloc(sizeof(NODE));
    if (curr == NULL) {
        printf("Memory allocation problem!\n");
        return NULL;
    }
    curr->data = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(curr->data, name);
    curr->next = NULL;
    return curr;
}
LINK append(LINK head, LINK curr) {
    LINK nextNode = head;
    if (head == NULL) {
        head = curr;
        return head;
    }
    while (nextNode->next != NULL) {
        nextNode = nextNode->next;
    }
    nextNode->next = curr;
    return head;
}
int printList(LINK head) {
    int cnt = 0;
    LINK nextNode = head;
    while (nextNode != NULL) {
        printf("Node #%d is %s\n", ++cnt, nextNode->data);
        nextNode = nextNode->next;
    }
    return cnt;
}

void sortAscending(const LINK head) {
    LINK current = head;
    LINK temp = NULL;
      if (head == NULL) {
        return;
      }
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    char** tempDataArray = (char**)malloc(count * sizeof(char*));
    if (tempDataArray == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    current = head;
    int i = 0;
    while (current != NULL) {   //데이터 복사
        tempDataArray[i] = current->data;
        current = current->next;
        i++;
    }


    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(tempDataArray[i], tempDataArray[j]) > 0) {
                char* temp = tempDataArray[i];
                tempDataArray[i] = tempDataArray[j];
                tempDataArray[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("Node #%d is %s\n", i + 1, tempDataArray[i]);

    }

    free(tempDataArray);
}

void sortDescending(const LINK head) {
    LINK current = head;
    LINK temp = NULL;
  if (head == NULL) {
    return;
  }
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    char** tempDataArray = (char**)malloc(count * sizeof(char*));
    if (tempDataArray == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    current = head;
    int i = 0;
    while (current != NULL) {   //데이터 복사
        tempDataArray[i] = current->data;
        current = current->next;
        i++;
    }


    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(tempDataArray[i], tempDataArray[j]) < 0) {
                char* temp = tempDataArray[i];
                tempDataArray[i] = tempDataArray[j];
                tempDataArray[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("Node #%d is %s\n", i + 1, tempDataArray[i]);

    }

    free(tempDataArray);
}

int countNodes(LINK head) {
    int count = 0;
    LINK curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}

int main(void) {
    char name[30];
    LINK head = NULL;
    LINK curr;

    int cases = 0;
    while (cases != 4) { // Input data >> case

        printf("Select menu [(1) append (2) delete (3) sorting (4) exit program] : ");
        scanf("%d", &cases);

        switch (cases) {

        case 1: // 순차저장이나, 넣을 위치 선택 가능

            printf("Input data >> ");
            scanf("%s", name);

          int loc;
            printf("input location (1 ~ %d) >> ", countNodes(head) + 1);
            scanf("%d", &loc);

            if (loc < 1 || loc > countNodes(head) + 1) {
                printf("Enter the right number!\n");
              break;
            }
            

            curr = createNode(name);

            if (loc == 1) { // 입력 위치가 첫 번째인 경우
                curr->next = head;
                head = curr;
            }
            else { // 중간 또는 마지막 위치에 노드를 추가하는 경우
                LINK prev = NULL;
                LINK temp = head;
                int cnt = 1;
                while (temp != NULL && cnt < loc) {
                    prev = temp;
                    temp = temp->next;
                    cnt++;
                }
                prev->next = curr;
                curr->next = temp;
            }

            printList(head); // 변경된 리스트 출력
            break;

        case 2: //선택한 위치의 노드 삭제

            if (head == NULL) {
                printf("List is Empty!\n");
                break;
            }
            printf("delete location (1 ~ %d) >> ", countNodes(head));

            scanf("%d", &loc);
            if (loc < 1 || loc > countNodes(head)) {
                printf("Enter the right number!\n");
                break;
            }
            if (loc == 1) {
                LINK temp = head;
                head = head->next;
                printf("Node #1 %s is delete!\n", temp->data);
                free(temp->data);
                free(temp);
            }
            else {
                LINK prev = NULL;
                LINK curr = head;
                int cnt = 1;
                while (curr != NULL && cnt < loc) {
                    prev = curr;
                    curr = curr->next;
                    cnt++;
                }
                prev->next = curr->next;
                printf("Node #%d %s is delete!\n", loc, curr->data);
                free(curr->data);
                free(curr);
            }


            printList(head);
            break;

        case 3: //sorting 오름/내림

            if (head == NULL) {
                printf("List is Empty!\n");
                break;
            }

            printf("Select option [(1) ascending (2) descending] : ");
            int sort_option;
            scanf("%d", &sort_option);

            switch (sort_option) {
            case 1:
              printf("linked list is sorted!!\n");
                sortAscending(head);
                break;
            case 2:
              printf("linked list is sorted!!\n");
                sortDescending(head);
              break;
            }

            break;

        case 4:

            break;

        default:
            printf("Enter the right number!\n");
            break;
        }
    }
}