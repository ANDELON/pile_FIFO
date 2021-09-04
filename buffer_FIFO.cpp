#include "buffer_FIFO.hpp"

buffer_FIFO::buffer_FIFO()
{
	longueur = 10;
	stocke = 0;
	a_entrer = &buffer[0];
	a_sortir = &buffer[0];
	RAZ_buffer();
}
buffer_FIFO::buffer_FIFO(int longueur_buff)
{
	longueur = longueur_buff;
	stocke = 0;
	a_entrer = &buffer[0];
	a_sortir = &buffer[0];
	RAZ_buffer();
}
buffer_FIFO::~buffer_FIFO()
{
}

void buffer_FIFO::RAZ_buffer()
{
	for(int i = 0; i < 10; i++)
	{
		buffer[i] = 0;
	}
	a_entrer = &buffer[0];
	a_sortir = &buffer[0];
	stocke = 0;
}

int* buffer_FIFO::give_buffer()
{
	return this->buffer;
}

void buffer_FIFO::push(int var)
{
	*a_entrer = var;
	if(a_entrer < (&buffer[0] + longueur -1))
	{
		a_entrer += 1;
		stocke += 1;
	}
	else
	{
		a_entrer = &buffer[0];
		stocke += 1;
	}
}

int buffer_FIFO::pop()
{
	int var = *a_sortir;
	*a_sortir = 0;
	if(a_sortir < &buffer[0] + longueur -1)
	{
		a_sortir += 1;
		stocke -= 1;
	}
	else
	{
		a_sortir = &buffer[0];
		stocke -= 1;
	}
	return var;
}

int buffer_FIFO::stock_buffer()
{
	return stocke;
}
