#include<iostream>
#include<vector>
#include<string>
#include<regex>
#include<mutex>
#include<thread>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };
const char* ispisRazreda[]{ "PRVI" , "DRUGI", "TRECI" ,"CETVRTI" };

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

bool ValidirajBrojTelefona(string broj) {
    return regex_match(broj, regex("[+][0-9]{2,3}[0]?[0-9]{2,3}[0-9]{2,3}[-]?[\\s]?[0-9]{2,3}"));
}

template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno;
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _omoguciDupliranje = omoguciDupliranje;
        _trenutno = 0;
    }
    Kolekcija(const Kolekcija& obj) {
        _trenutno = obj._trenutno;
        _omoguciDupliranje = obj._omoguciDupliranje;
        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];
        for (size_t i = 0; i < _trenutno; i++) {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj) {
            _omoguciDupliranje = obj._omoguciDupliranje;
            _trenutno = obj._trenutno;
            delete[]_elementi1;
            delete[]_elementi2;
            _elementi1 = new T1[_trenutno];
            _elementi2 = new T2[_trenutno];
            for (int i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }
        }
        return *this;
    }
    bool operator ==(Kolekcija obj) {
        if (obj._trenutno != _trenutno)
            return false;
        for (int i = 0; i < _trenutno; i++)
        {
            if (_elementi1[i] != obj._elementi1[i] || _elementi2[i] != obj._elementi2[i])
                return false;
        }
        return true;
    }
    bool operator !=(Kolekcija obj) {
        return !(*this == obj);
    }

    Kolekcija operator()(int pocetak, int kraj) {
        Kolekcija add;
        if (pocetak < 0 || kraj > _trenutno)
            throw exception("Preskocen opseg!");
        for (size_t i = pocetak; i <= kraj; i++) {
            add.AddElement(_elementi1[i], _elementi2[i]);
        }
        return add;
    }

    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
    }

    void AddElement(T1 el1, T2 el2) {
        if (!_omoguciDupliranje) {
            for (size_t i = 0; i < _trenutno; i++) {
                if (_elementi1[i] == el1 && _elementi2[i] == el2)
                    throw exception("Nema dupliranja!");
            }
        }
        T1* temp1 = new T1[_trenutno + 1];
        T2* temp2 = new T2[_trenutno + 1];
        for (int i = 0; i < _trenutno; i++)
        {
            temp1[i] = _elementi1[i];
            temp2[i] = _elementi2[i];
        }
        temp1[_trenutno] = el1;
        temp2[_trenutno] = el2;
        _trenutno++;
        delete[]_elementi1;
        delete[]_elementi2;
        _elementi1 = temp1;
        _elementi2 = temp2;
        temp1 = nullptr;
        temp2 = nullptr;
    }

    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() const { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};

class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }
    int toDays() const {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }
    bool operator==(const Datum& obj) {
        return *_godina == *obj._godina && *_mjesec == *obj._mjesec && *_dan == *obj._dan;
    }
    bool operator!=(Datum& obj) {
        return !(obj == *this);
    }
    bool operator>(const Datum& obj) {
        return this->toDays() > obj.toDays();
    }

    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};

class Predmet {
    char* _naziv;
    Kolekcija<Datum*, int>* _ocjene;
public:
    Predmet(const char* naziv = "", Datum datum = Datum(), int ocjena = 0) {
        _naziv = GetNizKaraktera(naziv);
        _ocjene = new Kolekcija<Datum*, int>(ocjena);
        if (ocjena > 0)
            AddOcjena(datum, ocjena);
    }
    Predmet(const Predmet& obj) {
        _naziv = GetNizKaraktera(obj._naziv);
        _ocjene = new Kolekcija<Datum*, int>(*obj._ocjene);
    }

    float ProsjekDatuma() {
        float prosjek = 0;
        if (_ocjene->getTrenutno() < 1)
            return prosjek;
        for (int i = 0; i < _ocjene->getTrenutno() - 1; i++)
        {
            prosjek += abs(_ocjene->getElement1(i)->toDays() - _ocjene->getElement1(i + 1)->toDays());
        }
        return float(prosjek / _ocjene->getTrenutno());
    }

    bool operator==(Predmet obj) {
        return strcmp(_naziv, obj._naziv) == 0;
    }
    bool operator != (Predmet obj) {
        return !(*this != obj);
    }

    Predmet& operator=(const Predmet& obj) {
        if (this != &obj) {
            _naziv = GetNizKaraktera(obj._naziv);
            _ocjene = new Kolekcija<Datum*, int>(*obj._ocjene);
        }
        return *this;
    }
    void AddOcjena(Datum& datumOcjene, int ocjena) {
        _ocjene->AddElement(new Datum(datumOcjene), ocjena);
    }
    float ProsjekPredmeta() {
        float prosjek = 0;
        if (_ocjene->getTrenutno() == 0)
            return prosjek;
        for (size_t i = 0; i < _ocjene->getTrenutno(); i++) {
            prosjek += _ocjene->getElement2(i);
        }
        return float(prosjek / _ocjene->getTrenutno());
    }

    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<Datum*, int> GetOcjene() { return _ocjene; }

    friend ostream& operator<< (ostream& COUT, Predmet& obj) {
        COUT << "Naziv: " << obj._naziv << endl;
        COUT << ":::DATUM ::: OCJENE:::" << endl;
        for (size_t i = 0; i < obj._ocjene->getTrenutno(); i++) {
            COUT << "Datum: " << *obj._ocjene->getElement1(i) << ", ocjena: " << obj._ocjene->getElement2(i) << endl;
        }
        cout << "Prosjek: " << obj.ProsjekPredmeta() << endl;
        return COUT;
    }

};

class Uspjeh {
    eRazred _razred;
    //char* se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet*, const char*> _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
        _polozeniPredmeti;
    }
    Uspjeh(const Uspjeh& obj) {
        _razred = obj._razred;
        _polozeniPredmeti = obj._polozeniPredmeti;
    }
    Uspjeh& operator=(const Uspjeh& obj) {
        if (this != &obj) {
            _razred = obj._razred;
            _polozeniPredmeti = obj._polozeniPredmeti;
        }
        return *this;
    }

    float ProsjekSvihPredmeta() {
        float prosjek = 0;
        if (_polozeniPredmeti.getTrenutno() == 0)
            return prosjek;
        for (size_t i = 0; i < _polozeniPredmeti.getTrenutno(); i++) {
            prosjek += _polozeniPredmeti.getElement1(i)->ProsjekPredmeta();
        }
        return float(prosjek / _polozeniPredmeti.getTrenutno());
    }

    Kolekcija<Predmet*, const char*>& GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() const { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT << "Razred: " << ispisRazreda[obj._razred] << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.getTrenutno(); i++) {
            COUT << *obj._polozeniPredmeti.getElement1(i) << " - " << obj._polozeniPredmeti.getElement2(i) << endl;
        }
        return COUT;
    }
};


mutex m;
class Kandidat {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;

    void SaljiMail(eRazred razred, float prosjekRazreda, float prosjekSkolovanja) {
        m.lock();
        cout << "\nFROM:info@fit.ba" << endl;
        cout << "TO: " << _emailAdresa << endl;
        cout << "Postovani: " << _imePrezime << ", evidentirali ste uspjeh za: " << ispisRazreda[razred] << "." << endl;
        cout << "Dosadasnji uspjeh (prosjek) na nivou: " << ispisRazreda[razred] << " iznosi: " << prosjekRazreda << ", a ukupni uspjeh u toku skolovanja iznosi: " << prosjekSkolovanja << endl;
        cout << "Pozdrav\nFIT Team." << endl;
        m.unlock();
    }
    void SaljiSMS(eRazred razred, float prosjekSkolovanja) {
        m.lock();
        cout << "Svaka cast za uspjeh: " << prosjekSkolovanja << " u " << ispisRazreda[razred] << " razredu." << endl;
        m.unlock();
    }
public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        if (ValidirajBrojTelefona(emailAdresa))
            _emailAdresa = emailAdresa;
        else
            _emailAdresa = "NOT VALID";

    }
    Kandidat(const Kandidat& obj) {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        /*_brojTelefona = ValidirajBrojTelefona(obj._brojTelefona) ? _brojTelefona : NOT_VALID;*/
        _brojTelefona = obj._brojTelefona;
        _uspjeh = obj._uspjeh;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            _uspjeh = obj._uspjeh;
        }
        return *this;
    }

    float GetProsjekRazreda(eRazred razred) {
        float prosjek = 0;
        if (_uspjeh.size() == 0)
            return prosjek;

        for (size_t i = 0; i < _uspjeh.size(); i++) {
            if (_uspjeh[i].GetERazred() == razred) {
                for (size_t j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++) {
                    prosjek += _uspjeh[i].GetPredmeti().getElement1(j)->ProsjekPredmeta();
                }
                return prosjek / _uspjeh[i].GetPredmeti().getTrenutno();
            }
        }
    }

    bool ProvjerIste(eRazred razred, Predmet& predmet) {
        for (size_t i = 0; i < _uspjeh.size(); i++) {
            if (_uspjeh[i].GetERazred() == razred) {
                for (size_t j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++) {
                    if (*_uspjeh[i].GetPredmeti().getElement1(j) == predmet)
                        return true;
                }
            }
        }
        return false;
    }

    bool AddPredmet(eRazred razred, Predmet& predmet, const char* napomena = "---") {
        for (size_t i = 0; i < _uspjeh.size(); i++) {
            if (_uspjeh[i].GetERazred() == razred) {
                if (predmet.ProsjekPredmeta() < 2.5)
                    return false;
                if (ProvjerIste(razred, predmet))
                    return false;
                if (_uspjeh[i].GetPredmeti().getTrenutno() >= 5)
                    return false;

                _uspjeh[i].GetPredmeti().AddElement(new Predmet(predmet), napomena);
                float prosjekRazreda = GetProsjekRazreda(razred);
                float prosjehSkolovanja = _uspjeh[i].ProsjekSvihPredmeta();
                thread t1(&Kandidat::SaljiMail, this, razred, prosjekRazreda, prosjehSkolovanja);
                t1.join();
                if (prosjekRazreda >= 4.5) {
                    thread sms(&Kandidat::SaljiSMS, this, razred, prosjehSkolovanja);
                    sms.join();
                }
                return true;
            }
        }
        Uspjeh u(razred);
        u.GetPredmeti().AddElement(new Predmet(predmet), napomena);
        _uspjeh.push_back(u);
        float prosjekRazreda = GetProsjekRazreda(razred);
        float prosjehSkolovanja = u.ProsjekSvihPredmeta();
        thread t1(&Kandidat::SaljiMail, this, razred, prosjekRazreda, prosjehSkolovanja);
        t1.join();
        return true;
    }

    Kolekcija<Predmet, float> operator()(Datum* prvi, Datum* drugi) {
        Kolekcija<Predmet, float> temp;
        for (int i = 0; i < _uspjeh.size(); i++)
        {
            for (int j = 0; j < _uspjeh[i].GetPredmeti().getTrenutno(); j++)
            {
                for (int k = 0; k < _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getTrenutno(); k++)
                {
                    auto element = _uspjeh[i].GetPredmeti().getElement1(j)->GetOcjene().getElement1(k);
                    if (element > prvi && drugi > element)
                    {
                        temp.AddElement(*_uspjeh[i].GetPredmeti().getElement1(j), _uspjeh[i].GetPredmeti().getElement1(j)->ProsjekDatuma());
                    }
                }
            }
        }
        return temp;
    }

    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }
};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite ulogu i nacin koristenja generickog tipa future<>?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Ukratko opisite na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    cout << PORUKA;
    cin.get();
    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum
        datum19062021(19, 6, 2021),
        datum20062021(20, 6, 2021),
        datum30062021(30, 6, 2021),
        datum05072021(5, 7, 2021);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    //parametri: nazivPredmeta, datum, prva ocjena
    Predmet Matematika("Matematika", datum19062021, 5),
        Fizika("Fizika", datum20062021, 5),
        Hemija("Hemija", datum30062021, 2),
        Engleski("Engleski", datum05072021, 5);

    Matematika.AddOcjena(datum05072021, 3);
    Matematika.AddOcjena(datum05072021, 3);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti jednaka 0
    cout << Matematika << endl;


    /*
    broj telefona mora biti u formatu
    - znak +
    - pozivni broj drzave (2 ili 3 cifre)
    - pozivni broj operatera (2 cifre) npr. 063, 061, 065 pri cemu je broj 0 opcionalan
    - prvi dio broja (2 ili 3 cifre)
    - razmak ili crtica, oboje opcionalno tj. broj telefona ne mora sadrzavati niti jedno niti drugo
     - drugi dio broja (2 ili 3 cifre)
    ukoliko broj telefona nije u validnom formatu, njegova vrijednost se postavlja na NOT VALID
    */

    if (ValidirajBrojTelefona("+38761222333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222-333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+38761222 333"))
        cout << "Broj telefona validan" << crt;
    if (ValidirajBrojTelefona("+387061222 333"))
        cout << "Broj telefona validan" << crt;
    if (!ValidirajBrojTelefona("+38761 222 333"))
        cout << "Broj NIJE telefona validan" << crt;
    if (!ValidirajBrojTelefona("+387 61222 333"))
        cout << "Broj NIJE telefona validan" << crt;


    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "+38761222333");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "+387061222 333");
    Kandidat brojTelefonaNotValid("Ime Prezime", "korisnik@klix.ba", "+387 61222 333");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova tipa Predmet) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Metoda vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!" << crt;
    //Matematiku je vec dodana u prvom razredu
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.
    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu". Slanje SMS-a izvrsiti samo u slucaju da je broj telefona validna, u protivnom ispisati poruku „BROJ TELEFONA NIJE VALIDAN“
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(new Datum(18, 06, 2021), new  Datum(21, 06, 2021));
    cout << jasminUspjeh << crt;

    cin.get();
    system("pause>0");
}
