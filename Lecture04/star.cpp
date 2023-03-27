#include<iostream>
#include<conio.h>
int main()
{
	while(1)
	{
		std::cout << '*';
		if(_kbhit())
		{
			int ch = _getch();
			if(ch==27)
			{
				break;
			}
		}
			}
	return 0;
}
