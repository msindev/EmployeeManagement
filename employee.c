#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>

static struct termios old, new;

static struct employee_data
{
	char name[100],position[100],qualification[100];
	int age,emp_id,work_exp;
	float salary;
	long int phone;
	char certifications[200];
	char prog_lang[100];
}personal;

void head_disp();;
void emp_append();
void emp_delete();
void emp_modify();
void emp_displayAll();
void emp_display();
void emp_search();
void initTermios(int);
void resetTermios();
char getch_(int);
char getch();
char getche();

#define size 1

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}

int main(void)
{
	FILE *data;
	int menu_choice;
	char create;
	head_disp();
	data = fopen("employeeRecord.txt","r+");
	if(data==NULL)
	{
		printf("\n\t Employee Database Not Found!\n Press N key to create new Database.");
		printf("\n\tTo EXIT, press Enter key\n");
		create = getche();
		if(tolower(create)=='n')
		{
			data = fopen("employeeRecord.txt","w+");
			printf("\n\tEmployee Record Database has been created in the current directory.\n");
			printf("\n\tYou must Restart the Application\nPress Enter key to continue.\n");
			char x;
			x = getch();
			exit(0);
		}
		else
		{	
			printf("\n\n\tThank You for using this Application.\n");
			printf("\n\n\tApplication will EXIT Now.");
			exit(0);
		}
	}
	while(1)
	{
		head_disp();;
		printf("\n \t 1.Add New Employee");
		printf("\n \t 2.Modify an Employee's Record");
		printf("\n \t 3.Search for an Employee");
		printf("\n \t 4.Delete an Employee Record");
		printf("\n \t 5.Display All Employee's Record");
		printf("\n \t 6.Display an Employee Record (Employee ID/Name Required)");
		printf("\n \t Enter any number to EXIT");
		printf("\n\n \tINPUT:\t"); 
		scanf("%d",&menu_choice);
		switch(menu_choice)
		{
			case 1:
					emp_append();
					break;
			case 2:
					emp_modify();
					break;
			case 3:
					emp_search();
					break;
			case 4:
					emp_delete();
					break;
			case 5:
					emp_displayAll();
					break;
			case 6:
					emp_display();
					break;
			default:
					head_disp();
					printf("\n\n\tThank You for using this Application.\n");
					exit(0);
		}
	}
	return 0;
}

void head_disp()
{
	system("clear");
	printf("\n\n\t\t\t************************************************");
	printf("\n\t  \t\t**                                            **");
	printf("\n\t  \t\t**      EMPLOYEE MANAGEMENT SOFTWARE          **");
	printf("\n\t  \t\t**                                            **");
	printf("\n\t\t\t************************************************\n");
}                                             

void emp_append()
{
	FILE *data;
	data = fopen("employeeRecord.txt","a");
	head_disp();;
	printf("\n \tEmployee ID:\t");
	scanf("%d",&personal.emp_id);
	printf("\n \tEmployee Name:\t");
	scanf("%s",personal.name);
	printf("\n \tEmployee Position:\t");
	scanf("%s",personal.position);
	printf("\n \tEmployee Age:\t");
	scanf("%d",&personal.age);
	printf("\n \tEmployee Work Experience:\t");
	scanf("%d",&personal.work_exp);
	printf("\n \tEmployee Salary:\t");
	scanf("%f",&personal.salary);
	printf("\n \tEmployee Phone Number:\t");
	scanf("%ld",&personal.phone);
	printf("\n \tEmployee Qualifications:\t");
	scanf("%s",personal.qualification);
	printf("\n \tEmployee Certifications:\t");
	scanf("%s",personal.certifications);
	printf("\n \tProgramming languages Known:\t");
	scanf("%s",personal.prog_lang);
	if(fwrite(&personal,sizeof(personal),size,data)!=size)
	{
		printf("\n\tError in Writing to File.");
		exit(0);
	}
	else
	{
		printf("\n\tEmployee Record Successfully Written.");
	}
	fclose(data);
	printf("\n\n\tPress 1 to Continue and 0 to EXIT");
	printf("\n\n\tINPUT:\t");
	int exit_status;
	scanf("%d",&exit_status);
	if(exit_status!=1)
	{
		head_disp();
		printf("\n\n\tThank You for Using this Application.\n");
		exit(0);
	}
}

void emp_modify()
{
	head_disp();;
	FILE *data;
	int id,found=0;
	data = fopen("employeeRecord.txt","r+");
	printf("\n\tEnter Employee ID to Edit Record:\t");
	scanf("%d",&id);
	while(fread(&personal,sizeof(personal),size,data)==size)
	{
		if(personal.emp_id == id)
		{
			found = 1;
			printf("\n\tEXISTING RECORD IS......");
			printf("\n\n\tEMPLOYEE ID:\t%d",personal.emp_id);
			printf("\n\tEMPLOYEE NAME:\t%s",personal.name);
			printf("\n\tEMPLOYEE POSITION:\t%s",personal.position);
			printf("\n\tEMPLOYEE AGE:\t%d",personal.age);
			printf("\n\tEMPLOYEE QUALIFICATIONS:\t%s",personal.qualification);
			printf("\n\tEMPLOYEE CERTIFICATIONS:\t%s",personal.certifications);
			printf("\n\tEMPLOYEE WORK EXPERIENCE:\t%d",personal.work_exp);
			printf("\n\tEMLOYEE SALARY:\t%.2f",personal.salary);
			printf("\n\tEMPLOYEE PHONE NUMBER:\t%ld",personal.phone);
			printf("\n\tPROGRAMMING LANGUAGES KNOWN:\t%s",personal.prog_lang);
			printf("\n\n************MODIFYING EMPLOYEE RECORD**************\n");
			printf("\n\tEnter New Employee Name:\t");
			scanf("%s",personal.name);
			printf("\n\tEnter New Employee Position:\t");
			scanf("%s",personal.position);
			printf("\n\tEnter New Employee Age:\t");
			scanf("%d",&personal.age);
			printf("\n\tEnter New Employee Qualifications:\t");
			scanf("%s",personal.qualification);
			printf("\n\tEnter New Employee Certifications:\t");
			scanf("%s",personal.certifications);
			printf("\n\tEnter New Employee Work Experience:\t");
			scanf("%d",&personal.work_exp);
			printf("\n\tEnter new Employee Salary:\t");
			scanf("%f",&personal.salary);
			printf("\n\tEnter new Employee Phone Number:\t");
			scanf("%ld",&personal.phone);
			printf("\n\tEnter new Employee Programming languages Known:\t");
			scanf("%s",personal.prog_lang);
			fseek(data,-sizeof(personal),SEEK_CUR);
        	fwrite(&personal,sizeof(personal),size,data);
        	head_disp();;
        	printf("\n\n\tEmployee Record Successfuly Written.");
		}
		break;
	}
	if(found == 0)
	{
		printf("\n\tRECORD NOT FOUND...");
	}
	fclose(data);
	printf("\n\n\tPress 1 to Continue and 0 to EXIT");
	printf("\n\n\tINPUT:\t");
	int exit_status;
	scanf("%d",&exit_status);
	if(exit_status!=1)
	{
		head_disp();
		printf("\n\n\tThank You for Using this Application.\n");
		exit(0);
	}
}

void emp_search()
{
	head_disp();;
	FILE *data;
	data = fopen("employeeRecord.txt","r");
	int found = 0,search_choice,search_emp_id;
	char search_name[100],ch='Y';
	printf("\n\tWhat Do You Know about the Employee?");
	printf("\n\tEmployee ID: Enter 1");
	printf("\n\tEmployee Name: Enter 2");
	printf("\n\tINPUT:\t");
	scanf("%d",&search_choice);
	switch(search_choice)
	{
		case 1:
				printf("\n\tEnter Employee ID:\t");
				scanf("%d",&search_emp_id);
				break;
		case 2:
				printf("\n\tEnter Employee Name:\t");
				scanf("%s",search_name);
				break;
		default:
				ch='N';
				printf("\n\tWRONG CHOICE.\n");
	}
	while(fread(&personal,sizeof(personal),size,data)==size)
	{
		if(personal.emp_id == search_emp_id || strcmp(personal.name,search_name)==0)
			{
				found = 1;
				printf("\n\t******************EMPLOYEE RECORD IS......");
				printf("\n\n\tEMPLOYEE ID:\t%d",personal.emp_id);
				printf("\n\tEMPLOYEE NAME:\t%s",personal.name);
				printf("\n\tEMPLOYEE POSITION:\t%s",personal.position);
				printf("\n\tEMPLOYEE AGE:\t%d",personal.age);
				printf("\n\tEMPLOYEE QUALIFICATIONS:\t%s",personal.qualification);
				printf("\n\tEMPLOYEE CERTIFICATIONS:\t%s",personal.certifications);
				printf("\n\tEMPLOYEE WORK EXPERIENCE:\t%d",personal.work_exp);
				printf("\n\tEMLOYEE SALARY:\t%.2f",personal.salary);
				printf("\n\tEMPLOYEE PHONE NUMBER:\t%ld",personal.phone);
				printf("\n\tPROGRAMMING LANGUAGES KNOWN:\t%s",personal.prog_lang);
			}
	}
	if(found == 0 && ch!='N')
	{
		printf("\n\tNO SUCH EMPLOYEE RECORD FOUND.");
	}
	fclose(data);
	printf("\n\n\tPress 1 to Continue and 0 to EXIT");
	printf("\n\n\tINPUT:\t");
	int exit_status;
	scanf("%d",&exit_status);
	if(exit_status!=1)
	{
		head_disp();
		printf("\n\n\tThank You for Using this Application.\n");
		exit(0);
	}
}

void emp_delete()
{
	head_disp();;
	int found = 0,del_emp_id;
	FILE *data,*temp;
	data = fopen("employeeRecord.txt","r");
	temp = fopen("temp_data.txt","w");
	if(data == NULL)
	{
		printf("\n\tError in Opening File");
		exit(0);
	}
	printf("\n\tEnter Employee ID to delete it's Record:\t");
	scanf("%d",&del_emp_id);
	while((fread(&personal,sizeof(personal),size,data)==size))
	{
		if(personal.emp_id!=del_emp_id)
			fwrite(&personal,sizeof(personal),size,temp);	
	}
	fclose(data);
    fclose(temp);
    remove("employeeRecord.txt");
    rename("temp_data.txt","employeeRecord.txt");
    data=fopen("employeeRecord.txt","r");
    printf("\n\tRecord successfully deleted.\n\n");
    printf("\n\n\tPress 1 to Continue and 0 to EXIT");
	printf("\n\n\tINPUT:\t");
	int exit_status;
	scanf("%d",&exit_status);
	if(exit_status!=1)
	{
		head_disp();
		printf("\n\n\tThank You for Using this Application.\n");
		exit(0);
	}
}

void emp_displayAll()
{
	head_disp();;
	FILE *data;
    data=fopen("employeeRecord.txt","r");
    int totalemployee=0;
    int i=0;
    printf("\n\n\t**********************ALL EMPLOYEES INFORMATION*********************\n\n");
    while((fread(&personal,sizeof(personal),size,data)==size))
    {
    	i++;
    	printf("\n\n\tEMPLOYEE ID:\t%d",personal.emp_id);
		printf("\n\tEMPLOYEE NAME:\t%s",personal.name);
		printf("\n\tEMPLOYEE POSITION:\t%s",personal.position);
		printf("\n\tEMPLOYEE AGE:\t%d",personal.age);
		printf("\n\tEMPLOYEE QUALIFICATIONS:\t%s",personal.qualification);
		printf("\n\tEMPLOYEE CERTIFICATIONS:\t%s",personal.certifications);
		printf("\n\tEMPLOYEE WORK EXPERIENCE:\t%d",personal.work_exp);
		printf("\n\tEMLOYEE SALARY:\t%.2f",personal.salary);
		printf("\n\tEMPLOYEE PHONE NUMBER:\t%ld",personal.phone);
		printf("\n\tPROGRAMMING LANGUAGES KNOWN:\t%s\n\n\n",personal.prog_lang);
	}
	totalemployee+=i;
    printf("\n\n\tTOTAL EMPLOYEES: %d\n\n",totalemployee);
    fclose(data);
    printf("\n\n\tPress 1 to Continue and 0 to EXIT");
	printf("\n\n\tINPUT:\t");
	int exit_status;
	scanf("%d",&exit_status);
	if(exit_status!=1)
	{
		head_disp();
		printf("\n\n\tThank You for Using this Application.\n");
		exit(0);
	}
	
}

void emp_display()
{
	head_disp();;
	FILE *data;
	data = fopen("employeeRecord.txt","r");
	int found = 0,search_emp_id;
	printf("\n\tEnter Employee ID to display it's Record:\t");
	scanf("%d",&search_emp_id);
	while(fread(&personal,sizeof(personal),size,data)==size)
	{
		if(personal.emp_id == search_emp_id)
			{
				found = 1;
				printf("\n\tEMPLOYEE RECORD IS......");
				printf("\n\tEMPLOYEE ID:\t%d",personal.emp_id);
				printf("\n\tEMPLOYEE NAME:\t%s",personal.name);
				printf("\n\tEMPLOYEE POSITION:\t%s",personal.position);
				printf("\n\tEMPLOYEE AGE:\t%d",personal.age);
				printf("\n\tEMPLOYEE QUALIFICATIONS:\t%s",personal.qualification);
				printf("\n\tEMPLOYEE CERTIFICATIONS:\t%s",personal.certifications);
				printf("\n\tEMPLOYEE WORK EXPERIENCE:\t%d",personal.work_exp);
				printf("\n\tEMLOYEE SALARY:\t%.2f",personal.salary);
				printf("\n\tEMPLOYEE PHONE NUMBER:\t%ld",personal.phone);
				printf("\n\tPROGRAMMING LANGUAGES KNOWN:\t%s",personal.prog_lang);
				break;
			}
	}
	if(found == 0)
	{
		printf("\n\tNO SUCH EMPLOYEE RECORD FOUND.");
	}
	printf("\n\n\tPress 1 to Continue and 0 to EXIT");
	printf("\n\n\tINPUT:\t");
	int exit_status;
	scanf("%d",&exit_status);
	if(exit_status!=1)
	{
		head_disp();
		printf("\n\n\tThank You for Using this Application.\n");
		exit(0);
	}
	fclose(data);
}
