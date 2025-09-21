#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student{
    int id;
    char name[20];
    char course[20];
    int Fee_payed;
    int Fee_remaining;
    int installment;
};
struct Course{
    char course_name[50];
    int strength;
    int course_fee;
};

int main(){
    printf("Welcome to School Managing System."); // taking input action from user.
    int choice;
    printf("\n======================================================\n");
    printf("Choose option From following: \n");
    printf("1.Add New Student\n");
    printf("2.Add New Course\n");
    printf("3.View all Course\n");
    printf("4.Edit Course\n");
    printf("5.Fee installment\n");
    printf("6.Grades of Student\n");
    printf("7.Remove student\n");
    printf("8.Remove division\n");
    printf("0.Exit\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    printf("\n======================================================\n");
    if(choice == 1)
    {
        Add_Student();
    }
    if(choice == 2)
    {
        Add_Course();
    }
    if(choice == 5)
    {
        Fee_Installment();
    }
    return 0;
}

void Add_Student()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    FILE *fc = fopen("course.dat","ab");
    FILE *temp = fopen("temp.dat","ab");
    fs = fopen("student.dat","rb");
    fc = fopen("course.dat","rb");
    int No_of_student = 0; // No of student default value.
    int No_of_course = 0; // No of course default value.
    struct Student s[100]; // making arry of student structure.
    struct Course c[100]; // making arry of course structure.
    No_of_student = fread(s,sizeof(struct Student),100,fs); // reading from file and storing no of student value.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    //Taking Details from user and storing value in arrys.
    printf("Enter Student id: ");
    scanf("%d",&s[No_of_student].id);
    getchar();
    printf("Enter Student Name: ");
    fgets(s[No_of_student].name,sizeof(s[No_of_student].name),stdin);
    s[No_of_student].name[strcspn(s[No_of_student].name,"\n")] = '\0';
    printf("Enter Student Course name: ");
    fgets(s[No_of_student].course,sizeof(s[No_of_student].course),stdin);
    s[No_of_student].course[strcspn(s[No_of_student].course,"\n")] = '\0';
    //fees managment.
    int fees_given;
    for (int i = 0; i < No_of_course; i++)
    {
        if(s[No_of_student].course==c[i].course_name)
        {
            printf("Fees need to pay for this course is: %d",c[i].course_name);
            printf("Enter Fees Payed: ");
            scanf("%d",&fees_given);
            if(fees_given==0)
            {
                s[No_of_student].Fee_payed = 0;
                s[No_of_student].Fee_remaining = 0;
                s[No_of_student].installment = 0;
            }
            else
            {
                s[No_of_student].Fee_payed = fees_given;
                s[No_of_student].Fee_remaining = c[i].course_fee-fees_given;
                s[No_of_student].installment = 1;
            }
            c[i].strength++;
        }
        fwrite(&c[i],sizeof(struct Course),1,temp);
    }
    fclose(temp);
    remove("course.dat");
    rename("temp.dat","course.dat");
    fclose(fc);
    //writing new arry element in file.
    fs = fopen("student.dat","ab");
    fwrite(&s[No_of_student],sizeof(struct Student),1,fs);
    fclose(fs);
    printf("Student Created Suceesfully.");
}

void Add_Course()
{
    //creating file if its not there.
    FILE *fc = fopen("course.dat","ab");
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    //Taking User inputs.
    printf("Enter New Course name: ");
    fgets(c[No_of_course].course_name,sizeof(c[No_of_course].course_name),stdin);
    c[No_of_course].course_name[strcspn(c[No_of_course].course_name,"\n")]='\0';
    printf("Enter Course Fee: ");
    scanf("%d",c[No_of_course].course_fee);
    c[No_of_course].strength =0;
    fwrite(&c[No_of_course],sizeof(struct Course),1,fc);
    fclose(fc);
}

void View_All_Course()
{
    //creating file if its not there.
    FILE *fc = fopen("course.dat","ab");
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    //Printing Output.
    printf("\n------------------------------------------------------------\n");
    printf("%-10s | %-10s | %-5s","Course Name","Course Fee","Strength");
    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i < No_of_course; i++)
    {
        printf("%-10s | %-10d | %-5d",c[i].course_name,c[i].course_fee,c[i].strength);
    }
}
void Edit_Course()
{
    //creating file if its not there.
    FILE *fc = fopen("course.dat","ab");
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    char edit_course_name[50];
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    View_All_Course();
    //Editing Course.
    printf("Enter Course name You want to Edit: ");
    fgets(edit_course_name,sizeof(edit_course_name),stdin);
    edit_course_name[strcspn(edit_course_name,"\n")]='\0';
    for (int i = 0; i < No_of_course; i++)
    {
        if(strcmp(edit_course_name,c[i].course_name)==0)
        {
            int changing_field;
            printf("what field you want to change: \n");
            printf("1.Course name\n");
            printf("2.Course fee\n");
            printf("your choice: ");
            scanf("%d",&changing_field);
            if(changing_field==1)
            {
                
            }
        }
    }
}

void Fee_Installment()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    FILE *fc = fopen("course.dat","ab");
    fs = fopen("student.dat","rb");
    fc = fopen("course.dat","rb");
    int No_of_student = 0; // No of student default value.
    int No_of_course = 0; // No of course default value.
    struct Student s[100]; // making arry of student structure.
    struct Course c[100]; // making arry of course structure.
    No_of_student = fread(s,sizeof(struct Student),100,fs); // reading from file and storing no of student value.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    int Filter_student_id;
    //Taking student id from user.
    printf("Enter Student id You want to edit Fee installment: ");
    scanf("%d",&Filter_student_id);
    //running loop and checking every id to user inputed id and getting index i for which we need to change fee installment.
    for (int i = 0; i < No_of_student; i++)
    {
        if(Filter_student_id==s[i].id)
        {
            printf("Name of student is: %s",s[i].name);
            printf("Fees Already Payed is: %s",s[i].Fee_payed);
            printf("Fees remaining to give is: %s",s[i].Fee_remaining);
            printf("Want To procced intallment %d[y/n]",s[i].installment);
            char procced_choice;
            scanf(" %c",&procced_choice);
            if(procced_choice=='y')
            {
                int fees_given;
                printf("Enter next installment payment amount: ");
                scanf("%d",&fees_given);
                for (int j = 0; j < No_of_course; j++)
                {
                    if(s[i].course==c[j].course_name)
                    {
                        s[i].Fee_payed += fees_given;
                        s[i].Fee_remaining = c[i].course_fee-s[i].Fee_payed;
                        s[i].installment++;
                        if(s[i].Fee_remaining==0)
                        {
                            printf("Congratulation YOur all fees Payed.");
                        }
                    }
                }
                printf("Fee Installment updated.");
            }
        }
    }
}