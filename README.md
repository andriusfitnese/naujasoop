

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
| Skaitymo laikas                    | 0.04  | 0.37  | 3.96   | 40.53   | 334.27 |
| Rūšiavimo laikas                   | 0.01  | 0.08  | 0.95   | 11.68   | 169.38 |
| Atskyrimo i vektorius laikas       | 0.003 | 0.03  | 0.35   | 4.48    | 280.20 |
| Visas veikimo laikas               | 0.05  | 0.48  | 5.26   | 56.68   | 783.85 |




