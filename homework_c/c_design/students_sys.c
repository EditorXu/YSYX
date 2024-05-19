#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define KEY 5

typedef struct Student {
    char first_name[50];
    char last_name[50];
    char id[13];
    int score;
    int retake;
		int rank;
    char gpa[3];
    int num;
} Student;

void Students_printf(Student students[]){
	printf("Name_f\t Name_l\t  stu_id\t score\t retake\t GPA\t rank\n");
  for(int i = 0; i < students->num; i++){
    printf("%-8s %-8s %-14s %-7d %-7d %-7s %-7d\n", students[i].first_name, students[i].last_name, students[i].id, students[i].score, students[i].retake, students[i].gpa, students[i].rank);
  }
}

void Students_sort(Student students[]){
	int number = students->num;
	for(int i = 0; i < number; i++){
		for(int j = i; j > 0; j--){
			if(students[j].score > students[j-1].score){
				Student tmp = students[j];
				students[j] = students[j-1];
				students[j-1] = tmp;
			}
		}
	}
	students->num = number;
}

void Students_rank(Student students[])
{
	Student tmp[100];
	for(int i = 0; i < students->num; i++){
		tmp[i]= students[i];
	}

	Students_sort(tmp);
	tmp[0].rank = 1;
	if(students->num > 1){
		for(int i = 1; i < students->num; i++){
			if(tmp[i].score == tmp[i-1].score){
				tmp[i].rank = tmp[i-1].rank;
				}
			else if(tmp[i].score < tmp[i-1].score){
				tmp[i].rank = tmp[i-1].rank + 1;
			}
		}
	}

	for(int i = 0; i < students->num; i++){
		for(int j = 0; j < students->num; j++){
			if(strcmp(students[i].id, tmp[j].id) == 0){
				students[i].rank = tmp[j].rank;
			}
		}
	}
}

void Students_add(Student students[]){
				scanf("%s %s %s %d", students[students->num].first_name, students[students->num].last_name, students[students->num].id, &students[students->num].score);
        if (strlen(students[students->num].id) == 12) {
            // Calculate retake
            students[students->num].retake = (students[students->num].id[3] == '2') ? 0 : 1;
            if (students[students->num].score >= 93) {
                strcpy(students[students->num].gpa, "A+");
            } else if (students[students->num].score >= 85) {
                strcpy(students[students->num].gpa, "A");
            } else if (students[students->num].score >= 80) {
                strcpy(students[students->num].gpa, "B+");
            } else if (students[students->num].score >= 75) {
                strcpy(students[students->num].gpa, "B");
            } else if (students[students->num].score >= 70) {
                strcpy(students[students->num].gpa, "C+");
            } else if (students[students->num].score >= 65) {
                strcpy(students[students->num].gpa, "C");
            } else if (students[students->num].score >= 60) {
                strcpy(students[students->num].gpa, "D");
            } else if (students[students->num].score >= 0){
                strcpy(students[students->num].gpa, "F");
            }
            students->num++;
						Students_rank(students);
        }
				else{
					printf("\n%s %s the id is wrong. \nThis student's imformation doesn't input the database\n",students[students->num].first_name, students[students->num].last_name);
				}
}

void Students_input(Student students[]) {
		printf("How many students do you want to input?");
		int n;
		scanf("%d",&n);
    students->num = 0;

		for(int i = 0; i < n; i++){
				Students_add(students);
    }
}

void Students_delete(Student students[]){
	printf("Please input the id of the student deleted.\n");
	char delete[13];
	scanf("%s",delete);
	
	for(int i = 0; i < students->num; i++){
		if(strcmp(delete,students[i].id) == 0){
			for(int j = i; j < students->num - 1; j++){
				students[i] = students[i+1];
			}

			students->num--;
			break;
		}
	}
	Students_rank(students);
	Students_printf(students);
}

void Students_search(Student students[]){
	printf("Please input the id what you want to search.");
	char id[13];
	scanf("%s",id);

	for(int i = 0; i < students->num; i++){
		if(strcmp(students[i].id,id) == 0){
			printf("\nName_f\t Name_l\t  stu_id\t score\t retake\t GPA\t rank\n");
      printf("%-8s %-8s %-14s %-7d %-7d %-7s %-7d\n", students[i].first_name, students[i].last_name, students[i].id, students[i].score, students[i].retake, students[i].gpa, students[i].rank);
    }
	}
}

void Students_sort_by_score(Student students[]){
	Students_sort(students);
	Students_printf(students);
}

void encrypt(int key, char *scores) {
    int len = strlen(scores);
    for (int j = 0; j < len; j++) {
		if(scores[j] != ' '){
            int digit = scores[j] - '0';  // 将字符转换为整数
            digit = (digit + key) % 10;
            scores[j] = '0' + digit;  // 将整数转换回字符
        }
	}
}

void Students_encrypt(Student students[]) {
    char scores[1000] = {0};  // 假设总长度不超过1000
	for (int i = 0; i < students->num; i++) {
        char score[10];
        sprintf(score, "%d ", students[i].score);  // 注意添加空格
        strcat(scores, score);
    }
    scores[strlen(scores) - 1] = '\0';  // 移除最后一个多余的空格
	encrypt(KEY, scores);
    printf("Encrypted Scores: %s\n",scores);
	/*
	for (int i = 0; i < count; i++) {
        if (i > 0) printf(" ");
        printf("%s", scores[i]);
    }
	*/
    printf("\n");
}

void Students_decrypt(Student students[]) {
    printf("Decrypted Scores: ");
    for (int i = 0; i < students->num; i++) {
		printf("%d ",students[i].score);
    }
    printf("\n");
}

void Students_analysis(Student students[]) {
    int counts[8] = {0};  // A+, A, B+, B, C+, C, D, F
    char *grades[] = {"A+", "A", "B+", "B", "C+", "C", "D", "F"};
    for (int i = 0; i < students->num; i++) {
        for (int j = 0; j < 8; j++) {
            if (strcmp(students[i].gpa, grades[j]) == 0) {
                counts[j]++;
                break;
            }
        }
    }
    printf("GPA Analysis:\n");
    for (int i = 0; i < 8; i++) {
        printf("%s: %d\n", grades[i], counts[i]);
    }
}

int main() {
    Student students[100];
    Students_input(students);

		printf(" Okay, data upload finished. What do you what to do next? You can enter a number to tell me.\n");
		printf("1 add\n2 delete\n3 search\n4 sort by score\n5 encrypt\n6 decrypt\n7 analysis\n8 printf\n0 exit\n");
		
		while(1){
			int action;
			scanf("%d",&action);

			switch(action){
				case 0:
					exit(1);
					break;
				case 1:
					Students_add(students);
					break;
				case 2:
					Students_delete(students);
					break;
				case 3:
					Students_search(students);
					break;
				case 4:
					Students_sort_by_score(students);
					break;
				case 5:
					Students_encrypt(students);
					break;
				case 6:
					Students_decrypt(students);
					break;
				case 7:
					Students_analysis(students);
					break;
				case 8:
					Students_printf(students);
					break;
				default:
					printf("Input wrong! Please input again!");
				}
				printf("\n Do you still need my service? You can enter a number to tell me. \n");
				printf("1 add\n2 delete\n3 search\n4 sort by score\n5 encrypt\n6 decrypt\n7 analysis\n8 printf\n0 exit\n");
		}

    return 0;
}

