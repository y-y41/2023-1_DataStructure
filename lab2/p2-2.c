#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char *name;
	int student_id;
	char *major;
} student;

int main(int argc, char** args)
{
	char *input_path, *output_path;
	FILE *fi, *fo;

	int num;
	int i;

	student* students;

	input_path = args[1];
	output_path = args[2];

	fi = fopen(input_path, "r");
	fo = fopen(output_path, "w");

	fscanf(fi, "%d", &num);

	students = (student*) malloc(sizeof(student) * num);

	for (i=0; i<num; i++) {
		students[i].name = (char*) malloc(sizeof(char) * 30);
		students[i].major = (char*) malloc(sizeof(char) * 30);
		fscanf(fi, "%s %d %s", students[i].name, &students[i].student_id, students[i].major);
		fprintf(fo, "%-30s %-30d %-30s\n", students[i].name, students[i].student_id, students[i].major);
	}

	for (i=0; i<num; i++) {
		free(students[i].name);
		free(students[i].major);
	}
	free(students);

	fclose(fi);
	fclose(fo);
}

