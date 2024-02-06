/* Kirjasto (library)
 *
 * Kuvaus:
 *  Ohjelma toteuttaa kirjaston, jossa sovelletaan erilaisia STL-kirjaston
 *  funktioita. Kirjastoja voi olla useita, ja jokaisen kirjaston kirjojen
 *  tiedot on määritetty tietueessa Book. Kirjalla on siis tiedot: tekijä,
 *  nimi ja varausten määrä.
 *      Ohjelma kysyy ensiksi syötetiedostoa, mikä sisältää useiden
 *  kirjastojen tietokannat. Mikäli tiedostoa ei löydy, ohjelma tulostaa
 *  virheilmoituksen ja lopettaa suorittamisen. Mikäli tiedosto löytyy,
 *  ohjelma lukee tiedoston läpi ja tallentaa sen tiedot mappiin
 *  Kirjasto-luokkaa käyttäen. Ohejelma tarkastaa
 *  syötteen oikeellisuutta ja antaa tarvittaessa virheilmoituksen.
 *  Tämän jälkeen ohjelma kysyy käyttäjältä tämän haluamaa käskyä jokaisella
 *  suorituskierroksella.
 *      Käyttäjä voi syöttää käskyt:
 *  libraries:   Tulostaa kaikki tiedostossa olevat kirjastot
 *
 *  material <kirjasto>:    tulostaa kaikki kyseisen kirjaston teokset
 *
 *  books <kirjasto> <tekijä>:  tulostaa tietyn kaikki kirjaston kyseisen
 *        kirjailijan kirjat varaus-statuksineen
 *
 *  reservable <tekijä> <kirjan_nimi>:  tulostaa lyhyimmän varausjonon
 *      halutun tekijän halutulle kirjalle sekä kirjastot aakkosjärjestyksessä,
 *      joissa kirjaa on saatavilla samanpituisella varausjonolla
 *
 * loanable:    Tulostaa kaikki kirjat, jotka löytyvät valmiina tietokannan
 *              hyllyistä
 *
 *  Ohjelman suoritus päättyy käyttäjän antamaan syötteeseen "quit".
 *
 * Ohjelman kirjoittaja:
 *  Nimi: Roope Lindroos
 *  E-Mail: roope.lindroos@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Ohjelma ensimmäisiä isompia projekteja ja tätä kirjoittaessa käynnissä vasta
 * toinen ohjelmointikurssi. Koodi olisi mahdollista kirjoittaa huomattavasti
 * tehokkaammin, tyylikkäämmin (helpommin luettavasti) ja fiksumpia rakneteita ja
 * toimintoja käyttäen.
 *  */

#include "library.hh"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <utility>
#include <algorithm>


using namespace std;

using Database = map<string, Library>;


// Method splits string-input to smaller pieces and contains them in vector
vector<string> split(const string& line, const char delimiter,
                     bool ignore_empty = false){

    vector<string> result;
    string tmp = line;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


// Changes the info of reservation from string to integer
int reservation(const string& res_string){

    if (res_string == "on-the-shelf"){
        return 0;
    } else {
        return stoi(res_string);
    }
}


// Method prints names of all existing libraries
void print_libraries(const Database& database){

    for (auto part : database){
        cout << part.first << endl;
    }
}


// Method returns true if size of the vector is same as given number
bool params_found(vector<string> params, unsigned long int comparison){
    if (params.size() != comparison){
        return false;
    } else {
        return true;
    }
}


//Method for printing loanable books from the whole database
void print_loanables(Database& data){
    Database::iterator dataiter = data.begin();
    Library loanables = {};

    while (dataiter != data.end()){
        vector<Book> temp_books = dataiter->second.all_books();

        for (auto part : temp_books){

            if ((not loanables.book_found(part.author, part.title))
                    and (part.reservations == 0)){

                loanables.add_book(part.author, part.title,
                                   part.reservations);

            }
        }

        dataiter++;
    }

    loanables.print_all();
}


int main(){

    // Reading and checking correct input
    string input_name = "";
    cout << "Input file: ";
    getline(cin, input_name);

    ifstream input_file(input_name);

    if(not input_file){
        cout << "Error: input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    Database database = {};
    string line = "";


    // Saving input_file to containers
    while (getline(input_file, line)){
        vector<string> temp;
        temp = split(line, ';', true);

        if (temp.size() != 4){
            cout << "Error: empty field" << endl;
            return EXIT_FAILURE;
        }

        if (database.find(temp.at(0)) == database.end()){
            Library temp_lib = {};
            database.insert({temp.at(0), temp_lib});

        }

        database.at(temp.at(0)).add_book(temp.at(1), temp.at(2),
                                         reservation(temp.at(3)));
    }

    input_file.close();

    string STOP = "quit";

    // Main program which asks users input until given command to end
    while (true){
        string command;
        vector<string> cmd_temp;
        cout << "lib> ";
        getline(cin, command);

        cmd_temp = split(command, ' ', true);


        // Command to end program
        if (cmd_temp.at(0) == STOP){
            return EXIT_SUCCESS;


          // Command to print all libraries
        } else if (cmd_temp.at(0) == "libraries"){

            print_libraries(database);


            // Command to print all material from spesific library
        } else if (cmd_temp.at(0) == "material"){

            if (not params_found(cmd_temp,2)){
                cout << "Error: wrong number of parameters" << endl;
                continue;
            }

            if (database.find(cmd_temp.at(1)) == database.end()){
                    cout << "Error: unknown library" << endl;
                    continue;
            }

            database.at(cmd_temp.at(1)).print_all();


            // Command to print all books from spesific author
            // with their reservations
        } else if (cmd_temp.at(0) == "books"){

            if (not params_found(cmd_temp,3)){
                cout << "Error: wrong number of parameters" << endl;
                continue;
            }

            if (database.find(cmd_temp.at(1)) == database.end()){
                    cout << "Error: unknown library" << endl;
                    continue;
            }

            database.at(cmd_temp.at(1)).print_books(cmd_temp.at(2));


        } else if (cmd_temp.at(0) == "reservable"){

            vector<string>::iterator iter;

            // Adding the whole title together
            if (cmd_temp.size() > 3){
                iter = cmd_temp.begin() +3;

                while (iter != cmd_temp.end()){

                    cmd_temp.at(2) += " " + *iter;

                    iter++;
                }
            }

            // Check if the title has quotation marks
            string title_s = cmd_temp.at(2);

            size_t pos;
            while ((pos = title_s.find('\"')) != string::npos ){
                title_s.erase(pos, 1);
            }

            Database::iterator dataiter = database.begin();
            Library temp = {};
            int res_tmp = -1;
            int least_reservations = temp.MAX_RES;
            vector<string> libraries_tmp = {};

            while (dataiter != database.end()){

                if (dataiter->second.book_found(cmd_temp.at(1),
                                                title_s)){

                    res_tmp = dataiter->second.get_queue(cmd_temp.at(1),
                                                         title_s);

                    if (res_tmp == least_reservations){
                        libraries_tmp.push_back(dataiter->first);
                    }

                    if (res_tmp < least_reservations){
                        least_reservations = res_tmp;
                        libraries_tmp = {};
                        libraries_tmp.push_back(dataiter->first);
                    }

                }

                dataiter++;
            }

            // Printing the result of previous search
            if(res_tmp == -1){
                cout << "Book is not a library book" << endl;
                continue;
            }

            if (least_reservations >= temp.MAX_RES){
                cout << "Book is not reservable from any library" << endl;
                continue;

            } else if (least_reservations == 0){
                cout << "on the shelf" << endl;

            } else {
                cout << least_reservations << " reservations" << endl;
            }

            //printing the names of libraries where book is found
            for (auto lib : libraries_tmp){
                cout << "--- " << lib << endl;
            }

            // Command to print all books available of the shelf
        } else if (cmd_temp.at(0) == "loanable"){

            // Checking the amount of parameters
            if (not params_found(cmd_temp, 1)){
                cout << "Error: wrong number of parameters" << endl;
                continue;
            }

            print_loanables(database);

            // Warning for unknown command
        } else {
            cout << "Error: unknown command" << endl;
        }
    }
}
