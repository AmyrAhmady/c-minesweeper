#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 14
#define COLUMNS 30

char field[ROWS][COLUMNS];
int fieldStat[ROWS][COLUMNS];

void FirstTimeInit();
void PrintField();
void ClearField();
int CountSidesBombs(int x, int y);
void CheckField(int x, int y);
void MakeBombs();

int main(void)
{
	int x, y;
	FirstTimeInit();
	PrintField();
	MakeBombs();

	while (1)
	{
		char cmd[3];
		fgets(cmd, sizeof(cmd) * 3, stdin);
		if (strcmp(cmd, "fla\n") == 0) // fla baraye flag kardane ye khune (parcham bezari)
		{
			scanf("%d%d", &x, &y);
			if (field[x][y] == '#')
			{
				field[x][y] = 'P'; // parcham gozashte shode
				fieldStat[x][y] = 2; // parcham gozashte shode
				PrintField();
			}
		}
		else if (strcmp(cmd, "ufl\n") == 0) // unfl baraye unflag kardane ye khune (parchamo bardari)
		{
			scanf("%d%d", &x, &y);
			if (field[x][y] == 'P')
			{
				field[x][y] = '#'; // parcham bardashte shode
				fieldStat[x][y] = 0; // parcham bardashte shode
				PrintField();
			}
		}
		else if (strcmp(cmd, "cho\n") == 0) // cho baraye entekhabe ye khune
		{
			scanf("%d%d", &x, &y);
			if (fieldStat[x][y] == 1)
			{
				printf("Game Over"); // entekhabe bomb
				PrintField();
			}
			else
			{
				CheckField(x, y); // check kardane khuneye entekhab shode
				PrintField(); // printe zamine jadide bazi
			}
		}
	}

	return 0;
}

void FirstTimeInit()
{
	int i, j;
	for (i = 0; i < ROWS; i++) // sefr krdn hame khna ha
	{
		for (j = 0; j < COLUMNS; j++)
		{
			field[i][j] = '#'; // hame khune ha makhfi shan
			fieldStat[i][j] = 0; // hame khune ha flageshun 0 she (bedune bomb)
		}
	}
}

void PrintField()
{
	ClearField();
	int i, j;
	for (i = 0; i < ROWS; i++) // rasme zamin bazi
	{
		// printe shomare haye sotun ha
		if (i == 0)
		{
			for (int x = 0; x < COLUMNS; x++)
			{
				if (x < 10) // printe adade kuchik tar az 10 ba yek space ezafe baraye andaze haye barabar
				{
					if (x == 0)
						printf("   %i ", x); // printe adade 0 dar sotun ba 3 space poshte an
					else
						printf(" %i ", x);
				}
				else // printe adade do raghami
					printf("%i ", x);
			}
			printf("\n");
			// printe marze balaye bazi
			for (int x = 0; x < COLUMNS * 3 + 4; x++)
				printf("-");
			printf("\n");
		}

		// printe zamine bazi
		for (j = 0; j < COLUMNS; j++)
		{
			// printe marze samte chape bazi
			if (j == 0)
				printf("| ");
			// printe character ha baraye zamine asli
			printf(" %c ", field[i][j], sizeof(char));
		}
		// printe marz va adade satr ha samte raste bazi
		printf(" | %i\n", i);
	}
	// printe marze paine bazi
	for (int x = 0; x < COLUMNS * 3 + 4; x++)
		printf("-");
	printf("\n");
}

void MakeBombs()
{
	int i;
	int random_x, random_y; //tolid adad tasadofi
	srand(time(NULL));

	for (i = 0; i < 40; i++) //min gozari khane ha
	{
		random_x = rand() % ROWS;
		random_y = rand() % COLUMNS;
		if (fieldStat[random_x][random_y] == 1)
		{
			i = i - 1;
		}
		else
		{
			fieldStat[random_x][random_y] = 1;
		}
	}
}

int CountSidesBombs(int x, int y)
{
	int min = 0;

	if (fieldStat[x - 1][y] == 1) // chap
		min++;
	if (fieldStat[x + 1][y] == 1) // rast
		min++;
	if (fieldStat[x][y - 1] == 1) // bala
		min++;
	if (fieldStat[x][y + 1] == 1) // pain
		min++;
	if (fieldStat[x - 1][y - 1] == 1) // chap-bala
		min++;
	if (fieldStat[x + 1][y + 1] == 1) // rast-pain
		min++;
	if (fieldStat[x + 1][y - 1] == 1) // rast-bala
		min++;
	if (fieldStat[x - 1][y + 1] == 1) // chap-pain
		min++;

	return min;
}

void CheckField(int x, int y)
{
	int min = 0;
	int i = 0;
	min = CountSidesBombs(x, y);
	if (min != 0)
	{
		field[x][y] = (char)((int)min + (int)'0');
		fieldStat[x][y] = 2;
		PrintField();
	}
	else
	{
		field[x][y] = ' ';
		fieldStat[x][y] = 2;

		if (fieldStat[x + 1][y] != 2 && (x + 1 >= 0 && x + 1 <= ROWS - 1 && y >= 0 && y <= COLUMNS - 1))
			CheckField(x + 1, y);

		if (fieldStat[x][y + 1] != 2 && (x >= 0 && x <= ROWS - 1 && y + 1 >= 0 && y + 1 <= COLUMNS - 1))
			CheckField(x, y + 1);

		if (fieldStat[x - 1][y] != 2 && (x - 1 >= 0 && x - 1 <= ROWS - 1 && y >= 0 && y <= COLUMNS - 1))
			CheckField(x - 1, y);

		if (fieldStat[x][y - 1] != 2 && (x >= 0 && x <= ROWS - 1 && y - 1 >= 0 && y - 1 <= COLUMNS - 1))
			CheckField(x, y - 1);

		if (fieldStat[x + 1][y + 1] != 2 && (x + 1 >= 0 && x + 1 <= ROWS - 1 && y + 1 >= 0 && y + 1 <= COLUMNS - 1))
			CheckField(x + 1, y + 1);

		if (fieldStat[x - 1][y - 1] != 2 && (x - 1 >= 0 && x - 1 <= ROWS - 1 && y - 1 >= 0 && y - 1 <= COLUMNS - 1))
			CheckField(x - 1, y - 1);

		if (fieldStat[x + 1][y - 1] != 2 && (x + 1 >= 0 && x + 1 <= ROWS - 1 && y - 1 >= 0 && y - 1 <= COLUMNS - 1))
			CheckField(x + 1, y - 1);

		if (fieldStat[x - 1][y + 1] != 2 && (x - 1 >= 0 && x - 1 <= ROWS - 1 && y + 1 >= 0 && y + 1 <= COLUMNS - 1))
			CheckField(x - 1, y + 1);
	}
}

void ClearField()
{
	system("cls");
}
