#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char mevcutKonum[255];
struct linkedlist* start;
struct mevcutKonumStack* startMevcutKonum;
struct node* bulunulanAdres;
int i=0;
int j=0;
struct linkedlist
{
    char klasorVeDosyaIsimleri[25];
    char hangiAdreste[255];
    struct linkedlist* next;
};

struct linkedlist* yeniDugum(char klasorVeyaDosyaIsmi[], char hangiAdrese[])
{
    struct linkedlist* eklenecek=(struct linkedlist*)malloc(sizeof(struct linkedlist));
    strcpy(eklenecek->klasorVeDosyaIsimleri,klasorVeyaDosyaIsmi);
    strcpy(eklenecek->hangiAdreste,hangiAdrese);
    eklenecek->next=NULL;
    return eklenecek;
}
void sonaEkle(char klasorVeyaDosyaIsmi[], char hangiAdrese[])
{
    struct linkedlist* eklenecek= yeniDugum(klasorVeyaDosyaIsmi,hangiAdrese);
    if(start==NULL)
    {
        start=eklenecek;
    }
    else
    {
        struct linkedlist* temp=start;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=eklenecek;
    }
}

void ls(char gezinmekIstenenAdres[])
{
    struct linkedlist* temp=start;
    //temp!=NULL && strcmp(temp->hangiAdreste, gezinmekIstenenAdres)==0
    while(temp!=NULL)
    {
        if(strcmp(temp->hangiAdreste,gezinmekIstenenAdres)==0)
        {
            printf("%s ", temp->klasorVeDosyaIsimleri);
        }
        temp=temp->next;

    }
    printf("\n");
}
void elemanSil(char hedef[])
{
    struct linkedlist*temp=start;
    struct linkedlist* onceki;
    while(temp!=NULL && strcmp(temp->klasorVeDosyaIsimleri,hedef)!=0)
    {
        onceki=temp;
        temp=temp->next;
    }
    onceki->next=temp->next;
    free(temp);
}
void linkedlistTraverse()
{
    struct linkedlist*temp=start;
    while(temp!=NULL)
    {
        printf("%s %s\n",temp->klasorVeDosyaIsimleri,temp->hangiAdreste);
        temp=temp->next;
    }
    printf("\n");
}
int subDirectoryCheck(char arananDosyaVeyaKlasor[])
{
    struct linkedlist* temp=start;
    while(strcmp(temp->klasorVeDosyaIsimleri,arananDosyaVeyaKlasor)!=0 )
    {
        temp=temp->next;
    }
    if(strcmp(temp->hangiAdreste,mevcutKonum)==0)
    {
        return 10;
    }
    else
    {
        return 20;
    }
}
char subDirectoryVarMi(char arananDosyaVeyaKlasor[])
{
    int flag=0;
    struct linkedlist* temp=start;
    while(temp!=NULL)
    {
        if(strcmp(arananDosyaVeyaKlasor,temp->klasorVeDosyaIsimleri)==0)
        {
            flag++;
        }
        temp=temp->next;
    }
    if(flag!=0)
    {
        return 't';
    }
    else
    {
        return 'f';
    }
}
struct mevcutKonumStack
{
    char mevcutKonum[155];
    struct mevcutKonumStack* next;
};


struct mevcutKonumStack* dugumolustur(char data[])
{
    struct mevcutKonumStack* eklenecek=(struct mevcutKonumStack*)malloc(sizeof(struct mevcutKonumStack));
    strcpy(eklenecek->mevcutKonum,data);
    eklenecek->next=NULL;
    return eklenecek;
}
void mevcutKonumStackEkle(char data[])
{
    struct mevcutKonumStack* eklenecek= dugumolustur(data);
    if(startMevcutKonum==NULL)
    {
        startMevcutKonum=eklenecek;
    }
    else
    {
        eklenecek->next=startMevcutKonum;
        startMevcutKonum=eklenecek;
    }
    strcpy(mevcutKonum,startMevcutKonum->mevcutKonum);
}
void popMevcutKonum()
{
    if(startMevcutKonum==NULL)
    {
        printf("Stack bostur.");
    }
    else
    {
        struct mevcutKonumStack* temp;
        temp=startMevcutKonum->next;
        free(startMevcutKonum);
        startMevcutKonum=temp;
    }
    strcpy(mevcutKonum,startMevcutKonum->mevcutKonum);
}
void stackMevcutKonumGez()
{
    struct mevcutKonumStack* temp=startMevcutKonum;
    while(temp!=NULL)
    {
        printf("%s ",temp->mevcutKonum);
        temp=temp->next;
    }
    printf("\n");
}
struct node
{
    FILE* dosya[2];
    char klasorIsmi[255];
    char nodeIsmi[255];
};


void rootKlasorYarat()
{
    char rootKlasoruIsmi[255];
    printf("Ana dizini giriniz: ");
    scanf("%s", rootKlasoruIsmi);
    char path[1024];
    sprintf(path,"C:\\%s",rootKlasoruIsmi);
    mkdir(path, 0777);
    struct node* root=(struct node*)malloc(sizeof(struct node));
    strcpy(root->klasorIsmi,rootKlasoruIsmi);
    strcpy(root->nodeIsmi,path);
    strcpy(mevcutKonum,path);
    mevcutKonumStackEkle(path);
    bulunulanAdres=root;
}

void touch()
{
    char path[255];
    char girilenDosyaIsmi[255];
    //printf("Olusturmak istediginiz dosyanin adini uzantisiyle birlikte giriniz: ");
    scanf("%s",girilenDosyaIsmi);
    sprintf(path,"%s\\%s",mevcutKonum,girilenDosyaIsmi);
    bulunulanAdres->dosya[j]=fopen(path,"w");
    fclose(bulunulanAdres->dosya[j]);
    j++;
    sonaEkle(girilenDosyaIsmi,mevcutKonum);
}
void mkdr()//bu fonksiyon bu haliyle çalýþtý.
{
    struct node eklenecek;
    char normalKlasorIsmi[255];
    //printf("Olusturmak istediginiz klasor ismini giriniz: ");
    scanf("%s",normalKlasorIsmi);
    char path[255];
    sprintf(path,"%s\\%s",mevcutKonum,normalKlasorIsmi);
    mkdir(path,0777);
    strcpy(eklenecek.klasorIsmi,normalKlasorIsmi);
    strcpy(eklenecek.nodeIsmi,path);
    sonaEkle(normalKlasorIsmi,mevcutKonum);
}
void cd()
{
    char hedefDizin[25];
    //printf("Gitmek istediginiz dizini giriniz: ");
    scanf("%s",hedefDizin);
    sprintf(mevcutKonum,"%s\\%s",mevcutKonum,hedefDizin);
    mevcutKonumStackEkle(mevcutKonum);
}
void oncekiDizineGit()
{
    popMevcutKonum();
}
void nano()
{
    char h[25];
    char y[255];
    char path[50];
    scanf("%s",h);
    sprintf(path,"%s\\%s",mevcutKonum,h);
    int index=0;
    char c;
    if(subDirectoryCheck(h)==10)
    {

            while(1)
            {
                c=getchar();
                if(c!=';')
                {
                    y[index++]=c;
                }
                else
                {
                    break;
                }
            }
            FILE* dosya=fopen(path,"a");
            fprintf(dosya,"%s",y);
            fclose(dosya);

    }
    else
    {
        printf("Error//file is not working directory.\n");
    }


}
void cat()
{
    char h[25];
    char path[50];
    char s[255];
    scanf("%s",h);
    sprintf(path,"%s\\%s",mevcutKonum,h);
    FILE* dosya=fopen(path,"r");
    while(!feof(dosya))
    {
        fgets(s,255,dosya);
        printf("%s",s);
    }
    printf("\n");

    fclose(dosya);
}
void rm()
{
    char path[255];
    char y[50];
    scanf("%s",y);
    sprintf(path,"%s\\%s",mevcutKonum,y);
    int x=remove(path);
    elemanSil(y);
}
void rmdr()
{
    char path[255];
    char y[50];
    scanf("%s",y);
    sprintf(path,"%s\\%s",mevcutKonum,y);
    int x=rmdir(path);
}
char dosyami(char kontrolEdilecek[])
{
    int flag=0;
    for(int m=0; kontrolEdilecek[m]!='\0'; m++)
    {
        if(kontrolEdilecek[m]=='.')
        {
            flag++;
        }
    }
    if(flag!=0)
    {
        return 't';
    }
    else
    {
        return 'f';
    }
}
/*void icerigiTemizle(char adres[])
{
    struct linkedlist* temp=start;
    char path[255];
    char path2[255];
    strcpy(path,adres);
    strcpy(path2,adres);
    while(temp!=NULL)
    {
        if(strcmp(temp->hangiAdreste,adres)==0)
        {
            if(dosyami(temp->klasorVeDosyaIsimleri)=='f')
            {
                sprintf(path,"%s\\%s",path,temp->klasorVeDosyaIsimleri);
                icerigiTemizle(path);
            }
            else
            {
                sprintf(path2,"%s\\%s",path,temp->klasorVeDosyaIsimleri);
                int x=remove(path2);
            }
        }
        temp=temp->next;
    }

}*/
void dosyalariSil(char adres[])
{
    struct linkedlist*temp=start;
    char path[255];
    char path2[255];
    while(temp!=NULL)
    {
        if(strcmp(adres,temp->hangiAdreste)==0)
        {
            if(dosyami(temp->klasorVeDosyaIsimleri)=='t')
            {
                sprintf(path,"%s\\%s",adres,temp->klasorVeDosyaIsimleri);
                int x=remove(path);
                elemanSil(temp->klasorVeDosyaIsimleri);
            }
            else
            {
                sprintf(path2,"%s\\%s",adres,temp->klasorVeDosyaIsimleri);
                dosyalariSil(path2);
            }
        }
        temp=temp->next;
    }
}
void klasorleriSil(char adres[])
{
    char path[255];
    struct linkedlist*temp=start;
    int sonuc=0;
    while(temp!=NULL)
    {
        if(strcmp(adres,temp->hangiAdreste)==0)
        {
            if(dosyami(temp->klasorVeDosyaIsimleri)=='f')
            {
                sprintf(path,"%s\\%s",adres,temp->klasorVeDosyaIsimleri);
                sonuc=rmdir(path);
                elemanSil(temp->klasorVeDosyaIsimleri);
                if(sonuc!=0)
                {
                    klasorleriSil(path);
                    rmdir(path);
                }

            }
        }
        temp=temp->next;
    }

}
void rmr()
{
    char path[255];
    char y[25];
    scanf("%s",y);
    sprintf(path,"%s\\%s",mevcutKonum,y);
    dosyalariSil(path);
    klasorleriSil(path);
    rmdir(path);
    elemanSil(y);
}

int main(){
    rootKlasorYarat();
    printf("\n");
    int controller;
    int j=1;
    char a[15];
    while(j==1)
    {

        printf("%s ",mevcutKonum);
        scanf("%s",a);
        if(strcmp(a,"mkdr")==0)
        {
            mkdr();
        }
        else if(strcmp(a,"touch")==0)
        {
            touch();
        }
        else if(strcmp(a,"ls")==0)
        {
            ls(mevcutKonum);
        }
        else if(strcmp(a,"cd")==0)
        {
            cd();
        }
        else if(strcmp(a,"cd..")==0)
        {
            oncekiDizineGit();
        }
        else if(strcmp(a,"nano")==0)
        {
            nano();
        }
        else if(strcmp(a,"rm")==0)
        {
            rm();
        }
        else if(strcmp(a,"rmr")==0)
        {
            rmr();
        }
        else if(strcmp(a,"rmdr")==0)
        {
            rmdr();
        }
        else if(strcmp(a,"cat")==0)
        {
            cat();
        }
        else if(strcmp(a,"exit")==0)
        {
            j=0;
        }
    }



    return 0;
}
