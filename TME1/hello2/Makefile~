F=hello1


.PHONY: a s c


a:
	gpasm -pp16f877 $(F).asm

s:a
	gpsim -pp16f877 -s$(F).cod

c:
	rm *.cod *.hex *.lst 2> /dev/null || true