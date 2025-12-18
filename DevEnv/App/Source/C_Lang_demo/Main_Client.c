#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<Engine.h>

//using namespace std;


int main(int argv, char* argc[])
//int WinMain()
{

	CLIENT* Primary = malloc(sizeof(CLIENT));

	if (Primary == NULL) {
		return 1; // handle allocation failure
	}

	Primary->Width = 1200;
	Primary->Height = 800;
	Primary->Title = L"Hello World! - 12/17/2025";
	Primary->Active_black_title_bar = true;

	Create_Client_Window(Primary);

	printf("\Client created!\n");
	//cout << "\Client created!\n";

	while (Queue(Primary))
	{

	}

	printf("\nClient destroyed!\n");
	//cout << "\nClient destroyed!\n";

	Destroy_Client_Window(Primary);

	//free(Primary);

	return 0;
}
