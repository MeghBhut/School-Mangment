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
    int Marks;
};
struct Course{
    char course_name[50];
    int strength;
    int course_fee;
};

int main(){
    printf("Welcome to School Managing System."); // taking input action from user.
    while (1)
    {
        int choice;
        printf("\n======================================================\n");
        printf("Choose option From following: \n");
        printf("1.Add New Student\n");
        printf("2.Add New Course\n");
        printf("3.View all Course\n");
        printf("4.View all Student\n");
        printf("5.Edit Course\n");
        printf("6.Edit Student\n");
        printf("7.Fee installment\n");
        printf("8.Grades of Student\n");
        printf("9.Remove student\n");
        printf("10.Remove Course\n");
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
        if(choice == 3)
        {
            View_All_Course();
        }
        if(choice == 4)
        {
            View_All_Student();
        }
        if(choice == 5)
        {
            Edit_Course();
        }
        if(choice == 6)
        {
            Edit_Student();
        }
        if(choice == 7)
        {
            Fee_Installment();
        }
        if(choice == 8)
        {
            Grades_of_Student();
        }
        if(choice == 9)
        {
            Remove_Student();
        }
        if(choice == 10)
        {
            Remove_Course();
        }
        if(choice == 0)
        {
            printf("Thanks for using our System!");
            return 0;
        }
    }
    return 0;
}

void Add_Student()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    fclose(fs);
    FILE *fc = fopen("course.dat","ab");
    fclose(fc);
    FILE *temp = fopen("temp.dat","wb");
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
    s[No_of_student].Marks = 0;
    //fees managment.
    int fees_given;
    for (int i = 0; i < No_of_course; i++)
    {
        if(strcmp(s[No_of_student].course,c[i].course_name)==0)
        {
            printf("Fees need to pay for this course is: %d\n",c[i].course_fee);
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
    fclose(fc);
    fclose(fs);
     if (remove("course.dat") != 0) {
        printf("Error deleting old course.dat file.\n");
    } else {
        if (rename("temp.dat", "course.dat") != 0) {
            printf("Error renaming temp.dat to course.dat.\n");
        } else {
            printf("Course data updated successfully.\n");
        }
    }
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
    fclose(fc);
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    //Taking User inputs.
    getchar();
    printf("Enter New Course name: ");
    fgets(c[No_of_course].course_name,sizeof(c[No_of_course].course_name),stdin);
    c[No_of_course].course_name[strcspn(c[No_of_course].course_name,"\n")]='\0';
    printf("Enter Course Fee: ");
    scanf("%d",&c[No_of_course].course_fee);
    c[No_of_course].strength =0;
    fclose(fc);
    fc = fopen("course.dat","ab");
    fwrite(&c[No_of_course],sizeof(struct Course),1,fc);
    fclose(fc);
    printf("Course Created Sucessfully!");
}

void View_All_Course()
{
    //creating file if its not there.
    FILE *fc = fopen("course.dat","ab");
    fclose(fc);
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    //Printing Output.
    printf("%d",No_of_course);
    printf("\n------------------------------------------------------------\n");
    printf("%-10s | %-10s | %-5s","Course Name","Course Fee","Strength");
    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i < No_of_course; i++)
    {
        printf("%-10s | %-10d | %-5d",c[i].course_name,c[i].course_fee,c[i].strength);
    }
    printf("\n");
    fclose(fc);
}

void View_All_Student()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    fclose(fs);
    fs = fopen("student.dat","rb");
    int No_of_student = 0; // No of course default value.
    struct Student s[100]; // making arry of course structure.
    No_of_student = fread(s,sizeof(struct Course),100,fs); // reading from file and storing no of course value.
    //Printing Output.
    printf("\n------------------------------------------------------------\n");
    printf("%-10s | %-10s | %-5s","Student Name","Course","Fees Remmaining");
    printf("\n------------------------------------------------------------\n");
    for (int i = 0; i < No_of_student; i++)
    {
        printf("%-10s | %-10s | %-5d",s[i].name,s[i].course,s[i].Fee_remaining);
    }
    printf("\n");
    fclose(fs);
}

void Edit_Course()
{
    //creating file if its not there.
    FILE *fc = fopen("course.dat","ab");
    fclose(fc);
    FILE *temp = fopen("temp.dat","ab");
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    char edit_course_name[50];
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    View_All_Course();
    //Editing Course.
    getchar();
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
            printf("0.Exit\n");
            printf("your choice: ");
            scanf("%d",&changing_field);
            if(changing_field==1)
            {
                printf("Enter new Course name: ");
                fgets(c[i].course_name,sizeof(c[i].course_name),stdin);
                c[i].course_name[strcspn(c[i].course_name,"\n")]='\0';
            }
            else if(changing_field==2)
            {
                printf("Enter new Course Fee: ");
                scanf("%d",&c[i].course_fee);
            }
            else if(changing_field==0)
            {
                return;
            }
            else
            {
                printf("Invalid Iput");
                return;
            }
            fwrite(&c[i],sizeof(struct Course),1,temp);
        }
    }
    fclose(temp);
    fclose(fc);
    remove("course.dat");
    rename("temp.dat","course.dat");
    printf("Course Updated Sucessfully.");
}

void Edit_Student()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    fclose(fs);
    FILE *temp = fopen("temp.dat","ab");
    fs = fopen("student.dat","rb");
    int No_of_student = 0; // No of student default value.
    char edit_student_name[50];
    struct Student s[100]; // making arry of student structure.
    No_of_student = fread(s,sizeof(struct Student),100,fs); // reading from file and storing no of student value.
    View_All_Student();
    //Editing Course.
    getchar();
    printf("Enter Student name You want to Edit: ");
    fgets(edit_student_name,sizeof(edit_student_name),stdin);
    edit_student_name[strcspn(edit_student_name,"\n")]='\0';
    for (int i = 0; i < No_of_student; i++)
    {
        if(strcmp(edit_student_name,s[i].name)==0)
        {
            int changing_field;
            printf("what field you want to change: \n");
            printf("1.Student name\n");
            printf("2.student course\n");
            printf("0.Exit\n");
            printf("your choice: ");
            scanf("%d",&changing_field);
            if(changing_field==1)
            {
                getchar();
                printf("Enter new Student name: ");
                fgets(s[i].name,sizeof(s[i].name),stdin);
                s[i].name[strcspn(s[i].name,"\n")]='\0';
            }
            else if(changing_field==2)
            {
                printf("Enter new Course: ");
                scanf("%d",&s[i].course);
            }
            else if(changing_field==0)
            {
                return;
            }
            else
            {
                printf("Invalid Iput");
                return;
            }
            fwrite(&s[i],sizeof(struct Student),1,temp);
        }
    }
    fclose(temp);
    fclose(fs);
    remove("student.dat");
    rename("temp.dat","student.dat");
    printf("Student details Updated Sucessfully.");
}

void Grades_of_Student()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    fclose(fs);
    FILE *temp = fopen("temp.dat","ab");
    fs = fopen("student.dat","rb");
    int No_of_student = 0; // No of student default value.
    char edit_student_name[50];
    struct Student s[100]; // making arry of student structure.
    No_of_student = fread(s,sizeof(struct Student),100,fs); // reading from file and storing no of student value.
    View_All_Student();
    //Editing Course.
    getchar();
    printf("Enter Student name You want to add marks: ");
    fgets(edit_student_name,sizeof(edit_student_name),stdin);
    edit_student_name[strcspn(edit_student_name,"\n")]='\0';
    for (int i = 0; i < No_of_student; i++)
    {
        if(strcmp(edit_student_name,s[i].name)==0)
        {
            printf("Enter marks(out of 100): ");
            scanf("%d",&s[i].Marks);
            fwrite(&s[i],sizeof(struct Student),1,temp);
        }
    }
    fclose(temp);
    fclose(fs);
    remove("student.dat");
    rename("temp.dat","student.dat");
    printf("Student details Updated Sucessfully.");
}

void Remove_Course()
{
    //creating file if its not there.
    FILE *fc = fopen("course.dat","ab");
    fclose(fc);
    FILE *temp = fopen("temp.dat","ab");
    fc = fopen("course.dat","rb");
    int No_of_course = 0; // No of course default value.
    char remove_course_name[50];
    struct Course c[100]; // making arry of course structure.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    View_All_Course();
    //Editing Course.
    getchar();
    printf("Enter Course name You want to remove: ");
    fgets(remove_course_name,sizeof(remove_course_name),stdin);
    remove_course_name[strcspn(remove_course_name,"\n")]='\0';
    for (int i = 0; i < No_of_course; i++)
    {
        if(strcmp(remove_course_name,c[i].course_name)==0)
        {
            char sure_remove;
            printf("Are u surely want to remove this course.[y/n]: ");
            scanf(" %c",&sure_remove);
            if(sure_remove=='y')
            {
                continue;
            }
            else
            {
                fwrite(&c[i],sizeof(struct Course),1,temp);
            }
        }
        fwrite(&c[i],sizeof(struct Course),1,temp);
    }
    fclose(temp);
    fclose(fc);
    remove("course.dat");
    rename("temp.dat","course.dat");
    printf("Course Updated Sucessfully.");
}

void Remove_Student()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    fclose(fs);
    FILE *fc = fopen("course.dat","ab");
    fclose(fc);
    FILE *temp = fopen("temp.dat","ab");
    FILE *temp2 = fopen("temp2.dat","ab");
    fs = fopen("student.dat","rb");
    fc = fopen("course.dat","rb");
    int No_of_student = 0; // No of student default value.
    int No_of_course = 0; // No of course default value.
    char remove_student_name[50];
    struct Student s[100]; // making arry of student structure.
    struct Course c[100]; // making arry of course structure.
    No_of_student = fread(s,sizeof(struct Student),100,fs); // reading from file and storing no of student value.
    No_of_course = fread(c,sizeof(struct Course),100,fc); // reading from file and storing no of course value.
    View_All_Student();
    //Editing Course.
    getchar();
    printf("Enter Student name You want to remove: ");
    fgets(remove_student_name,sizeof(remove_student_name),stdin);
    remove_student_name[strcspn(remove_student_name,"\n")]='\0';
    for (int i = 0; i < No_of_student; i++)
    {
        if(strcmp(remove_student_name,s[i].name)==0)
        {
            char sure_remove;
            printf("Are u surely want to remove this student.[y/n]: ");
            scanf(" %c",&sure_remove);
            if(sure_remove=='y')
            {
                for (int j = 0; j < No_of_course; j++)
                {
                    if(strcmp(s[i].course,c[j].course_name)==0)
                    {
                        c[j].strength--;
                    }
                }
                continue;
            }
            else
            {
                fwrite(&s[i],sizeof(struct Student),1,temp);
            }
        }
        fwrite(&s[i],sizeof(struct Student),1,temp);
    }
    for (int j = 0; j < No_of_course; j++)
    {
        fwrite(&c[j],sizeof(struct Course),1,temp2);
    }
    fclose(temp);
    fclose(temp2);
    fclose(fs);
    fclose(fc);
    remove("student.dat");
    remove("course.dat");
    rename("temp.dat","student.dat");
    rename("temp2.dat","course.dat");
    printf("Student removed Sucessfully.");
}

void Fee_Installment()
{
    //creating file if its not there.
    FILE *fs = fopen("student.dat","ab");
    fclose(fs);
    FILE *fc = fopen("course.dat","ab");
    fclose(fc);
    FILE *temp = fopen("temp.dat","wb");
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
            printf("Name of student is: %s\n",s[i].name);
            printf("Fees Already Payed is: %d\n",s[i].Fee_payed);
            printf("Fees remaining to give is: %d\n",s[i].Fee_remaining);
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
                    if(strcmp(s[i].course,c[j].course_name)==0)
                    {
                        s[i].Fee_payed += fees_given;
                        s[i].Fee_remaining = c[j].course_fee-s[i].Fee_payed;
                        s[i].installment++;
                        if(s[i].Fee_remaining==0)
                        {
                            printf("Congratulation YOur all fees Payed.\n");
                        }
                    }
                    fwrite(&s[i],sizeof(struct Student),1,temp);
                }
                printf("Fee Installment updated.");
            }
        }
    }
    fclose(temp);
    fclose(fs);
    fclose(fc);
    remove("student.dat");
    rename("temp.dat","student.dat");
}
