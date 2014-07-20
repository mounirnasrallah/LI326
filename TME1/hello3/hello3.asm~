
;; Adresse 0, instructions qui sont executés après un reset.
ORG 0
	call initialisation
	goto main


;; Adresse 4, instructions à executer en cas d'interruption, qui équivaut à un return.
ORG 4
	retfie

	
list    p=16f877        	; definit le processeur cible
include "p16f877.inc" ; declaration des noms de registres


initialisation
	
;;  Definition du registre de configuration du pic
;;  _CP_OFF   : le code n'est pas protege et peut être relu
;;  _WDT_OFF  : pas de timer watch dog
;;  _PWRTE_ON : attente d'un délai de 72ms apres le power on
;;  _HS_OSC   : le pic utilise un oscillateur à quartz
;;  _LVP_OFF  : pas de mode programmation basse tension

__CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _HS_OSC & _LVP_OFF
	
	
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

	return
main
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