// Rumeysa Ulusoy 
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int number_array = 0;

struct priority_queue {
 int size;
 int count;
 int *array;
 int *index;
};

struct linked_list{
	int file_num;
	int num_of_word;
	char word [5000][50];
    struct linked_list *next;
    int relevant;
 };
 
void texts (struct linked_list* node, int doc, int relevant);
void enqueue (struct priority_queue* heap, int key, int file_num);
int* build_maxheap (int array [], int index[], int number_of_mem);
void max_heapify(int array[], int index[], int a, int heap_size);
int dequeue ( int array [], int index[], int heap_size);
void search_word(struct linked_list* head, char keyword []);

int main () {

 DIR *folder;
 struct dirent *entry;

 char content[1000];   
 FILE *file;   
 folder = opendir("files");

 if (folder == NULL) {
 printf("there's no file.");
 return(1);	
 }
 entry = readdir(folder);
 entry = readdir(folder);
 entry = readdir(folder);
 
 struct linked_list* head = NULL;
 head = malloc(sizeof(struct linked_list));
 head->next = NULL;

  
 int times = 1;

  printf("1- %s opened.\n", entry->d_name);

  char filename[1000];
  sprintf(filename, "%s/%s", "files", entry->d_name);

  file = fopen(filename, "r");
  int x = 0;
   
 
   int num_of_word = 0;
   if(file != NULL) {
   

    while (!feof(file)) {  
    fscanf(file, "%[^,.\":?!*/_+-() ]%*[,.\":?!*/_+-() ]", content); 
	int a = 0;
	 for(a = 0; content[a]; a++){
    content[a] = tolower(content[a]);
    }
    
    num_of_word++;
    
   strcpy(*(head->word + x) , content);
   x++; 
   
   }

  fclose(file);	
  strcpy(*(head->word + x) , "\0");
  
  }

  head->num_of_word = num_of_word;
  head->file_num = 1;
  struct linked_list* node = NULL;
  node = head;
  
  while((entry = readdir(folder))  != NULL) {
  int x = 0;
  times++;
   
  printf("%d- %s opened.\n", times, entry->d_name);

  char filename[1000]; 
  sprintf(filename, "%s/%s", "files", entry->d_name);

  file = fopen(filename, "r");
  
   struct linked_list* new = NULL;   
   new = malloc(sizeof(struct linked_list));
   
   
   int num_of_word = 0;
   if(file != NULL) {
   

    while (!feof(file)) {  
    
    fscanf(file, "%[^,.\":?!*/_+-() ]%*[,.\":?!*/_+-() ]", content); 
    num_of_word++;
    
    int a = 0;
     for(a = 0; content[a]; a++){
    content[a] = tolower(content[a]);
    }

   strcpy(*(new->word + x) , content);
   x++; 
   
   }

  fclose(file);
  
  strcpy(*(new->word + x) , "\0");
  
  }
  
  new->num_of_word = num_of_word;
  new->file_num = times;
  node->next = new;
  new->next = NULL;
  node = new;
  
 }

closedir(folder);

char keyword[20];
printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
printf("\n");
printf("\n  Enter a keyword: ");
scanf("%s", keyword);	
	
	
search_word(head, keyword);

struct linked_list* temp = head;

int num_of_member = 0;
int array_of_key [42];
printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
printf("\n\n");
int h;
int y = 0;

for (h = 0; h < 42; h++) {
printf("  Number of relevant of document %d : %d\n", temp->file_num, temp->relevant);	
if (temp->relevant != 0) {
array_of_key [y] = temp->relevant;
y++;	
num_of_member++;
	
}

temp  = temp->next;
}

 struct linked_list* temp2 = head;

 struct priority_queue heap;
 heap.count = 0;
 heap.size = 42;
 heap.array = (int *) malloc(sizeof(int) * 42 );
 heap.index = (int *) malloc(sizeof(int) * 42 );

 
 int k = 0;
 for (k; k < 42; k++) {
 if (temp2->relevant != 0) {
 printf("_ ");
 enqueue (&heap, temp2->relevant, temp2->file_num);
 number_array++;	
 }	

 temp2 = temp2->next;	 
 	
 }	
 
 heap.size = number_array;
 heap.array = build_maxheap (heap.array, heap.index, number_array);

 int doc_number = number_array;
 printf("\n"); 
 printf("\n  The relevance order is:");  
 int doc1;
 int relevant1;
 int doc2;
 int relevant2;
 int doc3;
 int relevant3;
 int doc4;
 int relevant4;
 int doc5;
 int relevant5;

 if (doc_number > 0) {
 doc1 = heap.index[0];
 printf(" Doc%d", doc1);
 relevant1 = dequeue(heap.array, heap.index, number_array);
 printf("(%d)", relevant1 );	
 }

 if (doc_number > 1) {
 printf(",");	
 doc2 = heap.index[0];
 printf(" Doc%d", doc2);
 relevant2 = dequeue(heap.array, heap.index, number_array);
 printf("(%d)", relevant2);
 }

 if (doc_number > 2) {
 printf(",");	
 doc3 = heap.index[0];
 printf(" Doc%d", doc3);
 relevant3 = dequeue(heap.array, heap.index, number_array);
 printf("(%d)", relevant3);
 }
 
 if (doc_number > 3) {
 printf(",");
 doc4 = heap.index[0];
 printf(" Doc%d", doc4);
 relevant4 = dequeue(heap.array, heap.index, number_array);
 printf("(%d)", relevant4);
 }
 
 if (doc_number > 4) {
 printf(",");	
 doc5 = heap.index[0];
 printf(" Doc%d", doc5);
 relevant5 = dequeue(heap.array, heap.index, number_array);
 printf("(%d).", relevant5);
 }

 if (doc_number > 0) {
 struct linked_list* temp_for_1 = head;
 texts(temp_for_1, doc1, relevant1);
 }
 
 if (doc_number > 1) {
 struct linked_list* temp_for_2 = head;
 texts(temp_for_2, doc2, relevant2);
 }

 if (doc_number > 2) {
 struct linked_list* temp_for_3 = head;
 texts(temp_for_3, doc3, relevant3);
 }

 if (doc_number > 3) {
 struct linked_list* temp_for_4 = head;
 texts(temp_for_4, doc4, relevant4);
 }

 if (doc_number > 4) {
 struct linked_list* temp_for_5 = head;
 texts(temp_for_5, doc5, relevant5);
 }
}

void texts (struct linked_list* node, int doc, int relevant) {
	
 printf("\n\n");
 printf("  Doc%d(%d): ", doc, relevant);
 int u = 0;
 for(u; u < doc - 1; u++  ) {
 node = node->next;	
 }

 u = 0;
 for(u; u < node->num_of_word; u++ ) {
 printf("%s ", *(node->word + u) );	
 }	
	
}


void enqueue (struct priority_queue* heap, int key, int file_num) {
 
 int num = heap->count++;
 
 heap->array[num] = key;
 heap->index[num] = file_num;
 
 int a = a * heap->size + 1;
 
 while(a != 0 && heap->array[(a - 1) / 2] < heap->array[a]) {
 	int temp = heap->array[(a - 1) / 2];
 	int temp2 = heap->index[(a - 1) / 2];
 	heap->array[(a - 1) / 2] = heap->array[a];
 	heap->index[(a - 1) / 2] = heap->index[a];
 	heap->array[a] = temp;
 	heap->index[a] = temp2;
 	a = (a - 1) / 2;
 	
 }
 
}


int* build_maxheap (int array [], int index[], int number_of_mem) {

int heap_size = number_of_mem;
int a;
for (a = number_of_mem / 2; a >= 0; a-- ) {
max_heapify(array, index, a, heap_size);

}	
return array;
}


void max_heapify(int array[], int index[], int a, int heap_size) {

int num, new_ind, left, right, largest;
left = (2 * a + 1);
right = (2 * a + 2);

 if (left >= heap_size) {
 return;		
 } 
 else {
 
 if (left <= heap_size && array[left] > array[a]) {
 largest = left;	
 }
 else {
 largest = a;
 }
 
 if (right <= heap_size && array[right] > array[largest]) {
 largest = right;	
 }

 if (largest != a) {
 num = array[a];
 new_ind = index[a];
 
 array[a] = array[largest];
 index[a] = index[largest];
 
 array[largest] = num;
 index[largest] = new_ind;
 max_heapify(array, index, largest, heap_size);	
 }
}
}


int dequeue ( int array [], int index[], int heap_size) {
 int root = array[0];	
 array[0] = array[heap_size-1];
 index[0] = index[heap_size-1];
 number_array = number_array - 1;
 heap_size = number_array;
 max_heapify(array, index, 0, heap_size);
 return root;
}


void search_word(struct linked_list* head, char keyword []) {
struct linked_list* hd = head;	

int b = 1;

 while ( b < 43 ) {
 	
 int relevant = 0;
 int num_of_word = hd->num_of_word;
 int a = 0;
 
 for (a; a < num_of_word; a++) {
  
  if (strcmp(keyword, *(hd->word + a)) == 0) {
  relevant++;	
  }
  	
 }	
	
 hd->relevant = relevant;	

 b++;
 hd = hd->next;
 }	
		
}
