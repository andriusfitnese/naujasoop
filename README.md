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
Naudojamas paprastas vektorius studentų duomenims laikyti, o nerdai ir galiorka yra atitinkamai deque ir list.

Hipotetiškai, perėjus prie klasių turėtų būt pagerėjęs vykdymo laikas, tačiau su mano įgudžiais visko gali būt.


Benchmarkas su iš v1.0 naudojant deque su struktūra konteinerį ir 3 strategiją (O3 optimizacija)
-

![image](https://github.com/user-attachments/assets/c3ae1b2c-2dc0-4f00-b59b-bb3987cb1519)
![image](https://github.com/user-attachments/assets/a8c17aee-a13b-4611-a72c-1b37a0680032)
![image](https://github.com/user-attachments/assets/5aacfb15-872e-43c2-834f-f18d8a325354)
![image](https://github.com/user-attachments/assets/962816c0-c009-40f2-85af-1a859d85308e)
![image](https://github.com/user-attachments/assets/93356782-bf7e-47f8-bf07-b38d80342bde)



| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003 | 0.04  | 0.21   | 1.41   | 11.89 |
| Rūšiavimo laikas                   | 0.0003  | 0.002 | 0.02   | 0.30 | 3.62 |
| Atskyrimo i vektorius laikas       | 0.0003 | 0.001  | 0.02   | 0.28    | 2.97  |
| Irašymo i nerdus laikas            | 0.04  |  0.03 |  0.22  |  3.03 | 31.71 |
| Irašymo i galiorką laikas          |  0.02   |  0.01  |  0.12  |  1.81   |  21.29  |
| Visas veikimo laikas               | 0.06  | 0.08  | 0.58   | 6.82   |  72.49 |



Naudojant ta pačia strategiją, konteinerį su klase vietoj studentų struktūros: (O3 optimizacija)
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

Matome smarkiai pagerėjusį atskyrimo į vektorius laiką bei įrašymo į failą laiką, bet nepakitusį/padidėjusį skaitymo ir rūšiavimo laiką.



OPTIMIZACIJOS LYGIŲ ANALIZĖ
--------------------------------------------------------------------------------------------------------------------------------------------------------
Žinome, kad naudojant Makefile yra 3 variantai pasirinkti optimizacijos lygį, pagal kurį priklauso programos executable veikimo greitis bei pačio .exe kūrimo greitis. Tad padariau lenteles išbandyt, kokį skirtumą turi šie optimizacijos lygiai.


O1
-

![image](https://github.com/user-attachments/assets/e8ac859e-f933-40f1-bc2f-51fc7ea7ce05)
![image](https://github.com/user-attachments/assets/25021a3f-2a74-4f05-a571-097e3fd0d59c)
![image](https://github.com/user-attachments/assets/08756782-c549-49cc-a295-c52b8c7d1182)
![image](https://github.com/user-attachments/assets/ee44f5ca-2707-40c3-80eb-37e8e8ceaa89)
![image](https://github.com/user-attachments/assets/7537b3d7-22f5-449e-943e-936ebb774294)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.004 | 0.04  | 0.20   | 1.81   | 12.48 |
| Rūšiavimo laikas                   | 0.0004  | 0.005 | 0.06   | 0.85 | 14.91 |
| Atskyrimo i vektorius laikas       | 0.0003 | 0.003  | 0.02   | 0.24    | 3.28  |
| Irašymo i nerdus laikas            | 0.003  |  0.02 |  0.17  |  1.75 | 19.69 |
| Irašymo i galiorką laikas          |  0.002   |  0.01  |  0.12  |  1.18   |  13.42  |
| Visas veikimo laikas               | 0.01  | 0.08  | 0.58   | 5.83   |  63.77 |

O2
-

![image](https://github.com/user-attachments/assets/b22bd4aa-1c45-4359-ad6e-faec9a0a928a)
![image](https://github.com/user-attachments/assets/a758f2ea-4712-4822-b704-c358ebf4719c)
![image](https://github.com/user-attachments/assets/936844ab-a665-446e-aeb5-2ddcd90e8b1a)
![image](https://github.com/user-attachments/assets/ddbc1369-1960-42c9-8c13-0001abd193d8)
![image](https://github.com/user-attachments/assets/a9c27763-d5f8-450a-97d6-709bcc22383f)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.02 | 0.04  | 0.22   | 1.72   | 12.39 |
| Rūšiavimo laikas                   | 0.0005  | 0.005 | 0.07   | 0.84 | 14.92 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.02   | 0.21    | 2.79  |
| Irašymo i nerdus laikas            | 0.03 |  0.02 |  0.17  |  1.71 | 17.73 |
| Irašymo i galiorką laikas          |  0.02   |  0.01  |  0.12  |  1.22   |  12.72  |
| Visas veikimo laikas               | 0.07  | 0.08  | 0.59   | 5.69   |  60.56 |


O3
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


Matome, kad skirtumai nėra žymūs, tiktais make trunka ilgiau kurti executable failus kylant optimizacijos lygiui.
