# 1.Scopul proiectului
###	Proiectul are ca scop implementarea unui modul wifi, mai exact o aplicatie pe telefon care sa controleze folosind anumite butoane efectele care sa apara pe led stripe. Cu ajutorul acestui proiect invatam cum se face conexiunea dintre o aplicatie si o placa Arduino prin modul wifi, precum si functionarea Led Stripe-urilor si multitudinilor de efecte pe care le putem crea cu ajutorul acestora.
# 2.Componentele utilizate
###	Pentru acest proiect am folosit urmatoarele:
  *	Un cablu usb pe care l-am taiat la un capat ca sa putem sa alimentam ledurile de la priza sau orice alta componenta ca de exemplu: port usb de la laptop sau o baterie externa
  *	Un ESP8266 ESP-12E CH340G NodeMCU V3 Development Board pe care l-am folosit ca sa implementam codul
  *	Fire tata tata pe care le-am desfacut ca sa putem sa legam firele de la cablul taiat de firele de la leduri pe care le-am izolat ulterior
# 3. Detalii de proiectare si implementare
*	Pentru proiectare prima oara am construit aplicatia de pe telefon unde am adaugat 8 butoane care comuta intre 8 moduri de functionare, precum si un selector de rgb sub forma de zebra de unde putem allege orice culoare dorim noi pe care sa-l putem afisa pe leduri.
*	Dup ace aplicatia noastra a fost gata, am conectat niste porturi virtuale prin intermediul aplicatiei Blynk in codul Arduino de unde am luat valorile de 0 sau 1 ale butoanelor. In momentul in care apasam pe un buton aceasta valoare de 1 va fi transmisa codului, precum si valoarea de 0 cand butonul este stins.
*	Am instalat librariile necesare de FastLed si Blynk, precum si biblioteca necesara pentru placa ESP8266. Am folosit modulul wifi incorporate pe aceasta placa pentru a putea face conexiunea la internet.
