#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define MAX 256
#include <string.h>
#include <fstream>
using namespace std;

void shift_sin(char nome[],int pos){
    int i=0;
    for(i=pos;nome[i]!='\0';i++)
        nome[i]=nome[i+1];
    nome[i]='\0';
}

void estrai_consonanti(char nome[]){
	for(int i=0;nome[i]!='\0';i++){
		if(nome[i]=='a'||nome[i]=='e'||nome[i]=='i'||nome[i]=='o'||nome[i]=='u')  
            shift_sin(nome,i);
    }	
}

void trasforma_maiuscolo(char nome[]){
     for(int i=0;nome[i]!='\0';i++){
         if(nome[i]>='a'&&nome[i]<='z')
             nome[i]=nome[i]-32;
     }
}

void estrai_vocali(char nome[]){
     for(int i=0;nome[i]!='\0';i++){
		if(nome[i]!='a'||nome[i]!='e'||nome[i]!='i'||nome[i]!='o'||nome[i]!='u')  
            shift_sin(nome,i);
    }
}	
    
void trova_codice(char temp[],char comune[],char codice[],char nome_file[],char n_file[],int & selezione){
    ifstream lettura;
    bool trovato=false;
    int val;
    if(selezione==1)
    	lettura.open(n_file);
	else
		lettura.open(nome_file);
	if(!lettura){
			system("cls");
			cout<<"\n\n LETTURA NON RIUSCITA \n\n";	
		}
	while(trovato==false&&lettura.eof()!=1){
		lettura.getline(temp,MAX,';');
		lettura.getline(codice,MAX,'\n');
		val=strcmp(comune,temp);
		if(val==0)
			trovato=true;
    }
	lettura.close();    
}

void controllo_cognome(char cognome[],char vocali[]){
	int l;
	strcpy(vocali,cognome);
	estrai_vocali(vocali);
	l=strlen(cognome);
    if(l<3)
	       cognome[l]=88;
    else
    {
    	estrai_consonanti(cognome);
    	estrai_consonanti(cognome);
    	l=strlen(cognome);
    	if(l<3)
    		cognome[l]=vocali[0];
	}
	trasforma_maiuscolo(cognome);
}

void controllo_nome(char nome[],char vocali[],char cd_fiscale[],int & index_pos){
	int l;
	strcpy(vocali,nome);
	estrai_vocali(vocali);
	l=strlen(nome);
	if(l<3){
		nome[l]=88;
		for(int j=0;j<3;j++,index_pos++){
			cd_fiscale[index_pos]=nome[j];
			}	
	}
	else{
		estrai_consonanti(nome);
		estrai_consonanti(nome);
		l=strlen(nome);
		if(l>=4){
			for(int j=0;j<4;j++){
			if(j==0||j==2||j==3){
				cd_fiscale[index_pos]=nome[j];
				index_pos++;
				}
			}	
		}
		else if(l==3){
			for(int j=0;j<3;j++,index_pos++){
			cd_fiscale[index_pos]=nome[j];
			}
		}
		else if(l<3){
			nome[l]=vocali[0];	
			for(int j=0;j<3;j++,index_pos++){
			cd_fiscale[index_pos]=nome[j];
			}
		}
	}
	trasforma_maiuscolo(cd_fiscale);
}

void trova_valore(char dispari[], char n_file[],int & somma){
	int val;
	char temp[MAX]={'\0'},temp1[MAX]={'\0'};
	bool trovato=false;
	ifstream lettura;
	
	for(int i=0;dispari[i]!='\0';i++){
		lettura.open(n_file);
			if(!lettura){
				cout<<"\n\n\n";
				system("pause");
				cout<<"\n\n LETTURA NON RIUSCITA FILE DISPARI \n\n";	
			}
			trovato=false;
			while(trovato==false&&lettura.eof()!=1){
				lettura.getline(temp,MAX,';');
				lettura.getline(temp1,MAX,'\n');
				if(dispari[i]==temp[0]){
					trovato=true;
					val=atoi(temp1);
					somma=somma+val;
				}	
			}
		lettura.close();
	}
}

void genera_lettera(char cd_fiscale[],int & totale){
	char dispari[MAX]={'\0'},pari[MAX]={'\0'},n_file[MAX]="dispari.txt",nome_file[MAX]="pari.txt";
	int somma=0;
	for(int i=0,p=0,d=0;cd_fiscale[i]!='\0';i++){
		if(i%2==0){
			dispari[d]=cd_fiscale[i];
			d++;
		}
		else{
			pari[p]=cd_fiscale[i];
			p++;
		}		
	}
	trova_valore(dispari,n_file,somma);
	trova_valore(pari,nome_file,somma);
	totale=somma;
}

void funz_sleep(char frase[]){
	for(int i=0;frase[i]!='\0';i++){
		cout<<frase[i];
		Sleep(70);
	}
}

int main(){
	
	int val,index_pos=0,l,totale=0,resto=0,selezione;
	char cognome[MAX]={'\0'},nome[MAX]={'\0'},mese[MAX]={'\0'},comune[MAX]={'\0'},n_file[MAX]="Codice comuni.csv",nome_file[MAX]="Codici esteri.txt",cd_fiscale[MAX]={'\0'},anno[MAX]={'\0'},giorno[MAX]={'\0'};
	char temp[MAX],codice[MAX]={'\0'},vocali[MAX]={'\0'},january[MAX]="GENNAIO",march[MAX]="MARZO",april[MAX]="APRILE",lettera,frase[MAX]="     BENVENUTI ALLA GENERAZIONE DEL CODICE FISCALE";
	char frase1[MAX]="     INSERIMENTO DELLA DATA DI NASCITA";
	
	funz_sleep(frase);
	cout<<"\n\n\n";
	cout<<"    -Inserisci il tuo cognome: ";
	cin.get(cognome,MAX,'\n');
	cin.ignore();
	controllo_cognome(cognome,vocali);
	for(int i=0;i<3;i++,index_pos++)
		cd_fiscale[index_pos]=cognome[i];
	cout<<"\n\n\n";
	//-------------------------------------------------
	cout<<"    -Inserisci il tuo nome: ";
	cin.get(nome,MAX,'\n');
	controllo_nome(nome,vocali,cd_fiscale,index_pos);
	cin.ignore();
	cout<<"\n\n\n";
	//------------------------------------------------
	funz_sleep(frase1);
	cout<<"\n\n\n\n";
	cout<<"    -Inserisci l'anno: ";
	cin.get(anno,MAX,'\n');
	for(int i=0;anno[i]!='\0';i++){
		if(i==2||i==3){
			cd_fiscale[index_pos]=anno[i];
			index_pos++;	
		}
	}
	cout<<"\n\n";
	cin.ignore();
	//------------------------------------------------
	cout<<"    -Inserisci il mese(per scritto): ";
	cin.get(mese,MAX,'\n');
	trasforma_maiuscolo(mese);
	switch(mese[0]){
		
		case('G'):
			val=strcmp(mese,january);
			if(val==0)
				cd_fiscale[index_pos]=65;
			else
				cd_fiscale[index_pos]=72;
			break;	
		case('F'):
			cd_fiscale[index_pos]=70;
			break;
		case('M'):
			val=strcmp(mese,march);
			if(val==0)
				cd_fiscale[index_pos]=67;
			else
				cd_fiscale[index_pos]=69;
			break;
		case('A'):
			val=strcmp(mese,april);
			if(val==0)
				cd_fiscale[index_pos]=68;
			else
				cd_fiscale[index_pos]=77;
		case('L'):
			cd_fiscale[index_pos]=mese[0];
			break;
		case('S'):
			cd_fiscale[index_pos]=80;
			break;
		case('O'):
			cd_fiscale[index_pos]=82;
			break;
		case('N'):
			cd_fiscale[index_pos]=83;
			break;
		case('D'):
			cd_fiscale[index_pos]=84;
			break;
	}
	index_pos++;
	cout<<"\n\n";
	do
	{
		cout<<"    -Inserisci maschio o femmina(M/F): ";
		cin>>lettera;
		if(lettera>='a'&&lettera<='z')
			lettera=lettera-32;
	}while(lettera!='M'&&lettera!='F');
	cout<<"\n\n";
	cin.ignore();
	//-------------------------------------------------
	cout<<"    -Inserisci il giorno: ";
	cin.get(giorno,MAX,'\n');
	l=strlen(giorno);
	if(lettera=='M')
	{
		if(l==1){
			cd_fiscale[index_pos]=48;
			index_pos++;
			cd_fiscale[index_pos]=giorno[0];
			index_pos++;
		}
		else{
			cd_fiscale[index_pos]=giorno[0];
			index_pos++;
			cd_fiscale[index_pos]=giorno[1];
			index_pos++;	
		}
	}
	else{
		if(l==1){
			cd_fiscale[index_pos]=52;
			index_pos++;
			cd_fiscale[index_pos]=giorno[0];
			index_pos++;
		}
		else{
			switch(giorno[0]){
				case('1'):
					cd_fiscale[index_pos]=53;
					break;
				case('2'):
					cd_fiscale[index_pos]=54;
					break;
				case('3'):
					cd_fiscale[index_pos]=55;
					break;
			}
			index_pos++;
			cd_fiscale[index_pos]=giorno[1];
			index_pos++;	
		}
	}
	cout<<"\n\n";
	cin.ignore();
	//-------------------------------------------------
	system("cls");
	cout<<"1--->ITALIA"<<endl;
	cout<<"2--->ESTERO"<<endl;
	do{
		cout<<"Sei nato in ITALIA/ESTERO? ";
		cin>>selezione;	
	}while(selezione!=1&&selezione!=2);
	cout<<"\n\n";
	cin.ignore();
	cout<<"    -Inserisci il COMUNE/STATO DI PROVENIENZA di dove sei nato: ";
	cin.get(comune,MAX,'\n');
	cin.ignore();
	trasforma_maiuscolo(comune);
	cout<<"\n\n\n";
	system("pause");
	system("cls");
	
	trova_codice(temp,comune,codice,nome_file,n_file,selezione);
	
	for(int i=0;codice[i]!='\0';i++,index_pos++)                                        
	        cd_fiscale[index_pos]=codice[i];
 
    genera_lettera(cd_fiscale,totale);
    resto=totale%26;
    cd_fiscale[index_pos]=65+resto;
    
    cout<<"Il tuo codice fiscale e':   ";funz_sleep(cd_fiscale);
    
	cout<<"\n\n\n\n\n\n";
	system("pause");
	return 0;
}
