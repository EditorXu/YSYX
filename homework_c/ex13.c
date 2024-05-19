#include<stdio.h>
int main(int argc,char *argv[])
{
	for(int j = 1 ; j < argc;j++)
	{
		for(int i = 0;argv[j][i] != '\0';i++)
		{
			char letter = argv[j][i];
			if(letter >= 'A' && letter <= 'Z')
			{
				letter = letter + 32;
			}

			if(letter == 'a')
			{
				printf("%d: 'A'\n",i);
			}
			else if(letter == 'e')
			{
				printf("%d: 'E'\n",i);
			}
			else if(letter == 'i')
			{
				printf("%d: 'I'\n",i);
			}
			else if(letter == 'o')
			{
				printf("%d: 'O'\n",i);
			}
			else if(letter == 'u')
			{
				printf("%d: 'U'\n",i);
			}
			else if(letter == 'y')
			{
				if(i > 2)
				{
					printf("%d: 'Y'\n",i);
				}
			}
			else
			{
				printf("%d: %c is not a vowel\n",i,letter);
			}
		}

	}

	return 0;
}
