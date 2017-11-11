#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>

struct employee_data
{
	char name[100],position[100],qualification[100];
	int age,emp_id;
	char certifications[200];
	char prog_lang[100];
}personal;

struct employee_salary
{
	float basic,hra,da,total,pf;
}salary;

void emp_append();
void emp_delete();
void emp_modify();
void emp_displayAll();
void emp_display();
void emp_search();

int main(void)
{
	FILE *data;
	char create;
	int menu_choice;
	system("clear");
	data = fopen("employeeRecord.dat","r+");
	if(data==NULL)
	{
		system("clear");
		printf("\n Employee Database Not Found!\n Press N key to create new Database.");
		printf("\nTo EXIT, press Enter key\n");
		create = getchar();
		if(tolower(create)=='n')
		{
			data = fopen("employeeRecord.dat","w+");
			printf("Employee Record Database has been created in the current directory.\n");
			printf("You must Restart the Application\nPress Enter key to continue.\n");
			char x;
			scanf("%c",&x);
			fclose(data);
			exit(0);
		}
		else
		{
			printf("Thank You for using this Application.\n");
			exit(0);
		}
	}
	while(1)
	{
		rewind(data);	
		printf("\n \t 1.Add New Employee");
		printf("\n \t 2.Modify an Employee's Record");
		printf("\n \t 3.Search for an Employee");
		printf("\n \t 4.Delete an Employee Record");
		printf("\n \t 5.Display All Employee's Record");
		printf("\n \t 6.Display an Employee Record (Employee ID/Name Required)");
		printf("\n \t Enter ANY key to EXIT\t");
		scanf("%d", &menu_choice);
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
					system("clear");
					printf("Thank You for using this Application.\n");
					exit(0);
		}
	}
	return 0;
}

void emp_append()
{
	FILE *data;
	data = fopen("employeeRecord.dat","a");
	system("clear");
	printf("\n \tEmployee ID:\t");
	scanf("%d",&personal.emp_id);
	printf("\n \tEmployee Name:\t");
	scanf("%s",personal.name);
	printf("\n \tEmployee Position:\t");
	scanf("%s",personal.position);
	printf("\n \tEmployee Age:\t");
	scanf("%d",&personal.age);
	printf("\n \tEmployee Qualifications:\t");
	scanf("%s",personal.qualification);
	printf("\n \tEmployee Certifications:\t");
	scanf("%s",personal.certifications);
	printf("\n \tProgramming languages Known:\t");
	scanf("%s",personal.prog_lang);
	fprintf(data,"%d \t%s \t%s \t%d \t%s \t%s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
	fprintf(data,"%d",0);
	fclose(data);
}

void emp_modify()
{
	FILE *data,*temp_data;
	int id,found;
	system("clear");
	data = fopen("employeeRecord.dat","r");
	temp_data = fopen("temp_data.dat","w+");
	if(temp_data == NULL)
	{
		printf("\n\tError in Opening File.");
		exit(0);
	}
	printf("\n\tEnter Employee ID to Edit Record:\t");
	scanf("%d", &id);
	while(1)
	{
		fscanf(data,"%d",&personal.emp_id);
		if(personal.emp_id == 0)
			break;
		if(personal.emp_id == id)
		{
			found = 1;
			fscanf(data,"%s",personal.name);
			fscanf(data,"%s",personal.position);
			fscanf(data,"%d",&personal.age);
			fscanf(data,"%s",personal.qualification);
			fscanf(data,"%s",personal.certifications);
			fscanf(data,"%s",personal.prog_lang);
			printf("\n\tEXISTING RECORD IS......");
			printf("\n\t %d\t %s\t %d\t %s\t %s\t %s",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
			printf("\n\tEnter New Employee Name:\t");
//			fflush(stdin);
			scanf("%[^\n]s",personal.name);
			printf("\n\tEnter New Employee Position:\t");
			scanf("%[^\n]s",personal.position);
			printf("\n\tEnter New Employee Age");
			scanf("%d",&personal.age);
			printf("\n\tEnter New Employee Qualifications:\t");
			scanf("%[^\n]s",personal.qualification);
			printf("\n\tEnter New Employee Certifications:\t");
			scanf("%[^\n]s",personal.certifications);
			fprintf(temp_data,"%d\t %s\t %d\t %s\t %s\t %s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
		}
		else
		{
			fscanf(data,"%s",personal.name);
			fscanf(data,"%s",personal.position);
			fscanf(data,"%d",&personal.age);
			fscanf(data,"%s",personal.qualification);
			fscanf(data,"%s",personal.certifications);
			fscanf(data,"%s",personal.prog_lang);
			fprintf(temp_data,"%d\t %s\t %d\t %s\t %s\t %s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
		}
	}
	fprintf(temp_data,"%d",0);
	fclose(temp_data);
	fclose(data);
	if(found == 0)
		printf("\n\tRECORD NOT FOUND...");
	else
	{
		data = fopen("employeeRecord.dat","w");
		if(data == NULL)
		{
			printf("\n\tError in Opening Database");
			exit(0);
		}
		temp_data = fopen("temp_data.dat","r");
		if(temp_data == NULL)
		{
			printf("\n\tError in Opening Database");
			exit(0);
		}
		while(1)
		{
			fscanf(temp_data,"%d",&personal.emp_id);
			if(personal.emp_id == 0)
				break;
			fscanf(temp_data,"%s",personal.name);
			fscanf(temp_data,"%s",personal.position);
			fscanf(temp_data,"%d",&personal.age);
			fscanf(temp_data,"%s",personal.qualification);
			fscanf(temp_data,"%s",personal.certifications);
			fscanf(temp_data,"%s",personal.prog_lang);
			fprintf(data,"%d\t %s\t %d\t %s\t %s\t %s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
		}
		fprintf(data,"%d",0);
		fclose(temp_data);
		fclose(data);
	}
}

void emp_search()
{
	FILE *data;
	data = fopen("employeeRecord.dat","r");
	int found = 0,search_choice,search_emp_id;
	char search_name[100],ch='Y';
	system("clear");
	printf("\n\tWhat Do You Know about the Employee?");
	printf("\n\tEmployee ID: Enter 1");
	printf("\n\tEmployee Name: Enter 2\t");
	scanf("%d",&search_choice);
	while(ch=='Y')
	{
		switch(search_choice)
		{
			case 1:
					ch='N';
					printf("\n\tEnter Employee ID:\t");
					scanf("%d",&search_emp_id);
					break;
			case 2:
					ch='N';
					printf("\n\tEnter Employee Name:\t");
					scanf("%[^\n]s",search_name);
					break;
			default:
					printf("\n\tWRONG CHOICE.Retry(Y/N):\t");
					scanf("%c",&ch);
					ch = toupper(ch);
		}
	}
	while(1)
	{
		fscanf(data,"%d",&personal.emp_id);
			if(personal.emp_id == 0)
				break;
			if(personal.emp_id == search_emp_id || strcmp(personal.name,search_name)==0)
			{
				found = 1;
				fscanf(data,"%s",personal.name);
				fscanf(data,"%s",personal.position);
				fscanf(data,"%d",&personal.age);
				fscanf(data,"%s",personal.qualification);
				fscanf(data,"%s",personal.certifications);
				fscanf(data,"%s",personal.prog_lang);
				printf("\n\tEMPLOYEE RECORD IS......");
				printf("\n\t %d\t %s\t %d\t %s\t %s\t %s",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
			}
	}
	if(found == 0)
		printf("\n\tNO SUCH EMPLOYEE RECORD FOUND.");
		fclose(data);
}

void emp_delete()
{
	int found = 0,del_emp_id;
	FILE *data,*temp_data;
	data = fopen("employeeRecord.dat","r");
	temp_data = fopen("temp_data.dat","w");
	if(temp_data == NULL)
	{
		printf("\n\tError in Opening File");
		exit(0);
	}
	printf("\n\tEnter Employee ID to delete it's Record:\t");
	scanf("%d",&del_emp_id);
	while(1)
	{
		fscanf(data,"%d",&personal.emp_id);
		if(personal.emp_id == 0)
			break;
		if(personal.emp_id == del_emp_id)
		{
			found = 1;
			fscanf(data,"%s",personal.name);
			fscanf(data,"%s",personal.position);
			fscanf(data,"%d",&personal.age);
			fscanf(data,"%s",personal.qualification);
			fscanf(data,"%s",personal.certifications);
			fscanf(data,"%s",personal.prog_lang);
		}
		else
		{
			fscanf(data,"%s",personal.name);
			fscanf(data,"%s",personal.position);
			fscanf(data,"%d",&personal.age);
			fscanf(data,"%s",personal.qualification);
			fscanf(data,"%s",personal.certifications);
			fscanf(data,"%s",personal.prog_lang);
			fprintf(temp_data,"%d\t %s\t %d\t %s\t %s\t %s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
		}
	}
	fprintf(temp_data,"%d",0);
	fclose(data);
	if(found == 0)
	{
		printf("\n\t Employee ID Not Found");
		printf("\n\t Unable to Delete Employee");
	}
	else
	{
		data = fopen("employeeData.dat","w");
		if(data == NULL)
		{
			printf("\n\t ERROR IN OPENING FILE");
			exit(0);
		}
		temp_data = fopen("temp_data","r");
		if(temp_data == NULL)
		{
			printf("\n\t ERROR IN OPENING FILE");
			exit(0);
		}
		while(1)
		{
			fscanf(temp_data,"%d",&personal.emp_id);
			if(personal.emp_id == 0)
				break;
			fscanf(temp_data,"%s",personal.name);
			fscanf(temp_data,"%s",personal.position);
			fscanf(temp_data,"%d",&personal.age);
			fscanf(temp_data,"%s",personal.qualification);
			fscanf(temp_data,"%s",personal.certifications);
			fscanf(temp_data,"%s",personal.prog_lang);
			fprintf(data,"%d\t %s\t %d\t %s\t %s\t %s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
		}
		fprintf(data,"%d",0);
		fclose(temp_data);
		fclose(data);
	}
}

void emp_displayAll()
{
	FILE *data;
	data = fopen("employeeRecord.dat","r");
	system("clear");
	while(1)
	{
		fscanf(data,"%d",&personal.emp_id);
			if(personal.emp_id == 0)
				break;
		fscanf(data,"%s",personal.name);
		fscanf(data,"%s",personal.position);
		fscanf(data,"%d",&personal.age);
		fscanf(data,"%s",personal.qualification);
		fscanf(data,"%s",personal.certifications);
		fscanf(data,"%s",personal.prog_lang);
		printf("%d\t %s\t %d\t %s\t %s\t %s\n",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
	}
	fclose(data);
}

void emp_display()
{
	FILE *data;
	data = fopen("employeeRecord.dat","r");
	int found = 0,search_emp_id;
	printf("\n\tEnter Employee ID to display it's Record:\t");
	scanf("%d",&search_emp_id);
	while(1)
	{
		fscanf(data,"%d",&personal.emp_id);
			if(personal.emp_id == 0)
				break;
			if(personal.emp_id == search_emp_id)
			{
				found = 1;
				fscanf(data,"%s",personal.name);
				fscanf(data,"%s",personal.position);
				fscanf(data,"%d",&personal.age);
				fscanf(data,"%s",personal.qualification);
				fscanf(data,"%s",personal.certifications);
				fscanf(data,"%s",personal.prog_lang);
				printf("\n\tEMPLOYEE RECORD IS......");
				printf("\n\t %d\t %s\t %d\t %s\t %s\t %s",personal.emp_id,personal.name,personal.position,personal.age,personal.qualification,personal.certifications,personal.prog_lang);
			}
	}
	if(found == 0)
		printf("\n\tNO SUCH EMPLOYEE RECORD FOUND.");
	fclose(data);
}
