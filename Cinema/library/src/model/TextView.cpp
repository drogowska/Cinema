//
// Created by student on 16.06.2020.
//

#include "model/TextView.h"
#include "model/Cinema.h"
#include "model/Movie.h"
#include "model/Hall.h"
#include "model/Reservation.h"
#include <iostream>

using namespace std;

TextView::TextView(const CinemaPtr &cinema) : cinema(cinema), user(nullptr) {}

TextView::~TextView() {

}

void TextView::clearScreen() {
    system("clear");
    cout << "   POPCORN CRUMBS (ᵔᴥᵔ)   " << endl
         << "--------------------------" << endl;
    //system(cls); <-windows
}

void TextView::clearScreenWithoutLogo() {
    system("clear");
}

int TextView::choose(int howManyOptions) {

    int choice;
    if (howManyOptions == 1) cout << endl << "Wybor: ";
    else cout << endl << "Wybor [0-" << howManyOptions - 1 << "]:";
    for (;;) {
        cin >> choice;
        if (choice >= 0 && choice < howManyOptions)
            return choice;
    }
}

std::string TextView::convertDateAndTime(boost::posix_time::ptime dateAndTime) {
    ostringstream out;
    tm pt_tm = to_tm(dateAndTime);
    out << pt_tm.tm_year << "-";
    if (pt_tm.tm_mon < 9) out << "0";
    out << pt_tm.tm_mon + 1 << "-";
    if (pt_tm.tm_mday < 10) out << "0";
    out << pt_tm.tm_mday << " ";
    if (pt_tm.tm_hour < 10) out << "0";
    out << pt_tm.tm_hour << ":";
    if (pt_tm.tm_min < 10) out << "0";
    out << pt_tm.tm_min;
    return out.str();
}


void TextView::mainPage() {
    for (;;) {
        clearScreen();
        if (user == nullptr) {
            clearScreenWithoutLogo();
            cout << "Witaj w kinie POPCORN CRUMBS! (ᵔᴥᵔ)" << endl
                 << "[1] Zaloguj sie" << endl
                 << "[2] Dolacz do nas" << endl
                 << "[0] ⏎ Wyjscie" << endl;
            switch (choose(3)) {
                case 1:
                    signIn();
                    break;
                case 2:
                    signUp();
                    break;
                default:
                    clearScreenWithoutLogo();
                    return;
            }
        } else {
            cout << "Zalogowano jako: " << user->getFirstName() << " " << user->getLastName() << endl
                 << "Twoj typ konta: ";
            if (user->isWorker()) {
                cout << "PRACOWNIK," << user->getDiscountTypeName() << endl << endl
                     << "[1] ustawienia konta" << endl
                     << "[2] przegladaj filmy" << endl
                     << "[3] pokaz moje rezerwacje" << endl << endl
                     << "opcje pracownika:" << endl
                     << "[4] zarzadzaj uzytkownikami" << endl
                     << "[5] zarzadzaj filmami" << endl
                     << "[6] zarzadzaj seansami" << endl
                     << "[7] zarzadzaj salami" << endl
                     << "[0] ⏎ wyloguj sie" << endl;
                switch (choose(8)) {
                    case 1:
                        accountSettings();
                        break;
                    case 2:
                        showMovies();
                        break;
                    case 3:
                        showReservations();
                        break;
                    case 4:
                        manageVisitors();
                        break;
                    case 5:
                        manageMovies();
                        break;
                    case 6:
                        manageSeances();
                        break;
                    case 7:
                        manageHalls();
                        break;
                    default:
                        user = nullptr;
                        break;
                }
            } else {
                cout << " ODWIEDZAJACY, " << user->getDiscountTypeName() << endl << endl
                     << "[1] ustawienia konta" << endl
                     << "[2] przegladaj filmy" << endl
                     << "[3] pokaz moje rezerwacje" << endl
                     << "[0] ⏎ wyloguj sie" << endl;
                switch (choose(4)) {
                    case 1:
                        accountSettings();
                        break;
                    case 2:
                        showMovies();
                        break;
                    case 3:
                        showReservations();
                        break;
                    default:
                        user = nullptr;
                        break;
                }
            }

        }
    }
}

void TextView::signIn() {
    string email, password;
    VisitorPtr visitor;

    for (;;) {
        clearScreen();
        cout << "LOGOWANIE" << endl << "email: ";
        cin >> email;
        cout << "haslo: ";
        cin >> password;

        VisitorPredicate p = [email, password](VisitorPtr ptr) -> bool {
            return ((ptr->getEmail() == email) && (ptr->getPassword() == password));
        };

        try {
            visitor = cinema->visitorsManager.find(p);
            break;
        }
        catch (exception &e) {
            cout << "Dane nieprawidlowe :(" << endl
                 << "[1] Sprobuj jeszcze raz" << endl
                 << "[0] ⏎ Powrot" << endl;
            if (choose(2) == 0) return;
        }
    }
    user = visitor;
    return;
}

void TextView::signUp() {
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string password;
    std::string phoneNumber;
    DiscountType discountType;

    for (;;) {
        clearScreen();
        cout << "REJESTRACJA" << endl;
        cout << "Podaj imie:";
        cin >> firstName;
        cout << "Podaj nazwisko:";
        cin >> lastName;
        cout << "Podaj email:";
        cin >> email;
        cout << "Podaj haslo:";
        cin >> password;
        cout << "Podaj nr telefonu:";
        cin >> phoneNumber;
        cout << "Wybierz typ odwiedzającego:" << endl
             << "[1] Dziecko" << endl
             << "[2] Senior" << endl
             << "[3] Student" << endl
             << "[0] Standardowy" << endl;
        switch (choose(4)) {
            case 1:
                discountType = Kid;
                break;
            case 2:
                discountType = Senior;
                break;
            case 3:
                discountType = Student;
                break;
            default:
                discountType = Default;
        }
        try {
            cinema->visitorsManager.addVisitor(firstName, lastName, email, password, phoneNumber, discountType, 0);
            break;
        }
        catch (exception &e) {
            cout << "Dane nieprawidlowe :( Napotkano problem:" << endl
                 << e.what() << endl
                 << "[1] Sprobuj jeszcze raz" << endl
                 << "[0] ⏎ Powrot" << endl;
            if (choose(2) == 0) return;
        }
    }
    cout << "Utworzono konto. Dane do logowania:" << endl
         << "email: " << email << endl
         << "haslo: " << password << endl
         << "Jeżeli jestes pracownikiem, popros innego pracownika o nadanie dodatkowych praw." << endl
         << "[0] Kontynnuj" << endl;
    choose(1);
    return;
}


void TextView::showMovies() {
    for (;;) {
        clearScreen();
        cout << "FILMY" << endl << "Wybierz film, aby wyswietlic dostepne seanse" << endl;
        for (int i = 0; i < cinema->moviesManager.size(); i++) {
            MoviePtr movie = cinema->moviesManager.getMovie(i);
            cout << endl << "[" << i + 1 << "] " << movie->getTitle() << " cena: " << movie->getBasePrice() << endl;
        }
        cout << "[0] ⏎ Powrot";
        int choice = choose(cinema->moviesManager.size() + 1);
        if (choice == 0) return;
        else showSeances(cinema->moviesManager.getMovie(choice - 1));
    }
}


void TextView::showSeances(const MoviePtr &movie) {
    SeancePredicate p = [movie](SeancePtr ptr) -> bool {
        return (ptr->getMovie() == movie);
    };

    for (;;) {
        clearScreen();
        cout << "FILM: " << movie->getTitle() << endl
             << "cena bazowa: " << movie->getBasePrice() << endl << endl
             << "SEANSE:" << endl
             << "Wybierz seans, aby utworzyc nowa rezerwacje" << endl;
        vector<SeancePtr> seances = cinema->seancesManager.findAll(p);
        for (int i = 0; i < seances.size(); i++) {
            cout << "[" << i + 1 << "] " << convertDateAndTime(seances[i]->getDateAndTime());
            cout << " sala: " << seances[i]->getHall()->getHallNumber() << " typ: ";
            if (seances[i]->getSeanceType() == threeD) cout << "3D" << endl;
            else cout << "2D" << endl;
        }
        cout << "[0] ⏎ Powrot" << endl;
        int choice = choose(seances.size() + 1);
        if (choice == 0) return;
        makeReservation(seances[choice - 1]);
    }
}

void TextView::showReservations() {
    VisitorPtr user = TextView::user;
    ReservationPredicate p = [user](ReservationPtr ptr) -> bool {
        return (ptr->getVisitor() == user);
    };
    for (;;) {
        clearScreen();
        cout << "MOJE REZERWACJE" << endl
             << "Wybierz rezerwacje jezeli chcesz ja anulowac" << endl
             << "Aby dodac nowe rezerwacje, przegladaj filmy" << endl << endl;
        vector<ReservationPtr> reservations = cinema->reservationsManager.findAll(p);
        for (int i = 0; i < reservations.size(); i++) {
            SeancePtr seance = reservations[i]->getSeance();
            cout << "[" << i + 1 << "] " << seance->getMovie()->getTitle() << " sala: "
                 << seance->getHall()->getHallNumber() << " rzad: "
                 << reservations[i]->getRow() << " miejsce: " << reservations[i]->getSeat() << endl
                 << "    kiedy: " << convertDateAndTime(seance->getDateAndTime()) << " cena: "
                 << reservations[i]->getActualPrice() << endl;
        }
        cout << "[0] ⏎ Powrot" << endl;
        int choice = choose(reservations.size() + 1);
        if (choice == 0) return;
        cout << "Czy napewno chcesz ANULOWAC rezerwacje?" << endl
             << "[1] Tak, anuluj rezerwacje" << endl
             << "[0] Nie" << endl;
        if (choose(2) == 1) {
            cinema->reservationsManager.removeReservation(reservations[choice - 1]);
            cout << "Rezerwacja zostala anulowana." << endl
                 << "[0] Odswiez" << endl;
            choose(1);
        }
    }
}

void TextView::makeReservation(const SeancePtr &seance) {
    ReservationPredicate p = [seance](ReservationPtr ptr) -> bool {
        return (ptr->getSeance() == seance);
    };
    HallPtr hall = seance->getHall();
    int chosenRow, chosenSeat;
    int rowsNumber = hall->getNumberOfRows();
    int seatsInRowNumber = hall->getNumberOfSeatInRow();
    bool **seats = new bool *[rowsNumber];
    for (int i = 0; i < hall->getNumberOfRows(); i++) {
        seats[i] = new bool[seatsInRowNumber];
        for (int j = 0; j < seatsInRowNumber; j++) seats[i][j] = 0;
    }

    vector<ReservationPtr> reservations = cinema->reservationsManager.findAll(p);
    for (ReservationPtr ptr :reservations) {
        seats[ptr->getRow() - 1][ptr->getSeat() - 1] = 1;
    }

    for (;;) {
        clearScreen();
        cout << "TWORZENIE REZERWACJI NA SEANS" << endl
             << "film: " << seance->getMovie()->getTitle()
             << " kiedy: " << convertDateAndTime(seance->getDateAndTime())
             << " sala: " << hall->getHallNumber() << endl
             << endl << "[ ] - wolne [x] - zajete" << endl;

        cout << "==EKRAN==";
        for (int i = 3; i <= seatsInRowNumber; i++) cout << "===";
        cout << endl << "   ";
        for (int i = 1; i <= seatsInRowNumber; i++) {
            cout << i << " ";
            if (i < 10) cout << " ";
        }
        for (int i = 0; i < rowsNumber; i++) {
            cout << endl << i + 1 << " ";
            if (i < 9) cout << " ";
            for (int j = 0; j < seatsInRowNumber; j++) {
                cout << "[";
                if (seats[i][j]) cout << "x";
                else cout << " ";
                cout << "]";
            }
        }
        cout << endl << "Podaj rzad [1-" << rowsNumber << "]:";
        cin >> chosenRow;
        cout << "Podaj miejscie [1-" << seatsInRowNumber << "]:";
        cin >> chosenSeat;
        try {
            cinema->reservationsManager.addReservation(user, seance, chosenRow, chosenSeat);
        }
        catch (exception &e) {
            cout << "Nie udalo sie, wystapil problem:" << endl
                 << e.what() << endl
                 << "[1] Wybierz inne" << endl
                 << "[0] ⏎ Powrot" << endl;
            if (choose(2) == 1) continue;
            else break;
        }
        cout << "Zarezerwowano miejsce!" << endl
             << "[0] ⏎ Powrot" << endl;
        choose(1);
        break;
    }

    for (int i = 0; i < hall->getNumberOfRows(); i++) {
        delete[] seats[i];
    }
    delete[] seats;
}

void TextView::accountSettings() {
    for (;;) {
        clearScreen();
        cout << "USTAWIENIA KONTA" << endl
             << "Imie: " << user->getFirstName() << endl
             << "Nazwisko: " << user->getLastName() << endl
             << "Mail: " << user->getEmail() << endl
             << "Nr telefonu: " << user->getPhoneNumber() << endl << endl;

        string newValue;

        cout << "[1] Zmien imie" << endl
             << "[2] Zmien nazwisko" << endl
             << "[3] Zmien mail" << endl
             << "[4] Zmien nr telefonu" << endl
             << "[5] Zmien haslo" << endl
             << "[6] Usun konto" << endl
             << "[0] ⏎ Powrot" << endl;
        switch (choose(7)) {
            case 1:
                cout << "Podaj nowe imie: ";
                cin >> newValue;
                try {
                    user->setFirstName(newValue);
                    break;
                } catch (exception &e) {
                    cout << "Wystapil problem: " << endl
                         << e.what() << endl
                         << "[0] ⏎ Powrot" << endl;
                    choose(1);
                    break;
                }
            case 2:

                cout << "Podaj nowe nazwisko: ";
                cin >> newValue;
                try {
                    user->setLastName(newValue);
                    break;
                } catch (exception &e) {
                    cout << "Wystapil problem: " << endl
                         << e.what() << endl
                         << "[0] ⏎ Powrot" << endl;
                    choose(1);
                    break;
                }

            case 3:

                cout << "Podaj nowy email: ";
                cin >> newValue;
                try {
                    user->setEmail(newValue);
                    break;
                } catch (exception &e) {
                    cout << "Wystapil problem: " << endl
                         << e.what() << endl
                         << "[0] ⏎ Powrot" << endl;
                    choose(1);
                    break;
                }

            case 4:

                cout << "Podaj nowy nr telefonu: ";
                cin >> newValue;
                try {
                    user->setPhoneNumber(newValue);
                    break;
                } catch (exception &e) {
                    cout << "Wystapil problem: " << endl
                         << e.what() << endl
                         << "[0] ⏎ Powrot" << endl;
                    choose(1);
                    break;
                }

            case 5:

                cout << "Podaj nowe haslo: ";
                cin >> newValue;
                try {
                    user->setPassword(newValue);
                    cout << "Haslo zmienione" << endl
                         << "[0] Ok" << endl;
                    choose(1);
                    break;
                } catch (exception &e) {
                    cout << "Wystapil problem: " << endl
                         << e.what() << endl
                         << "[0] ⏎ Powrot" << endl;
                    choose(1);
                    break;
                }

            case 6:
                cout << "Czy na pewno chcesz USUNAC KONTO? Twoje rezerwacje zostana anulowane!" << endl
                     << "[1] Tak, usun konto" << endl
                     << "[0] ⏎ Nie" << endl;
                if (choose(2) == 1) {
                    cinema->fullRemoveVisitor(user);
                    user = nullptr;
                    return;
                }
                break;
            default:
                return;
        }
    }
}


void TextView::manageVisitors() {
    for (;;) {
        clearScreen();
        cout << "ZARZADZANIE UZYTKOWNIKAMI" << endl
             << "Wybierz uzytkownika aby dodac go do pracownikow lub usunac jego konto" << endl << endl;
        for (int i = 0; i < cinema->visitorsManager.size(); i++) {
            VisitorPtr visitor = cinema->visitorsManager.getVisitor(i);

            cout << "[" << i + 1 << "] " << visitor->getId() << endl;
            if (visitor->isWorker()) cout << "   PRACOWNIK, ";
            else cout << "   ODWIEDZAJACY, ";
            cout << visitor->getDiscountTypeName();
            cout << "   " << visitor->getFirstName() << " " << visitor->getLastName() << endl;
            cout << "   " << visitor->getEmail() << " " << visitor->getPhoneNumber() << endl;

        }
        cout << "[0] ⏎ Powrot" << endl;
        int choice = choose(cinema->visitorsManager.size() + 1);
        if (choice == 0) return;
        VisitorPtr chosenVisitor = cinema->visitorsManager.getVisitor(choice - 1);
        cout << "Wybrano uzytkownika " << chosenVisitor->getFirstName() << " " << chosenVisitor->getLastName() << endl
             << "[1] Dodaj do pracownikow" << endl
             << "[2] Usun konto" << endl
             << "[0] Powrot" << endl;
        switch (choose(3)) {
            case 1:
                if (chosenVisitor->isWorker()) {
                    cout << "Ten uzytkownik jest juz pracownikiem." << endl
                         << "[0] Ok";
                    choose(1);
                    continue;
                } else {
                    chosenVisitor->setWorker(1);
                    cout << "Uzytkownik zostal dodany do pracownikow!" << endl
                         << "[0] Odswiez";
                    choose(1);
                    continue;
                }
                break;
            case 2:
                cout << "Czy na pewno chcesz usunac tego uzytkownika razem z jego/jej rezerwacjami?" << endl
                     << "[1] Tak, usun" << endl
                     << "[0] Nie" << endl;
                if (choose(2) == 0) continue;
                if (cinema->visitorsManager.getVisitor(choice - 1) == user) {
                    cinema->fullRemoveVisitor(chosenVisitor);
                    user = nullptr;
                    return;
                }
                cinema->fullRemoveVisitor(chosenVisitor);
                cout << "Uzytkownik zostal usuniety z systemu" << endl
                     << "[0] Odswiez" << endl;
                choose(1);
                break;
            default:
                return;
        }
    }
}

void TextView::manageMovies() {

    string title;
    unsigned int basePrice;
    for (;;) {
        clearScreen();
        cout << "ZARZADZANIE FILMAMI" << endl
             << "Wybierz film aby go usunac albo dodaj nowy film" << endl << endl
             << "[1] DODAJ nowy film" << endl;
        for (int i = 0; i < cinema->moviesManager.size(); i++) {
            MoviePtr movie = cinema->moviesManager.getMovie(i);
            cout << "[" << i + 2 << "] " << movie->getTitle() << " cena bazowa: " << movie->getBasePrice() << endl;
        }
        cout << "[0] ⏎ Powrot" << endl;
        int choice = choose(cinema->moviesManager.size() + 2);
        if (choice == 0) return;
        if (choice == 1) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Podaj tytul: ";
            getline(cin, title);
            cout << "Podaj cene: ";
            cin >> basePrice;
            try {
                cinema->moviesManager.addMovie(title, basePrice);
            } catch (exception &e) {
                cout << "Wystapil problem:" << endl
                     << e.what()
                     << "[0] ⏎ Powrot";
                continue;
            }
        } else {
            MoviePtr chosenMovie = cinema->moviesManager.getMovie(choice - 2);
            cout << "Czy na pewno chcesz usunac film " << chosenMovie->getTitle() << " razem z jego seansami?" << endl
                 << "[1] Tak, usun" << endl
                 << "[0] Nie" << endl;
            if (choose(2) == 0) continue;
            cinema->fullRemoveMovie(chosenMovie);
            cout << "Film zostal usuniety z systemu" << endl
                 << "[0] Odswiez" << endl;
            choose(1);
        }
    }
}

void TextView::manageSeances() {

    int mon;
    tm pt_tm;
    pt_tm.tm_sec = 0;
    SeanceType seanceType;

    for (;;) {
        clearScreen();
        cout << "ZARZADZANIE SEANSAMI" << endl
             << "Wybierz film, ktorego seansami chcesz zarzadzac" << endl << endl;
        for (int i = 0; i < cinema->moviesManager.size(); i++) {
            MoviePtr movie = cinema->moviesManager.getMovie(i);
            cout << "[" << i + 1 << "] " << movie->getTitle() << endl;
        }
        cout << "[0] ⏎ Powrot" << endl;
        int choice = choose(cinema->moviesManager.size() + 1);
        if (choice == 0) return;
        MoviePtr chosenMovie = cinema->moviesManager.getMovie(choice - 1);
        for (;;) {
            clearScreen();
            cout << "ZARZADZANIE SEANSAMI: " << chosenMovie->getTitle() << endl
                 << "Wybierz seans aby go usunac albo dodaj nowy seans" << endl << endl;
            SeancePredicate p = [chosenMovie](SeancePtr ptr) -> bool {
                return (ptr->getMovie() == chosenMovie);
            };
            vector<SeancePtr> seances = cinema->seancesManager.findAll(p);
            cout << "[1] DODAJ nowy seans" << endl;
            for (int i = 0; i < seances.size(); i++) {
                cout << "[" << i + 2 << "] ID: " << seances[i]->getId() << endl
                     << "    " << convertDateAndTime(seances[i]->getDateAndTime())
                     << " sala: " << seances[i]->getHall()->getHallNumber() << " typ: ";
                if (seances[i]->getSeanceType() == threeD) cout << "3D" << endl;
                else cout << "2D" << endl;
            }
            cout << "[0] ⏎ Powrot" << endl;
            choice = choose(seances.size() + 2);
            if (choice == 0) break;
            if (choice == 1) {
                if (cinema->hallsManager.size() == 0) {
                    cout << "W kinie nie ma zadnej sali, nie mozna dodac seansu." << endl
                         << "[0] ⏎ Powrot";
                    choose(1);
                    continue;
                }

                cout << "Podaj rok (np. 2020):";
                cin >> pt_tm.tm_year;
                cout << "Podaj miesiac (np. 1):";
                cin >> mon;
                pt_tm.tm_mon = mon - 1;
                cout << "Podaj dzien miesiaca (np. 15):";
                cin >> pt_tm.tm_mday;
                cout << "Podaj godzine (np. 9):";
                cin >> pt_tm.tm_hour;
                cout << "Podaj minuty (np. 30):";
                cin >> pt_tm.tm_min;
                boost::posix_time::ptime dateAndTime = boost::posix_time::ptime_from_tm(pt_tm);
                cout << "Wybierz typ:" << endl
                     << "[1] 3D" << endl
                     << "[0] 2D" << endl;
                (choose(2)) ? seanceType = threeD : seanceType = twoD;
                cout << "Wybierz sale:" << endl;
                for (int i = 0; i < cinema->hallsManager.size(); i++) {
                    cout << "[" << i + 1 << "]" << cinema->hallsManager.getHall(i)->getHallNumber() << endl;
                }
                cout << "[0] ⏎ Powrot";
                choice = choose(cinema->hallsManager.size() + 1);
                if (choice == 0) continue;
                HallPtr chosenHall = cinema->hallsManager.getHall(choice - 1);
                try {
                    cinema->seancesManager.addSeance(dateAndTime, seanceType, chosenMovie, chosenHall);
                } catch (exception &e) {
                    cout << "Wystapil problem:" << endl
                         << e.what()
                         << "[0] ⏎ Powrot" << endl;
                    choose(1);
                    continue;
                }
                cout << "Dodano nowy seans!" << endl
                     << "[0] ⏎ Powrot" << endl;
                choose(1);
                continue;
            }
            SeancePtr chosenSeance = seances[choice - 2];
            cout << "Czy na pewno chcesz usunac seans razem z rezerwacjami na niego?" << endl
                 << "[1] Tak, usun" << endl
                 << "[0] Nie" << endl;
            if (choose(2) == 0) continue;
            cinema->fullRemoveSeance(chosenSeance);
            cout << "Seans zostal usuniety z systemu" << endl
                 << "[0] Odswiez" << endl;
            choose(1);
        }
    }


}

void TextView::manageHalls() {
    string hallNumber;
    int numberOfRows, numberOfSeatsInRow;
    for (;;) {
        clearScreen();
        cout << "ZARZADZANIE SALAMI" << endl
             << "Wybierz sale aby ja usunac albo dodaj nowa sale" << endl << endl
             << "[1] DODAJ nowa sale" << endl;
        for (int i = 0; i < cinema->hallsManager.size(); i++) {
            HallPtr hall = cinema->hallsManager.getHall(i);
            cout << "[" << i + 2 << "] " << hall->getHallNumber() << endl << "    liczba rzedow: "
                 << hall->getNumberOfRows() << " liczba miejsc w rzedzie: " << hall->getNumberOfSeatInRow() << endl;
        }
        cout << "[0] ⏎ Powrot" << endl;
        int choice = choose(cinema->hallsManager.size() + 2);
        if (choice == 0) return;
        if (choice == 1) {
            cout << "Podaj nazwe sali: ";
            cin >> hallNumber;
            cout << "Podaj liczbe rzedow: ";
            cin >> numberOfRows;
            cout << "Podaj liczbe miejsc w rzedzie: ";
            cin >> numberOfSeatsInRow;
            try {
                cinema->hallsManager.addHall(hallNumber, numberOfRows, numberOfSeatsInRow);
            } catch (exception &e) {
                cout << "Wystapil problem:" << endl;
                cout << e.what();
                cout << "[0] ⏎ Powrot";
                continue;
            }
            cout << "Dodano nowa sale!" << endl;
            cout << "[0] ⏎ Powrot" << endl;
            choose(1);
            continue;
        } else {
            HallPtr chosenHall = cinema->hallsManager.getHall(choice - 2);
            cout << "Czy na pewno chcesz usunac sale " << chosenHall->getHallNumber() << " razem z jej seansami?"
                 << endl;
            cout << "[1] Tak, usun" << endl
                 << "[0] Nie" << endl;
            if (choose(2) == 0) continue;
            cinema->fullRemoveHall(chosenHall);
            cout << "Sala zostala usunieta z systemu" << endl
                 << "[0] Odswiez" << endl;
            choose(1);
        }
    }
}









