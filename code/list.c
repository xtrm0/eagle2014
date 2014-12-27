#include "../include/list.h"

list_no * l_init(size_t bytes) {
	list_no * base = calloc(1,sizeof(list_no));
	base->val = calloc(1,bytes);
	return base;
}

void l_push_next(list_no * base, void * val, size_t bytes) {
	list_no * aux = calloc(1, sizeof(list_no));
	TESTMEM(aux);
	aux->val = calloc(1, bytes);
	TESTMEM(aux->val);
	memcpy(aux->val, val, bytes);
	aux->next = base->next;
	base->next = aux;
}
void l_push_back(list_no * base, void * val, size_t bytes) {
	l_push_next(l_back(base),val,bytes);
}

void l_destroy(list_no * base) {
	list_no * aux;
	while (base!=NULL) {
		aux=base;
		base=base->next;
		if (aux->val!=NULL) free(aux->val);
		free(aux);
	}
}
list_no * l_find(list_no * base, int (*f)(void *,void *), void * arg) {
	while (base->next!=NULL) {
		printf("%d\n", f(base->next, arg));
		if (f(base->next, arg)==0) return base;
		base=base->next;
	}
	return NULL;
}
void l_copy(list_no * base, list_no * novabase, size_t bytes) {
	base = base->next;
	while (base!=NULL) {
		novabase->next = l_init(bytes);
		memcpy(novabase->next->val, base->val, bytes);
		novabase=novabase->next;
		base=base->next;
	}
}

list_no * l_back(list_no *base) {
	while (base->next!=NULL)
		base=base->next;
	return base;
}