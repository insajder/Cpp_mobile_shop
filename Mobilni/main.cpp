//Jelena Ilic NRT-32/19

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#define MAX 50
using namespace std;

// struktura koja funkcionise pomocu ulancanih listi, adrese se nalaze na random lokacijama
struct mobilni{
	char naziv[MAX+1];
	float cena;
	int kolicina;
	mobilni *sledeca; // cuva adresu za sledeci clan strukture
};

// Funkcija za unos podataka o mobilnom telefonu(naziv, cena i kolicina),
// vraca strukturu, sa argumentom pokazivac na strukturu tipa mobilni,
// poziva funkciju upis u datoteku koja otvara tekstualnu datoteku i upisuje podatke
mobilni *unos(mobilni *prva);

// Funkcija za izmenu podataka o mobilnom telefonu(cenu i kolicinu),
// vraca strukturu, sa argumentom pokazivac na strukturu tipa mobilni,
// poziva funkciju upis u datoteku koja otvara tekstualnu datoteku i upisuje podatke
mobilni *izmena(mobilni *prva);

// Funkcija za brisanje podataka o mobilnom telefonu(naziv, cena i kolicina),
// vraca strukturu, sa argumentom pokazivac na strukturu tipa mobilni
// poziva funkciju upis u datoteku koja otvara tekstualnu datoteku i upisuje podatke
mobilni *brisanje(mobilni *prva);

// Funkcija za prikaz podataka o mobilnim telefonima(naziv, cena i kolicina),
// sa argumentom pokazivac na strukturu tipa mobilni
void prikaz(mobilni *prva);

// Funkcija za pretrazivanje podatka o mobilnom telefonu,
// pretrazuje po nazivu i prikazuje sve podatke o pronadjenom mobilnom telefonu,
// sa argumentom pokazivac na strukturu tipa mobilni
void pretraga(mobilni *prva);

// Funkcija koja upisuje u tekstualnu datoteku podatke i otvara se u zavisnosti od prosledjenog moda,
// sa argumentom pokazivac na strukturu tipa mobilni, 
// poziva se u funkcijama unos, izmena i brisanje
void upis_u_datoteku(mobilni *prva);

int br_struktura=0;

int main(){
	mobilni *prva = NULL, *tekuca;
	char opcija;
	int br=0;

	tekuca = prva;

	cout<<"***MOBILNI TELEFONI***"<<endl;

	while(1){
		cout<<"__________________________________"<<endl;
		cout<<"1 - Unos\n2 - Izmena\n3 - Brisanje\n4 - Prikaz\n5 - Pronadji\n6 - Kraj"<<endl;	
		
		while(1){
			cout<<"Vas izbor: ";
			cin>>opcija;
			cin.ignore();
			if(opcija == '1' || opcija == '2' || opcija == '3' || opcija == '4' || opcija == '5' || opcija == '6'){
				break;
			}else{
				cout<<"Pogresan unos. Pokusajte ponovo."<<endl;
			}
		}
		if(opcija=='6') break;
	
		switch(opcija){
		case '1':
			prva = unos(prva);
			break;
		case '2':
			if(br_struktura!=0){
				prva = izmena(prva);
			}else{
				cout<<"Ne postoji ni jedan mobilni telefon u prodavnici."<<endl;
			}	
			break;
		case '3':
			prva = brisanje(prva);
			break;
		case '4':
			prikaz(prva);
			break;
		case '5':
			pretraga(prva);
			break;
		default:
			cout<<"Nepostojeca opcija."<<endl;
			break;
		}
	}
	delete prva;
	return 0;
}
mobilni *unos(mobilni *prva){
	mobilni *nova = new mobilni;
	if(nova==NULL){
		cerr<<"Nije uspela dinamicka dodela memorije!"<<endl;
		exit(1);
	}

	cout<<"Uneti naziv mobilnog telefona: ";
	cin.get(nova->naziv, MAX+1);
	cin.ignore();
	while(cout<<"Uneti cenu mobilnog telefona: " && !(cin>>nova->cena)){
		cin.clear();
		cin.ignore();
		cout<<"Pogresan unos. Pokusajte ponovo."<<endl;
	}
	while(cout<<"Uneti kolicinu mobilnih telefona: " && !(cin>>nova->kolicina)){
		cin.clear();
		cin.ignore();
		cout<<"Pogresan unos. Pokusajte ponovo."<<endl;
	}
	nova->sledeca = NULL;

	if (prva == NULL) {
		prva = nova; // upis prvog elementa u strukturu 
	} else { 
		mobilni *trenutna = new mobilni;
		if(trenutna==NULL){
			cerr<<"Nije uspela dinamicka dodela memorije!"<<endl;
			exit(1);
		}
		trenutna = prva;
		while(trenutna->sledeca != NULL) trenutna = trenutna->sledeca; // dolazi se do poslednjeg tako sto se proverava da li je NULL
		trenutna->sledeca = nova; // upis ostalih elementata u stukturu
	}
	br_struktura++;

	upis_u_datoteku(prva);
	return prva;
}
mobilni *izmena(mobilni *prva){
	char  izmena_po_nazivu[MAX+1], izbor;
	int br=0;

	mobilni *trenutna = new mobilni;
	trenutna = prva;
	
	cout<<"Uneti naziv mobilnog telefona: ";
	cin.get(izmena_po_nazivu, MAX+1);

	while(trenutna!=NULL){
		if(br==br_struktura) break;
		if(strcmp(trenutna->naziv, izmena_po_nazivu)==0){
			cout<<"Izmenite: \n1 - cenu\n2 - kolicinu\n3 - odustani"<<endl;
			while(1){
				cout<<"Vas izbor: ";
				cin>>izbor;
				cin.ignore();
				if(izbor == '1' || izbor == '2' || izbor == '3'){
					break;
				}else{
					cout<<"Pogresna opcija. Pokusajte ponovo."<<endl;
				}
			}

			if(izbor == '1'){
				cout<<"Uneti novu cenu: ";
				cin>>trenutna->cena;
				break;
			}else if(izbor == '2'){
				cout<<"Uneti novu kolicinu: ";
				cin>>trenutna->kolicina;
				break;
			}else{
				break;
			}
		}

		trenutna = trenutna->sledeca;
		br++;
	}

	if(izbor == '3'){
		cout<<"Odustali ste od izmene."<<endl;
	}else if(izbor == '1' || izbor == '2'){
		cout<<"Uspesna izmena."<<endl;
	}else{
		cout<<"Ne postoji mobilni telefon sa tim nazivom."<<endl;	
	}

	upis_u_datoteku(prva);
	return prva;
}
mobilni *brisanje(mobilni *prva){
	char  brisanje_po_nazivu[MAX+1];
	int br=0, ind=0;

	mobilni *trenutni = new mobilni;
	mobilni *prethodni = new mobilni;
	if(trenutni==NULL || prethodni==NULL){
		cerr<<"Nije uspela dinamicka dodela memorije!"<<endl;
		exit(1);
	}

	trenutni = prva;

	cout<<"Uneti naziv mobilnog telefona: ";
	cin.get(brisanje_po_nazivu, MAX+1);
	cin.ignore();

	while(trenutni!=NULL){
		if(br==br_struktura) break;
		if(strcmp(trenutni->naziv, brisanje_po_nazivu)!=0){ //poredjenje zadatog naziva i naziva koji sadrzi struktura, ako nije nadjen
			prethodni = trenutni; // predhodnom se dodeljuju podaci trenutnog clana stukture
			trenutni = trenutni->sledeca; // trenutnom se dodeljuje sledeca adresa u listi
		}else{
			if(br == 0) { // brise se prvi cvor
				mobilni *temp = new mobilni;
				if(temp==NULL){
					cerr<<"Nije uspela dinamicka dodela memorije!"<<endl;
					exit(1);
				}
				temp = prva;
				prva = prva->sledeca;
			} else { // ostali cvorovi
				prethodni->sledeca = trenutni->sledeca; // adresa sa prethodnog postaje adresa sa koju sadrzi trenutni i dalje se nakon te adrese redjaju elementi
				trenutni = trenutni->sledeca; 
			}
			ind=1;
			break;
		}
		
		br++;
	}

	if(ind==0){
		cout<<"Ne postoji mobilni telefon sa tim nazivom."<<endl;
	}else{
		cout<<"Uspesno brisanje."<<endl;
		br_struktura--;
	}

	upis_u_datoteku(prva);
	return prva;
}
void prikaz(mobilni *prva){
	int br=0;

	mobilni *trenutna = new mobilni;
	trenutna = prva;

	while(trenutna!=NULL){
		if(br==br_struktura) break; //prekid petlje ukoliko je broj iteracija kroz petlju jednak broju elemenata u strukturi
		cout<<"Naziv: "<<trenutna->naziv<<" | Cena: "<<trenutna->cena<<" | Kolicina: "<<trenutna->kolicina<<endl;
		trenutna = trenutna->sledeca; //mob uzima podatke sa sledece adrese
		br++;
	}
	cout<<endl;
}
void pretraga(mobilni *prva){
	char  pronadji_po_nazivu[MAX+1], izbor;
	int br=0;
	bool ind=false;

	mobilni *trenutna = new mobilni;
	if(trenutna == NULL){
		cerr<<"Nije uspela dinamicka dodela memorije!"<<endl;
		exit(1);
	}
	trenutna = prva;
	
	cout<<"Uneti naziv mobilnog telefona: ";
	cin.get(pronadji_po_nazivu, MAX+1);
	cin.ignore();

	while(trenutna!=NULL){
		if(br==br_struktura) break;
		
		if(strcmp(trenutna->naziv, pronadji_po_nazivu)==0){ //poredjenje zadatog naziva i naziva koji sadrzi struktura			
			ind=true; //indikator je true ako je pronadjen naziv mobilnog telefona
			cout<<"Pronadjen je moblini telefon sa tim nazivom."<<endl;
			cout<<"Naziv: "<<trenutna->naziv<<" | Cena: "<<trenutna->cena<<" | Kolicina: "<<trenutna->kolicina<<endl; 
			break;
		}

		trenutna = trenutna->sledeca; //ako nije pronadjen mob uzima podatke sa sledece adrese 
		br++;
	}
	if(ind==false){
		cout<<"Ne postoji mobilni telefon sa tim nazivom."<<endl;
	}
}

void upis_u_datoteku(mobilni *prva) {
	fstream f; 
	int br = 0;

	f.open("dat.txt", ios::out); //otvaranje datoteke za upis
	
	if(!f){
		cerr<<"Nije uspelo otvaranje datoteke za upis!"<<endl;
		exit(1);
	}
	f.seekp(0);

	mobilni *tekuca = prva;
	while(tekuca != NULL){
		if(br==br_struktura) break;
		
		f<<tekuca->naziv<<" "<<tekuca->cena<<" "<<tekuca->kolicina<<endl;

		tekuca = tekuca -> sledeca;
		br++;
	}

	f.close();
}
