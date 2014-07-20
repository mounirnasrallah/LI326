; ------------------------------------------------------------------------
; programme : hello4
; Date      : 20050108:2328
; Version   : 1
; Auteurs   : franck
; Notes     : suppose que l'horloge externe est à 20MHz
; toujours le chenillard mais avec une routine de délai qui ralentit le
; décalage du portd, l'attente est de 200 microsecondes.
; ------------------------------------------------------------------------
 
        list    p=16f877        ; definit le processeur cible
        include "p16f877.inc"   ; declaration des noms de registres
 
        ; Definition du registre de configuration du PIC
        ; _CP_OFF   : le code n'est pas protege et peut etre relu
        ; _WDT_OFF  : pas de timer watch dog
        ; _PWRTE_ON : attente d'un délai apres le power on
        ; _HS_OSC   : oscillateur à quartz
        ; _LVP_OFF  : pas de mode programmation basse tension
        __CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _HS_OSC & _LVP_OFF
 
        CBLOCK  0x20            ; première adresse de la zone
           wait200us_arg : 1    ; 1 octet de nom wait200us_arg
        ENDC
 
        org     0               ; adresse du reset
        call    initialisation
        goto    main
 
        org     4               ; adresse du vecteur d'interruption
        retfie                  ; par défaut ne rien faire
 
initialisation
        BANKSEL TRISD           ; aller dans le banc de registres TRSID
        clrf    TRISD           ; place tous les signaux du port D en sortie
        BANKSEL PORTD           ; revenir dans le banc de registres PORTD
        return
 
main    movlw   1               ; met 0x01  sur port D
        movwf   PORTD
loop    rrf     PORTD,f
        call    wait200us
        goto    loop            ; on boucle sur la rotation
 
wait200us ; routine d'attente active
        movlw   d'XXX'          ; XXX -> W                ? cycle
        movwf   wait200us_arg   ; W -> wait200us_arg      ? cycle
        goto    $+1             ; nop2                    ? cycles
        decfsz  wait200us_arg,f ; wait200us_arg--         ? cycle si faux sinon ?
        goto    $-2             ; goto adr courante -2    ? cycles
        return                  ;                         ? cycles
; ------------------------------------------------------------------------------
        END                     ; directive terminant un programme
