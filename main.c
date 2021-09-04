
/*This program helps managing a departmental store by helping to define goods, keep its records, make bills, keep records of the sales*/
//Including all the header files we need 
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <dos.h>

//declaring the functions we will use in the program
void mainmenu();
int MasterVerify();
void CreateManager();
void CreateCashier();
void Verification();
void ManagerMenu();
void CashierMenu();
void GoodsEntry();
void GoodsListDisplay();
void EditGoods();
void DeleteGoods();
void DeleteData();
void Billing();
void TotalSalesDisplay();
void SetColor(int ForgC)     //defining SetColor function implicitly to add colors property to our texts
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
};
struct goods    //to keep records of the goods in the store
{
	char itemcode[50];
	char itemname[50];
	int rate;
}a;
struct authorize    //to keep record of the user data and password for manager and cashier
{
	char admin_name[50];
	char admin_password[50];
	char user_name[50];
	char user_password[50];
}b;
struct goods2   //to keeep sales record while billing and to display it later
{
	char itemcode[50];
	char itemname[50];
	int rate;
	int quantity;
	int cost;
}c;
char CashierName[50];   //globally defining CashierName so that we dont have to pass it for printing the name in the bill
int grandtotal=0;   //globally defining the grandtotal of value of total sales
char choice1,choice2;

void main()
{
	long int i,j;
	SetColor(30);
	printf ("\n\t\t********************************************************\n");   //welcome screen
	printf ("\t\t*   Welcome to DEPARTMENTAL STORE MANAGEMENT SYSTEM    *\n");
	printf ("\t\t********************************************************\n\n\n");
	SetColor(15);
	printf ("\nLoading");
	for (i=0;i<7;i++)
	{
        Sleep(250);
        printf (".");   //loading effect
	}
	printf("\nPress any key to continue!!\n");
	getch();
	mainmenu();
}

void mainmenu()
{
    system("cls");
    SetColor(219);
	printf ("\n\t\t                MAIN MENU\n");
	printf("\t\t============================================\n\n");
	printf ("\n\nEnter the choices:\n(L) to login.\n(A) For Admin Menu: (to create Manager/Cashier).\n(E) to exit:");
	askchoice2:
	choice1=getche();
	switch (choice1)
	{
			case 76:
			case 108:
				Verification();
				break;
			case 65:
			case 97:
				/* Admin  Menu */
				if(MasterVerify()==0)   //verifies the master key for admin
                {
                    system("cls");
                    printf("\t\t  ADMIN MENU\n");
                    printf("\t\t**************\n\n");
                    SetColor(10);
                    printf ("\nEnter (M) to create Manager ID:\n");
                    printf ("Enter (C) to create Cashier ID:\n");
                    printf ("Enter (D) to delete existing data:\n");
                    printf ("Enter (R) to return to main menu:\n");
                    askchoice1:
                    choice2=getche();
                    switch(choice2)
                    {
                        case 77:
                        case 109:
                            CreateManager();
                            break;
                        case 67:
                        case 99:
                            CreateCashier();
                            break;
                        case 82:
                        case 114:
                            mainmenu();
                            break;
                        case 68:
                        case 100:
                            DeleteData();
                            break;
                        default:
                        {
                            printf ("\nInvalid Selection!\nEnter again:\n");
                            Beep(200, 900);
                            goto askchoice1;   //asks the user to input his/her choice again
                            break;
                        }
                    }
                }
                else
                {
                    printf("\nMaster Key Mismatch !\nYou will be redirected to Main Menu\n\n");  //if MasterVerify()!=0
                    Beep(200, 900);
                    getch();
                    mainmenu();
                }
                break;

            case 69:
            case 101:
                exit(1);
            default:
            {
                printf ("\nInvalid Selection!\nEnter again:");
                Beep(200, 900);
                goto askchoice2; //asks the user to input his/her choice again
            }
    }
}

int MasterVerify()
{
    char master[]="createme", key[10], pas;
    int i=0;
    SetColor(111);
    printf("\n\n\nEnter the master password: ");
	while (pas!='\n')
    {
        pas=getche();
	    if (pas==13)    //maximum allowed length of password is 13
            break;
        if (pas!='\b')
        {
            key[i]=pas;
            printf("\b*");  //displays asterisk in place of characters of password thus enhancing security
        }
        else if (pas=='\b')
        {
            printf (" ");
            printf ("\b");
            i=i-2;
        }
        i=i+1;
	}
    printf ("\n");
    key[i]='\0';
    return (strcmp(master,key));
}

void CreateManager()
{
	FILE *f1;
	char p;
	int i=0;
	SetColor(14);
    if((f1=fopen("authorize1.dat","ab+"))==NULL)  
    {
        if ((f1=fopen("authorize1.dat","wb+"))==NULL)
        {
            printf ("cannot open the file");
            Beep(200, 900);
            getch();
            mainmenu();
        }
    }
    fflush(stdin);
    printf ("\n\nEnter the user name:");
    gets(b.admin_name);
    printf ("Enter the password:");
    while (p!='\n')
    {
        p=getche();
        if (p==13)
            break;
        if (p!='\b')
        {
            b.admin_password[i]=p;
            printf("\b*");
        }
        else if (p=='\b')
        {
            printf (" ");
            printf ("\b");
            i=i-2;
        }
        i=i+1;
    }
    printf("\n");
    b.admin_password[i]='\0';
    fwrite(&b,sizeof(b),1,f1);
    fflush(stdin);
    fclose(f1);
    printf ("Created Successfully!");
    printf("\n\nEnter any key to get redirected back to main menu.\n");
    getch();
	mainmenu();
}

void CreateCashier()
{
	FILE *f2;
	char name,p;
	int i=0;
	SetColor(14);
	if((f2=fopen("authorize2.dat","ab+"))==NULL)
    {
        if ((f2=fopen("authorize2.dat","wb+"))==NULL)
        {
            printf ("\n\nCannot open.");
            Beep(200, 900);
            getch();
            mainmenu();
        }
    }
    fflush(stdin);
    printf ("\n\nEnter the cashier's user name:");
    gets(b.user_name);
    printf ("Enter the password:");
    while (p!='\n')
    {
        p=getche();
        if (p==13)
            break;
        if (p!='\b')
        {
            b.user_password[i]=p;
            printf("\b*");
        }
        else if (p=='\b')
        {
            printf (" ");
            printf ("\b");
            i=i-2;
        }
        i=i+1;
    }
    printf ("\n");
    b.user_password[i]='\0';
    fwrite(&b,sizeof(b),1,f2);
    fflush(stdin);
    fclose(f2);
    printf ("Created Successfully!");
    printf("\n\nEnter any key to get redirected back to main menu.\n");
    getch();
    mainmenu();
}

void Verification()
{
	FILE *f1;
	FILE *f2;
	int i,flag1=0,len,j;
	char name1[50],password1[50],name2[50],password2[50],p1,p2;
	char choice3,choice4;
	system("cls");
	printf("\n\t\t     SIGN IN   ");
	printf("\n\t\t================\n\n");
	SetColor(10);
	printf ("\nTo login as manager press (M).");
	printf ("\nTo login as cashier press (C)");
	printf ("\nTo return to main menu press (R):\n");
	la1:
	choice3=getche();
	switch (choice3)
	{
			case 77:
			case 109:
                if((f1=fopen("authorize1.dat","rb+"))==NULL)
                {
                    printf ("\nCannot open/ Create Manager First !\n");
                    Beep(200, 900);
                    getch();
                    mainmenu();
                    break;
                }
				askname:
                fflush(stdin);
				printf ("\n\nEnter the user name:");
				gets(name1);
				while(fread(&b,sizeof(b),1,f1)==1)
				{
                    if (strcmp(name1,b.admin_name)==0)
                    {
                        while (flag1==0)
                        {
							printf ("Enter the password:");
                            i=0;
                            while (p1!='\n')
                            {
                                p1=getche();
                                if (p1==13)
                                    break;
                                if (p1!='\b')
                                {
                                    password1[i]=p1;
                                    printf("\b*");
                                }
                                else if (p1=='\b')
                                {
                                    printf (" ");
                                    printf ("\b");
                                    i=i-2;
                                }
                                i=i+1;
                            }
                            printf ("\n");
                            password1[i]='\0';
                            if (strcmp(password1,b.admin_password)==0)
                            {
                                flag1=1;
								printf ("\nWelcome!");
								Sleep(1000);
								fclose(f1);
                                ManagerMenu();
                            }
                            else
                            {
                                printf ("\nInvalid Password!\n");
                                Beep(200, 900);
                                for (j=0;j<45;j++)
                                    password1[j]='\0';
                                getch();
                            }
                        }
                        break;
					}
					else
                    {
                        printf ("\nUser name not found.\n");
                        Beep(200, 900);
                        getch();
                        rewind(f1);
                        goto askname;
                        break;
                    }
					fclose(f1);
				}
				break;
            case 99:
            case 67:
                f2=fopen("authorize2.dat","rb+");
                if((f2=fopen("authorize2.dat","rb+"))==NULL)
                {
                    printf ("\nCannot open / Create Cashier First !\n");
                    Beep(200, 900);
                    getch();
                    mainmenu();
                    break;
                }
                else
                {
                    askname1:
                    fflush(stdin);
                    printf ("\n\nEnter the user name:");
                    gets(name2);
                    while(fread(&b,sizeof(b),1,f2)==1)
                    {
                        if (strcmp(name2,b.user_name)==0)
                        {
                            while (flag1==0)
                            {
                                strcpy(CashierName,name2);
                                printf ("Enter the password:");
                                i=0;
                                while (p2!='\n')
                                {
                                    p2=getche();
                                    if (p2==13)
                                        break;
                                    if (p2!='\b')
                                    {
                                        password2[i]=p2;
                                        printf("\b*");
                                    }
                                    else if (p2=='\b')
                                    {
                                        printf (" ");
                                        printf ("\b");
                                        i=i-2;
                                    }
                                    i=i+1;
                                }
                                printf ("\n");
                                password2[i]='\0';
                                if (strcmp(password2,b.user_password)==0)
                                {
                                    flag1=1;
                                    printf ("\nWelcome!");
                                    printf("\n\nLoading");
                                    for (i=0;i<3;i++)
                                    {
                                        Sleep(250);
                                        printf (".");
                                    }
                                    fclose(f2);
                                    CashierMenu();
                                    break;
                                }
                                else
                                {
                                    printf ("Invalid Password!\n");
                                    Beep(200, 900);
                                    for (j=0;j<45;j++)
                                        password1[j]='\0';
                                    getch();
                                }
                            }
                            break;
                        }
                        else
                        {
                            printf ("\nUser name not found !");
                            Beep(200, 900);
                            rewind(f2);
                            getch();
                            goto askname1;
                        }
                    }
                    fclose(f2);
                }
                break;
            case 114:
            case 82:
                mainmenu();
                break;
            default:
                printf ("\nInvalid Selection!\nEnter again:\n");
                Beep(200, 900);
                goto la1;
        }
}

void CashierMenu()
{
	long int i,j;char ch;
	SetColor(219);
   	system("cls");
	printf ("\nBilling is ready!");
	printf ("\nPress (E) to exit.\nOR\nAny other key to continue billing:\n");
	ch=getche();
	switch (ch)
	{
			case 69:
			case 101:
                mainmenu();
            default:
                Billing();
	}
}

void ManagerMenu()
{
	char choice4;
	long int i,j;
	printf ("\nLoading");
	for (i=0;i<3;i++)
	{
			Sleep(250);
			printf (".");
	}
	system("cls");
    printf("\n\t\t  ADMIN MENU\n");
    printf("\t\t**************\n\n");
	SetColor(219);
	printf ("\nEnter (A) to add to good list.");
	printf ("\nEnter (E) to  edit the good list.");
	printf ("\nEnter (D) to display list of goods.");
	printf ("\nEnter (S) to view the total sales.");
	printf ("\nPress (space bar) to delete to good list.");
	printf ("\nEnter (R) to return to Main Menu:\n");
	la2:
        choice4=getche();
        switch (choice4)
        {
            case 65:
            case 97:
                GoodsEntry();
                break;
            case 69:
            case 101:
                EditGoods();
                break;
            case 68:
            case 100:
                GoodsListDisplay();
                break;
            case 32:
                DeleteGoods();
                break;
            case 115:
            case 83:
                TotalSalesDisplay();
                break;
            case 82:
            case 114:
                mainmenu();
                break;
            default:
                printf("\nInvalid Selection!\nEnter again:\n");
                Beep(200, 900);
                goto la2;
        }
}

void GoodsEntry()
{
	FILE *f;
	char ques;
	printf("\n");
	SetColor(13);
	if ((f=fopen("goods.txt","ab+"))==NULL)
	{
        if ((f=fopen("goods.txt","wb+"))==NULL)
        {
            printf ("\nCannot open the file\n");
            Beep(200, 900);
            getch();
        }
	}
	while(1)
	{
        printf ("\nEnter the item code to be added:");
        gets (a.itemcode);
        printf ("Enter the item name:");
        gets (a.itemname);
        printf ("Enter the rate for unit quantity:");
        scanf ("%d",&a.rate);
        fwrite(&a,sizeof(a),1,f);
        fflush(stdin);
        printf ("\nEnter the 'esc' key to exit or any other key to continue:");
        ques=getche();
        if(ques==27)
            break;
	}
	fclose(f);
	ManagerMenu();
}

void GoodsListDisplay()
{
	FILE *f;
	int i,j;
	printf ("\nLoading");
	for (i=0;i<4;i++)
	{
        for (j=0;j<=100000000;j++);
        printf (".");
	}
	system("cls");
	printf("\n\n");
	SetColor(15);
	printf ("\b\b\b   \b\b\b");
	printf ("\b\b\b");
	if ((f=fopen("goods.txt","rb"))!=NULL)
	{
            printf ("                       GOODS INVENTORY                   ");
			printf ("\n\n\n Item code       Item name                    Cost(Rs.)\n");
			printf ("-------------------------------------------------------\n");
			while (fread(&a,sizeof(a),1,f)==1)
			{
				printf("%s",a.itemcode);
				printf("\t\t");
				printf("%s",a.itemname);
				if ((strlen(a.itemname)>0)&& (strlen(a.itemname)<=7))   //for tabular formatting of output
                    printf("\t\t");
                if ((strlen(a.itemname)>7)&& (strlen(a.itemname)<13))
                    printf ("\t ");
				if ((strlen(a.itemname)>=13) && (strlen(a.itemname)<16))
                    printf ("\t");
				printf ("\t\t%d\n",a.rate);
			}
			fclose(f);
			getch();
	}
	ManagerMenu();
}
void EditGoods()
{
	FILE *f;
	char itemcode[50];
	int size=sizeof(a);
	SetColor(14);
	printf("\n\n");
	if ((f=fopen("goods.txt","rb+"))!=NULL)
	{
        printf ("\nEnter the item code of the product:");
        gets(itemcode);
        fflush(stdin);
        while (fread(&a,sizeof(a),1,f)==1)
        {
            if (strcmp(a.itemcode,itemcode)==0)
            {
				printf ("\nEnter the new item code:");
				gets (a.itemcode);
				printf ("Enter the new item name:");
				gets (a.itemname);
				printf ("Enter the rate for unit quantity:");
				scanf ("%d",&a.rate);
				fseek(f,-size,SEEK_CUR);    //points the file pointer to the location of item to be replaced
				fwrite(&a,sizeof(a),1,f);
				printf ("\nDone!\n");
				getch();
				break;
            }
        }
        fclose(f);
	}
	ManagerMenu();
}

void DeleteGoods()
{
	FILE *f,*temp;
	char itemcode[50];
	int size=sizeof(a);
	f=fopen("goods.txt","rb");
	temp=fopen("tempgoods.txt","wb");
	SetColor(177);
	printf ("\n\n\nEnter the item code of the product to be deleted:");
	fflush(stdin);
	gets(itemcode);
	while (fread(&a,sizeof(a),1,f)==1)
	{
		if (strcmp(a.itemcode,itemcode)!=0)   //writes every other data except that to be deleted to a temporary file
            fwrite(&a,sizeof(a),1,temp);
    }
    fclose(f);
    remove("goods.txt");
    fclose(temp);
	rename("tempgoods.txt","goods.txt");
	printf ("\nSuccessfully Deleted!");
	ManagerMenu();
}

void Billing()
{
	struct goods b[50];
	FILE *f;
	FILE *f1;char itemcode[50];int i=0,j,sum=0;
	int quantity[200],cost[200],tender,change,disc;
	char choice;
	time_t t;
	system("cls");
	SetColor(11);
	printf("\t\t\t*****************\n");
	printf("\t\t\t**** BILLING ****");
	printf("\n\t\t\t*****************");
	f=fopen("goods.txt","rb+");
	f1=fopen("keeprecords.dat","ab+");
	fflush(stdin);
	printf ("\n\nEnter the items:");
	do
	{
        printf ("\n\nEnter the item code: ");
        scanf("%s",&itemcode);
        while(fread(&a,sizeof(a),1,f)==1)
        {
            if(strcmp(a.itemcode,itemcode)==0)
            {
				puts(a.itemname);
				printf ("Rs.%d\n",a.rate);
				strcpy (b[i].itemcode,a.itemcode);
				strcpy (b[i].itemname,a.itemname);
				b[i].rate=a.rate;
				printf("Enter the quantity:");
				scanf ("%d",&quantity[i]);
				cost[i]=quantity[i]*b[i].rate;
				sum=sum+cost[i];
				strcpy (c.itemcode,b[i].itemcode);
				strcpy (c.itemname,b[i].itemname);
				c.rate=b[i].rate;
				c.quantity=quantity[i];
				c.cost=cost[i];
				fwrite(&c,sizeof(c),1,f1);
				fflush(stdin);
                i++;
				break;
            }
        }
        rewind(f);
        printf("\nEnter P to print bill.\nOr enter any key to continue adding items. ");
        choice = getch();
        if(choice == 'P' || choice == 'p')
            break;
    }while(1);
    fclose(f);
    fclose(f1);
    system("cls");
    SetColor(15);
    printf("\t\t\t\t  BD SUPER-MARKET\n\t\t\t\t   Ready for you\n");
    printf("\t\t\t\tKolalam Pur, Nepal");
    time(&t);
    printf("\n\n\t%s\n",ctime(&t));
    printf ("\n Item code      Item name             Cost\t\tQty\t\tAmount\n");
    printf ("------------    -----------        ---------\t\t----\t\t------\n");
    for (j=0;j<i;j++)
    {
        printf("%s",b[j].itemcode);
        printf("\t\t");
        printf("%s",b[j].itemname);
        if ((strlen(b[j].itemname)>0)&& (strlen(b[j].itemname)<=7))
            printf("\t\t");
        if ((strlen(b[j].itemname)>7)&& (strlen(b[j].itemname)<13))
			printf ("\t");
        if ((strlen(b[j].itemname)>=13) && (strlen(b[j].itemname)<16))
			printf ("\t");
        printf("\t%d\t\t%d\t\t%d\n",b[j].rate,quantity[j],cost[j]);
    }
    printf ("\n\t\t\t\t\tTotal:\tRs.%d",sum);
    disc=sum<=1000?0.1*sum:((sum>1000&&sum<=3000)?0.12*sum:0.15*sum);   //predefined criteria for discount
    printf("\n\t\t\t\t\tDiscount: Rs.%d",disc);
    printf("\n\t\t\t\t\tNet Total: Rs.%d",sum-disc);
    printf ("\n\t\t\t\t\tTender:\tRs.");
    scanf ("%d",&tender);
    change=tender-(sum-disc);
    printf ("\t\t\t\t\tChange:\tRs.%d",change);
    printf ("\nCashier: ");
    puts(CashierName);
    printf("\n\n\t\t\t\t**************************\n");
    printf("\t\t\t\t* THANK YOU FOR VISITING *\n");
    printf("\t\t\t\t**************************\n");
    getch();
    CashierMenu();
}

void TotalSalesDisplay()
{
	FILE *f4;long int i=0,j,k;
	printf ("\n\nLoading");
	for (k=0;k<3;k++)
	{
        Sleep(250);
        printf (".");
	}
	system("cls");
	printf("\n\t\t\t TOTAL SALES\n");
	SetColor(2);
	if ((f4=fopen("keeprecords.dat","r+"))!=NULL)
	{
        printf ("\n Item code      Item name              Cost       Quantity     Amount\n");
        printf ("-------------------------------------------------------------------------\n");
        while (fread(&c,sizeof(c),1,f4)==1)
        {
            printf("%s",c.itemcode);
            printf("\t\t");
            printf("%s",c.itemname);
            grandtotal=grandtotal+c.cost;
            if ((strlen(c.itemname)>0)&& (strlen(c.itemname)<=7))
				printf("\t\t");
            if ((strlen(c.itemname)>7)&& (strlen(c.itemname)<13))
				printf ("\t");
            if ((strlen(c.itemname)>=13) && (strlen(c.itemname)<16))
				printf ("\t");
            printf ("\t%d\t    %d\t\t%d\n",c.rate,c.quantity,c.cost);
            i=i+1;
        }
        printf ("\nTotal Sales=Rs. %d.00",grandtotal);
        fclose(f4);
	}
	else{
        printf("\nSales Data Couldn't Be Opened.\n");
        Beep(200, 900);
	}getch();
	ManagerMenu();
}

void DeleteData()
{
    int i;
    char ch;
    SetColor(14);
    i = 0;
    system("cls");
    printf("\n\t\t       DELETE USER DATA        ");
    printf("\n\t\t*******************************");
    printf("\n\nEnter (M) to delete Managers' User Data: \n");
    printf("Enter (C) to delete Cashiers' User Data:\n");
    printf("Enter (S) to delete Sales Data:\n");
    printf("Enter (R) to return to Main Menu: \n");
    la4:
    ch = getche();
    switch(ch)
    {
        case 77:
        case 109:
            i = remove("authorize1.dat");
            if (i==0)
            {
                printf("\nManager's Data Has Been Cleared Successfully !\nPress Enter to continue. \n");
                getch();
                DeleteData();
            }
            else
            {
                printf("\nManager's Data Couldn't Be Cleared!\nPress Enter to continue. \n");
                Beep(200, 900);
                getch();
                DeleteData();
            }
            break;

        case 67:
        case 99:
            i = remove("authorize2.dat");
            if (i==0)
            {
                printf("\nCashier's Data Has Been Cleared Successfully !\nPress Enter to continue.\n");
                getch();
                DeleteData();
            }
            else
            {
                printf("\nCashier's Data Couldn't Be Cleared!\nPress Enter to continue. ");
                Beep(200, 900);
                getch();
                DeleteData();
            }
            break;

        case 115:
        case 83:
            i = remove("keeprecords.dat");
            if (i==0)
            {
                printf("\nSales Data Has Been Cleared Successfully !\nPress Enter to continue. ");
                getch();
                DeleteData();
            }
            else
            {
                printf("\nSales Data Couldn't Be Cleared!\nPress Enter to continue. ");
                Beep(200, 900);
                getch();
                DeleteData();
            }
            break;

        case 82:
        case 114:
            mainmenu();
            break;

        default:
            printf("\n\tEnter Valid Option ! ");
            Beep(200, 900);
            break;
    }
    mainmenu();
    getch();
}
