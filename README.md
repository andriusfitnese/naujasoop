

Kompiuterio, naudoto testavimui specifikacijos:
CPU: Ryzen 7 5800U
RAM: 32GB DDR4 3200MHz
SSD: 480GB, ne M.2
Naudojamas paprastas vektorius studentų duomenims laikyti, o nerdai ir galiorka yra atitinkamai deque ir list.

Hipotetiškai, deque ar list vietoj paprasto vektoriaus studentų duomenims laikyti būtų negera mintis, kadangi jie naudoja daugiau atminties.
Skaitymas visiems yra O(n), o rūšiavimas - O(n log(n)), tačiau list naudoja daugiau atminties dėl daugiau rodyklių, o deque dėl fragmentuotos atminties.


Benchmarkas su iš v0.4 naudojant paprastą vektorių studentų duomenų struktūrai
![image](https://github.com/user-attachments/assets/5cd598f4-c4a4-410a-9d1b-57b20068aa87)
![image](https://github.com/user-attachments/assets/f6afb370-cbff-4f5c-ab38-3e03df35e2a4)
![image](https://github.com/user-attachments/assets/a137566b-4f88-433f-9266-bba2ecd17643)
![image](https://github.com/user-attachments/assets/b41ea4f3-1e87-4cd2-9402-bd6418eb0bdd)



| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |
|------------------------------------|-------|-------|--------|---------|
| Skaitymo laikas                    | 0.14  | 1.07  | 10.70  | 44.46  |
| Rūšiavimo laikas                   | 0.02  | 0.22  | 1.21   | 8.83   |
| Atskyrimo i vektorius laikas       | 0.01  | 0.04  | 0.04   | 3.48   |
| Visas veikimo laikas               | 0.19  | 1.58  | 14.57  | 56.77  |



Naudojant deque vietoj vector studentams: (be energy saver, su įdetu krauti kompiuteriu bei perdarytu skaitymu su buffering, kuris neturėjo tiek daug reikšmės (iki 10%) kaip battery saver išjungimas...)

![image](https://github.com/user-attachments/assets/0fe07ecc-b20a-4e7e-87f2-36e5a9240c0e)
![image](https://github.com/user-attachments/assets/c914ddb3-7807-496d-9470-6983b5ede27d)
![image](https://github.com/user-attachments/assets/1fe18547-666e-4e97-86b8-949ffd72b07a)
![image](https://github.com/user-attachments/assets/a6ca4d46-c6e6-4846-9adc-924da7aa2541)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.04  | 0.37  | 3.96   | 40.53   | 334.27 |
| Rūšiavimo laikas                   | 0.01  | 0.08  | 0.95   | 11.68   | 169.38 |
| Atskyrimo i vektorius laikas       | 0.003 | 0.03  | 0.35   | 4.48    | 280.20 |
| Visas veikimo laikas               | 0.05  | 0.48  | 5.26   | 56.68   | 783.85 |


Naudojant list studentų duomenims laikyt (taipogi be energy saver)

Kad veiktų list, teko apkeisti rikiavimo algoritmą, kadangi list naudoja tiktais dvikrypčius iteratorius, ne kaip vector, deque ar array, kurie turi laisvosios prieigos iteratorius.

Tad, pavyzdžiui, norint rikiuot pagal vardą didėjimo tvarka, sort(grupe.begin(), grupe.end(), sortVardu); tapo grupe.sort(sortVardu);
Reiktų pastebėti skirtumus, kurie pasireiškia čia - su list, skaitymas vyksta ilgiau, palyginus su vector ar deque, tačiau rikiavimas yra žaibiškai greitas. Taip pat sunaudojama daugiau atminties, 1.5GB ant 1000000 įrašų palyginus su 900MB darant su deque.
![image](https://github.com/user-attachments/assets/093cb654-ac98-4168-8c9e-0fc9d0d699e8)
![image](https://github.com/user-attachments/assets/9d45a0fa-ba2c-4836-888e-a6c89ffdcf9f)
![image](https://github.com/user-attachments/assets/6de021cc-6bc3-42a3-a7ea-a9c94bc406dc)
![image](https://github.com/user-attachments/assets/e3f7f0c7-da0e-47ba-90b7-f45b254be181)

| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.07  | 0.59  | 5.03   | 53.00   | >6min |
| Rūšiavimo laikas                   | 0.0003  | 0.004 | 0.05   | 0.92 | ~15s |
| Atskyrimo i vektorius laikas       | 0.003 | 0.03  | 0.32   | 4.29    | >5min  |
| Visas veikimo laikas               | 0.07  | 0.62  | 5.40   | 58.22   |  ~11min |



STRATEGIJŲ ANALIZĖ
Nuo dabar vykdymo laikai gali būti daug trumpesni, kadangi naudojama sukompiliuotos programos, su .exe failais.
1 Strategija - minimaliai pakeista nuo v0.4, šiek tiek optimizuotos dalys skaitymo bei rūšiavimo v1.0 dev metu.

SU VECTOR

![image](https://github.com/user-attachments/assets/5b8189e9-b568-4e35-b90b-27d1a6a67b29)
![image](https://github.com/user-attachments/assets/7ff28522-7b56-4b38-a747-7da523573cf6)
![image](https://github.com/user-attachments/assets/ef3a9b33-300f-42ef-a5dc-b162d25994ad)
![image](https://github.com/user-attachments/assets/8342d488-783f-46f7-a08c-99d85e674387)
![image](https://github.com/user-attachments/assets/acacb69b-e780-4a63-bbfb-a4b421b8de5c)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |


SU DEQUE

![image](https://github.com/user-attachments/assets/74bd2719-6859-4a25-9bfe-ac87e10251ce)
![image](https://github.com/user-attachments/assets/3c19fa0e-36bb-4de4-9816-223b1c33b85a)
![image](https://github.com/user-attachments/assets/94957b03-4406-4a6b-8d50-e3b787a07297)
![image](https://github.com/user-attachments/assets/9892dd2d-43f9-43f4-a71f-2e7178f7b349)
![image](https://github.com/user-attachments/assets/64a62a23-a271-41eb-9b4a-91f4ec6e4d2b)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |


SU LIST

![image](https://github.com/user-attachments/assets/e1878e5f-7c01-439f-ace9-7377908fbe8a)
![image](https://github.com/user-attachments/assets/bde2f41d-4c75-4320-92e1-845c6a3f9d51)
![image](https://github.com/user-attachments/assets/1f410158-0952-4b29-997d-a480c8d196da)
![image](https://github.com/user-attachments/assets/2c118cbd-3e39-403e-a0a2-584ee4eaae71)
![image](https://github.com/user-attachments/assets/d7d11035-fb02-4515-8d74-c1a324a3dab2)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |

Matome, kad list sunkiai tempiasi ypač su dideliais duomenų kiekiais.



STRATEGIJA 2

SU VECTOR

![image](https://github.com/user-attachments/assets/1ffdfdb4-5ed8-4e36-a73c-2ac7107d996f)
![image](https://github.com/user-attachments/assets/bddeeda1-e03a-4437-a1f6-96478ebb0850)
![image](https://github.com/user-attachments/assets/d15e2524-99e8-4851-86aa-5fc5a71918c7)
![image](https://github.com/user-attachments/assets/94e882bf-fdd2-4db7-b581-bd82a325d81a)
![image](https://github.com/user-attachments/assets/127b8c6d-4c7e-4011-a777-aea8bf5c5d3e)

| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |

SU DEQUE
![image](https://github.com/user-attachments/assets/28ba876e-cfec-4b51-919a-d30cc97aa59f)
![image](https://github.com/user-attachments/assets/c0b95346-fe75-4b75-bb74-18b45f9b19ca)
![image](https://github.com/user-attachments/assets/cc9bb7d7-8f61-4bb6-b53a-7b9a17bac422)
![image](https://github.com/user-attachments/assets/7a73de78-d77e-4ceb-94ae-a4da5768f8c1)
![image](https://github.com/user-attachments/assets/b7e190e0-20a6-4124-8f63-0c5bf21ba378)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |

SU LIST
![image](https://github.com/user-attachments/assets/fb1e5b79-bd4d-40a9-a78c-2b3357d901e2)
![image](https://github.com/user-attachments/assets/81d39738-228c-4f95-8f2e-d19a5345664e)
![image](https://github.com/user-attachments/assets/72d377d5-bbb9-450d-8cb3-7d882d1beeaa)
![image](https://github.com/user-attachments/assets/27ccd5f7-e8cb-436b-9578-2d5f67c8b10b)
![image](https://github.com/user-attachments/assets/ce9524d7-769d-4296-b28a-42169b6e4fb6)


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |



STRATEGIJA 3

SU VECTOR


| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |

SU DEQUE

| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |

SU LIST

| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |10000000|
|------------------------------------|-------|-------|--------|---------|--------|
| Skaitymo laikas                    | 0.003  | 0.02  | 0.23   | 1.11   | 8.90 |
| Rūšiavimo laikas                   | 0.0001  | 0.002 | 0.01   | 0.17 | 10.09 |
| Atskyrimo i vektorius laikas       | 0.0004 | 0.003  | 0.04   | 0.56    | 9.78  |
| Irašymo i nerdus laikas            |        |        |        |        |       |
| Irašymo i galiorką laikas          |        |        |        |        |       |
| Visas veikimo laikas               | 0.004  | 0.03  | 0.29   | 1.84   |  28.77 |
