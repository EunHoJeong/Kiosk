#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define SIZE 30
#define sSIZE 5

char cpyBeverage[sSIZE][sSIZE][SIZE] = { 0 }; // 주문한음료 출력

int returnValue = 0; // 메뉴선택

int count[4][4] = { 0 }; // 음료 수량

int input_Count[4][4] = { 0 }; // 음료 수량을 받은값

int input = 0; // 메뉴 화살표

int amount[4][4] = { 0 }; // 음료 부분금액

int nLocker = 0; // 총 금액

int ptr = 0; // 엔터치고 결과값변경값



struct beverage {

	char cName[SIZE];

	char cBeverage[sSIZE][SIZE];

	int nPrice[4];

};

int print_Menu(struct beverage*, int); //메뉴판 출력

void print_Beverage(struct beverage*); //메뉴메뉴판 출력

void input_Quilriti_Menu(struct beverage*); // 음료 구매수량 선택

void print_Locker(); // 음료 개수 금액 총금액

int print_Payment(int); // 결제창

int keyboard(); // 키보드 입력


int main()
{
    int end = 0;
	//메뉴판 초기값

	struct beverage menu = { "Menu" , {{"Coffee"}, {"A D E"}, {"Smoothie"}, {"T E A"}, {"종료"} },{0} };

	struct beverage coffee = { "Coffee", {{"Americano"}, {"Espresso"}, {"Cafe latte"}, {"Cafe mocha"}, {"이전"}}, {3000,2500,4000,4000 } };

	struct beverage ade = { "A D E", {{"Orande ADE"}, {"Lemon ADE"}, {"Blueberries ADE"}, {"Grapefruit ADE"}, {"이전"}}, {3500,3500,3500,3500 } };

	struct beverage smoothie = { "Smoothie", {{"Kiwi Smoothie"}, {"Choco Smoothie"}, {"Strawberry Smoothie"}, {"미숫가루"}, {"이전"}}, {4000,4000,4000,4000 } };

	struct beverage tea = { "T E A", {{"EarlGray Tea"}, {"Peppermint Tea"}, {"Green Tea"}, {"Rosemary Tea"}, {"이전"}}, {5000,6000,4000,6000} };



	//프로그램 실행 후 반복

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
	printf("★☆★☆★☆★☆★☆★☆★\n☆			☆\n");
	printf("★	감사합니다.	★\n☆			☆\n");
	printf("★☆★☆★☆★☆★☆★☆★\n");

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

		printf("	  > 결제 <\n");

		printf("==================================\n");

		printf("	 %s\n", menu->cBeverage[4]);

	}

	else if (input == 5) {

		printf("	  결제\n");

		printf("==================================\n");

		printf("	  > %s <\n", menu->cBeverage[4]);

	}

	else {

		printf("	  결제\n");

		printf("==================================\n");

		printf("	  %s\n", menu->cBeverage[4]);

	}
	print_Locker();

	result = keyboard();


	if (result == 2) {
		input++;
		input %= 6;
	}

	else if (result == 1) { // 맨위에서 위로가면 맨밑으로
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




void print_Beverage(struct beverage* menu)  //메뉴판 출력
{
	int i = 0, result = 0;

	printf("	  Select %s.		\n", menu->cName);
	printf("==================================\n");

	for (i = 0; i < 4; i++) {

		if (input == i) {
			printf("    > %-18s <  %d원 \n\n", menu->cBeverage[i], menu->nPrice[i]);
			continue;
		}

		printf("  %-22s %d원	\n\n", menu->cBeverage[i], menu->nPrice[i]);
	}

	printf("==================================\n");

	if (input == 4)
		printf("	 > %s <\n", menu->cBeverage[4]);

	else
		printf("	  %s\n", menu->cBeverage[4]);

	print_Locker();

	result = keyboard();

	if (result == 2) { // 키보드 down 인풋 +1
		input++;
		input %= 5;
	}

	else if (result == 1) { // 키보드 up 인풋 -1
		input--;

		if (input < 0) // 인풋이 음수로가면 인풋 최대값으로
			input = 4;
	}

	else if (result == 3) {

		if (input != 4) { // 종료버튼을 안누르면 소메뉴판 출력
			input_Quilriti_Menu(menu);

		}

		else
			returnValue = 0;

		input = 0;
	}

	return;
}

void input_Quilriti_Menu(struct beverage* q_Menu) // 소메뉴
{
	int result = 0, sub[4][4] = { 0 }, q_Input = 0;

	while (1) {

		system("cls");

		if (q_Input == 0) {
			printf("%18s	> ▲ <\n", q_Menu->cBeverage[input]);
			printf("			  ▼\n");
		}

		else if (q_Input == 1) {
			printf("%18s	  ▲\n", q_Menu->cBeverage[input]);
			printf("			> ▼ < \n");
		}

		else {
			printf("%18s	  ▲\n", q_Menu->cBeverage[input]);
			printf("			  ▼\n");
		}

		if (q_Input == 2) {
			printf("	수량: %d\n			 > 확인 <\n", count[returnValue - 1][input]);
		}

		else {
			printf("	수량: %d\n			  확인 \n", count[returnValue - 1][input]);
		}

		printf("\n	금액: %d\n", q_Menu->nPrice[input] * count[returnValue - 1][input]);

		printf("\n=================================\n");

		if (q_Input == 3) {
			printf("	> 이전 <\n");
		}

		else
			printf("	이전\n");

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
				if (count[i][j] == 0) { // 아까움
					strcpy_s(cpyBeverage[i][j], sizeof(cpyBeverage[i][j]), "");
					ptr = 0;
				}

			}
				if (input_Count[i][j] != 0)
					printf("	%-20s  수량: %d개  금액: %d원\n", cpyBeverage[i][j], input_Count[i][j], amount[i][j]);
		}

	}
	if (nLocker < -1)
		nLocker = 0;
	printf("\n	총금액: %d원", nLocker);

	return;
}



int keyboard() // 키보드 입력 함수
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

		printf("----500원, 1000원, 5000원, 10000원, 50000원 가능----\n");

		printf("	결제하시려면 0을 이전으로 돌아가려면 1을입력해주세요.\n");

		printf("===================================================\n");

		printf("	넣은돈: %d\n", total);

		print_Locker();

		printf("	돈을 넣어주세요: ");

		scanf_s("%d", &money);



		if (money == 0) {

			system("cls");
			if (total > nLocker) {
				printf("결제가 완료됐습니다 잔돈 %d원을 받아가세요.", total-nLocker);
				Sleep(2000);
				end = 5;
				system("cls");
				break;
			}
			else if(total == nLocker){
                printf("결제가 완료됐습니다.", total-nLocker);
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

			printf("	돈을 다시 넣어주세요.");

			Sleep(1500);

			system("cls");

			continue;

		}

		total += money;

		printf("넣은돈: %d\n", total);

		retun = 0;

		system("cls");
	}

	return end;
}
