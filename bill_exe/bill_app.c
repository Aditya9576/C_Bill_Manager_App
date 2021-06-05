#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "SetPath.txt"
#define or ||
/*------------------variable decleration---------------------*/
	char opt,conf;
	char name[50];
	int amount;
	FILE *cache;
	FILE *buff;
	char temp_buff[100];
	char fname[100];
	char ftemp[100];
	int count; /*-----to count no. of time user inputed the data------*/
	extern char path[100];
	char temp_path[100];
/*---------------------------------------------------------*/
void edit();
void delete();
void undo();
void display();
/*--------------------------------------------------- main modules------------------------------*/
/*-----1. New File--------*/
void new_file()/*----clear & create new data-----*/
{						
	cache = fopen(temp_path,"w");/*----clear & create new data-----*/
	if(cache == NULL)
	{
		printf("Unable to open cache_file\n");
		perror("Error(newfile_cache) ");
		getch();
		exit(1);
	}
	else
	{
		printf("Done !");
		fclose(cache);
	}
}


/*------2. Today-------*/
void today()
{
	int tru = 1;
	char conf;
	while(tru)
	{
		again:
		system("cls");
		printf("1. Edit\n2. Delete\n3. Undo\n4. Display\n5. Back\noption: ");
		scanf("%c",&opt);
		if( opt == 49 or opt == 50  or opt == 51 or opt ==52 or opt ==53)
		{
			fflush(stdin);
			goto sos;
		}
		else{
			printf("Invalid Input !\n");
			fflush(stdin);
			getch();
			goto again;
		}
		sos:
		fflush(stdin);
		switch(opt)
		{
			case '1':
				edit();
				fflush(stdin);
				/*fflush(stdin);*/
				break;
			case '2':
				printf("confirm(y/n): ");
				scanf("%c",&conf);
				printf("\n");
				fflush(stdin);
				if(conf == 'y' or conf == 'Y')
				{
					delete();
					fflush(stdin);
				}
				break;
			case '3':
				undo();
				fflush(stdin);
				break;
			case '4':
				display();
				fflush(stdin);
				getch();
				break;
			case '5':
				tru=0;
				break;
			default:
				printf("invalid input !\n");
				getch();
		}
	}
}

/*-----3. Print-------*/
void print()
{
	FILE *print;
	char temp[100];
	int i,final;
	strcpy(temp,path);
	strcat(temp,"/SavedFiles");
	printf("Enter Name: \n");
	scanf("%s",name);

	strcat(temp,"/");
	strcat(temp,name);
	strcat(temp,".txt");
	printf("%s",temp);
	cache = fopen(temp_path,"r");/* open cached file to copy the data */
	if(cache == NULL)
	{
		perror("Error ");
		printf("\nNo data created");
		getch();
		system("cls");
	}
	else
	{
		print = fopen(temp,"w");
		i=1;
		final = 0;
		while(fscanf(cache,"%s %d",name,&amount)!=EOF)
		{
			final = final + amount;
			fprintf(print,"%d%c %s %d\n",i,'.',name,amount);
			i++;
		}
		fprintf(print,"\n%s%d","Total Amount: ",final);
		fclose(cache);
		fclose(print);
		printf("Done !\n");
		getch();
	}
}

/*-----4. Search-------*/
void search()
{
	char search_name[20];
	char name[20];
	int amount,count;
	FILE *cache;
	system("cls");
	printf("Enter Name: ");
	scanf("%s",search_name);/*Enter Customer Name*/
	cache = fopen(temp_path,"r");
	if(cache == NULL)
		perror("Error in Search: ");
	else
	{
		count = 0;
		while(fscanf(cache,"%s %d",name,&amount)!=EOF)
		{
			if(strcmp(strupr(name),strupr(search_name)) == 0) /*Find the data according to input */
			{
				count += 1;
				printf("%d. Name: %s -> Amount: %d\n",count,name,amount);/*print the data*/
			}
		}
		if(count == 0) /*if no match found*/
			printf("No Match Found !");
	}
}

/*---------------------------main_file-------------------------------*/
int main()
{
	char c;
	strcpy(temp_path,path);		
	strcat(temp_path,"/files/newfile_cache");
	while (1)
	{
		again:
		system("cls");
		printf("1. New Entery\n2. Today\n3. Print\n4. Search\n5. Exit\n");/*---print will give the copy of out data to share or to print----*/
		printf("option: ");
		scanf("%c",&opt);
		if( opt == 49 or  opt == 50 or opt == 51 or opt ==52 or opt == 53)
		{
			fflush(stdin);
			goto sos;
		}
		else{
			printf("Invalid Input !\n");
			fflush(stdin);
			getch();
			goto again;
		}
		fflush(stdin);
		sos:
		switch(opt)
		{
			case '1':/*----clear & create new data-----*/
				printf("confirm(y/n): ");
				scanf("%c",&c);
				fflush(stdin);
				if(c == 'y')
				{
					new_file();
					getch();
				}
				break;
			case '2':
				today();
				break;
			case '3':
				print();
				fflush(stdin);
				break;
			case '4':
				search();
				fflush(stdin);
				getch();
				break;
			case '5':
				printf("Press 'y' to confirm: ");
				conf = getche();
				if(conf == 'y' or conf == 'Y')
					exit(0);
				else
					system("cls");
				break;
			default:
				printf("Invalid Input !\n");

		}
	}
	return 0;
}

/*------------------------Today----------------------------*/
/*-----1. Edit--------*/
void edit()
{
	cache = fopen(temp_path,"a");
	if(cache == NULL)
	{
		perror("Error(edit) ");
		printf("\nUnabel to open cache_file !");
		getch();
		exit(1);
	}
	system("cls");
	printf("#-----Enter * in the Name to exit-------------#\n");
	while(1) 
	{
		printf("Name: ");
		scanf("%s",name);
		printf("\t\t\t");
		if(strcmp(name,"*") == 0)/* ---------to break the loop -----------*/
			break;
		printf("Amount: ");
		scanf("%d",&amount);
		printf("\n");
		fprintf(cache,"%s %d",name,amount);
	}
	fclose(cache);
}
/*---------delete-------*/
void delete()
{
	int i,j;
	printf("Enter Index: ");
	scanf("%d",&i);
	cache = fopen(temp_path,"r");
	if(cache == NULL)
	{
		perror("Error ");
		getch();
		exit(1);
	}
	strcpy(temp_buff,path);
	strcat(temp_buff,"/files/buffer_file");
	buff = fopen(temp_buff,"w");
	if(buff == NULL)
	{
		perror("Error(buffer) ");
		exit(1);
	}
	while(fscanf(cache,"%s %d",name,&amount)!=EOF)
		fprintf(buff,"%s %d",name,amount);
	fclose(cache);
	fclose(buff);
	cache = fopen(temp_path,"w");
	if(cache == NULL)
		exit(1);
	buff = fopen(temp_buff,"r");
	if(buff == NULL)
		exit(1);
	j=1;
	while(fscanf(buff,"%s %d",name,&amount)!=EOF)
	{
		if(j != i)
			fprintf(cache,"%s %d",name,amount);		
		++j;	
	}
	fclose(cache);
	fclose(buff);
}

/*----3. Undo-----*/
void undo()
{
	buff = fopen(temp_buff,"r");
	if(buff == NULL)
	{
		perror("Error(undo->buffer_file) ");
	}
	else
	{
		cache = fopen(temp_path,"w");
		if(buff == NULL)
		{
			perror("Error(undo->cache_file) ");
		}
		else
		{
			while(fscanf(buff,"%s %d",name,&amount)!=EOF)
			{
				fprintf(cache,"%s %d",name,amount);
			}
		}
	}
	
	fclose(cache);
	fclose(buff);
}






/*----4. Display---------*/
void display()
{
	int i = 0;
	int total;
	fflush(stdin);
	cache = fopen(temp_path,"r");/*----open the cached file---*/
	total = 0;
	if(cache == NULL)
	{
		perror("Error(display) ");
	}
	else
	{
		system("cls");
		printf("#Name:\t\t\t#Amount(Rs):\n");
		while(fscanf(cache,"%s %d",name,&amount)!=EOF)
		{
			total = total + amount;
			printf("\n%d.%s\t\t\t%d",++i,name,amount );
		}
		printf("\n\n#Total Amount: %u",total );
	}
}
