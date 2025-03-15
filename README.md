

Kompiuterio, naudoto testavimui specifikacijos:
CPU: Ryzen 7 5800U
RAM: 32GB DDR4 3200MHz
SSD: 480GB, ne M.2
Naudojamas paprastas vektorius studentų duomenims laikyti, o nerdai ir galiorka yra atitinkamai deque ir list.

Hipotetiškai, deque ar list vietoj paprasto vektoriaus studentų duomenims laikyti būtų negera mintis, kadangi jie naudoja daugiau atminties.
Skaitymas visiems yra O(n), o rūšiavimas - O(n log(n)), tačiau list naudoja daugiau atminties dėl daugiau rodyklių, o deque dėl fragmentuotos atminties.

Benchmarkas su iš v0.4 naudojant paprastą vektorių studentų duomenų struktūrai (Reiktų paminėt, kad šiuos testus vykdžiau ant gan lėto kompiuterio ir ant energy saving rėžimo, tai nors ir naudojami buffers ir async vietomis, vykdymas vis tiek gan lėtas.) - 
![image](https://github.com/user-attachments/assets/26fe63ca-9f13-4c7a-bca2-7f6b4fbb439d)
![image](https://github.com/user-attachments/assets/c25dac96-640a-4333-adea-6382a7cd63d7)
![image](https://github.com/user-attachments/assets/7acdc519-32a7-4976-8710-f07c7eede184)
![image](https://github.com/user-attachments/assets/0976d3ab-76b0-4c23-a013-a7b507c1cd60)

| Studentų kiekis                    | 1000  | 10000 | 100000 | 1000000 |
|------------------------------------|-------|-------|--------|---------|
| Skaitymo laikas                    | 0.14  | 1.07  | 10.70  | 127.38  |
| Rūšiavimo laikas                   | 0.02  | 0.22  | 1.21   | 16.33   |
| Atskyrimo i vektorius laikas       | 0.01  | 0.04  | 0.04   | 6.94    |
| Nerdų surašymo laikas              | 0.01  | 0.15  | 1.35   | 14.84   |
| Galiorkos surašymo laikas          | 0.01  | 0.10  | 0.94   | 10.52   |
| Visas veikimo laikas               | 0.19  | 1.58  | 14.57  | 176     |



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
