NAUDOJIMOSI INSTRUKCIJA:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Ačiū, kad parsisiuntėte šią programą! Deja, nesu baisiai protingas, todėl ir rašau naudojimosi instrukciją, kadangi paleidimas nėra vien paprasto .exe failo paspaudimas.

Pradedant nuo pradžių, turite turėti veikiantį GCC, kurio versija palaiko C++17 ar naujesnes versijas.
Antra, turite turėti veikiantį MinGW, kuris reikalingas programos .exe failo sukūrimui, kuriam reikia mingw32-make komandos. Tam pridedu šią nuorodą: https://nerdyelectronics.com/install-mingw-on-windows-for-make/

---------------------------------------------------------------------
Reikalingos komandos:

mingw32-make vector - sukuria .exe versijai su vektoriaus tipo konteineriu

mingw32-make class  - sukuria .exe versijai su deque tipo konteineriu, bet naudojant klasę.

mingw32-make list   - sukuria .exe versijai su list tipo konteineriu

mingw32-make clean  - ištrina bin failą, kuriame laikomi sukurti jūsų .exe failai bei sugeneruoti duomenų failai

mingw32-make -B     - rebuildina visų konteinerių tipų .exe failus

--------------------------------------------------------------------------------

Parsisiuntę repo, turite du variantus:

Visual Studio
-
  Atsidaryti .sln failą, kuris atidarys visą projektą per Visual Studio, per kurį galėsite atsidaryti terminalą (CTRL+~) ir suvesti atitinkamas komandas, surašytas viršuje.

CMD
-
  Atsidaryti command line, (ieškoti cmd paspaudus Windows ikoną), nuvesti path iki šitos repo direktorijos naudojant cd komandą, pvz: cd C:\Users\andri\OneDrive\Desktop\oop naujas\bin ir tada vesti atitinkamas komandas pagal Jūsų poreikį.


Tai atlikus, atsiras bin folder'is, kuriame rasite .exe failus.
Paleidus programą, visi pasirinkimai bus aiškiai jums duoti.

Gero naudojimo!

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


TESTAVIMAS
-

Kompiuterio, naudoto testavimui specifikacijos:
CPU: Ryzen 7 5800U
RAM: 32GB DDR4 3200MHz
SSD: 480GB, ne M.2



v1.1 benchmark'as (O3 optimizacija)
-

![image](https://github.com/user-attachments/assets/e2540cf4-4f2e-4a25-ae8a-bce9edebf667)
![image](https://github.com/user-attachments/assets/2e670fa6-28aa-438e-8988-ef868e04f21f)
![image](https://github.com/user-attachments/assets/d2e97aa2-9634-4f94-8cee-dae7acf24a48)
![image](https://github.com/user-attachments/assets/e3831801-1726-4993-97a2-4f9c13ace2cd)
![image](https://github.com/user-attachments/assets/dcc80e43-4d32-402a-8c6e-f9c2de081b7b)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003 | 0.02  | 0.20   | 1.62   | 14.45 |
| Rūšiavimo laikas                   | 0.0004  | 0.005 | 0.06   | 0.80 | 14.45 |
| Atskyrimo i vektorius laikas       | 0.0003 | 0.002  | 0.02   | 0.21    | 2.78  |
| Irašymo i nerdus laikas            | 0.007  |  0.02 |  0.17  |  1.72 | 18.21 |
| Irašymo i galiorką laikas          |  0.005   |  0.01  |  0.12  |  1.19   |  12.29  |
| Visas veikimo laikas               | 0.02  | 0.06  | 0.56   | 5.54   |  60.00 |


Naujienos
---------------------------------------------------------------------------------------------------------------------------------------------------------------

v1.2 buvo pritaikyta klasei penkių metodų taisyklė - t.y kopijavimo ir kėlimo konstruktoriai bei assign'eriai ir destruktorius.
Taip pat pridėti operatorių išvesties ir įvesties būdai

Ką jie daro?
-----------

![image](https://github.com/user-attachments/assets/9b79e803-85c2-45ec-a025-676f98cf623b)

Šios taisyklės pagerina optimizaciją ir tuo pat programos veikimą, tiksliai parodantys klasei, kaip ką apdoroti, kelti, kopijuoti, bei naikinti.

Su išvesties ir įvesties metodais supaprastintas įvedimas ir išvedimas ranka arba atsitiktinai generuojant, t.y - viskas, kas nesusiję su darbu su failu.
Tuose operatoriuose dabar perkelta faktiškai viskas, kas buvo kitose dalyse kodo ir susiję su rankiniu įvedimu bei išvedimu.
![image](https://github.com/user-attachments/assets/6b508693-94b0-4f46-bac2-bd61bfdcaee6)
(Šios eilutės užėmė daug vietos main.cpp faile, o dabar yra atskirai ir tvarkingai laikomos operatoriuje funkcijų .cpp faile, kur jas daug lengviau iššaukti.)

Su išvedimu tas pats - paprasčiau suprast kodą, lengviau iššaukt.

Prieš -
![image](https://github.com/user-attachments/assets/b47b977b-2fc9-4787-bf77-a89ce36ad4ad)


Po - 
![image](https://github.com/user-attachments/assets/c5c067dc-92ab-48e8-a510-27c32da5dc9e)

Dabar cout<<n ne tik paprastai išveda į ekraną n, o aktyvuoja viską, kas yra išvedimo operatoriuje -
![image](https://github.com/user-attachments/assets/2c9b8263-a832-4ef2-b1c3-833dad52847e)

