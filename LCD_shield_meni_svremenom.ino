#include <LiquidCrystal.h>

/*******************************************************
 * 
Ovaj program namijenjen je za korištenje s LCD Shieldom
Jednostavan izbornik

Marko Miroslav Bača, 2018

********************************************************/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int tipkalo_odabir     = 0;
int tipkalo_vrijednost  = 0; //analogna vrijednost
int izbornik = 0;
unsigned long vrijeme_interval = 0;
unsigned long pocetno_vrijeme = 0;
unsigned long trenutno_vrijeme = 0;


int desna = 0;
int lijeva = 1;
int gore = 2;
int dolje = 3;
int odaberi = 4;
int nista = 5;


int citaj_tipkalo()
{
 delay(100);
 tipkalo_vrijednost = analogRead(0);
 // Koristite analogno čitanje pina 0 kako bi pročitali vrijednosti svojih tipki moje vrijednosti: 0, 100, 258, 413, 645,1023
 // te na tu vrijednost dodajemo 50 kako bi bili sigurni da će očitanje biti dobro
 if (tipkalo_vrijednost > 1000) return nista; 
 if (tipkalo_vrijednost < 50)   return desna;  
 if (tipkalo_vrijednost < 150)  return gore; 
 if (tipkalo_vrijednost < 300)  return dolje; 
 if (tipkalo_vrijednost < 460)  return lijeva; 
 if (tipkalo_vrijednost < 700)  return odaberi;  

 return nista;
}
void naslovna(){
 lcd.clear();          
 lcd.setCursor(0,0);
 lcd.print("Izbornik za ulaz");
 lcd.setCursor(0,1);
 lcd.print("pritisnite enter");
  }

void setup(){
 lcd.begin(16, 2);
 naslovna();             
}
 
void loop(){
 tipkalo_odabir = citaj_tipkalo();
 
 if(tipkalo_odabir==4){ //ulazak u izbornik
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Izbornik:");
  delay(300);
  pocetno_vrijeme = millis();
  do{
    tipkalo_odabir = citaj_tipkalo();
    if(tipkalo_odabir==2){
      izbornik++;
      if(izbornik>=4){
        izbornik=0;
        }
        pocetno_vrijeme = millis();
        delay(300);
      }
    else if(tipkalo_odabir==3){
      izbornik--;
      if(izbornik<0){
        izbornik=3;
        }
        pocetno_vrijeme = millis();
        delay(300);
      }
    lcd.setCursor(0,1);
        switch(izbornik){
          case 0: {lcd.print("Opcija: 1");break;}
          case 1: {lcd.print("Opcija: 2");break;}
          case 2: {lcd.print("Opcija: 3");break;}
          case 3: {lcd.print("Opcija: 4");break;}
    }
    
    trenutno_vrijeme = millis();
    vrijeme_interval=trenutno_vrijeme-pocetno_vrijeme; // izračunavanje trajanja od zadnjeg pritiska
    
    }while((tipkalo_odabir !=4) && (vrijeme_interval<10000));
    if(vrijeme_interval<10000){
      lcd.clear();
      lcd.print("Odabrali ste");
      lcd.setCursor(0,1);
        switch(izbornik){
           case 0: {lcd.print("Prvi izbornik");break;}
           case 1: {lcd.print("Drugi izbornik");break;}
           case 2: {lcd.print("Treci izbornik");break;}
            case 3: {lcd.print("Cetvrti izbornik");break;}
    }
    delay(5000);
    }
    izbornik=0;
    vrijeme_interval=0;
    naslovna();  
  }
}

