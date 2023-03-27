#include<iostream>
#include<conio.h>
int main()
{
	while(1)
	{
		if(_kbhit())
		{
			int ch = _getch();
			if(ch==27)
			{
				break;
			}
		}
		std::cout<< '*' <<std::endl;
	}
	return 0;
}
