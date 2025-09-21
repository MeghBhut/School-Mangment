#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student{
    int id;
    char name[20];
    int fees_payed;
};

int main(){
    printf("Welcome to School Managing System.");
    int choice;
    printf("\n======================================================\n");
    printf("Choose option From following: \n");
    printf("1.Add Student\n");
    printf("2.Add New Division\n");
    printf("3.Fee installment\n");
    printf("4.Grades of Student\n");
    printf("5.Remove student\n");
    printf("6.Remove division\n");
    printf("0.Exit\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    printf("\n======================================================\n");
    if(choice == 1)
    {

    }
    return 0;
}

void Add_Student()
{
    FILE *fp = fopen("student.dat","ab");
    fp = fopen("student.dat","rb");
    int No_of_student = 0;
    struct Student s[100];
    No_of_student = fread(s,sizeof(struct Student),100,fp);
    printf("Enter Student id: ");
    scanf("%d",&s[No_of_student].id);
    printf("Enter Student Name: ");
    fgets(s[No_of_student].name,sizeof(s[No_of_student].name),stdin);
    fp = fopen("student.dat","ab");
}