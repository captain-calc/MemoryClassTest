all: production

devel:
	$(MAKE) -C program debug

production:
	$(MAKE) -C program
