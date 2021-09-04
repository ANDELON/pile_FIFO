#include <iostream>

class buffer_FIFO
{
public:
	buffer_FIFO();
	buffer_FIFO(int);
	~buffer_FIFO();
	void RAZ_buffer();
	int* give_buffer();
	void push(int);
	int pop();
	int stock_buffer();
	int ok_to_push();
	int ok_to_pop();
private:
	int buffer[10];
	int longueur;
	int *a_entrer;
	int *a_sortir;
	int stocke;
};
