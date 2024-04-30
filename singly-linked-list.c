/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

//Node를 struct로 선언
typedef struct Node {
	int key;
	struct Node* link;
} listNode; //구조체 호출시 사용할 이름

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
    // 리스트의 첫 번째 노드를 가리키는 포인터 p와 그 전 노드를 가리키는 포인터 prev 선언
    listNode* p = h->first;
    listNode* prev = NULL;

    // 리스트의 모든 노드를 순회하며 메모리를 해제
    while(p != NULL) {
        prev = p;
        p = p->link;
        free(prev);
    }

    // 헤드 노드의 메모리 해제
    free(h);
    return 0;
}



/**
 * 리스트의 처음에 key에 대한 노드를 추가하는 함수
 * @return 정상적으로 추가되면 0, 그렇지 않으면 -1을 반환
 */
int insertFirst(headNode* h, int key) {
    // 새로운 노드 생성
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;

    // 새로운 노드를 리스트의 첫 번째 노드로 연결
    node->link = h->first;
    h->first = node;

    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    // 삽입할 새로운 노드 생성
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    // 리스트가 비어있을 경우 새로운 노드를 첫 번째 노드로 설정
    if (h->first == NULL) {
        h->first = node;
    }

    // 리스트 탐색을 위한 변수들
    listNode* n = h->first;
    listNode* trail = h->first;

    // 리스트를 탐색하면서 삽입할 위치를 찾음
    while (n != NULL) {
        if (n->key >= key) {
            // 새로운 노드를 삽입할 위치를 찾았을 때
            if (n == h->first) {
                // 첫 번째 노드 앞에 삽입해야 할 경우
                h->first = node;
                node->link = n;
            } else {
                // 중간에 삽입해야 할 경우
                node->link = n;
                trail->link = node;
            }
            return 0;
        }
        trail = n;
        n = n->link;
    }

    // 리스트의 끝까지 탐색했을 때 새로운 노드를 마지막에 삽입
    trail->link = node;
    return 0;
}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode)); //포인터node에 listnode 크기 만큼의 메모리 할당
	node->key = key; //node의 key에 입력받은 key값 저장
	node->link = NULL; //node의 link에 NULL값 저장(초기화)

	if (h->first == NULL) //h의 first가 NULL일때
	{
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //listnode n에 h의 first 저장
	while(n->link != NULL) {//n의 link!=NULL일 동안, 노드가 존재할 동안
		n = n->link; //n에 n의 link 저장
	}
	n->link = node; //n의 link에 node 저장
	return 0;

}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

		if(h->first==NULL){
			printf("nothing to delete.\n"); //삭제할 노드 없음.
			return 0;
		}
		listNode* n = h->first; //n에 h의 first를 저장

		h->first = n->link; //h의 first에 n의 link 저장
		free(n); //n에 할당된 메모리 해제


		return 0;
	
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h의 first가 NULL일때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first; //포인터 n에 h의 first 저장
	listNode* trail = NULL; //포인터 trail 초기화

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n!=NULL일 동안, 노드가 존재 할 동안
		if(n->key == key) { //n의 key가 입력된 key와 같을때
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n가 h의 first일 경우 
				h->first = n->link; //n의 link를 h의 frist에 저장
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link; //n의 link를 trail의 link에 저장
			}
			free(n); //n에 할당된 메모리 해제
			return 0;
		}

		trail = n; //trail에 n 저장
		n = n->link; //n에 n의 link를 저장 
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (h->first == NULL) //h의 first가 NULL일 때
	{
		printf("nothing to delete.\n"); //삭제할노드가없음
		return 0;
	}

	listNode* n = h->first; //n에 h의 frist 저장
	listNode* trail = NULL; //trail 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { //n의  link가 NULL일때
		h->first = NULL; //h의 first를 NULL로 초기화
		free(n); //n에 할당된 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) { //n->link != NULL일동안, 노드가 존재할 동안
		trail = n; //trail에 n 저장
		n = n->link; //n에 n의 link 저장
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->link = NULL; //trail의 link  NULL처리 
	free(n); //n에 할당된 메모리 해제


	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL) { //h의 first가 NULL일 경우
		printf("nothing to invert...\n"); //바꿀 노드가 없음
		return 0;
	}
	listNode *n = h->first; //포인터 n에 h의 first 저장
	listNode *trail = NULL; //포인터 trail NULL로 초기화
	listNode *middle = NULL; //포인터 middle NULL로 초기화

	while(n != NULL){ //n!=NULL일 동안 , 노드가 존재할 동안
		trail = middle; //trail에 middle 저장
		middle = n; //middle에는 n 저장
		n = n->link; //n에는 n의 link 저장
		middle->link = trail; //middle의 link에 trail 저장 
	}

	h->first = middle; //h의 first에는 middle 저장

	return 0;

}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { //노드가 존재할 동안 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

