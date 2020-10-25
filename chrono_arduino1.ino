// include the library code:
#include <LiquidCrystal.h>

const int Bouton1 = 6;//Reset
const int Bouton2 = 7;//Play/Pause
const int Bouton3 = 8;// Tours
const int Bouton4 = 9;//Allumer
bool etat1, etat2, etat3, etat4;

int sec = 0;
int min = 0;
int heure = 0;

int secTours = 0;
int minTours = 0;
int heureTours = 0;

bool etatChronometre = false;
int test = 0;

int i = 0; // Nombre de tours

/*Structure tours qui va contenir le temps de chaque tour*/

typedef struct Tours
{
  int heure, minutes, secondes;
} Tours;

Tours tours[10];
int secT, minT, heureT;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  pinMode(Bouton1, INPUT_PULLUP);
  pinMode(Bouton2, INPUT_PULLUP);
  pinMode(Bouton3, INPUT_PULLUP);
  pinMode(Bouton4, INPUT_PULLUP);

  lcd.begin(16, 2);
}

void afficheTours(LiquidCrystal lcd, Tours tabTour[], int i); // Affiche le chronometre avec le nombre de tours et sa duree
void demarage(bool* etatBouton); // fonction de demarage du chronometre
void eteint(bool* etatBouton);// Fonctions d'eteignage du chrono

void loop() {
  // set the cursor to column 0, line 1
  etat1 = digitalRead(Bouton1);
  etat2 = digitalRead(Bouton2);
  etat3 = digitalRead(Bouton3);
  etat4 = digitalRead(Bouton4);

  demarage(&etat4); //  demarage du chronometre

  if (etatChronometre == true && etat3 != 0)
    afficheTours(lcd, tours, i);
  
  if (etat3 == 0) // Tours
  {
    //if(i==0)
    //{
      tours[i].secondes = sec;
   	  tours[i].minutes = min;
      tours[i].heure = heure;
      
    //}
    /*else
    {
      tours[i].secondes = secT;
   	  tours[i].minutes = minT;
      tours[i].heure = heureT;
      secT=0;
      minT=0;
      heureT=0;
    }*/
    
    i++;
    delay(500);
  }

  Serial.println(etat2);

  if (etat2 == 0) // Pause/ Play
  {
    lcd.setCursor(0, 0);
    lcd.print("PAUSE!");
    Serial.println(etat2);
    while (1)
    {
      Serial.println(etat2);
      
      if (etat2 == 0)
      {
        delay(5000);
        lcd.clear();
        test = 0;
        break;
      }
    }
  }

  if (etat1 == 0) // Reset
  {
    sec = 0;
    min = 0;
    heure = 0;
    lcd.clear();
  }


  eteint(&etat4); //eteindre le chronometre
}


void afficheTours(LiquidCrystal lcd, Tours tabTour[], int i)
{
  lcd.setCursor(0, 0);
  if (i != 0) {
    lcd.print("Tour ");
    lcd.print(i);
    lcd.print(":");
  }


  if (heure < 10 && i != 0)
    lcd.print("0");
  else
    lcd.print("");
  if (i != 0)
    lcd.print(tabTour[i - 1].heure);
  if (i != 0)
    lcd.print(":");
  if (min < 10 && i != 0)
    lcd.print("0");
  if (i != 0)
    lcd.print(tabTour[i - 1].minutes);
  if (i != 0)
    lcd.print(":");
  if (i != 0)
    lcd.print(tabTour[i - 1].secondes);

  lcd.setCursor(0, 1);

  if (heure < 10)
    lcd.print("        0");
  else
    lcd.print("        ");
  lcd.print(heure);
  lcd.print(":");
  if (min < 10)
    lcd.print("0");
  lcd.print(min);
  lcd.print(":");
  lcd.print(sec);

  delay(1000);
  sec++;

  if (sec > 59)
  {
    sec = 0;
    min++;
    lcd.clear();
    lcd.setCursor(0, 0); //  on change la position du curseur
    if (i != 0)
    {
      lcd.print("Tour ");
      lcd.print(i);
      lcd.print(":");
    }


    if (heure < 10 && i != 0)
      lcd.print("0");
    else
      lcd.print("");
    if (i != 0)
      lcd.print(tabTour[i - 1].heure);
    if (i != 0)
      lcd.print(":");
    if (min < 10 && i != 0)
      lcd.print("0");
    if (i != 0)
      lcd.print(tabTour[i - 1].minutes);
    if (i != 0)
      lcd.print(":");
    if (i != 0)
      lcd.print(tabTour[i - 1].secondes);

  }

  if (min > 59)
  {
    min = 0;
    heure++;
    lcd.clear();
    lcd.setCursor(0, 0);
    if (i != 0)
    {
      lcd.print("Tour ");
      lcd.print(i);
      lcd.print(":");
    }

    if (heure < 10 && i != 0)
      lcd.print("0");
    else
      lcd.print("");
    if (i != 0)
      lcd.print(tabTour[i - 1].heure);
    if (i != 0)
      lcd.print(":");
    if (min < 10 && i != 0)
      lcd.print("0");
    if (i != 0)
      lcd.print(tabTour[i - 1].minutes);
    if (i != 0)
      lcd.print(":");
    if (i != 0)
      lcd.print(tabTour[i - 1].secondes);
  }
  
}

void demarage(bool * etatBouton)
{
  if (*etatBouton == 0 && etatChronometre == false)
  {
    etatChronometre = true;
    *etatBouton = 1;
  }
}

void eteint(bool * etatBouton)
{
  if (*etatBouton == 0 && etatChronometre == true)
  {
    etatChronometre = false;
    lcd.clear();
    sec = 0;
    min = 0;
    heure = 0;
    i = 0;
  }
}
