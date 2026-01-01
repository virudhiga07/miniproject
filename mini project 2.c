#include <stdio.h>
#include <stdlib.h>

struct Question {
    int qno;
    char question[100];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char optionD[50];
    char correctOption;
};
void addQuestion();
void displayQuestions();
void takeQuiz();
void viewScores();
int main() {
    int choice;

    do {
        printf("\n-----------------------------------------\n");
        printf(" Quiz Management System\n");
        printf("-----------------------------------------\n");
        printf("1. Add Question\n");
        printf("2. Display Questions\n");
        printf("3. Take Quiz\n");
        printf("4. View Scores\n");
        printf("5. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addQuestion(); break;
            case 2: displayQuestions(); break;
            case 3: takeQuiz(); break;
            case 4: viewScores(); break;
            case 5: printf("Exiting the program...\nThank you for using Quiz Management System!\n");
                    break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 5);

    return 0;
}void addQuestion() {
    FILE *fp;
    struct Question q;

    fp = fopen("quiz.txt", "a");
    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Question No: ");
    scanf("%d", &q.qno);
    getchar();

    printf("Enter Question: ");
    gets(q.question);

    printf("Enter Option A: ");
    gets(q.optionA);

    printf("Enter Option B: ");
    gets(q.optionB);

    printf("Enter Option C: ");
    gets(q.optionC);

    printf("Enter Option D: ");
    gets(q.optionD);

    printf("Enter Correct Option (A/B/C/D): ");
    scanf(" %c", &q.correctOption);

    fprintf(fp, "%d\n%s\n%s\n%s\n%s\n%s\n%c\n",
            q.qno, q.question,
            q.optionA, q.optionB,
            q.optionC, q.optionD,
            q.correctOption);

    fclose(fp);
    printf("Question added successfully!\n");
}
void displayQuestions() {
    FILE *fp;
    struct Question q;

    fp = fopen("quiz.txt", "r");
    if (fp == NULL) {
        printf("No questions available.\n");
        return;
    }

    printf("\n-----------------------------------------\n");

    while (fscanf(fp, "%d\n", &q.qno) != EOF) {
        fgets(q.question, 100, fp);
        fgets(q.optionA, 50, fp);
        fgets(q.optionB, 50, fp);
        fgets(q.optionC, 50, fp);
        fgets(q.optionD, 50, fp);
        fscanf(fp, " %c\n", &q.correctOption);

        printf("Q%d: %s", q.qno, q.question);
        printf("A) %s", q.optionA);
        printf("B) %s", q.optionB);
        printf("C) %s", q.optionC);
        printf("D) %s\n", q.optionD);
        printf("-----------------------------------------\n");
    }

    fclose(fp);
}void takeQuiz() {
    FILE *fp, *fs;
    struct Question q;
    char answer;
    int score = 0, total = 0;

    fp = fopen("quiz.txt", "r");
    if (fp == NULL) {
        printf("No quiz available!\n");
        return;
    }

    while (fscanf(fp, "%d\n", &q.qno) != EOF) {
        fgets(q.question, 100, fp);
        fgets(q.optionA, 50, fp);
        fgets(q.optionB, 50, fp);
        fgets(q.optionC, 50, fp);
        fgets(q.optionD, 50, fp);
        fscanf(fp, " %c\n", &q.correctOption);

        printf("\nQ%d: %s", q.qno, q.question);
        printf("A) %s", q.optionA);
        printf("B) %s", q.optionB);
        printf("C) %s", q.optionC);
        printf("D) %s", q.optionD);

        printf("Enter your answer (A/B/C/D): ");
        scanf(" %c", &answer);

        if (answer == q.correctOption)
            score++;

        total++;
    }

    fclose(fp);

    printf("\nYour Score: %d / %d\n", score, total);

    fs = fopen("scores.txt", "a");
    fprintf(fs, "Score: %d / %d\n", score, total);
    fclose(fs);
}
void viewScores() {
    FILE *fp;
    char ch;

    fp = fopen("scores.txt", "r");
    if (fp == NULL) {
        printf("No scores recorded yet.\n");
        return;
    }

    printf("\n----- Previous Scores -----\n");
    while ((ch = fgetc(fp)) != EOF)
        printf("%c", ch);

    fclose(fp);
}


