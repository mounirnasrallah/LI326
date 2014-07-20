
;; On définit STATUS qui contient l'adresse du
;; registre STATUS.
STATUS		EQU  H'0003'
	
;; On définit RP0 et RP1 qui contiennent l'adresse des
;; RP0 et RP1 du registre STATUS.
RP0		EQU  H'0005'
RP1		EQU  H'0006'

;; On met les bits RP0 et RP1 du registre STATUS à 1 et 0.
;; afin de séléctionner le banc de registre BANK1 où se trouve
;; le registre TRISD.
	bcf STATUS,RP1
	bsf STATUS,RP0

;; On définit TRISD qui contient l'adresse du registre TRISD
TRISD		EQU H'0088'

;; On met le port D en sortie ( tout les bits du registre TRISD à 0 )
	clrf TRISD
	
;; On met les bits RP0 et RP1 du registre STATUS à 0 afin
;; de séléctionner le banc de registre BANK0
	bcf STATUS,RP1
	bcf STATUS,RP0

;; On définit PORTD qui contient l'adresse du registre PORTD
PORTD		EQU  H'0008'
	
;; On met la valeur B'0000 0001' dans le registre W
	movlw 1

;; On met maintenant la valeur du registre W sur le port D
	movwf PORTD

boucle
;; On éffectue une rotation droite sur le PORTD
	rrf PORTD,f

;; On boucle en retournant à l'adresse de l'étiquette "boucle"
	goto boucle

;; Directive de fin de programme
	END		