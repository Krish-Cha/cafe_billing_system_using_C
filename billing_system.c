 #include<stdio.h>
 #include<conio.h>
 #include<string.h>
 #include<stdlib.h>

/*------Items structure---------*/

 struct items
 {
    char item[20];
    float price;
    int qty;
 };

/*-------order structure------*/

 struct orders
 {
    char customer[50];
    char date[50];
    int numofItems;
    struct items item[50];
 };

void billmaking(char name[50],char date[30])
{
    printf("\n\n");
    printf("\t\t\t\t\t\tNi-TECH CAFE\t\t\t\t\t\t");
    printf("\n-------------------------------------------------------------------------------------------");
    printf("\nDate: %s",date);
    printf("\nInvoice to: %s",name );
    printf("\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Items:\t\t");
    printf("Quantity:\t\t");
    printf("Total:\t\t");
    printf("\n--------------------------------------------------------------------------------------------");
    printf("\n");  
}

void billing(char item[20],int qty,float price)
{
    printf("%s\t\t",item);
    printf("   %d\t\t",qty);
    printf("         %0.2f\t\t",qty*price);
    printf("\n");
}

void bill_show(float total)
{
    printf("\n");
    float dis=0.2*total;
    float netTotal=total-dis;
    float gst=0.18*netTotal;
    float grandTotal = netTotal+gst;
    printf("----------------------------------------------------------------------------------------------");
    printf("\nSub Total\t\t\t%0.2f",total);
    printf("\nDiscount @20%\t\t\t%0.2f",dis);
    printf("\n\t\t\t\t------------------------------------------------------------------------------------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nGST @18%\t\t\t%.2f",gst);
    printf("\n\t\t\t\t------------------------------------------------------------------------------------");
    printf("\nGraand Total\t\t\t%.2f",grandTotal);
    printf("\n\t\t\t\t------------------------------------------------------------------------------------");
}

/*--------------Main function--------------------*/

int main()
{
    int opt,n,i;
    char name[50];
    char saveBill='y',flag='y';
    FILE *fp;
    while (flag=='y')
    {
        float toatl;
        int i=0;
        struct orders ord;
        struct orders order;
        printf("=========================================================================================");

        printf("\n1.Genarate Invoice");
        printf("\n2.show all Invoices");
        printf("\n3.Search Invoices");
        printf("\n4.Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d",&opt);

        printf("\nYour Choice is %d",opt);
        printf("\n");

        switch (opt)
        {
        case 1:
               printf("\nEnter the Name of Customer:  ");
               fgetc(stdin);
               fgets(ord.customer,50,stdin);
               ord.customer[strlen(ord.customer)-1]='\0';
               strcpy(ord.date,__DATE__);
               printf("\nEnter the Number of Items:  ");
               scanf("%d",&n);
               ord.numofItems=n;

               for(i=0;i<n;i++)
               {
                fgetc(stdin);
                printf("\n\n");
                printf("\nEnter the Item %d:  ",i+1);
                fgets(ord.item[i].item,20,stdin);
                ord.item[i].item[strlen(ord.item[i].item)-1]='\0';
                printf("\nEnter your Quantity:  ");
                scanf("%d",&ord.item[i].qty);
                printf("\nEnter the Price:  ");
                scanf("%f",&ord.item[i].price);
                toatl += ord.item[i].qty *ord.item[i].price;
               }

               billmaking(ord.customer,ord.date);
                
               for(i=0;i<ord.numofItems;i++)
               {
                billing(ord.item[i].item,ord.item[i].qty,ord.item[i].price);
               }
               bill_show(toatl);
               printf("\nDo you wnat to save your Invoice [y/n]:  ");
               scanf("%s",&saveBill);
               if (saveBill=='y')
               {
                  fp=fopen("nitech.txt","a+");    /*----file opening----*/
                  fwrite(&ord,sizeof(struct orders),1,fp);
                  if (fwrite!=0)
                  {
                     printf("\nSaved Successfully!");
                  }
                  else
                      printf("\nError Saving");
                  fclose(fp);
                  
               }
               
            break;
        case 2:
               fp=fopen("nitech.txt","r");
               printf("\n**********************************Previous Invoice****************************");
               while(fread(&order,sizeof(struct orders),1,fp))
               {
                float tot=0;
                billmaking(order.customer,order.date);
                for(i=0;i<order.numofItems;i++)
                {
                    billing(order.item[i].item,order.item[i].qty,order.item[i].price);
                    tot +=order.item[i].qty*order.item[i].price;
                }
                bill_show(tot);
               }
               fclose(fp);
               break;
        case 3:
               printf("\nEnter the name of customer:\t");
               fgetc(stdin);
               fgets(name,50,stdin);
               name[strlen(name)-1]='\0';

               fp=fopen("nitech.txt","r");
               printf("\n***********************************Invoice Name %s****************************",name);
               while(fread(&order,sizeof(struct orders),1,fp))
               {
                float tot=0;
                if(!strcmp(order.customer,name))
                {
                billmaking(order.customer,order.date);
                for(i=0;i<order.numofItems;i++)
                {
                    billing(order.item[i].item,order.item[i].qty,order.item[i].price);
                    tot +=order.item[i].qty*order.item[i].price;
                }
                bill_show(tot);
                i=1;
               }
               fclose(fp);
               }
               if(!i)
               {
                printf("\nInvoice not Found!");
               }
               fclose(fp);
               break;
        case 4:
              printf("\n---------------------------------THANK YOU !----------------------------------------");
              exit(0);
              break;       
        default:
            printf("\nEnter your correct choice ");
            break;
        }

        printf("\nAnythings else ?[y/n]\t");
        scanf("%s",&flag);
    }
    printf("\n\n");
    return 0;
  }

 
