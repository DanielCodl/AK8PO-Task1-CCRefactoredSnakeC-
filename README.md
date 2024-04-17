# AK8PO-Task1-CCRefactoredSnakeC-
Průběžný úkol 1: Legacy kód Snake refaktorovaný podle pravidel čistého kódu pro předmět "Pokročilé programování" (ak. rok 2023/24, LS, UTB, Informační Technologie, Kyber. bezpečnost).

URL původního kódu:
https://codereview.stackexchange.com/questions/127515/first-c-program-snake-game

Cíl:
Refaktoring dle pravidel čistého kódu by měl zahrnovat vylepšení pojmenování proměnných, strukturování kódu do menších metod, používání správných datových typů a zapouzdření souvisejících funkcí do tříd.

Provedené změny:
- Organizace kódu: Program byl rozdělen do tříd a metod, které zapouzdřují související funkcionalitu.
- Čitelnost: Úprava názvů proměnných a použití konstant tam, kde je to vhodné.
- Udržitelnost: Oddělení herní logiky od vstupů a vykreslovacích rutin (GUI), což umožňuje nezávislé úpravy jednotlivých částí kódu.
- Výkon: Snížena frekvence používání rutiny Console.Clear(), a to tím, že se spustí jen tam, kde je to nutné. Pro nastavení rychlosti hry se použije rutina Thread.Sleep().

