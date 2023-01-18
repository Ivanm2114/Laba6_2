#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <stddef.h>
#define lmax 200

struct izdat{
    int year;
    char name[lmax];
    char city[lmax];
};

struct book{
    int pages;
    float price;
    char author[lmax];
    char title[lmax];
    struct izdat izdatelstvo;
};


int input_natural_int()
{
    int res,x,count;
    float temp;
    count=0;
    while (count<1)
    {
        do
        {
            printf("Введите натуральное число\n");
            x=scanf("%f",&temp);
            while (getchar()!='\n');
        }
        while(x<1||temp<=0);
        if((int)temp==temp)
        {
            res=(int)temp;
            count++;
        }
    }
    return res;

}

float input_natural_float()
{
    int x;
    float res;
    do
    {
        printf("Введите положительное число:\n");
        x=scanf("%f",&res);
        while (getchar()!='\n');
    }
    while(x<1||res<=0);
    return res;

}

void rid_of_new_string_sym(char s[lmax]){
    s[strlen(s)-1]='\0';
}

void input_book(FILE *file, struct book *b){
    fgets(b->title,lmax-1,file);
    rid_of_new_string_sym(b->title);
    fscanf(file,"%f",&b->price);
    while(fgetc(file)!='\n');
    fgets(b->author,lmax-1,file);
    rid_of_new_string_sym(b->author);
    fscanf(file,"%d",&b->pages);
    while(fgetc(file)!='\n');
    fscanf(file,"%d",&b->izdatelstvo.year);
    while(fgetc(file)!='\n');
    fgets(b->izdatelstvo.city,lmax-1,file);
    rid_of_new_string_sym(b->izdatelstvo.city);
    fgets(b->izdatelstvo.name,lmax-1,file);
    rid_of_new_string_sym(b->izdatelstvo.name);

}



void output_book(struct book *b){
    printf("Название :\t\t");
    printf("%s",b->title);
    printf("Цена:\t\t\t");
    printf("%.2f\n", b->price);
    printf("Автор :\t\t\t");
    printf("%s",b->author);
    printf("Кол-во страниц :\t");
    printf("%d\n",b->pages);
    puts("Издательство:");
    printf("Год издания: \t\t");
    printf("%d\n",b->izdatelstvo.year);
    printf("Город:\t\t\t");
    printf("%s",b->izdatelstvo.city);
    printf("Название:\t\t");
    puts(b->izdatelstvo.name);

}


int function(struct book *a,int k, char b[lmax][lmax],char city[lmax], int year){
    int count=0;
    for(int i=0;i<k;i++){
        printf("%s%s\n",a[i].izdatelstvo.city,city);
        if(strcmp(a[i].izdatelstvo.city,city)==0 && a[i].izdatelstvo.year>year){
            strcpy(b[count++],a[i].title);
        }
    }
    printf("%d",count);
    return count;


}


int main(){
    struct book A[lmax];
    char titles[lmax][lmax], rfilename[lmax],wfilename[lmax];
    int k,year, count;
    char city[lmax];
    FILE *rfile,*wfile;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    puts("Введите название файла с данными:");
    gets(rfilename);
    puts("Введите название файла с результатом:");
    gets(wfilename);
    rfile=fopen(rfilename,"r");
    wfile=fopen(wfilename,"w");
    if (rfile){
        fscanf(rfile,"%d",&k);
        while(fgetc(rfile)!='\n');
        for(int i=0;i<k;i++){
            input_book(rfile,&A[i]);
        }
        puts("\n\n");
        for(int i=0;i<k;i++){
            printf("Книга %d\n",i+1);
            output_book(&A[i]);
            puts("\n");
        }
        puts("Введите город");
        gets(city);
        puts("Введите год");
        year=input_natural_int();
        count=function(A,k,titles,city,year);
        if(count>0){
            printf("Найдено %d книг(а) изданных(ая) после %d года и выпущенных(ая) в городе ",count, year);
            puts(city);
        for(int i=0;i<count;i++){
            puts(titles[i]);
        }}
        else{
            printf("Книги не найдены");
    }}
    return 0;
}
