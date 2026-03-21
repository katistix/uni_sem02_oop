#set page(paper: "a4", margin: 2cm)
#set text(font: "linux libertine", size: 11pt)

#align(center)[
  #text(weight: "bold", size: 16pt)[Lab 5 - Code Review Template]
]


#strong[Reviewer Name:] Tal Paul-Gabriel

#strong[Reviewer Group:] 217

#strong[Initial C application was created by (Name/Group):] Varga Daniel, 217

#v(1.5em)

#text(style: "italic")[Please fill in the following table using appropriate, complete data:] 

#table(
  columns: (1fr, 1.5fr),
  inset: 10pt,
  align: horizon,
  [*Review Category*], [*Details / Findings*],
  
  [List of application functionalities that are missing, are incomplete or buggy. ], 
  [- Niciuna gasita.],
  
  [List of program functions (except UI) that are not covered by tests. ], 
  [- Test coverage este de 100%.],

  [List of program functios lacking specification.], 
  [- Majoritatea functiilor nu au specificatie, exista doar comentarii in cod pentru a organiza functiile in categorii, dar nu exista specificatii pentru fiecare functie in parte.],
  
  [Is there a clear separation between each module's specification and its implementation? ], 
  [- Da, exista fisiere header pentru fiecare modul (desi nu contin specificatii pentru functii), iar implementarea este in fisierele .c.],
  
  [Is the application correctly layered? ], 
  [- Exista arhitectura stratificata corect, insa toate fisierele sunt in acelasi folder, ceea ce face ca separarea sa nu fie foarte clara.],
  
  [Does the application handle memory correctly (all memory is deallocated, no dangling pointers etc.). ], 
  [- Da, nu am gasit probleme de memorie in urma testelor manuale rulate cu valgrind.],
  
  [List those functions that are unclear to you (usually a sign of bad design). ], 
  [- Functiile sunt bine denumite, insa nu exista specificatii pentru functii.],
  
  [List the problems present in the reviewed application and indicate the number of man-hours you require for fixing them. ], 
  [
    - Aplicatia foloseste `strncpy_s`, care functioneaza doar pe windows, deci nu este portabila. Timp necesar pentru inlocuire: 30 minute.
    - Testele sunt rulate la inceputul functiei `main`, ceea ce inseamna ca daca un test esueaza, aplicatia nu va rula. Timp necesar pentru mutarea testelor intr-un fisier separat: 15 minute.
    - Build system-ul foloseste CMakeLists.txt, am inlocuit cu un Makefile mult mai simplu de inteles si portabil. Timp necesar pentru inlocuire: 20 minute.

  ]
)