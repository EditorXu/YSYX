#include<stdio.h>
int main()
{
	char *argv[] = { "California", "Oregon","Washington", "Texas"};
	int num_states = 4;
	char *states[num_states];
	
	for(int i =0;i <num_states;i++)
	{
		states[i] = argv[i];
	}

	int i = 0;

	while(i < num_states)
	{
		printf("state %d: %s\n", i, states[i]);
		i++;
	}

	return 0;
}
