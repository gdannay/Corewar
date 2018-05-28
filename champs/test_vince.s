.name "Vincent"
.comment "Cor"

entree:
        live %1
        and %1, %2, r5
        sti r5, %5, %5


entre:

live %1
#entree:
        #bonjour

  live %1   #salut :entree live :entree
      sti r5, %5, %:entree
      st r5, 5
live %:
