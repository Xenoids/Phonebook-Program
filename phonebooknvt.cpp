#include <stdio.h> 
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct data
{
	char nama[100];
	char nomor[100];
};

// data
data x[100];

void title()
{
	puts("Phone Book Program");
	puts("1. Add a new record");
	puts("2. Search for a name");
	puts("3. Modify a phone number");
	puts("4. Delete a record");
	puts("5. Exit the program");
	puts("Created by : Nicholas Valenthinus Tanoto - 2401960624 - Game Application and Technology");
	printf(">>");
}


// bool Validation
bool isalphabet(char namabackup[])
{
	for(int i=0;i<strlen(namabackup);i++)
	{
		if( ('a' <=namabackup[i] && namabackup[i] <= 'z') || ('A' <= namabackup[i] && namabackup[i] <= 'Z') )
		{
			if(strlen(namabackup) > 5 && strlen(namabackup) <40)
			{
				return true;
			}
		}
	}
	return false;
}

bool isnum(char nomorbackup[])
{
	for(int i=0;i<strlen(nomorbackup);i++)
	{
		if( '0' <= nomorbackup[i] && nomorbackup[i] <= '9' )
		{
			if(strlen(nomorbackup) == 12) 
			{
					return true;
			}
		}
	}
	return false;
}

bool isexistalpha(char existnama[])
{
	// menghitung banyak data
	int countexist = 0;
	char c;
	FILE* fp;
	fp = fopen("data.txt","r");
	while((c=getc(fp)) != EOF)
	{
		if(c == '\n') ++countexist;
	}
	fclose(fp);
	
		for(int i=0;i<countexist;i++)
		{
			if(strcmp(existnama,x[i].nama) == 0)
			{
				printf("The name is already exist!\n");	
				system("pause");			
				return true;
				break;
			}
		}

	return false;
}

bool isexistnum(char existnum[])
{
	// menghitung banyak data
	int countexist = 0;
	char c;
	FILE* fp;
	fp = fopen("data.txt","r");
	while((c=getc(fp)) != EOF)
	{
		if(c == '\n') ++countexist;
	}
	fclose(fp);
	

		
		for(int i=0;i<countexist;i++)
		{
			if(strcmp(existnum,x[i].nomor) == 0)
			{
				printf("The phonenumber is already exist!\n");
				system("pause");
				return true;
				break;
			}
		}

	return false;
}

bool isExistalphaformodify(char existalpha[])
{
	// menghitung banyak data
	int countexist = 0;
	char c;
	FILE* fp;
	fp = fopen("data.txt","r");
	while((c=getc(fp)) != EOF)
	{
		if(c == '\n') ++countexist;
	}
	fclose(fp);
	
		for(int i=0;i<countexist;i++)
		{
			if(strcmp(existalpha,x[i].nama) == 0)
			{			
				return true;
				break;
			}
		}

	return false;
}



// menu function
int count =0;
void addrecord();
void searchname();
void modifynumber();
void deleterecord();


int main()
{
	int input;
	do
	{
		title();
		scanf("%d",&input);
		getchar();
		system("cls");
	}while(input < 1 || input > 5);
	
	switch(input)
	{
		case 1:
		addrecord();
		break;
		case 2:
		searchname();	
		break;
		case 3:
		modifynumber();
		break;
		case 4:
		deleterecord();
		break;
		case 5:
		printf("Thank you for using this program!\n");
		// untuk reset data jadi kosong begitu udah mau exit
		/*remove("data.txt");
		remove("copy.txt"); */
		
		exit(0);
		break;
	}
	return 0;
}

void addrecord()
{
	FILE* fp;
	
	// backup
	char namabackup[100];
	char nomorbackup[100];
	
	// penampung
	bool isalphafix =false;
	bool isnumfix = false;
	bool isexistalphafix = false;
	bool isexistnumfix = false;
	
	do{
	system("cls");
	printf("Input your friend name [alphabet only][5 - 40] : ");
	scanf("%[^\n]",namabackup);
	getchar();
	isalphafix = isalphabet(namabackup);
	isexistalphafix = isexistalpha(namabackup);
//	printf("isexistalpha = %d\n",isexistalphafix);
//	printf("isalpha =%d\n",isalphafix);
	}while(isalphafix == false || isexistalphafix == true);

	
	//debug checking nama yang distrcpy sesuai
	//printf("%s",x[count].nama);
	
	do{
	system("cls");
	printf("Input phone number [numeric only][12 digits] : ");
	scanf("%s",nomorbackup);	
	getchar();
	isnumfix = isnum(nomorbackup);
	isexistnumfix = isexistnum(nomorbackup);
//	printf("isexistnum = %d\n",isexistnumfix);
//	printf("isnum = %d\n",isnumfix);
	}while(isnumfix == false || isexistnumfix == true);	
	
	strcpy(x[count].nama,namabackup);
	strcpy(x[count].nomor,nomorbackup);
	fp =fopen("data.txt","a");
	fprintf(fp,"%s#%s\n",x[count].nama,x[count].nomor);
	fclose(fp);
	printf("Name : %s and Phonenumber : %s has been succesfully inputted\n",namabackup,nomorbackup);
	system("pause");
	
	// data ditambah
	count++;
	
	system("cls");
	main();
}

void searchname()
{	
	// ambil index
	int idx = -1;
	
	
	// menghitung banyak data
	int counts = 0;
	char c;
	FILE* fp;
	fp = fopen("data.txt","r");
	while((c=getc(fp)) != EOF)
	{
		if(c == '\n') ++counts;
	}
	fclose(fp);
	
	
	// check jumlah data sesuai apa ndak
	//printf("%d",counts);
	
	char searchnama[100];
	
	//char searchnomor[100];
	
	fp=fopen("data.txt","r");
	int size;
	
	// melihat dari awal hingga akhir
	fseek(fp,0,SEEK_END);
	
	// memberitahu jumlah char dari awal sampai akhir
	size =ftell(fp);
	fclose(fp);
	
	// validasi data ada apa ngga pada file
	if(size == 0 || fp == NULL)
	{
		printf("There is No data in File\n");
		system("pause");
		system("cls");
		main();
	} 
	else
	{
		
		fp=fopen("data.txt","r");
		printf("List All Friends Name and Phonenumber\n");
		printf("=========================================\n");
		for(int i=0;i<counts;i++)
		{
			fscanf(fp,"%[^#]#%s\n",x[i].nama,x[i].nomor);
			printf("%d.Name : %s\nPhonenumber : %s\n",i+1,x[i].nama,x[i].nomor);
		}
		fclose(fp);
		
		
		printf("input name that you want to search : ");
		scanf("%[^\n]",searchnama);
		
		/*
		fp=fopen("data.txt","r");
		
		for(int i=0;i<counts;i++)
		{
			fscanf(fp,"%s %s",x[i].nama,x[i].nomor);
			printf("Name : %s\n Number : %s\n",x[i].nama,x[i].nomor);
		}
		*/
	
		for(int i=0;i<counts;i++)
		{
			if(strcmp(searchnama,x[i].nama) == 0)
			{
				idx = i;
				break;
			}
		}
		fclose(fp);
		if(idx != -1) printf("Found name : %s with Phonenumber : %s\n",x[idx].nama,x[idx].nomor);
		else printf("No Similar name found!\n");
		system("pause");
		system("cls");
		main();	
	}
	
}

void modifynumber()
{
	
	// menghitung banyak data
	int countsmodify = 0;
	
	int idx = -1;
	char c;
	
	FILE* fp;
	fp = fopen("data.txt","r");
	while((c=getc(fp)) != EOF)
	{
		if(c == '\n') ++countsmodify;
	}
	fclose(fp);
	
	char modifynama[100];
	char modifynomor[100];
	
	fp=fopen("data.txt","r");
	int size;
	
	// melihat dari awal hingga akhir
	fseek(fp,0,SEEK_END);
	
	// memberitahu jumlah char dari awal sampai akhir
	size =ftell(fp);
	fclose(fp);
	
	// validasi data ada apa ngga pada file
	if(size == 0 || fp == NULL)
	{
		printf("There is No data in File\n");
		system("pause");
		system("cls");
		main();
	} 
	else
	{
		
	
		
		do{
		system("cls");
		fp=fopen("data.txt","r");
		printf("List All Friends Name and Phonenumber\n");
		printf("=========================================\n");
		for(int i=0;i<countsmodify;i++)
		{
			fscanf(fp,"%[^#]#%s\n",x[i].nama,x[i].nomor);
			printf("%d.Name : %s\nNumber : %s\n",i+1,x[i].nama,x[i].nomor);
		}
		fclose(fp);
		printf("input name that you want to modify the phonenumber : ");
		scanf("%[^\n]",modifynama);
		getchar();
		}while(isalphabet(modifynama) == false || isExistalphaformodify(modifynama) == false);

		if(countsmodify == 1)
		{
			if(strcmp(modifynama,x[0].nama) == 0)
			{
				idx = 0;
			}
			
			if(idx == 0)
			{
			int len;
			do{
			printf("input phonenumber to modify it [12 digits] : ");
			scanf("%s",modifynomor);
			len = strlen(modifynomor);
			getchar();
			}while(len != 12);
		
				if(strcmp(x[idx].nomor,modifynomor) != 0) 
				{
					fp = fopen("data.txt","w");
					strcpy(x[idx].nomor,modifynomor);
					printf("Sucessfully modify the phonenumber!\n");
					system("pause");
					fprintf(fp,"%s#%s\n",x[0].nama,modifynomor);
					fclose(fp);
				}
				else
				{
					printf("The Phonenumber is already exist!\n");
					system("pause");
					system("cls");
					main();
				}
		
			}
			else printf("No Similar name found!\n");
			system("cls");
			main();	
		}
		
		// countmodify lebih dari 1 data
		else
		{
			
		for(int i=0;i<countsmodify;i++)
		{
			if(strcmp(modifynama,x[i].nama) == 0)
			{
				idx = i;
				break;
			}
		}
		
		if(idx >= -1)
		{
			int len;
			do{
			printf("input phonenumber to modify it [12 digits] : ");
			scanf("%s",modifynomor);
			len = strlen(modifynomor);
			getchar();
			}while(len != 12);
			
			fp = fopen("data.txt","w");
			for(int i=0;i<countsmodify;i++){
				if(strcmp(x[idx].nomor,modifynomor) != 0) 
				{
					strcpy(x[idx].nomor,modifynomor);
					printf("Sucessfully modify the phonenumber!\n");
					break;
					system("pause");
				}
				else
				{
					printf("The Phonenumber is already exist!\n");
					break;
				}
			}
			for(int i=0;i<countsmodify;i++){
				fprintf(fp,"%s#%s\n",x[i].nama,x[i].nomor);
			}
			fclose(fp);
		}
		else printf("No Similar name found!\n");
		system("pause");
		system("cls");
		main();	
		}
	}
	
}

void deleterecord()
{
	
	// menghitung banyak data
	int countdelete = 0;
	char c;
	FILE* fp;
	fp = fopen("data.txt","r");
	while((c=getc(fp)) != EOF)
	{
		if(c == '\n') ++countdelete;
	}
	fclose(fp);
	
	
	// check jumlah data sesuai apa ndak
	//printf("%d",countsdelete);
	

	
	
	fp=fopen("data.txt","r");
	int size;
	
	// melihat dari awal hingga akhir
	fseek(fp,0,SEEK_END);
	
	// memberitahu jumlah char dari awal sampai akhir
	size =ftell(fp);
	fclose(fp);
	
	// validasi data ada apa ngga pada file
	if(size == 0 || fp == NULL)
	{
		printf("There is No data in File\n");
		system("pause");
		system("cls");
		main();
	}
	 
	else
	{
		
		// file ke 2 untuk diganti jadi file utama
		char* text = "data.txt";
		
		fp=fopen("data.txt","r");
		int i;
		for(i=0;i<countdelete;i++)
		{
			fscanf(fp,"%[^#]#%s\n",x[i].nama,x[i].nomor);
		}
			x[i] = x[-99];
			countdelete--;
		fclose(fp);
		
		fp = fopen("copy.txt","w");
				for(int i=0;i<countdelete;i++){
				fprintf(fp,"%s#%s\n",x[i].nama,x[i].nomor);
				}
	    fclose(fp);
	    	
	    remove(text);
	    rename("copy.txt",text);
	    printf("Deleted one Record Sucessfully!\n");
		system("pause");
		system("cls");
		main();	
	}
			
		
	}

