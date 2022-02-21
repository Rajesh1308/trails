#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
int login();
void mainmenu();
void add_details();
void display_details();
void search_details();
void delete_details();

struct member
{
    int id;
    char fname[15],lname[15];
    int age;
    char gender[10];
    int dt,mt,yr,nv;
    char vaccine[15],bd,allergy[50];

}s;
int main()
{
    printf("\n\n\t\t Welcome to Immunization data analyser\n\n");
    printf("\n\n\tPress any key to continue... \t");
    getch();
    system("cls");
    login();
}
int login()
{
    char username[10] = "IDA_admin";
    char password[10] = "password";
    char pass[10],uname[10];
    printf("Enter the user name : ");
    gets(uname);
    if(strcmp(uname,username) == 0)
    {
        printf("Enter the password : ");
        gets(pass);
        if(strcmp(password,pass) == 0)
        {
            sleep(1);
            system("cls");
            mainmenu();
        }
        else
        {
            system("cls");
            printf("Incorrect password \n Please try again\n");
            login();
        }

    }
    else
    {
         system("cls");
         printf("\n\t Incorrect username \n\t Please try again\n");
         login();
    }
}
void mainmenu()
{
    int ch;
    printf("\n\n\t Main Menu\n\n");
    printf("\n1.ADD DETAILS");
    printf("\n2.DISPLAY DETAILS");
    printf("\n3.SEARCH DETAILS");
    printf("\n4.DELETE DETAILS");
    printf("\n0.EXIT");
    printf("\n\nEnter the choice : ");
    scanf("%d",&ch);

        switch(ch)
        {
        case 1 :
            add_details();
            mainmenu();
            break;
        case 2 :
            display_details();
            mainmenu();
            break;
        case 3 :
            search_details();
            mainmenu();
            break;
        case 4 :
            delete_details();
            mainmenu();
            break;
        case 0 :
            printf("\n\n\tThank you using our service\n\n");
            exit(0);
        default :
            printf("\n\nInvalid key entered");
            mainmenu();
        }
}
void add_details()
{
    int ch;
    FILE *fp;
    fp = fopen("details.txt","ab+");
    if(fp == NULL)
    {
        printf("Error");
        mainmenu();
    }
    display_details();
    printf("\n\nEnter the details\n\n");
    printf("\nEnter a unique ID number : ");
    scanf("%d",&s.id);
    fflush(stdin);
    printf("\nEnter first name : ");
    gets(s.fname);
    printf("\nEnter last name : ");
    gets(s.lname);
    printf("\nEnter age : ");
    scanf("%d",&s.age);
    if(s.age < 16 || s.age >120)
    {
        system("cls");
        printf("This age does not exist or vaccination is not allowed");
        sleep(2);
        system("cls");
        mainmenu();
    }
    fflush(stdin);
    printf("\nEnter gender [Male/Female] :");
    gets(s.gender);
    printf("\nEnter the number of doses taken : ");
    scanf("%d",&s.nv);
    if(s.nv == 0)
    {
        printf("\n\nPlease request the person to vaccinate\n");
        sleep(1);
        s.dt = s.mt = s.yr = 0;
        strcpy(s.vaccine,"No dose taken");
        s.bd = 'N';
        strcpy(s.allergy,"No dose taken");
    }
    else if(s.nv > 0 && s.nv < 3)
    {
        printf("\nEnter the date of vaccination of first dose [dd mm yyyy] : ");
        scanf("%d %d %d",&s.dt,&s.mt,&s.yr);
        if(s.dt < 0 || s.dt > 31 || s.mt < 0 || s.mt > 12 || s.yr < 2019)
        {
            system("cls");
            printf("This date does not exist or vaccine is not manufactured");
            sleep(2);
            system("cls");
            mainmenu();
        }
        printf("Select the vaccine \n1.Covishield\n2.Covaxin\n3.Sputnik\n4.Others\n");
        printf("Enter the choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1 :
            strcpy(s.vaccine,"Covishield");
            break;
        case 2 :
            strcpy(s.vaccine,"Covaxin");
            break;
        case 3 :
            strcpy(s.vaccine,"Sputnik  ");
            break;
        case 4 :
            strcpy(s.vaccine,"Others");
            break;
        }
        fflush(stdin);
        printf("\nIs the booster dose taken? [Y/N] : ");
        s.bd = getchar();
        if(s.bd != 'Y' && s.bd != 'N')
        {
            system("cls");
            printf("Invalid key entered");
            sleep(2);
            system("cls");
            mainmenu();
        }
        fflush(stdin);
        printf("What side effects you had post vaccination? \nEnter Nil if no side effects : ");
        gets(s.allergy);

    }
    else
    {
        system("cls");
        printf("These many doses are not allowed");
        sleep(2);
        system("cls");
        mainmenu();
    }
    fwrite(&s,sizeof(s),1,fp);
    printf("Details added successfully\n");
    fclose(fp);
    display_details();
}
void display_details()
{
    FILE *fp;
    system("cls");
    fp = fopen("details.txt","rb");
    if(fp == NULL)
    {
        printf("Error");
        mainmenu();
    }
    printf("\n\n\tDetails in the record\n\n");
    printf("ID\tName\t\tAge\tGender\tNo of doses\tDate   \tVaccine name\tBooster dose\t Side effects\n");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        printf("%d   %s %s\t\t%d\t%s\t %d\t\t%d-%d-%d    %s   \t%c\t %s\n",s.id,s.fname,s.lname,s.age,s.gender,s.nv,s.dt,s.mt,s.yr,s.vaccine,s.bd,s.allergy);
    }
    fclose(fp);
}
void search_details()
{

    int no,flag = 0;
    FILE *fp;
    fp = fopen("details.txt","rb");
    if(fp == NULL)
    {
        printf("Error in opening the file");
        mainmenu();
    }
    display_details();
    printf("\n\nEnter ID to be searched : ");
    scanf("%d",&no);
    system("cls");
    while(fread(&s,sizeof(s),1,fp) > 0 && flag == 0)
    {
        if(s.id == no)
        {
            flag = 1;
            printf("\n\tRecord found successfully\n\n");
            printf("ID\tName\tAge\tGender\tNo of doses\tDate   \tVaccine name\tBooster dose\t Side effects\n");
            printf("%d   %s %s\t%d\t%s\t %d\t\t%d-%d-%d    %s   \t%c\t %s\n",s.id,s.fname,s.lname,s.age,s.gender,s.nv,s.dt,s.mt,s.yr,s.vaccine,s.bd,s.allergy);
        }
    }
    if(flag == 0)
    {
        printf("\n\tNo such record found !!!!\n");
        sleep(2);
        system("cls");
    }

    fclose(fp);
}
void delete_details()
{

    int no;
    unsigned int flag = 0;
    FILE *fp,*ft;
    fp = fopen("details.txt","ab+");
    if(fp == NULL)
    {
        printf("Error in opening the file");
        mainmenu();
    }
    display_details();
    printf("\n\nEnter ID number which to be deleted : ");
    scanf("%d",&no);
    ft = fopen("details1.txt","ab+");
    while(fread(&s,sizeof(s),1,fp) == 1)
    {
        if(s.id != no)
        {
            fwrite(&s,sizeof(s),1,ft);
        }
        else
        {
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("\n\n\tNo such record found");
        sleep(2);
    }
    else if(flag == 1)
    {
        printf("\n\nDeleted successfully\n");
        sleep(2);
    }
    fclose(fp);
    fclose(ft);
    remove("details.txt");
    rename("details1.txt","details.txt");
    printf("\nUpdated record\n");
    display_details();
}

