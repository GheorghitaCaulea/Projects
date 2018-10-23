#ifndef __MAIN_H__
#define __MAIN_H__

struct coord
{
	int line;
	int col;
};
/*Declar structura care tine lista ce reprezinta corpul serpilor.*/
typedef struct cel {
	struct cel *pre, *urm;
	struct coord lc;
} TCel, *TLDI, **TL;

/*Adaug campuri pentru corpul sarpelui, pentru coada si pentru coordonatele cozii inainte de mutare.*/
struct snake
{
	struct coord head;
	int encoding;
	char direction;
	TLDI body;
	TLDI last;
	int line_old_tail, col_old_tail;
};

void print_world(char *file_name, int num_snakes, struct snake *snakes,
	int num_lines, int num_cols, int **world);

void read_data(char *file_name, int *num_snakes, struct snake **snakes,
	int *num_lines, int *num_cols, int ***world);

void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	struct snake *snakes, int step_count, char *file_name);

#endif
