#include<stdio.h>
#include<string.h>

 struct Inventory{
    char name[50];
    float price;
    float DisInPercent;
    char Stock[50];
    char Condition[50];
    char AmmoAvailable[50];
    char InstallmentAvail[50];
    int Guncode;
    int legalcode;
    char GunDetail[100];
    char PaymentDue[50];
    char StorageArea[50];
    char BestCustomer[50];
    char ProfitOrLoss[50];
    char MoreStock[50];
    char AllAmmoStock[50];
    char ChangesReq[50];
    char ImportantNotes[50];
    char Reminders[50];
    char ColorsAvail[50];
};


void addInventory();              
void Input(struct Inventory *I);         
void saveInitialRecords(struct Inventory rec[], int n); 
void displayInventory();          
void searchInventory();           
void updateDiscount();            
void removeInventory();           
void countInventory();            
void updatePriceByCode();        
void displayProfitItems();        
void displayLossItems();          
void searchByName();              
void displayByStorageArea();      
void displayByColor();            
void showGunRecord();            

int main()
{
    int choice;

    struct Inventory Rec[20]={
        {"M416",1000,0.0,"Available","New","Yes","No",123,1122,"Assault rifle","No","Backside","Harry","Profit","No","10K","No","Good","None","Black"},
        {"Scar-L",600,0.0,"Available","New","Yes","No",213,2211,"Assault rifle","No","Inventory","None","No","No","5K","No","Average","None","Brown"},
        {"AUG-43",800,0.0,"Available","New","Yes","No",312,1221,"Assault rifle","No","Storage","Zyrx","Profit","No","2.5K","No","Good","None","Green"},
        {"UMP-45",400,0.0,"Available","New","Yes","No",345,2112,"SMG","No","Inventory","None","Profit","No","5K","No","Good","None","Brown"},
        {"S12K",1000,0.0,"Available","New","Yes","No",567,3211,"Shotgun","No","Backside","Harry","Profit","No","12 Boxes","No","Ammo","None","Grey"},
        {"DBS",1500,0.0,"Available","New","Yes","No",789,4211,"Shotgun","No","Storage","None","No","No","24 Boxes","No","Stable","None","Dark Grey"},
        {"S686",700,0.0,"Available","New","Yes","No",567,4231,"Shotgun","No","Inventory","Robert","Profit","No","12 Boxes","No","Ammo","None","Red"},
        {"S1897",800,0.0,"Available","New","Yes","No",657,9911,"Shotgun","No","Inventory","None","Low","No","31 Boxes","No","Sell","None","Grey"},
        {"M24",600,0.0,"Available","New","Yes","No",456,8711,"Sniper","No","Inventory","Harry","Profit","No","1K","No","Ammo","None","Dark Grey"},
        {"AWM",1500,0.0,"Available","New","Yes","No",999,8799,"Sniper","No","Backside","Smith","Profit","No","10 Boxes","No","Expensive","None","Green"}
    };

    saveInitialRecords(Rec,10);

    do{
        printf("\n-------- INVENTORY MENU----------\n");
        printf("1.  Add Inventory\n");
        printf("2.  Display Inventory\n");
        printf("3.  Search by Gun Code\n");
        printf("4.  Update Discount\n");
        printf("5.  Remove Inventory\n");
        printf("6.  Count Records\n");
        printf("7.  Update Price\n");
        printf("8.  Display Profit Items\n");
        printf("9.  Display Loss Items\n");
        printf("10. Search by Name\n");
        printf("11. Display by Storage Area\n");
        printf("12. Display by Color\n");
        printf("13. Show specific gun Record\n");
        printf("14. Save Initial Records Again\n");
        printf("15. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:{
			addInventory();
			break; }
            case 2: {
			displayInventory();
			 break; }
            case 3:{
			 searchInventory();
			  break;}
            case 4:{
			 updateDiscount(); 
			 break; }
            case 5: {
			removeInventory();
			 break; }
            case 6:{
			 countInventory(); 
			 break;}
            case 7: {
			updatePriceByCode();
			 break;}
            case 8:{
			 displayProfitItems();
			  break;}
            case 9:{
			displayLossItems(); 
			break; }
            case 10:{
			searchByName(); 
			break;  }
            case 11:{
			displayByStorageArea();
			 break; }
            case 12:{
			 displayByColor(); 
			 break; }
            case 13:{
			 showGunRecord();
			  break;}
            case 14: {
			saveInitialRecords(Rec,10);
			 break;  }
            case 15:{
			 printf("Exiting Program...\n");
			  break; }
            default: printf("Invalid Choice\n");
        }
    }while(choice!=15);

    return 0;
}



void addInventory()
{
    struct Inventory I;
    Input(&I);
    FILE *f=fopen("record.dat","ab");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    fwrite(&I,sizeof(I),1,f);
    printf("Gun record added successfully!\n");
    fclose(f);
}

void Input(struct Inventory *I)
{   fflush(stdin);
    printf("Enter gun name:\n");
    gets(I->name);
    printf("Enter price of this gun:\n");
    scanf("%f",&I->price);
    printf("Enter discount in percent:\n");
    scanf("%f",&I->DisInPercent);
    printf("Choose a code for this gun and enter it:\n");
    scanf("%d",&I->Guncode);
}

void saveInitialRecords(struct Inventory rec[], int n)
{
    FILE *f=fopen("record.dat","wb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    for(int i=0;i<n;i++)
        fwrite(&rec[i],sizeof(struct Inventory),1,f);
    fclose(f);
}

void displayInventory()
{
    struct Inventory I;
    FILE *f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1)
        printf("Name:%s | Price:%.2f | Code:%d\n",I.name,I.price,I.Guncode);
    fclose(f);
}

void searchInventory()
{
    struct Inventory I;
    int code;
    printf("Enter valid gun code:\n");
    scanf("%d",&code);
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(I.Guncode==code)
            printf("Found: %s %.2f\n",I.name,I.price);
        }
    fclose(f);
}

void updateDiscount()
{
   struct Inventory I;
    float new_dis;
    int flg=0;
    FILE *f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    FILE *tf=fopen("Temp.dat","wb");
    if(tf==NULL){
    	printf("Unable to open file");
    	return;
	}
    int code;
    printf("Enter valid gun code:\n");
    scanf("%d",&code);
    while(fread(&I,sizeof(I),1,f)==1){
        if(I.Guncode==code){
        	flg=1;
            printf("New Discount:\n");
            scanf("%f",&new_dis);
            I.DisInPercent=new_dis;
        }
        fwrite(&I,sizeof(I),1,tf);
    }
    fclose(f);
    fclose(tf);
    if(flg==1){
    	remove("record.dat");
    	rename("Temp.dat","record.dat");
    	printf("Discount Updated!\n");
	}
	else{
		remove("Temp.dat");
		printf("No gun found with this code");
	}
}

void removeInventory()
{
    struct Inventory I;
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
	FILE *t;
    t=fopen("temp.dat","wb");
    if(t==NULL){
    	printf("Unable to open file");
    	return;
	}
    int code;
    printf("Enter code of gun to be removed:\n");
    scanf("%d",&code);

    while(fread(&I,sizeof(I),1,f)==1){
        if(I.Guncode!=code){
            fwrite(&I,sizeof(I),1,t);
                       }
                   }
                   
    fclose(f);
	fclose(t);
    remove("record.dat");
    rename("temp.dat","record.dat");
    printf("Gun record removed successfully if valid code entered...");
}

void countInventory()
{
    struct Inventory I;
    int c=0;
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
    	c++;
	} 
    fclose(f);
    printf("Total Records: %d\n",c);
}

void updatePriceByCode()
{
   struct Inventory I;
    float new_price;
    int found=0;
    FILE *f;
     f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    FILE *tf=fopen("Temp.dat","wb");
    if(tf==NULL){
    	printf("Unable to open temporary file");
    	return;
	}
	int code;
    printf("Enter correct code:\n");
    scanf("%d",&code);

    while(fread(&I,sizeof(I),1,f)==1){
        if(I.Guncode==code){
            printf("Enter new price:\n");
            scanf("%f",&new_price);
            I.price=new_price;
            found=1;
        }
            fwrite(&I,sizeof(I),1,tf);
        }
        fclose(f);
        fclose(tf);
    if(found){
    	remove("record.dat");
    	rename("Temp.dat","record.dat");
    	printf("Updated successfully!\n");
	}
	else{
		printf("Round not found\n");
		remove("Temp.dat");
	}

}

void displayProfitItems()
{
    struct Inventory I;
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(strcmp(I.ProfitOrLoss,"Profit")==0){
            printf("%s\n",I.name);            }
        }
    fclose(f);
}

void displayLossItems()
{
  struct  Inventory I;
  FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(strcmp(I.ProfitOrLoss,"No")==0){
            printf("%s\n",I.name);        }
        }
    fclose(f);
}

void searchByName()
{
   struct Inventory I;
    char name[50];
    fflush(stdin);
	printf("Enter correct name of gun:\n");
	gets(name);                                       
    FILE *f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(strcmp(I.name,name)==0){
            printf("Found: %s %.2f\n",I.name,I.price);
            break;
                              }
        else{
        	printf("No gun found with this name\n");
        	break;
		}
	}
    fclose(f);
}

void displayByStorageArea()
{
   struct Inventory I;
    char area[50];
    printf("Enter storage area name:\n");
    scanf("%s",area);
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(strcmp(I.StorageArea,area)==0){
            printf("%s\n",I.name);  
			                             }
			                     }
    fclose(f);
}

void displayByColor()
{
   struct Inventory I;
    char col[50];
    printf("Enter color:\n");
    scanf("%s",col);
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(strcmp(I.ColorsAvail,col)==0){
            printf("Gun of this color present is:\n");
            printf("%s\n",I.name);      }
}
fclose(f);
}

void showGunRecord()
{
   struct Inventory I;
    int code;
    printf("Enter code of that gun:\n");
    scanf("%d",&code);
    FILE *f;
    f=fopen("record.dat","rb");
    if(f==NULL){
    	printf("Unable to open file.");
    	return;
	}
    while(fread(&I,sizeof(I),1,f)==1){
        if(I.Guncode==code){
            printf("%s %.2f %s %s %s\n",
                   I.name,I.price,I.Condition,
                   I.StorageArea,I.ColorsAvail);
               }
               }
    fclose(f);
}
