#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>

using namespace std;

/* Klasa o nazwie Element:
   Obiekt Element to jeden z elementow wiadomosci przeslanej przez uzytkownika, ktory zawiera:
   -  std::string fewWords -> tekst elementu np. "Ala ma"
   -  int indexOfElement -> indeks owego elementu, niezbedny do pozniejszego posortowania 
*/
class Element{
    private:
        std::string fewWords;
        int indexOfElement;

    public:
        
        //Konstruktory
        Element(){};
        Element(std::string words,int index){
            fewWords = words;
            indexOfElement = index;
        }

        //Funkcje dające dostęp do indeksu oraz treści elementu
        string getString(){ return fewWords;};
        int getindexOfElement(){ return indexOfElement;};

};

/* Klasa o nazwie Message
   Obiekt Message to wiadomość napisana przez użytkownika, zawiera on:
   - int numberOfElements -> liczba wszystkich elementow, powstalych po podzieleniu wiadomosci
   - int numberOfWords -> liczba slow występujacych w wiadomosci, UWAGA jesli po slowie nastepuje ",", "." badz inny znak słowo bedzie zapisane w postaci "Ana,"
   - int wordsPerElement -> liczba slow przypadajaca na jeden element, liczba ta jest zalezna od tego jak uzytkownik bardzo bedzie chcial wymieszac odpowiedz
   - int arraySize -> rozmiar tablicy 
   - Element* list -> tablica elementow
*/
class Message{
    private:
        int numberOfElements;
        int numberOfWords;
        int wordsPerElement;
        int arraySize;
        Element* list;

    public:
        //Konstruktor inicjujacy liste obiektow Element oraz zapisujace podstawowe parametry wiadomosci
        Message(int noe, int now, int wpe, string arr[]){
            if(noe >= now){
                noe = now;
                std::cout<< "maximum number of elements cannot be greater than number of words, so we changed it to " << now << std::endl;
            }
            numberOfElements = noe;
            numberOfWords = now;
            wordsPerElement = wpe;
            InitListOfElements(arr);
        }

        //Funkcja zwracajaca oraz dajaca dostep do liczby stworzonych Elementow
        int getNumberOfElements(){return numberOfElements;};
        //Funkcja zwracajaca oraz dajaca dostep do liczby slow w wiadomosci
        int getNumberOfWords(){return numberOfWords;};
        //Funkcja zwracajaca oraz dajaca dostep do liczby slow przypadajaca na jeden Element
        int getWordsPerElement(){return wordsPerElement;};
        //Funckja zwracajaca oraz dajaca dostep do listy Elementow
        Element getListOfElementsArray(){return (*list);};
        //Funckja zwracajaca oraz dajaca dostep do rozmiaru tablicy
        int getSizeOfArray(){return arraySize;}

        //Funkcja wyswietlajaca powstala liste obiektow Element
        void displayElementsWithIndex(){
            std::string temp;
            for (size_t i = 0; i < (*this).getSizeOfArray(); ++i) {
                std::cout << list[i].getString();
            }
        }

        //Funkcja wyswietlajaca i mieszajaca elementy listy obiektow Element
        void displayElementsWithIndexShuffle(){
            for (int i = getSizeOfArray() - 1; i > 0; i--)
            {
                int j = rand() % (i + 1);
                swap(list[i], list[j]);
                std::cout << list[i].getString();
            }
        }

        //Funkcja sortujaca liste obiektow Element po ich indeksach
        void sortByIndex(){
            for(int i=0;i<(*this).getNumberOfElements();i++){   
                for(size_t j = 1; j < getSizeOfArray()-i; j++) {
                if(list[j-1].getindexOfElement()>list[j].getindexOfElement())
                    swap(list[j-1],list[j]);
                }
            }
        }
        
        //Funkcja tworzaca liste obiektow Element 
        void InitListOfElements(string arr[]){ 
            int index = 0;
            std::string words ="";
            arraySize = getNumberOfElements();
            int temp = 0;
            list = new Element[arraySize];
            for (int i = 0; i < arraySize; ++i){
                list[i] = Element();
            }
            for(int k=0; k<getNumberOfWords();k++){
                if((k%getWordsPerElement()) == (getWordsPerElement()-1)){
                    words.append(arr[k]);
                    words.append(" ");
                    index+=1;
                    Element elementToPush(words,index);
                    list[temp] = elementToPush;
                    temp++;
                    words="";
                    }
                else if(k == getNumberOfWords()-1){
                    words.append(arr[k]);
                    index+=1;
                    Element elementToPush(words,index);
                    list[temp] = elementToPush;
                    temp++;
                }
                else{
                    words.append(arr[k]);
                    words.append(" ");
                } 
            }
        }
};


//Funkcja rozdzielajaca na tablicę słów
void splitMassageIntoWords(string arr[], int N, string str)
{
    int n = 0;
    istringstream iss(str);
    for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
        arr[n] = *it;
    // for(int i=0; i < N; i++){
    //     std::cout<< arr[i] << std::endl;
    // }    
}

//Funkcja liczaca ilosc slow w wiadomosci
unsigned int countWordsInString(std::string const& str)
{
    std::stringstream  stream(str);
    std::string oneWord;
    unsigned int count = 0;

    while(stream >> oneWord) 
    { ++count;}
    return count;
}


int main() 
{

    double numberOfElements;
    int numberOfWords;
    double wordsPerElement;
    std::string message;

    std::cout << "Hello, mister John please write your message to Anna." << std::endl;
    getline(cin, message); //Pobranie wiadomosci 
    
    numberOfWords = countWordsInString(message); //Obliczenie ilosci slow w wiadomosci
    std::string arrayOfWords[numberOfWords]; //Inicjacja tablicy o odpowiednim wymiarze 
    
    splitMassageIntoWords(arrayOfWords,numberOfWords,message); //Wywolanie funkcji dzielacej wiadomosc na tablice slow

    std::cout << numberOfWords << std::endl;

    std::cout << "Nice job John, let's keep it goin now tell me how many elements do you want: ";
    std::cin >> numberOfElements;   //Pobranie od uzytkownika na jak wiele Elementow program ma podzielic wiadomosc
    wordsPerElement = ceil(numberOfWords/numberOfElements); //Obliczenie jak wiele slow przypada na jeden Element
    
    Message theMessage(numberOfElements,numberOfWords,wordsPerElement,arrayOfWords);    //Inicjacja obiektu Message 

    std::cout << "Your message after changing few details" << std::endl;
    theMessage.displayElementsWithIndexShuffle();   //Wyswietlenie oraz wymieszanie elementow tablicy Elementow
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Message which Anna sees: " << std::endl;

    theMessage.sortByIndex();   //Sortowanie tablicy Elementow po ich indeksach
    theMessage.displayElementsWithIndex();  //Wystwietlenie posortowanej tablicy Elementow
    
    std::cout << std::endl;
    std::cout << std::endl;

    system("pause");
    return 0;
}




