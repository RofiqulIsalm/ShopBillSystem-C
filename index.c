#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
struct item{
    char item[20];
    float price;
    int qty;
};
struct orders
{
    char customar[50];
    char date[30];
    int num_item;
    struct item itm[50];
};
int opt_cho();
void Bill_hader(char date[50],char name[50]);
void Bill_body(char product[50],int qty,float price);
void Bill_footer(float total);
void textcolor(int color_name);



int main(){
    struct orders ord;
    struct orders order;
    int n;
    float total;
    char save,ch;
    FILE *fp;
    int opt;
    Flag:
    opt = opt_cho();
    switch(opt){
        case 1:
           
            system("cls");
            printf("\n\t\t\t\t===========================================\n");
            printf("\t\t\t\t........ Wellcome To Shop Of Pala .........\n");
            printf("\t\t\t\t===========================================\n");
            printf("\n\n\n");
            printf("\nEnter Customar name\t\t\t: ");
            fgets(ord.customar,50,stdin);
            ord.customar[strlen(ord.customar)-1]=0;
            strcpy(ord.date,__DATE__);

            printf("\nPlease enter the item\t\t\t: ");
            scanf("%d",&n);
            ord.num_item=n;
            fgetc(stdin);
            for (int i = 0; i < n; i++)
            {
                
                printf("\nPlease enter %d item\t\t\t: ",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                printf("\nPlease enter quntity\t\t\t: ");
                scanf("%d",&ord.itm[i].qty);
                printf("Please enter unity price\t\t: ");
                scanf("%f",&ord.itm[i].price);
                fgetc(stdin);
                total += ord.itm[i].qty*ord.itm[i].price;
            }
            Bill_hader(ord.date,ord.customar);
            for (int i = 0; i < ord.num_item; i++)
            {
                Bill_body(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            Bill_footer(total);
            printf("\n\n\t\t\t\tDo you want to save [Y/N]\t: ");
            scanf("%c",&save);
            if (save=='Y'||save=='y')
            {
                fp =fopen("Shop_Bill.txt","a+");
                fwrite(&ord,sizeof(struct orders),1,fp);
                if (fwrite!=0)
                {
                    system("cls");
                    textcolor(2);
                    printf("\n\t\t\t\t\t\t=======================");
                    printf("\n\t\t\t\t\t\t== Successfully Save ==");
                    printf("\n\t\t\t\t\t\t=======================");
                    textcolor(0);
                    printf("\n\n\t\t\t\t\t\tBack To Home [Y/N]:  ");
                    fgetc(stdin);
                    scanf("%c",&ch);
                    textcolor(7);
                    if (ch=='Y'|| ch =='y')
                    {
                        goto Flag;
                    }
                    else
                    {
                        return 0;
                    }
                    
                    
                }
                else{
                    system("cls");
                    textcolor(4);
                    printf("\n\t\t\t\t\t\t=======================");
                    printf("\n\t\t\t\t\t\t==   Error to save   ==");
                    printf("\n\t\t\t\t\t\t=======================");
                    textcolor(0);
                    printf("\n\n\t\t\t\t\t\tBack To Home [Y/N]:  ");
                    scanf("%c",&ch);
                    textcolor(7);
                    if (ch=='Y'|| ch == 'y')
                    {
                        opt_cho();
                    }
                    else
                    {
                        return 0;
                    }
                }  
                fclose(fp);     
            }
            break;
        
        case 2:
            system("cls");
            fp = fopen("Shop_Bill.txt","r");
            printf("\n\t\t\t\t==============================================");
            printf("\n\t\t\t\t............... Customar List  ...............");
            printf("\n\t\t\t\t==============================================");
            printf("\n");
            while(fread(&order,sizeof(struct orders),1,fp)){
                total = 0;
                Bill_hader(order.date,order.customar);
                for(int i=0;i<order.num_item;i++){
                    Bill_body(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    total+=order.itm[i].qty * order.itm[i].price;
                }
                Bill_footer(total);
            }
            
            printf("\n\t\t\t\t\t\t\t\t\t\t\t\tGo Back[Y/N]: ");
            scanf("%c",&ch);
            if (ch=='y'|| ch=='Y')
            {
                goto Flag;
            }
            
            fclose(fp);
            break;
        case 3:
            system("cls");
            system("COLOR 0A");
            printf("\n\t\t\t\t==============================================");
            printf("\n\t\t\t\t.............. Exit From Program .............");
            printf("\n\t\t\t\t==============================================");
            printf("\n\n\n");
            getchar();
            return 0;
        }
    
}
void textcolor(int color_name){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_name);
}
void Bill_hader(char date[50],char name[50]){
    system("cls");

    printf("\n\t\t\t\t==============================================");
    printf("\n\t\t\t\t............... You Total Bill ...............");
    printf("\n\t\t\t\t==============================================");
    printf("\n");
    printf("\t\t\t\tDate: %s",date);
    printf("\n\t\t\t\tCustomar Name:\t%s",name);
    printf("\n\t\t\t\t==============================================\n");
    printf("\t\t\t\tProduct\t\tQuntity\t\t\tPrice");
    printf("\n\t\t\t\t______________________________________________");
}
void Bill_body(char product[50],int qty,float price){
    printf("\n\t\t\t\t%s\t\t%d\t\t\t%.2f",product,qty,qty*price);
}
void Bill_footer(float total){
    float discount = 0.1 * total;
    float net_total = total - discount;
    float cgest = 0.09 * net_total;
    float graed_total = net_total +2 * cgest;
    printf("\n\t\t\t\t==============================================");
    printf("\n\t\t\t\tSub total\t\t\t\t%.2f",total);
    printf("\n\t\t\t\tDiscount 10%%:\t\t\t\t%.2f",discount);
    printf("\n\t\t\t\t\t\t\t\t--------------");
    printf("\n\t\t\t\tNet Total:\t\t\t\t%.2f",net_total);
    printf("\n\t\t\t\tCGST 9%%:\t\t\t\t%.2f",cgest);
    printf("\n\t\t\t\tSGST 9%%:\t\t\t\t%.2f",cgest);
    printf("\n\t\t\t\t----------------------------------------------");
    printf("\n\t\t\t\tToTal Cost:\t\t\t\t%.2f",graed_total);
}
int opt_cho(){
    int opt;
    system("cls");
    printf("\n\t\t\t\t===========================================\n");
    printf("\t\t\t\t........ Wellcome To Shop Of Pala .........\n");
    printf("\t\t\t\t===========================================\n");
    printf("\n\n\n");
    printf("Please choose one of these : \n");
    printf("............................\n\n");
    printf("1 ==> Add New Customar.\n");
    printf("2 ==> Last Customar.\n");
    printf("3 ==> Exit.\n");
    printf("\n\n");
    printf("Your Choice :\t");
    scanf("%d",&opt);
    fgetc(stdin);
return opt;
}
