#set page(paper: "a4", margin: 2cm)
#set text(font: "linux libertine", size: 11pt)

#align(center)[
  #text(weight: "bold", size: 16pt)[Lab 5 - Code Review Template]
]


#strong[Reviewer Name:]

#strong[Reviewer Group:]

#strong[Initial C application was created by (Name/Group):]

#v(1.5em)

#text(style: "italic")[Please fill in the following table using appropriate, complete data:] 

#table(
  columns: (1fr, 1.5fr),
  inset: 10pt,
  align: horizon,
  [*Review Category*], [*Details / Findings*],
  
  [List of application functionalities that are missing, are incomplete or buggy. ], 
  [],
  
  [List of program functions (except UI) that are not covered by tests. ], 
  [],

  [List of program functios lacking specification.], 
  [],
  
  [Is there a clear separation between each module's specification and its implementation? ], 
  [#v(3em)],
  
  [Is the application correctly layered? ], 
  [#v(3em)],
  
  [Does the application handle memory correctly (all memory is deallocated, no dangling pointers etc.). ], 
  [#v(3em)],
  
  [List those functions that are unclear to you (usually a sign of bad design). ], 
  [],
  
  [List the problems present in the reviewed application and indicate the number of man-hours you require for fixing them. ], 
  []
)