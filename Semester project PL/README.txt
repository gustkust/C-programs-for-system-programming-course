
W skład projektu wchodzą dwa pliki:
inf145215_s.c - plik serwera
inf145215_k.c - plik klienta

Kompilacja poprzez komendy:
gcc -Wall inf145215_s.c -o server
gcc -Wall inf145215_k.c -o client

Uruchomienie w osobnych oknach terminala (jednym dla serwera i po jednym dla klientów):
./server
./client

Przed następnymi uruchomieniami programów warto usunąć kolejki ipc; komenda:
-ipcrm -a