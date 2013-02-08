#include <stdio.h>
#include <stdlib.h>

struct in_data{
	unsigned int in;
	unsigned int out;
};

struct in_data raw_data[] = { {100,180}, {200,350}, {300,400}, {400, 450}, {500, 510}, {600, 580}, {700, 650}, {800, 700}, {150, 100} };

#define ARR_SIZE(a) (sizeof(a)/sizeof((a)[0]))

int comparer(const void *_v1, const void *_v2)
{
	in_data *v1 = (in_data*)_v1;
	in_data *v2 = (in_data*)_v2;
	if(v1->out == v2->out)
		return 0;
	else if(v1->out > v2->out)
		return 1;
	return -1;
}

unsigned int calc(unsigned int x)
{
	if(raw_data[0].out > x) // too low
		return raw_data[0].in;
	
	int i, j;

	for(i = 0; i < ARR_SIZE(raw_data); ++i)
	{
		j = i + 1;
		if(j == ARR_SIZE(raw_data))	// behind last
			return raw_data[i].in;

		if(raw_data[j].out >= x)
			break;
	}

// 	if(i == ARR_SIZE(raw_data))
// 	{
// 		return raw_data[ARR_SIZE(raw_data)-1].in; // take last
// 	}

	int x1, x2, y1, y2;
	y1 = raw_data[i].in;
	y2 = raw_data[j].in;
	x1 = raw_data[i].out;
	x2 = raw_data[j].out;

	return ((int)(x-x1)*(y2-y1)/(x2-x1)+y1);
}

void main()
{

	qsort(raw_data, (sizeof(raw_data)/sizeof(raw_data[0])), sizeof(in_data), comparer);

	unsigned int out_min = -1, out_max = 0;

	unsigned int i;

	for(i = 0; i < (sizeof(raw_data)/sizeof(raw_data[0])); ++i)
	{
		if(raw_data[i].out > out_max)
			out_max = raw_data[i].out;
		if(raw_data[i].out < out_min)
			out_min = raw_data[i].out;
	}

	printf("%5s, %5s\n", "cmd", "real");
	for(i = 0; i < (sizeof(raw_data)/sizeof(raw_data[0])); ++i)
	{
		printf("%5d, %5d\n", raw_data[i].in, raw_data[i].out);
	}
// 	i = 50; printf("%5d -> %5d\n", i, calc(i));
// 	i = 110; printf("%5d -> %5d\n", i, calc(i));
// 	i = 220; printf("%5d -> %5d\n", i, calc(i));
// 	i = 333; printf("%5d -> %5d\n", i, calc(i));

	printf("\n%5s, %5s\n", "cmd", "out");
	for(i = 0; i <= out_max; i+=20)
	{
		printf("%5d, %5d\n", i, calc(i));
	}

    return;
}
