#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#define TOTAL_EMP 200
typedef struct
{
    char name[50];
    int date;
    char artist[20];
    double album_price;
} Album;

int i = 0, n = 0;
char choice;
int read = 0, record = 0;
FILE *file1, *file2;
Album emp[TOTAL_EMP];
void fileload(Album emp[])
{
    file2 = fopen("hasan.txt", "w+");
    if (file2 == NULL)
    {
        printf("Error opening file2\n");
        exit(1);
    }

    do
    {
        read = fscanf(file2, "%39[^,],%d,%19[^,],%lf\n", emp[record].name, &emp[record].date, emp[record].artist, &emp[record].album_price);

        if (read == 4)
            record++;
        if (read != 4 && !feof(file2))
        {
            printf("File format error\n");
            exit(1);
        }
        if (ferror(file2))
        {
            printf("Error reading from file2\n");
            exit(1);
        }
    }
    while (!feof(file2));
    fclose(file2);
}

void add_Album(Album emp[])
{
    file1 = fopen("file.txt", "w+");
    char another = 'y';
    while (another == 'y')
    {
        printf("\nAlbum %d information:\n", record + 1);
        fflush(stdin);
        printf("Enter Album Name: ");
        scanf("%[^\n]%*c", emp[record].name);
        fflush(stdin);
        printf("Enter Date: ");
        scanf("%d", &emp[record].date);
        fflush(stdin);
        printf("Enter Artist Name: ");
        scanf("%[^\n]%*c", emp[record].artist);
        fflush(stdin);
        printf("Album Price: ");
        fflush(stdin);
        scanf("%lf", &emp[record].album_price);
        printf("\n");
        printf("Do you want to Add another Album? (y/n): ");
        fflush(stdin);
        another = getchar();
        record++;
    }
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    fclose(file1);
    printf("\n%d Album added to file1\n", record);
}
void list_Album(Album employees[])
{
    printf("%-7s %-20s %-7s %-20s %-10s\n", "Serial", "Name", "date", "artist", "Salary");
    for (i = 0; i < record; i++)
    {
        printf("%-7d %-20s %-7d %-20s %-10.2lf\n", i, emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
    }
    system("pause");
}
void modify_Album(Album emp[])
{
    printf("Enter the serial number of the Album you want to modify: ");
    fflush(stdin);
    scanf("%d", &n);
    printf("\nEmployee %d info:\n", n);
    fflush(stdin);
    printf("Album Name: ");
    scanf("%[^\n]%*c", emp[n].name);
    fflush(stdin);
    printf("Date: ");
    scanf("%d", &emp[n].date);
    fflush(stdin);
    printf("Artist Name: ");
    scanf("%[^\n]%*c", emp[n].artist);
    fflush(stdin);
    printf("Album price: ");
    fflush(stdin);
    scanf("%lf", &emp[n].album_price);
    printf("\n");
    file1 = fopen("CCsvf.csv", "w+");
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    printf("Album %d modified\n", n);
    fclose(file1);
    system("pause");
}

void delete_Album(Album emp[])
{
    printf("Enter Album serial number : ");
    fflush(stdin);
    scanf("%d", &n);
    for (i = n; i < record; i++)
    {
        strcpy(emp[i].name, emp[i + 1].name);
        emp[i].date = emp[i + 1].date;
        strcpy(emp[i].artist, emp[i + 1].artist);
        emp[i].album_price = emp[i + 1].album_price;
    }
    record--;
    file1 = fopen("CCsvf.csv", "w+");
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    fclose(file1);
    printf("Album %d is deleted\n", n);
    system("pause");
}
void search_Album(Album emp[])
{

    printf("Enter the name of the Album you want to search: ");
    fflush(stdin);
    char name[40];
    scanf("%[^\n]%*c", name);
    for (i = 0; i < record; i++)
    {
        if (strcmp(emp[i].name, name) == 0)
        {
            printf("%-7s %-20s %-7s %-20s %-10s\n", "Serial", "Name",   "Date",   "Artist name", "Salary");
            printf("%-7d %-20s %-7d %-20s %-10.2lf\n", i, emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
            system("pause");
        }
    }
}
void sort_Album_name(Album emp[])
{
    int i, j;
    Album temp;
    for (i = 0; i < record; i++)
    {
        for (j = 0; j < record - 1; j++)
        {
            if (strcmp(emp[j].name, emp[j + 1].name) > 0)
            {
                strcpy(temp.name, emp[j].name);
                temp.date = emp[j].date;
                strcpy(temp.artist, emp[j].artist);
                temp.album_price = emp[j].album_price;
                strcpy(emp[j].name, emp[j + 1].name);
                emp[j].date = emp[j + 1].date;
                strcpy(emp[j].artist, emp[j + 1].artist);
                emp[j].album_price = emp[j + 1].album_price;
                strcpy(emp[j + 1].name, temp.name);
                emp[j + 1].date = temp.date;
                strcpy(emp[j + 1].artist, temp.artist);
                emp[j + 1].album_price = temp.album_price;
            }
        }
    }
    file1 = fopen("CCsvf.csv", "w+");
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    fclose(file1);
    printf("Albul sorted by name\n");
    system("pause");
}
void sort_Album_date(Album emp[])
{
    int i, j;
    Album temp;
    for (i = 0; i < record; i++)
    {
        for (j = 0; j < record - 1; j++)
        {
            if (emp[j].date > emp[j + 1].date)
            {
                strcpy(temp.name, emp[j].name);
                temp.date = emp[j].date;
                strcpy(temp.artist, emp[j].artist);
                temp.album_price = emp[j].album_price;
                strcpy(emp[j].name, emp[j + 1].name);
                emp[j].date = emp[j + 1].date;
                strcpy(emp[j].artist, emp[j + 1].artist);
                emp[j].album_price = emp[j + 1].album_price;
                strcpy(emp[j + 1].name, temp.name);
                emp[j + 1].date = temp.date;
                strcpy(emp[j + 1].artist, temp.artist);
                emp[j + 1].album_price = temp.album_price;
            }
        }
    }
    file1 = fopen("CCsvf.csv", "w+");
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    fclose(file1);
    printf("Employee sorted by date\n");
    system("pause");
}

void sort_Album_artist(Album emp[])
{
    int i, j;
    Album temp;
    for (i = 0; i < record; i++)
    {
        for (j = 0; j < record - 1; j++)
        {
            if (strcmp(emp[j].artist, emp[j + 1].artist) > 0)
            {
                strcpy(temp.name, emp[j].name);
                temp.date = emp[j].date;
                strcpy(temp.artist, emp[j].artist);
                temp.album_price = emp[j].album_price;
                strcpy(emp[j].name, emp[j + 1].name);
                emp[j].date = emp[j + 1].date;
                strcpy(emp[j].artist, emp[j + 1].artist);
                emp[j].album_price = emp[j + 1].album_price;
                strcpy(emp[j + 1].name, temp.name);
                emp[j + 1].date = temp.date;
                strcpy(emp[j + 1].artist, temp.artist);
                emp[j + 1].album_price = temp.album_price;
            }
        }
    }
    file1 = fopen("CCsvf.csv", "w+");
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    fclose(file1);
    printf("Album is sorted by Artist name\n");
    system("pause");
}
void sort_Album_salary(Album emp[])
{
    int i, j;
    Album temp;
    for (i = 0; i < record; i++)
    {
        for (j = 0; j < record - 1; j++)
        {
            if (emp[j].album_price > emp[j + 1].album_price)
            {
                strcpy(temp.name, emp[j].name);
                temp.date = emp[j].date;
                strcpy(temp.artist, emp[j].artist);
                temp.album_price = emp[j].album_price;
                strcpy(emp[j].name, emp[j + 1].name);
                emp[j].date = emp[j + 1].date;
                strcpy(emp[j].artist, emp[j + 1].artist);
                emp[j].album_price = emp[j + 1].album_price;
                strcpy(emp[j + 1].name, temp.name);
                emp[j + 1].date = temp.date;
                strcpy(emp[j + 1].artist, temp.artist);
                emp[j + 1].album_price = temp.album_price;
            }
        }
    }
    file1 = fopen("CCsvf.csv", "w+");
    for (i = 0; i < record; i++)
    {
        fprintf(file1, "%s,%d,%s,%.2lf\n", emp[i].name, emp[i].date, emp[i].artist, emp[i].album_price);
        if (ferror(file1))
        {
            printf("Error writing to file1\n");
            exit(1);
        }
    }
    fclose(file1);
    printf("Album sorted by Price\n");
    system("pause");
}
int main()
{

    fileload(emp);

    while (1)
    {
        printf("\n");
        printf("\n                          *o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *                   WELCOME TO                    *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *              | ALBUM MANAGEMENT |               *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *                                                 *     ");
        printf("\n                          *o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*o*     ");
        printf("\n\n");
        printf(" \t\t\t\t 1. Add Album  \n");
        printf(" \t\t\t\t 2. Album List \n");
        printf(" \t\t\t\t 3. Modify Album \n");
        printf(" \t\t\t\t 4. Delete Any Album \n");
        printf(" \t\t\t\t 5. Search Album \n");
        printf(" \t\t\t\t 6. Sort Album Records \n");
        printf(" \t\t\t\t 7. Exit System \n");
        printf(" \n \n Your Choice: ");
        fflush(stdin);
        choice = getchar();
        switch (choice)
        {
        case '1':
            system("cls");
            add_Album(emp);
            break;
        case '2':
            system("cls");
            list_Album(emp);
            break;
        case '3':
            system("cls");
            modify_Album(emp);
            break;
        case '4':
            system("cls");
            delete_Album(emp);
            break;
        case '5':
            system("cls");
            search_Album(emp);

            break;
        case '6':
            system("cls");

            printf(" \n:::::::::::::::::::::::::: Sorted part of ALBUM MANAGEMENT SYSTEM :::::::::::::::::::::::::: \n");
            printf("\t\t\t 1.Sort The album by Name \n");
            printf("\t\t\t 2.Sort The album by date \n");
            printf("\t\t\t 3.Sort The album by artist \n");
            printf("\t\t\t 4.Sort The album by Price \n");
            printf("\t\t\t 5.Return \n");
            printf(" \n \n Plz Enter Your Choice: ");
            fflush(stdin);
            choice = getchar();
            switch (choice)
            {
            case '1':
                system("cls");
                sort_Album_name(emp);
                break;
            case '2':
                system("cls");
                sort_Album_date(emp);
                break;
            case '3':
                system("cls");
                sort_Album_artist(emp);
                break;
            case '4':
                system("cls");
                \
                sort_Album_salary(emp);
                break;
            case '5':
                system("cls");
                break;
            default:
                system("cls");
                printf("\nInvalid choice & returning back ...\n");
                system("pause");
            }
            break;
        case '7':
            system("cls");
            exit(0);
            break;
        default:
            system("cls");
            printf("Invalid Choice");
            break;
        }
    }
    return 0;
}
