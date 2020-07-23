#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> //system için
FILE *dosya;
char satir[250];
char kelime[250];
char gecici[50];
	
	int satirsayisi(){
		int aa=0,cc=1,last;//Burada ifadelerimizi tanýmladýk.
		char ch;//Karakter olarak ch ifadesini tanýmladýk.
		 
		dosya=fopen("sehirler.txt","r");//Burada fopen içerisine dosyamýzýn tam adýný yazýyoruz.Ben mmsrn.txt olarak oluþturmuþtum siz deðiþtirebilirsiniz.
		while(!feof(dosya)){//Siz "for" döngüsüne de alabilirsiniz keyfinize göre size kalmýþ.
			ch=getc(dosya);
			if(ch=='\n'){//Eðer ch ifadesi boþluða denk gelirse satýr sayýsýný 1 arttýrýyoruz.
			cc++;
			}
		}
		 
		fclose(dosya);//Yazý yazýlan metin belgesini kapatýyoruz.
		return cc;
	}
	
	
	void satiroku(int sn){
		int i=0;
		dosya=fopen("sehirler.txt","r");
		for(i=0;i<sn;i++)
			fgets(satir,sizeof(satir),dosya);
			//printf("%s",satir);
		fclose(dosya);
	}
	
	typedef struct n{
		int plaka;
		char sehir[20];
		char bolge[20];
		int komsu;
		struct p *start;
		struct n * next;
	}node;
	
	typedef struct p{
		int kplaka;
		struct p * pnext;
	}plk;
	
	
	
	node *ekleSirali ( node *r, int plaka, char* sehir, char* bolge, int komsu ){
		if( r == NULL){ 
			r = (node *) malloc ( sizeof ( node) );
			r -> next = NULL;
			r -> plaka = plaka;
			strcpy(r -> sehir, sehir);
			strcpy(r -> bolge, bolge);
			r -> komsu=komsu;
			return r;
		}
		if(r -> plaka > plaka){ // ilk elemandan küeük durumu
			// root dešiziyor
			node * temp = ( node * ) malloc ( sizeof ( node ) );
			temp -> plaka = plaka;
			strcpy(temp -> sehir, sehir);
			strcpy(temp -> bolge, bolge);
			temp -> komsu=komsu;
			temp -> next = r;
			r = temp;
			return temp;
		}
		node * iter = r;
		while( iter -> next != NULL && iter -> next -> plaka < plaka ){
			iter = iter -> next;
		}
		
		node * temp = (node*)malloc(sizeof(node));
		temp->next = iter->next;
		iter->next = temp;
		temp->plaka = plaka;
		strcpy(temp -> sehir, sehir);
		strcpy(temp -> bolge, bolge);
		temp -> komsu=komsu;
		return r;
	 
	}
	
	void bastir( node * r){
		while (r != NULL){
			printf("%d ", r->plaka);
			printf("%s ", r->sehir);
			printf("%s ", r->bolge);
			printf("%d ", r->komsu);
			printf("\n");
			r = r -> next;
		}
		printf("\n");
	}
	
	node * sil(node *r, int plaka){
	 node *temp;
	 node *iter = r;
	 if( r->plaka == plaka){
	  temp = r;
	  r = r->next;
	  free (temp);
	  return r;
	 }
	 
	 while ( iter->next != NULL && iter->next->plaka != plaka){
	  iter = iter->next;
	 }
	 if ( iter->next == NULL){
	  printf( "Sayi bulunamadi!\n" );
	  return r;
	 }
	 temp = iter->next;
	 iter->next = iter->next->next; // ya da iter->next = temp->next
	 free (temp);
	 return r;
	}
	
	/*plk * ekleSirali2 ( plk * r, int kplaka){
		 if( r == NULL){
			  r = (plk *) malloc ( sizeof ( plk) );
			  r -> next = NULL;
			  r -> kplaka = kplaka;
			  return r;
		 }
		 if(r -> kplaka > kplaka){ // ilk elemandan küeük durumu
			  // root dešiziyor
			  plk * temp = ( plk * ) malloc ( sizeof ( plk ) );
			  temp -> kplaka = kplaka;
			  temp -> next = r;
			  r = temp;
			  return temp;
		 }
		 plk * iter = r;
		 while( iter -> next != NULL && iter -> next -> kplaka < kplaka ){
		  	iter = iter -> next;
		 }
		
		 plk * temp = (plk*)malloc(sizeof(plk));
		 temp->next = iter->next;
		 iter->next = temp;
		 temp->kplaka = kplaka;
		 return r;
	 
	}*/
	
	
	int main(){
		int x,i,komsu=0,k;
		char h;
		char *pch;
		char *pch2;
		
		node * root;
 		root = NULL;
 		plk * root2;
 		root2 = NULL;
 		
 		int kplaka;
		
		int plaka;
		char sehir[20];
		char bolge[20];
		
		int a;
		
		
		x = satirsayisi();
		
		
		for(i=1;i<=x;i++){
			satiroku(i);
			pch = strtok(satir,",");
			for(k=0;k<3;k++){
					if(k==0){
						plaka = atoi(pch);
						}
					else if(k==1){
					
						strcpy(sehir,pch);
						}
					else if(k==2){
						strcpy(bolge,pch);
					}
					pch = strtok(NULL, ",");
				}
				komsu=0;
				while (pch != NULL)
				{
					komsu++;
			    	pch = strtok (NULL, ",");
				}
				root = ekleSirali(root,plaka, sehir, bolge,komsu);
		}
		/*
		for(i=1;i<=x;i++){
			satiroku(i);
			pch = strtok(satir,",");
			for(k=0;k<3;k++){
					if(k==0){
						plaka = atoi(pch2);
						}
					else if(k==1){
					
						strcpy(sehir,pch2);
						}
					else if(k==2){
						strcpy(bolge,pch2);
					}
					pch2 = strtok(NULL, ",");
				}
				komsu=0;
				while (pch2 != NULL)
				{
					komsu++;
			    	pch2 = strtok (NULL, ",");
			    	kplaka = komsu;
			    	root2 = ekleSirali2(root2, kplaka);
				}
		}
		
		printf("Bastirmak icin 1 \nEkleme yapmak icin 2 \nSilmek icin 3\n");
		scanf("%d",a);
		
		switch(a){
			case 1:
				bastir(root);
				printf("\n");
				break;
				
			case 2:
				ekleSirali(root,plaka, sehir, bolge,komsu);
				break;
					
			case 3:
				sil(root, 45);
				break;
		}
		*/
		
		bastir(root);
		
		printf("\n");
		
		system("pause");
		return 0;
	} 
