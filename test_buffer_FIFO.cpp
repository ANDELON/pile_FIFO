#include <iostream>
#include "buffer_FIFO.hpp"
#include "lib_test.hpp"

void print_tab(int *, int);

int main()
{
	buffer_FIFO buffer;
	
	lib_test test;
	
	test.expect_equ(0, 0,"test initial de la lib de test");
	
	//test du système de test
	int tab_requis[1] = {1};
	int tab_envoye[1] = {1};
	test.expect_equ(tab_requis,tab_envoye,1,"test de la lib de test");
	
	int tab_requis_2[5] = {1,2,3,4,5};
	int tab_envoye_2[5] = {1,2,3,4,5};
	test.expect_equ(tab_requis_2,tab_envoye_2,5,"test de la lib de test");
	
	//test de la fonction RAZ buffer
 	int tab_requis_3[] = {0,0,0,0,0,0,0,0,0,0};
  	int* tab_envoye_3;
  	buffer.RAZ_buffer();
  	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction RAZ");
	test.expect_equ(0,buffer.stock_buffer(),"test de la fonction RAZ stock 0");
	test.expect_equ(0,buffer.ok_to_pop(),"test de la fonction validation a pop");
	
	//test stockage valeur dans le buffer
 	buffer.push(10);
 	tab_requis_3[0] = 10;
 	tab_envoye_3 = buffer.give_buffer();
 	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction push test initial");
	test.expect_equ(1,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(1,buffer.ok_to_pop(),"test de la fonction validation a pop");
 	
 	buffer.push(5);
 	tab_requis_3[1] = 5;
 	tab_envoye_3 = buffer.give_buffer();
 	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction push test push 1");
	test.expect_equ(2,buffer.stock_buffer(),"test de la fonction stock");
	
	//test pop initial
 	test.expect_equ(10,buffer.pop(),"test de la fonction pop 0");
  	tab_requis_3[0] = 0;
  	tab_envoye_3 = buffer.give_buffer();
  	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction  pop 1");
	test.expect_equ(1,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(1,buffer.ok_to_pop(),"test de la fonction validation a pop");
	
	//test pop second
 	test.expect_equ(5,buffer.pop(),"test de la fonctionpop 0");
 	tab_requis_3[1] = 0;
 	tab_envoye_3 = buffer.give_buffer();
 	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction pop 2");
	test.expect_equ(0,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(0,buffer.ok_to_pop(),"test de la fonction validation a pop");
	
	//test sur pop
	test.expect_equ(0,buffer.pop(),"test de la fonction sur pop 0");
	test.expect_equ(-1,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(0,buffer.ok_to_pop(),"test de la fonction validation a pop");
	
	//test de séquences entrées sorties, enchainement push - push
	//buffer à zéro ici, et tab_requis également
  	buffer.RAZ_buffer();
  	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction RAZ");
	test.expect_equ(0,buffer.stock_buffer(),"test de la fonction stock");
	
	buffer.push(1);
	buffer.push(2);
	buffer.push(3);
	buffer.push(4);
	tab_requis_3[0] = 1;
	tab_requis_3[1] = 2;
	tab_requis_3[2] = 3;
	tab_requis_3[3] = 4;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la sequence push push");
	test.expect_equ(4,buffer.stock_buffer(),"test de la fonction stock");
	
	//test de séquences entrées sorties, enchainement push - pop - push
	//buffer à zéro ici, et tab_requis également
  	buffer.RAZ_buffer();
	tab_requis_3[0] = 0;
	tab_requis_3[1] = 0;
	tab_requis_3[2] = 0;
	tab_requis_3[3] = 0;
	tab_requis_3[4] = 0;
	tab_requis_3[5] = 0;
  	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test de la fonction RAZ");
	test.expect_equ(0,buffer.stock_buffer(),"test de la fonction stock");
	
	buffer.push(1);
	buffer.push(2);
	tab_requis_3[0] = 1;
	tab_requis_3[1] = 2;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test push initiaux");
	test.expect_equ(2,buffer.stock_buffer(),"test de la fonction stock");
	
	//un petit pop
	test.expect_equ(1,buffer.pop(),"test de la fonction pop sequence");
	buffer.push(5);
	tab_requis_3[0] = 0;//on a poppé le first, il est mis à 0
	tab_requis_3[2] = 5;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test push initiaux");
	test.expect_equ(2,buffer.stock_buffer(),"test de la fonction stock");
	
	//reste à tester les limites
	std::cout<<"Visu du buffer avant test depassement: \n";
	print_tab(tab_envoye_3,10);
	buffer.push(4);
	buffer.push(5);
	buffer.push(6);
	buffer.push(7);
	buffer.push(8);
	buffer.push(9);
	buffer.push(10);
	tab_envoye_3 = buffer.give_buffer();
	std::cout<<"Visu du buffer avant remplissage: \n";
	print_tab(tab_envoye_3,10);
	
	
	tab_requis_3[3] = 4;
	tab_requis_3[4] = 5;
	tab_requis_3[5] = 6;
	tab_requis_3[6] = 7;
	tab_requis_3[7] = 8;
	tab_requis_3[8] = 9;
	tab_requis_3[9] = 10;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test push initiaux");
	test.expect_equ(9,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(1,buffer.ok_to_push(),"test de la fonction autorisation a push");
	
	//un coup de push en plus, et on doit revenir à 0
	buffer.push(11);
	tab_requis_3[0] = 11;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test push depassement");
	test.expect_equ(10,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(0,buffer.ok_to_push(),"test de la fonction autorisation a push");
	
	//test des pops:
	tab_envoye_3 = buffer.give_buffer();
	std::cout<<"Visu du buffer avant pop: \n";
	print_tab(tab_envoye_3,10);
	// 11, 2, 5, 4, 5, 6, 7, 8, 9, 10,
	//on teste toute la séquence dans l'ordre pour voir si tout se passe bien à la limite
	test.expect_equ(2,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(9,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(5,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(8,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(4,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(7,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(5,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(6,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(6,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(5,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(7,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(4,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(8,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(3,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(9,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(2,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(10,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(1,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(11,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(0,buffer.stock_buffer(),"test de la fonction stock");
	
	//test de la valeur du buffer après opérations
	tab_requis_3[0] = 0;
	tab_requis_3[1] = 0;
	tab_requis_3[2] = 0;
	tab_requis_3[3] = 0;
	tab_requis_3[4] = 0;
	tab_requis_3[5] = 0;
	tab_requis_3[6] = 0;
	tab_requis_3[7] = 0;
	tab_requis_3[8] = 0;
	tab_requis_3[9] = 0;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test apres pop avec depassement");
	test.expect_equ(0,buffer.ok_to_pop(),"test de la fonction validation a pop");
	
	//test push pop a proximite du depassement
	buffer.push(1);
	buffer.push(2);
	buffer.push(3);
	buffer.push(4);
	buffer.push(5);
	buffer.push(6);
	buffer.push(7);
	buffer.push(8);
	buffer.push(9);
	buffer.push(10);
	
	tab_requis_3[0] = 10;
	tab_requis_3[1] = 1;
	tab_requis_3[2] = 2;
	tab_requis_3[3] = 3;
	tab_requis_3[4] = 4;
	tab_requis_3[5] = 5;
	tab_requis_3[6] = 6;
	tab_requis_3[7] = 7;
	tab_requis_3[8] = 8;
	tab_requis_3[9] = 9;
	tab_envoye_3 = buffer.give_buffer();
	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test apres push et cycle");
	test.expect_equ(10,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(0,buffer.ok_to_push(),"test de la fonction autorisation a push");
	
	
	//test du pop
	test.expect_equ(1,buffer.pop(),"test de la fonction pop avec depassement");
	test.expect_equ(1,buffer.ok_to_push(),"test de la fonction autorisation a push");
	tab_requis_3[1] = 0;
	tab_envoye_3 = buffer.give_buffer();
 	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test apres push et cycle");
	test.expect_equ(9,buffer.stock_buffer(),"test de la fonction stock");
	
	//un nouveau push pour voir
	buffer.push(11);
	tab_requis_3[1] = 11;
	tab_envoye_3 = buffer.give_buffer();
 	test.expect_equ(tab_requis_3,tab_envoye_3,10,"test apres push et cycle");
	test.expect_equ(10,buffer.stock_buffer(),"test de la fonction stock");
	test.expect_equ(0,buffer.ok_to_push(),"test de la fonction autorisation a push");
	test.expect_equ(1,buffer.ok_to_pop(),"test de la fonction validation a pop");
	
	return 0;
}

void print_tab(int *tab, int longueur)
{
	for(int i = 0; i< longueur; i++)
	{
		std::cout<<tab[i]<< ", ";
	}
	std::cout<<"\n";
}
