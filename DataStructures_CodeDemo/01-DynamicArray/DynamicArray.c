#include "DynamicArray.h"

//?????????
DynamicArray Init_DynamicArray(){

	DArray* darray = malloc(sizeof(DArray));
	if (darray == NULL){
		return NULL;
	}
	darray->capacity = 5; //?????????5
	darray->size = 0;
	darray->address = (void**)malloc(sizeof(void*) * darray->capacity);

	return darray;
}
//???¦Ë?¨°???
void Insert_DynamicArray(DynamicArray darray, int pos, void* data){
	if (darray == NULL){
		return;
	}
	if (data == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	//?§Ø????????
	if (arr->size == arr->capacity){
		
		int newcapacity = arr->capacity * 2; //??????????
		//??????
		void** newspace = (void**)malloc(sizeof(void*) * newcapacity);
		//?????????????????
		memcpy(newspace,arr->address,sizeof(void*) * arr->capacity);
		//??????
		free(arr->address);
		arr->address = newspace;
		arr->capacity = newcapacity;

	}

	//?§Ø?¦Ë???????§¹?????pos??íà???????¦Â??????
	if (pos < 0 || pos > arr->size){
		pos = arr->size;
	}
	//??????
	int i = arr->size - 1;
	for (; i >= pos;i--){
		arr->address[i + 1] = arr->address[i];
	}
	arr->address[pos] = data;
	arr->size++;
}
//¦Â?????????
void PushBack_DynamicArray(DynamicArray darray, void* data){
	if (darray == NULL){
		return;
	}
	if (data == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	Insert_DynamicArray(darray, arr->size, data);
}
//??????????
void PushFront_DynamicArray(DynamicArray darray, void* data){
	if (darray == NULL){
		return;
	}
	if (data == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	Insert_DynamicArray(darray, 0, data);
}
//¦Ë?????
void RemoveByPos_DynamicArray(DynamicArray darray, int pos){
	if (darray == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	//??????????
	if (arr->size == 0){
		return;
	}
	if (pos < 0 || pos > arr->size - 1){
		return;
	}
	//??????
	int i = pos;
	for (; i < arr->size - 1; i++){
		arr->address[i] = arr->address[i + 1];
	}

	arr->size--;
}
//¦Â?????????
void PopBack_DynamicArray(DynamicArray darray){
	if (darray == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	//??????????
	if (arr->size == 0){
		return;
	}
	RemoveByPos_DynamicArray(darray, arr->size - 1);
}
//??????????
void PopFront_DynamicArray(DynamicArray darray){
	if (darray == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	//??????????
	if (arr->size == 0){
		return;
	}
	RemoveByPos_DynamicArray(darray, 0);
}
//????
void RemoveByVal_DynamicArray(DynamicArray darray, void* data, DATACOMPARE compare){
	if (darray == NULL){
		return;
	}
	if (data == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	//??????????
	if (arr->size == 0){
		return;
	}
	//??????????
	int i = 0;
	for (; i < arr->size;i++){
		if (compare(arr->address[i], data)){
			RemoveByPos_DynamicArray(darray, i);
			break;
		}
	}
}

//??????¦Ë?????
void* Get_DynamicArray(DynamicArray darray, int pos){
	if (darray == NULL){
		return NULL;
	}
	DArray* arr = (DArray*)darray;
	if (pos < 0 || pos >= arr->size){
		return NULL;
	}
	return arr->address[pos];
}

//?????§³
int Size_DynamicArray(DynamicArray darray){
	if (darray == NULL){
		return -1;
	}
	DArray* arr = (DArray*)darray;
	return arr->size;
}
//????????
int Capacity_DynamicArray(DynamicArray darray){
	if (darray == NULL){
		return -1;
	}
	DArray* arr = (DArray*)darray;
	return arr->capacity;
}
//????
void Print_DynamicArray(DynamicArray darray, DATAPRINT print){
	if (darray == NULL){
		return;
	}
	DArray* arr = (DArray*)darray;
	int i = 0;
	for (; i < arr->size;i++){
		print(arr->address[i]);
	}
}
//????????
void Destroy_DynamicArray(DynamicArray darray){
	if (darray == NULL){
		return;
	}
	free(darray);
}