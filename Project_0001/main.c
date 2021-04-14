#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define SIZE 30
#define sSIZE 5

char cpyBeverage[sSIZE][sSIZE][SIZE] = { 0 }; // �ֹ������� ���

int returnValue = 0; // �޴�����

int count[4][4] = { 0 }; // ���� ����

int input_Count[4][4] = { 0 }; // ���� ������ ������

int input = 0; // �޴� ȭ��ǥ

int amount[4][4] = { 0 }; // ���� �κбݾ�

int nLocker = 0; // �� �ݾ�

int ptr = 0; // ����ġ�� ��������氪



struct beverage {

	char cName[SIZE];

	char cBeverage[sSIZE][SIZE];

	int nPrice[4];

};

int print_Menu(struct beverage*, int); //�޴��� ���

void print_Beverage(struct beverage*); //�޴��޴��� ���

void input_Quilriti_Menu(struct beverage*); // ���� ���ż��� ����

void print_Locker(); // ���� ���� �ݾ� �ѱݾ�

int print_Payment(int); // ����â

int keyboard(); // Ű���� �Է�


int main()
{
    int end = 0;
	//�޴��� �ʱⰪ

	struct beverage menu = { "Menu" , {{"Coffee"}, {"A D E"}, {"Smoothie"}, {"T E A"}, {"����"} },{0} };

	struct beverage coffee = { "Coffee", {{"Americano"}, {"Espresso"}, {"Cafe latte"}, {"Cafe mocha"}, {"����"}}, {3000,2500,4000,4000 } };

	struct beverage ade = { "A D E", {{"Orande ADE"}, {"Lemon ADE"}, {"Blueberries ADE"}, {"Grapefruit ADE"}, {"����"}}, {3500,3500,3500,3500 } };

	struct beverage smoothie = { "Smoothie", {{"Kiwi Smoothie"}, {"Choco Smoothie"}, {"Strawberry Smoothie"}, {"�̼�����"}, {"����"}}, {4000,4000,4000,4000 } };

	struct beverage tea = { "T E A", {{"EarlGray Tea"}, {"Peppermint Tea"}, {"Green Tea"}, {"Rosemary Tea"}, {"����"}}, {5000,6000,4000,6000} };



	//���α׷� ���� �� �ݺ�

	while (1) {

		if (returnValue == 0)
			end = print_Menu(&menu, end);

		else if (returnValue == 1)
			print_Beverage(&coffee);

		else if (returnValue == 2)
			print_Beverage(&ade);

		else if (returnValue == 3)
			print_Beverage(&smoothie);

		else if (returnValue == 4)
			print_Beverage(&tea);

		else if (returnValue == 5)
			end = print_Payment(end);

		if (end == 5)
			break;

	}
	system("cls");
	printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�\n��			��\n");
	printf("��	�����մϴ�.	��\n��			��\n");
	printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�\n");

	return 0;
}





int print_Menu(struct beverage* menu, int end)
{
	int i = 0, result = 0;

	printf("	  Select %s.		\n", menu->cName);
	printf("==================================\n");

	for (i = 0; i < 4; i++) {

		if (input == i) {
			printf("	> %s <		\n\n", menu->cBeverage[i]);
			continue;
		}

		printf("	 %s 				\n\n", menu->cBeverage[i]);
	}

	printf("==================================\n");

	if (input == 4) {

		printf("	  > ���� <\n");

		printf("==================================\n");

		printf("	 %s\n", menu->cBeverage[4]);

	}

	else if (input == 5) {

		printf("	  ����\n");

		printf("==================================\n");

		printf("	  > %s <\n", menu->cBeverage[4]);

	}

	else {

		printf("	  ����\n");

		printf("==================================\n");

		printf("	  %s\n", menu->cBeverage[4]);

	}
	print_Locker();

	result = keyboard();


	if (result == 2) {
		input++;
		input %= 6;
	}

	else if (result == 1) { // �������� ���ΰ��� �ǹ�����
		input--;
		if (input < 0)
			input = 5;
	}

	else if (result == 3) {
		returnValue = (input + 1) % 7;
		end = input;
		input = 0;
	}

	return end;

}




void print_Beverage(struct beverage* menu)  //�޴��� ���
{
	int i = 0, result = 0;

	printf("	  Select %s.		\n", menu->cName);
	printf("==================================\n");

	for (i = 0; i < 4; i++) {

		if (input == i) {
			printf("    > %-18s <  %d�� \n\n", menu->cBeverage[i], menu->nPrice[i]);
			continue;
		}

		printf("  %-22s %d��	\n\n", menu->cBeverage[i], menu->nPrice[i]);
	}

	printf("==================================\n");

	if (input == 4)
		printf("	 > %s <\n", menu->cBeverage[4]);

	else
		printf("	  %s\n", menu->cBeverage[4]);

	print_Locker();

	result = keyboard();

	if (result == 2) { // Ű���� down ��ǲ +1
		input++;
		input %= 5;
	}

	else if (result == 1) { // Ű���� up ��ǲ -1
		input--;

		if (input < 0) // ��ǲ�� �����ΰ��� ��ǲ �ִ밪����
			input = 4;
	}

	else if (result == 3) {

		if (input != 4) { // �����ư�� �ȴ����� �Ҹ޴��� ���
			input_Quilriti_Menu(menu);

		}

		else
			returnValue = 0;

		input = 0;
	}

	return;
}

void input_Quilriti_Menu(struct beverage* q_Menu) // �Ҹ޴�
{
	int result = 0, sub[4][4] = { 0 }, q_Input = 0;

	while (1) {

		system("cls");

		if (q_Input == 0) {
			printf("%18s	> �� <\n", q_Menu->cBeverage[input]);
			printf("			  ��\n");
		}

		else if (q_Input == 1) {
			printf("%18s	  ��\n", q_Menu->cBeverage[input]);
			printf("			> �� < \n");
		}

		else {
			printf("%18s	  ��\n", q_Menu->cBeverage[input]);
			printf("			  ��\n");
		}

		if (q_Input == 2) {
			printf("	����: %d\n			 > Ȯ�� <\n", count[returnValue - 1][input]);
		}

		else {
			printf("	����: %d\n			  Ȯ�� \n", count[returnValue - 1][input]);
		}

		printf("\n	�ݾ�: %d\n", q_Menu->nPrice[input] * count[returnValue - 1][input]);

		printf("\n=================================\n");

		if (q_Input == 3) {
			printf("	> ���� <\n");
		}

		else
			printf("	����\n");

		print_Locker();

		result = keyboard();

		if (result == 2) {
			q_Input++;
			q_Input %= 4;
		}

		else if (result == 1)
			q_Input--;

		else if (result == 3) {

			if (q_Input == 0) {
				count[returnValue - 1][input]++;
				sub[returnValue - 1][input] += q_Menu->nPrice[input];
			}
			else if (q_Input == 1) {
                    if(count[returnValue - 1][input] >= 1){
                        count[returnValue - 1][input]--;
                        sub[returnValue - 1][input] -= q_Menu->nPrice[input];
                    }
			}
			else if (q_Input == 2) {

				strcpy_s(cpyBeverage[returnValue - 1][input], sizeof(cpyBeverage[returnValue - 1][input]), q_Menu->cBeverage[input]);
				input_Count[returnValue - 1][input] = count[returnValue - 1][input];
				amount[returnValue - 1][input] = q_Menu->nPrice[input] * count[returnValue - 1][input];
				nLocker += sub[returnValue - 1][input];
				sub[returnValue - 1][input] = 0;
				ptr = 1;

				break;
			}

			if (count[returnValue - 1][input] <= -1)
				count[returnValue - 1][input] = 0;

			if (q_Input >= 2)
				break;

		}

		if (q_Input < 0)
			q_Input = 3;

	}

	return;
}




void print_Locker()
{
	int i = 0, j = 0;

	printf("==================================\n");
	printf("	\n\n");

	for (i = 0; i < 4; i++) {

		for (j = 0; j < 4; j++) {
			if (ptr == 1) {
				if (count[i][j] == 0) { // �Ʊ��
					strcpy_s(cpyBeverage[i][j], sizeof(cpyBeverage[i][j]), "");
					ptr = 0;
				}

			}
				if (input_Count[i][j] != 0)
					printf("	%-20s  ����: %d��  �ݾ�: %d��\n", cpyBeverage[i][j], input_Count[i][j], amount[i][j]);
		}

	}
	if (nLocker < -1)
		nLocker = 0;
	printf("\n	�ѱݾ�: %d��", nLocker);

	return;
}



int keyboard() // Ű���� �Է� �Լ�
{
	int key = 0, result = 0;

	key = getch();

	if (key == 224) {

		key = getch();

		switch (key) {

		case 72:
			result = 1;
			break;

		case 80: //down
			result = 2;
			break;

		default:
			result = 0;
		}
	}

	else if (key == 13)
		result = 3;

	else
		return 0;

	system("cls");

	return result;
}



int print_Payment(int end)

{
	int i = 0, money = 0, check[sSIZE] = { 50000,10000,5000,1000,500 }, retun = 0, total = 0;

	while (1) {

		printf("----500��, 1000��, 5000��, 10000��, 50000�� ����----\n");

		printf("	�����Ͻ÷��� 0�� �������� ���ư����� 1���Է����ּ���.\n");

		printf("===================================================\n");

		printf("	������: %d\n", total);

		print_Locker();

		printf("	���� �־��ּ���: ");

		scanf_s("%d", &money);



		if (money == 0) {

			system("cls");
			if (total > nLocker) {
				printf("������ �Ϸ�ƽ��ϴ� �ܵ� %d���� �޾ư�����.", total-nLocker);
				Sleep(2000);
				end = 5;
				system("cls");
				break;
			}
			else if(total == nLocker){
                printf("������ �Ϸ�ƽ��ϴ�.", total-nLocker);
				Sleep(2000);
				end = 5;
				system("cls");
				break;
			}


		}

		if (money == 1) {
			returnValue = 0;
			total = 0;
			system("cls");
			break;
		}

		for (i = 0; i < sSIZE; i++) {

			if (money == check[i])

				retun = 1;

		}

		if (retun == 0) {

			printf("	���� �ٽ� �־��ּ���.");

			Sleep(1500);

			system("cls");

			continue;

		}

		total += money;

		printf("������: %d\n", total);

		retun = 0;

		system("cls");
	}

	return end;
}
